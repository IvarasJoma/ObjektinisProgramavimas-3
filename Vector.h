/**
 * @file Vector.h
 * @brief Dinaminio masyvo šabloninė klasė, analogiška `std::vector`.
 *
 * Šiame faile apibrėžta `Vector<T, Allocator>` klasė — pilnavertis dinaminis
 * masyvas, suderinamas su C++20/23 standartais. Palaikomi:
 * - pilnas iteratorių rinkinys (tiesioginiai ir atvirkštiniai),
 * - `emplace_back`, `insert`, `erase` su stipria išimčių garantija,
 * - C++20 trijų krypčių palyginimo operatorius (`<=>`),
 * - C++23 operacijos `append_range`, `assign_range`, `insert_range`,
 * - pasirinktiniai atminties valdytojai per `Allocator` šablono parametrą,
 * - `[[nodiscard]]` ant `emplace_back` (C++23),
 * - trivialių tipų optimizacijos (`memcpy`/`memmove`) per `<type_traits>`,
 * - `shift_right` naudoja priskyrimo operatorių inicializuotoje srityje
 *   ir `std::move_if_noexcept` neinicializuotoje srityje,
 * - `grow` išsaugo tikslų dydį kai `min_capacity > 2 * capacity()`,
 * - `max_size()` apima ir `difference_type` ribą rodyklių aritmetikai,
 * - šakų prognozavimo užuominos (`[[likely]]`/`[[unlikely]]`) karštuosiuose
 *   keliuose (`push_back`, `emplace_back`).
 *
 * @tparam T         Elementų tipas; turi tenkinti `VectorElement` sąvoką.
 * @tparam Allocator Atminties valdytojo tipas. Numatytasis — `std::allocator<T>`.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <compare>
#include <concepts>
#include <cstring>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <span>
#include <stdexcept>
#include <type_traits>
#include <vector>

/**
 * @brief Sąvoka, reikalaujanti, kad tipas `T` būtų perkeliamas (`std::movable`).
 *
 * Tik tokie tipai gali būti `Vector` elementais.
 *
 * @tparam T Tikrinamas tipas.
 */
template <typename T>
concept VectorElement = std::movable<T>;

/**
 * @brief Dinaminio masyvo šabloninė klasė.
 *
 * Saugo elementus nuosekliame atminties bloke. Kai laisvos vietos nebelieka,
 * masyvas automatiškai išplečiamas į naują bloką pagal augimo strategiją:
// nauja talpa = `max(3 * capacity(), 1)`, tačiau jei
// `needed > 3 * capacity()` — naudojamas tikslus `needed`,
 * taip vengiant perteklinės atminties eikvojimo didesnių įterpimų metu.
 *
 * ### Optimizacijos
 * - **Trivialių tipų optimizacijos**: `resize`, `reallocate`, `shift_right`,
 *   `erase` naudoja `memcpy`/`memmove` kai `T` yra trivialiai kopijuojamas.
 * - **Trivialiai sunaikinami tipai**: destruktorių ciklai praleidiami.
 * - **Šakų prognozavimas**: `[[likely]]`/`[[unlikely]]` karštuosiuose keliuose.
 * - **`shift_right`**: inicializuotoje srityje naudoja priskyrimo operatorių
 *   (ne konstruktorių), neinicializuotoje — `std::move_if_noexcept`.
 * - **`resize(n)`**: vieno argumento versija nereikalauja `T` kopijavimo.
 *
 * @tparam T         Elementų tipas; turi tenkinti @ref VectorElement sąvoką.
 * @tparam Allocator Atminties valdytojo tipas. Turi tenkinti C++ Allocator
 *                   reikalavimus. Numatytasis — `std::allocator<T>`. Leidžia
 *                   naudoti pool ar arena allocatorius našumui gerinti.
 */
template <VectorElement T, typename Allocator = std::allocator<T>>
class Vector {
public:
    // ── Tipų sinonimai ────────────────────────────────────────────────────────

    /** @brief Elementų tipas. */
    using value_type             = T;
    /** @brief Atminties valdytojo tipas. */
    using allocator_type         = Allocator;
    /** @brief `allocator_traits` sinoniminė deklaracija patogumui. */
    using alloc_traits           = std::allocator_traits<Allocator>;
    /** @brief Dydžiui skirtas tipas be ženklo. */
    using size_type              = std::size_t;
    /** @brief Atstumui tarp elementų skirtas tipas su ženklu. */
    using difference_type        = std::ptrdiff_t;
    /** @brief Elemento nuorodos tipas. */
    using reference              = T&;
    /** @brief Konstantinės elemento nuorodos tipas. */
    using const_reference        = const T&;
    /** @brief Rodyklės tipas (iš allocator_traits). */
    using pointer                = typename alloc_traits::pointer;
    /** @brief Konstantinės rodyklės tipas (iš allocator_traits). */
    using const_pointer          = typename alloc_traits::const_pointer;
    /** @brief Tiesioginio iteratoriaus tipas. */
    using iterator               = T*;
    /** @brief Konstantinio tiesioginio iteratoriaus tipas. */
    using const_iterator         = const T*;
    /** @brief Atvirkštinio iteratoriaus tipas. */
    using reverse_iterator       = std::reverse_iterator<iterator>;
    /** @brief Konstantinio atvirkštinio iteratoriaus tipas. */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // ── Konstruktoriai ────────────────────────────────────────────────────────

    /**
     * @brief Numatytasis konstruktorius. Sukuria tuščią masyvą.
     */
    Vector() noexcept(noexcept(Allocator())) : alloc() { create(); }

    /**
     * @brief Konstruktorius su allocatoriumi. Sukuria tuščią masyvą.
     *
     * @param a Naudojamas atminties valdytojas.
     */
    explicit Vector(const Allocator& a) noexcept : alloc(a) { create(); }

    /**
     * @brief Konstruktorius su pradiniu dydžiu (numatytoji inicializacija).
     *
     * Nereikalauja `T` kopijavimo — naudoja tik numatytąjį konstruktorių.
     * Tinkamas perkeliamoms tik tipo klasėms.
     *
     * @param n  Pradinių elementų skaičius.
     * @param a  Naudojamas atminties valdytojas.
     */
    explicit Vector(size_type n, const Allocator& a = Allocator())
        : alloc(a) { create_default(n); }

    /**
     * @brief Konstruktorius su pradiniu dydžiu ir reikšme.
     *
     * @param n    Pradinių elementų skaičius.
     * @param val  Pradinė visų elementų reikšmė.
     * @param a    Naudojamas atminties valdytojas.
     */
    Vector(size_type n, const T& val, const Allocator& a = Allocator())
        : alloc(a) { create(n, val); }

    /**
     * @brief Kopijavimo konstruktorius.
     *
     * Sukuria gilią kopiją kito `Vector` objekto. Allocatorius parenkamas
     * per `allocator_traits::select_on_container_copy_construction`.
     *
     * @param other Kopijuojamas objektas.
     */
    Vector(const Vector& other)
        : alloc(alloc_traits::select_on_container_copy_construction(other.alloc))
    { create(other.begin(), other.end()); }

    /**
     * @brief Kopijavimo konstruktorius su nurodytu allocatoriumi.
     *
     * @param other Kopijuojamas objektas.
     * @param a     Naudojamas atminties valdytojas.
     */
    Vector(const Vector& other, const Allocator& a)
        : alloc(a) { create(other.begin(), other.end()); }

    /**
     * @brief Perkėlimo konstruktorius.
     *
     * Perimamas `other` turinys ir allocatorius; po operacijos `other` tampa tuščias.
     *
     * @param other Perkeliamas objektas.
     */
    Vector(Vector&& other) noexcept
        : dat(other.dat), avail(other.avail), limit(other.limit),
          alloc(std::move(other.alloc))
    { other.dat = other.avail = other.limit = nullptr; }

    /**
     * @brief Perkėlimo konstruktorius su nurodytu allocatoriumi.
     *
     * Jei allocatoriai visada lygūs (`is_always_equal`) arba lyg šiuo atveju —
     * perima turinį be kopijų. Jei skiriasi — perkelia elementus po vieną
     * naudojant move konstruktorius (ne kopiją).
     *
     * @param other Perkeliamas objektas.
     * @param a     Naudojamas atminties valdytojas.
     */
    Vector(Vector&& other, const Allocator& a) : alloc(a) {
        if constexpr (alloc_traits::is_always_equal::value) {
            steal(other);
        } else if (a == other.alloc) {
            steal(other);
        } else {
            // Skirtingi allocatoriai — perkelti elementus (ne kopijuoti)
            create(std::make_move_iterator(other.begin()),
                   std::make_move_iterator(other.end()));
        }
    }

    /**
     * @brief Konstruktorius iš iteratorių diapazono.
     *
     * @tparam InputIt Įvesties iteratoriaus tipas.
     * @param first  Diapazono pradžia.
     * @param last   Diapazono pabaiga (neįskaičiuojama).
     * @param a      Naudojamas atminties valdytojas.
     */
    template <std::input_iterator InputIt>
    Vector(InputIt first, InputIt last, const Allocator& a = Allocator())
        : alloc(a) { create(first, last); }

    /**
     * @brief Konstruktorius iš inicializavimo sąrašo.
     *
     * @param il Inicializavimo sąrašas, pvz., `{1, 2, 3}`.
     * @param a  Naudojamas atminties valdytojas.
     */
    Vector(std::initializer_list<T> il, const Allocator& a = Allocator())
        : alloc(a) { create(il.begin(), il.end()); }

    /**
     * @brief Destruktorius. Sunaikina visus elementus ir atlaisvina atmintį.
     */
    ~Vector() { uncreate(); }

    // ── Priskyrimo operatoriai ────────────────────────────────────────────────

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     *
     * Atlieka gilią kopiją. Apsaugo nuo savęs priskyrimo.
     * Jei `propagate_on_container_copy_assignment` — kopijuoja allocatorių.
     *
     * @param other  Kopijuojamas objektas.
     * @return Nuoroda į šį objektą.
     */
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            if constexpr (alloc_traits::propagate_on_container_copy_assignment::value) {
                if (alloc != other.alloc) {
                    uncreate();
                    alloc = other.alloc;
                }
            }
            uncreate();
            create(other.begin(), other.end());
        }
        return *this;
    }

    /**
     * @brief Perkėlimo priskyrimo operatorius.
     *
     * Perimamas `other` turinys; po operacijos `other` tampa tuščias.
     * Jei `propagate_on_container_move_assignment` — perima allocatorių.
     *
     * @param other  Perkeliamas objektas.
     * @return Nuoroda į šį objektą.
     */
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            uncreate();
            if constexpr (alloc_traits::propagate_on_container_move_assignment::value)
                alloc = std::move(other.alloc);
            steal(other);
        }
        return *this;
    }

    /**
     * @brief Priskyrimo operatorius iš inicializavimo sąrašo.
     *
     * @param il  Inicializavimo sąrašas.
     * @return Nuoroda į šį objektą.
     */
    Vector& operator=(std::initializer_list<T> il) {
        uncreate();
        create(il.begin(), il.end());
        return *this;
    }

    /**
     * @brief Tiesioginis konvertavimas į `std::vector<T>`.
     * Sukuria kopiją visų elementų.
     */
    explicit operator std::vector<T>()        const { return std::vector<T>(dat, avail); }

    /**
     * @brief Tiesioginis konvertavimas į kintamąjį `std::span<T>`.
     */
    explicit operator std::span<T>()                { return std::span<T>(dat, avail); }

    /**
     * @brief Tiesioginis konvertavimas į konstantinį `std::span<const T>`.
     */
    explicit operator std::span<const T>()    const { return std::span<const T>(dat, avail); }

    // ── assign ───────────────────────────────────────────────────────────────

    /**
     * @brief Pakeičia turinį elementais iš iteratorių diapazono.
     *
     * @tparam InputIt  Įvesties iteratoriaus tipas.
     * @param first     Diapazono pradžia.
     * @param last      Diapazono pabaiga (neįskaičiuojama).
     */
    template <std::input_iterator InputIt>
    void assign(InputIt first, InputIt last) {
        size_type n = static_cast<size_type>(std::distance(first, last));
        if (n <= capacity()) {
            size_type old_sz = size();
            if (n <= old_sz) {
                std::copy(first, last, dat);
                destroy_range(dat + n, avail);
            } else {
                InputIt mid = std::next(first, static_cast<difference_type>(old_sz));
                std::copy(first, mid, dat);
                std::uninitialized_copy(mid, last, avail);
            }
            avail = dat + n;
        } else {
            uncreate();
            create(first, last);
        }
    }

    /**
     * @brief Pakeičia turinį `n` kopijų reikšmės `val`.
     *
     * @param n    Elementų skaičius.
     * @param val  Reikšmė, kuria pildoma.
     */
    void assign(size_type n, const value_type& val) {
        if (n <= capacity()) {
            // Reuse buffer: overwrite existing, construct/destroy the difference
            size_type old_sz = size();
            if (n <= old_sz) {
                std::fill(dat, dat + n, val);
                destroy_range(dat + n, avail);
            } else {
                std::fill(dat, avail, val);
                std::uninitialized_fill(avail, dat + n, val);
            }
            avail = dat + n;
        } else {
            uncreate();
            create(n, val);
        }
    }

    /**
     * @brief Pakeičia turinį inicializavimo sąrašo elementais.
     *
     * @param il  Inicializavimo sąrašas.
     */
    void assign(std::initializer_list<value_type> il) {
        uncreate(); create(il.begin(), il.end());
    }

    /**
     * @brief Pakeičia turinį diapazono elementais (C++23).
     *
     * @tparam R  Įvesties diapazono tipas.
     * @param r   Diapazonas, iš kurio paimami elementai.
     */
    template <std::ranges::input_range R>
    void assign_range(R&& r) {
        uncreate();
        create(std::ranges::begin(r), std::ranges::end(r));
    }

    // ── get_allocator ────────────────────────────────────────────────────────

    /**
     * @brief Grąžina naudojamo atminties valdytojo kopiją.
     * @return Atminties valdytojas.
     */
    allocator_type get_allocator() const noexcept { return alloc; }

    // ── Prieiga prie elementų ─────────────────────────────────────────────────

    /** @brief Prieiga be ribų tikrinimo. */
    reference       operator[](size_type n)       { return dat[n]; }
    /** @brief Konstantinė prieiga be ribų tikrinimo. */
    const_reference operator[](size_type n) const { return dat[n]; }

    /**
     * @brief Prieiga su ribų tikrinimu.
     * @throws std::out_of_range Jei `n >= size()`.
     */
    reference at(size_type n) {
        if (n >= size()) [[unlikely]]
            throw std::out_of_range("Vector::at: index out of range");
        return dat[n];
    }

    /**
     * @brief Konstantinė prieiga su ribų tikrinimu.
     * @throws std::out_of_range Jei `n >= size()`.
     */
    const_reference at(size_type n) const {
        if (n >= size()) [[unlikely]]
            throw std::out_of_range("Vector::at: index out of range");
        return dat[n];
    }

    /** @brief Nuoroda į pirmą elementą. */
    reference       front()       { return dat[0]; }
    /** @brief Konstantinė nuoroda į pirmą elementą. */
    const_reference front() const { return dat[0]; }
    /** @brief Nuoroda į paskutinį elementą. */
    reference       back()        { return avail[-1]; }
    /** @brief Konstantinė nuoroda į paskutinį elementą. */
    const_reference back()  const { return avail[-1]; }
    /** @brief Rodyklė į vidinę atmintį. */
    value_type*       data() noexcept       { return dat; }
    /** @brief Konstantinė rodyklė į vidinę atmintį. */
    const value_type* data() const noexcept { return dat; }

    // ── Iteratoriai ───────────────────────────────────────────────────────────

    /** @brief Iteratorius į pirmą elementą. */
iterator       begin()        noexcept { return dat; }
/** @brief Konstantinis iteratorius į pirmą elementą. */
const_iterator begin()  const noexcept { return dat; }
/** @brief Konstantinis iteratorius į pirmą elementą. */
const_iterator cbegin() const noexcept { return dat; }
/** @brief Iteratorius po paskutinio elemento. */
iterator       end()          noexcept { return avail; }
/** @brief Konstantinis iteratorius po paskutinio elemento. */
const_iterator end()    const noexcept { return avail; }
/** @brief Konstantinis iteratorius po paskutinio elemento. */
const_iterator cend()   const noexcept { return avail; }

/** @brief Atvirkštinis iteratorius į paskutinį elementą. */
reverse_iterator       rbegin()        noexcept { return reverse_iterator(end()); }
/** @brief Konstantinis atvirkštinis iteratorius į paskutinį elementą. */
const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }
/** @brief Konstantinis atvirkštinis iteratorius į paskutinį elementą. */
const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
/** @brief Atvirkštinis iteratorius prieš pirmą elementą. */
reverse_iterator       rend()          noexcept { return reverse_iterator(begin()); }
/** @brief Konstantinis atvirkštinis iteratorius prieš pirmą elementą. */
const_reverse_iterator rend()    const noexcept { return const_reverse_iterator(begin()); }
/** @brief Konstantinis atvirkštinis iteratorius prieš pirmą elementą. */
const_reverse_iterator crend()   const noexcept { return const_reverse_iterator(begin()); }

    // ── Talpa ─────────────────────────────────────────────────────────────────

    /** @brief `true` jei masyvas tuščias. */
    [[nodiscard]] bool      empty()    const noexcept { return dat == avail; }
    /** @brief Elementų skaičius. */
    [[nodiscard]] size_type size()     const noexcept { return static_cast<size_type>(avail - dat); }
    /** @brief Talpa be perskirstymo. */
    [[nodiscard]] size_type capacity() const noexcept { return static_cast<size_type>(limit - dat); }

    /**
     * @brief Maksimalus teoriškai galimas elementų skaičius.
     *
     * Apima tiek allocatoriaus ribą (`allocator_traits::max_size`), tiek
     * `difference_type` maksimumą — taip užtikrinama, kad rodyklių
     * aritmetika `end() - begin()` nepersidengtų.
     *
     * @return Maksimalus elementų skaičius.
     */
    [[nodiscard]] size_type max_size() const noexcept {
        return std::min(
            alloc_traits::max_size(alloc),
            static_cast<size_type>(std::numeric_limits<difference_type>::max())
        );
    }

    /**
     * @brief Rezervuoja atmintį bent `n` elementams.
     * Jei talpa jau pakankama — nieko nevykdo.
     *
     * @param n  Pageidaujama minimali talpa.
     */
    void reserve(size_type n) {
        if (n > capacity()) [[unlikely]]
            reallocate(n);
    }

    /**
     * @brief Sumažina talpa iki `size()`.
     *
     * Pastaba: pagal standartą ši operacija yra neprivaloma (hint),
     * tačiau ši implementacija visada ją vykdo.
     */
    void shrink_to_fit() {
    if (limit != avail) {
        if (size() == 0) {
            raw_deallocate();
            dat = avail = limit = nullptr;
        } else {
            size_type sz      = size();
            iterator  new_dat = alloc_traits::allocate(alloc, sz);
            trivial_move_or_uninit_move(dat, avail, new_dat);
            destroy_range(dat, avail);
            raw_deallocate();
            dat = new_dat;
            avail = limit = dat + sz;
        }
    }
    }

    /**
     * @brief Pakeičia dydį naudojant numatytąją inicializaciją.
     *
     * Nereikalauja `T` kopijavimo. Tinkamas `move-only` tipams.
     *
     * @param sz  Naujas dydis.
     */
    void resize(size_type sz) {
        if (sz < size()) {
            destroy_range(dat + sz, avail);
            avail = dat + sz;
        } else if (sz > size()) {
            if (sz > capacity()) [[unlikely]] reallocate(sz);
            for (iterator it = avail; it != dat + sz; ++it)
                alloc_traits::construct(alloc, it);
            avail = dat + sz;
        }
    }

    /**
     * @brief Pakeičia dydį pildant reikšme `val`.
     *
     * @param sz   Naujas dydis.
     * @param val  Reikšmė naujiems elementams.
     */
    void resize(size_type sz, const value_type& val) {
        if (sz < size()) {
            destroy_range(dat + sz, avail);
            avail = dat + sz;
        } else if (sz > size()) {
            if (sz > capacity()) [[unlikely]] reallocate(sz);
            std::uninitialized_fill(avail, dat + sz, val);
            avail = dat + sz;
        }
    }

    // ── Keitimo operacijos ────────────────────────────────────────────────────

    /**
     * @brief Prideda kopiją masyvo gale.
     * @param val  Pridedama reikšmė.
     */
    void push_back(const value_type& val) {
        if (avail == limit) [[unlikely]] grow();
        alloc_traits::construct(alloc, avail++, val);
    }

    /**
     * @brief Perkelia elementą į masyvo galą.
     * @param val  Perkeliama reikšmė.
     */
    void push_back(value_type&& val) {
        if (avail == limit) [[unlikely]] grow();
        alloc_traits::construct(alloc, avail++, std::move(val));
    }

    /**
     * @brief Sukuria elementą tiesiogiai masyvo gale.
     *
     * @tparam Args  Konstruktoriaus argumentų tipai.
     * @param args   Argumentai `T` konstruktoriui.
     * @return       Nuoroda į sukurtą elementą.
     * @note         `[[nodiscard]]` pagal C++23 standartą.
     */
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (avail == limit) [[unlikely]] grow();
        alloc_traits::construct(alloc, avail++, std::forward<Args>(args)...);
        return back();
    }

    /**
     * @brief Prideda diapazono elementus gale (C++23).
     *
     * @tparam R  Įvesties diapazono tipas.
     * @param r   Diapazonas.
     */
    template <std::ranges::input_range R>
    void append_range(R&& r) {
        if constexpr (std::ranges::sized_range<R>)
            reserve(size() + static_cast<size_type>(std::ranges::distance(r)));
        for (auto&& elem : r)
            push_back(std::forward<decltype(elem)>(elem));
    }

    /**
     * @brief Pašalina paskutinį elementą. Nieko nevykdo jei tuščias.
     */
    void pop_back() {
        if (avail != dat) [[likely]]
            alloc_traits::destroy(alloc, --avail);
    }

    /**
     * @brief Sunaikina visus elementus. `capacity()` lieka nepakitusi.
     */
    void clear() noexcept {
        destroy_range(dat, avail);
        avail = dat;
    }

    /**
     * @brief Įterpia vieno elemento kopiją.
     *
     * @param cpos  Pozicija prieš kurią įterpiama.
     * @param val   Įterpiama reikšmė.
     * @return      Iteratorius į įterptą elementą.
     */
    iterator insert(const_iterator cpos, const value_type& val) {
        return insert(cpos, size_type{1}, val);
    }

    /**
     * @brief Įterpia perkeliamą elementą.
     *
     * @param cpos  Pozicija prieš kurią įterpiama.
     * @param val   Perkeliama reikšmė.
     * @return      Iteratorius į įterptą elementą.
     */
    iterator insert(const_iterator cpos, value_type&& val) {
        size_type index = static_cast<size_type>(cpos - dat);
        if (avail == limit) [[unlikely]] grow(size() + 1);
        iterator pos = dat + index;
        shift_right(pos, 1);
        alloc_traits::construct(alloc, pos, std::move(val));
        ++avail;
        return pos;
    }

    /**
     * @brief Įterpia `n` kopijų reikšmės `val`.
     *
     * Jei talpos pakanka — stumiama vietoje. Priešingu atveju — realokacija.
     *
     * @param cpos  Pozicija prieš kurią įterpiama.
     * @param n     Kiekis.
     * @param val   Reikšmė.
     * @return      Iteratorius į pirmą įterptą elementą.
     */
    iterator insert(const_iterator cpos, size_type n, const value_type& val) {
        if (n == 0) return const_cast<iterator>(cpos);
        size_type index = static_cast<size_type>(cpos - dat);

        if (size() + n <= capacity()) [[likely]] {
            iterator pos = dat + index;
            shift_right(pos, n);
            for (size_type i = 0; i < n; ++i)
                alloc_traits::construct(alloc, pos + i, val);
            avail += n;
            return pos;
        } else {
            Vector tmp(alloc);
            tmp.reallocate(grow_capacity(size() + n));
            std::uninitialized_move(dat, dat + index, tmp.dat);
            std::uninitialized_fill(tmp.dat + index, tmp.dat + index + n, val);
            std::uninitialized_move(dat + index, avail, tmp.dat + index + n);
            tmp.avail = tmp.dat + size() + n;
            swap(tmp);
            return dat + index;
        }
    }

    /**
     * @brief Įterpia elementus iš iteratorių diapazono.
     *
     * Jei talpos pakanka — stumiama vietoje. Priešingu atveju — realokacija.
     *
     * @tparam InputIt  Iteratoriaus tipas.
     * @param cpos      Pozicija.
     * @param first     Pradžia.
     * @param last      Pabaiga.
     * @return          Iteratorius į pirmą įterptą elementą.
     */
    template <std::input_iterator InputIt>
    iterator insert(const_iterator cpos, InputIt first, InputIt last) {
        size_type index = static_cast<size_type>(cpos - dat);
        size_type n     = static_cast<size_type>(std::distance(first, last));
        if (n == 0) return dat + index;

        if (size() + n <= capacity()) [[likely]] {
            iterator pos = dat + index;
            shift_right(pos, n);
            iterator out = pos;
            for (auto it = first; it != last; ++it)
                alloc_traits::construct(alloc, out++, *it);
            avail += n;
            return pos;
        } else {
            Vector tmp(alloc);
            tmp.reallocate(grow_capacity(size() + n));
            std::uninitialized_move(dat, dat + index, tmp.dat);
            std::uninitialized_move(first, last, tmp.dat + index);
            std::uninitialized_move(dat + index, avail, tmp.dat + index + n);
            tmp.avail = tmp.dat + size() + n;
            swap(tmp);
            return dat + index;
        }
    }

    /**
     * @brief Įterpia inicializavimo sąrašo elementus.
     *
     * @param cpos  Pozicija.
     * @param il    Inicializavimo sąrašas.
     * @return      Iteratorius į pirmą įterptą elementą.
     */
    iterator insert(const_iterator cpos, std::initializer_list<value_type> il) {
        return insert(cpos, il.begin(), il.end());
    }

    /**
     * @brief Įterpia diapazono elementus (C++23).
     *
     * Jei talpos pakanka — stumiama vietoje. Priešingu atveju — realokacija.
     *
     * @tparam R    Diapazono tipas.
     * @param cpos  Pozicija.
     * @param r     Diapazonas.
     * @return      Iteratorius į pirmą įterptą elementą.
     */
    template <std::ranges::input_range R>
    iterator insert_range(const_iterator cpos, R&& r) {
        size_type index = static_cast<size_type>(cpos - dat);

        if constexpr (std::ranges::sized_range<R>) {
            size_type n = static_cast<size_type>(std::ranges::distance(r));
            if (n == 0) return dat + index;

            if (size() + n <= capacity()) {
                iterator pos = dat + index;
                shift_right(pos, n);
                iterator out = pos;
                for (auto&& elem : r)
                    alloc_traits::construct(alloc, out++,
                        std::forward<decltype(elem)>(elem));
                avail += n;
                return pos;
            } else {
                // reallocation path (same as before)
                Vector tmp(alloc);
                tmp.reallocate(grow_capacity(size() + n));
                std::uninitialized_move(dat, dat + index, tmp.dat);
                std::uninitialized_copy(std::ranges::begin(r),
                                        std::ranges::end(r),
                                        tmp.dat + index);
                std::uninitialized_move(dat + index, avail,
                                        tmp.dat + index + n);
                tmp.avail = tmp.dat + size() + n;
                swap(tmp);
                return dat + index;
            }
        } else {
            // Non-sized / single-pass: collect into a temporary Vector first,
            // then delegate to the sized overload
            Vector<T, Allocator> tmp_range(alloc);
            for (auto&& elem : r)
                tmp_range.push_back(std::forward<decltype(elem)>(elem));
            return insert_range(cpos, tmp_range);
        }
    }

    /**
     * @brief Sukuria elementą tiesiogiai nurodytoje pozicijoje.
     *
     * @tparam Args  Konstruktoriaus argumentų tipai.
     * @param cpos   Pozicija.
     * @param args   Argumentai `T` konstruktoriui.
     * @return       Iteratorius į sukurtą elementą.
     */
    template <typename... Args>
    iterator emplace(const_iterator cpos, Args&&... args) {
        size_type index = static_cast<size_type>(cpos - dat);
        if (avail == limit) [[unlikely]] grow(size() + 1);
        iterator pos = dat + index;
        shift_right(pos, 1);
        alloc_traits::construct(alloc, pos, std::forward<Args>(args)...);
        ++avail;
        return pos;
    }

    /**
     * @brief Pašalina elementą pozicijoje `cpos`.
     *
     * Trivialiai kopijuojamiems tipams naudoja `memmove`.
     *
     * @param cpos  Šalinamo elemento pozicija.
     * @return      Iteratorius į po pašalintojo buvusį elementą.
     */
    iterator erase(const_iterator cpos) {
        iterator pos = const_cast<iterator>(cpos);
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::memmove(pos, pos + 1,
                static_cast<std::size_t>(avail - pos - 1) * sizeof(T));
        } else {
            std::move(pos + 1, avail, pos);
        }
        alloc_traits::destroy(alloc, --avail);
        return pos;
    }

    /**
     * @brief Pašalina elementus diapazone `[cfirst, clast)`.
     *
     * Trivialiai kopijuojamiems tipams naudoja `memmove`.
     *
     * @param cfirst  Pirmas šalinamas.
     * @param clast   Po paskutinio šalinamo.
     * @return        Iteratorius į po diapazono buvusį elementą.
     */
    iterator erase(const_iterator cfirst, const_iterator clast) {
        iterator first = const_cast<iterator>(cfirst);
        iterator last  = const_cast<iterator>(clast);
        iterator new_avail;
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::size_t tail = static_cast<std::size_t>(avail - last);
            std::memmove(first, last, tail * sizeof(T));
            new_avail = first + tail;
        } else {
            new_avail = std::move(last, avail, first);
        }
        destroy_range(new_avail, avail);
        avail = new_avail;
        return first;
    }

    /**
     * @brief Keičia turinį su `other`. O(1).
     *
     * Jei `propagate_on_container_swap` — keičiasi ir allocatoriai.
     *
     * @param other  Kitas masyvas.
     */
    void swap(Vector& other) noexcept {
        std::swap(dat,   other.dat);
        std::swap(avail, other.avail);
        std::swap(limit, other.limit);
        if constexpr (alloc_traits::propagate_on_container_swap::value)
            std::swap(alloc, other.alloc);
    }

    // ── Palyginimo operatoriai ────────────────────────────────────────────────

    /**
     * @brief Lygybė — vienodi elementai ta pačia tvarka.
     */
    bool operator==(const Vector& other) const {
        return size() == other.size() &&
               std::equal(begin(), end(), other.begin());
    }

    /**
     * @brief Trijų krypčių palyginimas (C++20). Leksikografinė tvarka.
     */
    auto operator<=>(const Vector& other) const {
        return std::lexicographical_compare_three_way(
            begin(), end(), other.begin(), other.end());
    }

    /** @brief Nelygybė — `true` jei masyvai skiriasi. */
bool operator!=(const Vector& other) const { return !(*this == other); }
/** @brief Leksikografinė mažiau-už relacija. */
bool operator< (const Vector& other) const { return (*this <=> other) < 0; }
/** @brief Leksikografinė mažiau-arba-lygu relacija. */
bool operator<=(const Vector& other) const { return (*this <=> other) <= 0; }
/** @brief Leksikografinė daugiau-už relacija. */
bool operator> (const Vector& other) const { return (*this <=> other) > 0; }
/** @brief Leksikografinė daugiau-arba-lygu relacija. */
bool operator>=(const Vector& other) const { return (*this <=> other) >= 0; }

private:
    iterator  dat   = nullptr; ///< Rodyklė į pirmą elementą.
    iterator  avail = nullptr; ///< Rodyklė po paskutinio inicializuoto elemento.
    iterator  limit = nullptr; ///< Rezervuoto bloko pabaiga.
    Allocator alloc;           ///< Atminties valdytojas.

    // ── Pagalbiniai metodai ───────────────────────────────────────────────────

    /** @brief Nustato nulines rodykles (tuščias masyvas). */
    void create() { dat = avail = limit = nullptr; }

    /**
     * @brief Allokuoja ir pilda `n` kopijomis `val`.
     */
    void create(size_type n, const T& val) {
        if (n == 0) { dat = avail = limit = nullptr; return; }
        dat = alloc.allocate(n);
        limit = avail = dat + n;
        std::uninitialized_fill(dat, limit, val);
    }

    /**
     * @brief Allokuoja ir inicializuoja `n` elementų numatytaisiais.
     *
     * Nenaudoja kopijavimo — tinkama `move-only` tipams.
     */
    void create_default(size_type n) {
        if (n == 0) { dat = avail = limit = nullptr; return; }
        dat = alloc.allocate(n);
        avail = limit = dat + n;
        for (iterator it = dat; it != avail; ++it) alloc_traits::construct(alloc, it);
    }

    /**
     * @brief Allokuoja ir kopijuoja iš iteratorių diapazono.
     *
     * Trivialiai kopijuojamiems tipams su rodyklių iteratoriais
     * naudoja `memcpy` vietoj `uninitialized_move`.
     */
    template <typename InputIt>
    void create(InputIt first, InputIt last) {
        size_type n = static_cast<size_type>(std::distance(first, last));
        if (n == 0) { dat = avail = limit = nullptr; return; }
        dat = alloc.allocate(n);
        if constexpr (std::is_trivially_copyable_v<T> && std::is_pointer_v<InputIt>) {
            std::memcpy(dat, first, n * sizeof(T));
            avail = limit = dat + n;
        } else {
            limit = avail = std::uninitialized_move(first, last, dat);
        }
    }

    /**
     * @brief Sunaikina elementus ir atlaisvina atmintį. Nustato `nullptr`.
     */
    void uncreate() {
        if (dat) {
            destroy_range(dat, avail);
            raw_deallocate();
        }
        dat = avail = limit = nullptr;
    }

    /**
     * @brief Atlaisvina atmintį be destruktorių iškvietimo.
     */
    void raw_deallocate() {
        alloc.deallocate(dat, static_cast<size_type>(limit - dat));
    }

    /**
     * @brief Sunaikina elementus `[first, last)`.
     *
     * Trivialiai sunaikinami tipai — destruktoriai praleidiami.
     */
    void destroy_range(iterator first, iterator last) noexcept {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            for (iterator it = last; it != first; )
                alloc_traits::destroy(alloc, --it);
        }
    }

    /**
     * @brief Perkelia elementus į neinicializuotą sritį.
     *
     * `memcpy` trivialiai kopijuojamiems, `uninitialized_move` kitiems.
     */
    static void trivial_move_or_uninit_move(iterator src_first,
                                             iterator src_last,
                                             iterator dst) {
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::memcpy(dst, src_first,
                static_cast<std::size_t>(src_last - src_first) * sizeof(T));
        } else {
            std::uninitialized_move(src_first, src_last, dst);
        }
    }

    /**
     * @brief Perkelia turinį į naują bloką `new_capacity` dydžio.
     *
     * Trivialiai kopijuojamiems tipams — `memcpy`, destruktoriai praleidiami.
     *
     * @param new_capacity  Nauja talpa.
     */
    void reallocate(size_type new_capacity) {
        iterator new_dat = alloc.allocate(new_capacity);
        size_type sz     = size();
        trivial_move_or_uninit_move(dat, avail, new_dat);
        destroy_range(dat, avail); 
        if (dat) raw_deallocate();
        dat   = new_dat;
        avail = dat + sz;
        limit = dat + new_capacity;
    }

    /**
     * @brief Apskaičiuoja naują talpą augimo metu.
     *
     * - `needed <= 3 * capacity()`: trigubina (`max(3*cap, 1)`).
     * - `needed > 3 * capacity()`: naudoja tikslų `needed` — vengia
     *   perteklinės atminties kai vienu metu įterpiama daug elementų.
     *
     * @param needed  Minimali reikalinga talpa.
     * @return        Nauja talpa.
     */
    size_type grow_capacity(size_type needed) const noexcept {
        size_type cap     = capacity();
        size_type tripled = (cap <= std::numeric_limits<size_type>::max() / 3)
                            ? 3 * cap
                            : std::numeric_limits<size_type>::max();
        tripled = std::max(tripled, size_type{1});
        return (needed <= tripled) ? tripled : needed;
    }

    /**
     * @brief Automatiškai didina talpą.
     *
     * @param min_capacity  Minimali talpa (numatytoji — `size()+1`).
     */
    void grow(size_type min_capacity = 0) {
        reallocate(grow_capacity(std::max(min_capacity, size() + 1)));
    }

    /**
     * @brief Paima `other` resursus be kopijavimo (po operacijos `other` tuščias).
     */
    void steal(Vector& other) noexcept {
        dat   = other.dat;
        avail = other.avail;
        limit = other.limit;
        other.dat = other.avail = other.limit = nullptr;
    }

    /**
     * @brief Pastumia elementus `[pos, avail)` dešinėn per `n` pozicijų.
     *
     * ### Strategija:
     * - **Trivialiai kopijuojami tipai**: `memmove` — greičiausia, vienas kvietimas.
     * - **Neinicializuota sritis** `[avail, avail+n)`:
     *   `alloc_traits::construct` + `std::move_if_noexcept` — išimčių saugu,
     *   teisingai inicializuoja naujus objektus.
     * - **Inicializuota sritis** `[pos, avail-n)`:
     *   priskyrimo operatorius (`std::move_if_noexcept` assignment) — ne
     *   konstruktorius, nes objektai jau egzistuoja; konstruktoriaus kvietimas
     *   čia nutekintų destruktorius ne-trivialiai sunaikinami tipams.
     *
     * @param pos  Pirmasis stumtinas elementas.
     * @param n    Postūmis pozicijomis.
     */
    void shift_right(iterator pos, size_type n) {
        if (pos == avail) return;

        if constexpr (std::is_trivially_copyable_v<T>) {
            std::memmove(pos + n, pos,
                static_cast<std::size_t>(avail - pos) * sizeof(T));
            return;
        }
        size_type tail = static_cast<size_type>(avail - pos);
        if (n >= tail) {
            iterator src = pos, dst = pos + n;
            for (; src != avail; ++src, ++dst)
                alloc_traits::construct(alloc, dst, std::move_if_noexcept(*src));
            destroy_range(pos, avail);
        } else {
            iterator uninit_src = avail - n;
            iterator uninit_dst = avail;
            for (iterator it = uninit_src; it != avail; ++it, ++uninit_dst)
                alloc_traits::construct(alloc, uninit_dst,
                                        std::move_if_noexcept(*it));
            for (iterator it = uninit_src; it != pos; ) {
                --it;
                *(it + n) = std::move_if_noexcept(*it);
            }
        }
    }
};

// ── Laisvosios funkcijos ──────────────────────────────────────────────────────

/**
 * @brief Keičia du `Vector` objektus. O(1).
 *
 * @tparam T         Elementų tipas.
 * @tparam Allocator Atminties valdytojo tipas.
 * @param a          Pirmas masyvas.
 * @param b          Antras masyvas.
 */
template <VectorElement T, typename Allocator>
void swap(Vector<T, Allocator>& a, Vector<T, Allocator>& b) noexcept { a.swap(b); }

/**
 * @brief Pašalina visus elementus lygius `value` (C++20).
 *
 * @tparam T         Elementų tipas.
 * @tparam Allocator Atminties valdytojo tipas.
 * @tparam U         Lyginamos reikšmės tipas.
 * @param v          Masyvas.
 * @param value      Šalinama reikšmė.
 * @return           Pašalintų elementų skaičius.
 */
template <VectorElement T, typename Allocator, typename U>
typename Vector<T, Allocator>::size_type erase(Vector<T, Allocator>& v, const U& value) {
    auto it = std::remove(v.begin(), v.end(), value);
    auto n  = static_cast<typename Vector<T, Allocator>::size_type>(v.end() - it);
    v.erase(it, v.end());
    return n;
}

/**
 * @brief Pašalina visus elementus tenkinančius predikato sąlygą (C++20).
 *
 * @tparam T         Elementų tipas.
 * @tparam Allocator Atminties valdytojo tipas.
 * @tparam Pred      Predikato tipas.
 * @param v          Masyvas.
 * @param pred       Predikatas.
 * @return           Pašalintų elementų skaičius.
 */
template <VectorElement T, typename Allocator, typename Pred>
typename Vector<T, Allocator>::size_type erase_if(Vector<T, Allocator>& v, Pred pred) {
    auto it = std::remove_if(v.begin(), v.end(), pred);
    auto n  = static_cast<typename Vector<T, Allocator>::size_type>(v.end() - it);
    v.erase(it, v.end());
    return n;
}

#endif // VECTOR_H