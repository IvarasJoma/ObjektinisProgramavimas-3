/**
 * @file Vector.h
 * @brief Dinaminio masyvo šabloninė klasė, analogiška `std::vector`.
 *
 * Šiame faile apibrėžta `Vector<T>` klasė — pilnavertis dinaminis masyvas,
 * suderinamas su C++20/23 standartais. Palaikomi:
 * - pilnas iteratorių rinkinys (tiesioginiai ir atvirkštiniai),
 * - `emplace_back`, `insert`, `erase` su stipria išimčių garantija,
 * - C++20 trijų krypčių palyginimo operatorius (`<=>`),
 * - C++23 operacijos `append_range`, `assign_range`, `insert_range`.
 *
 * @tparam T Elementų tipas; turi tenkinti `VectorElement` sąvoką (t.y. būti perkeliamas).
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <compare>
#include <concepts>
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
 * masyvas automatiškai išplečiamas perkėlimo operacija į naują, didesnį bloką.
 *
 * @tparam T Elementų tipas; turi tenkinti @ref VectorElement sąvoką.
 */
template <VectorElement T>
class Vector {
public:
    // ── Tipų sinonimai ────────────────────────────────────────────────────────

    /** @brief Elementų tipas. */
    using value_type             = T;
    /** @brief Atminties valdytojo tipas. */
    using allocator_type         = std::allocator<T>;
    /** @brief Dydžiui skirtas tipas be ženklo. */
    using size_type              = std::size_t;
    /** @brief Atstumui tarp elementų skirtas tipas su ženklu. */
    using difference_type        = std::ptrdiff_t;
    /** @brief Elemento nuorodos tipas. */
    using reference              = T&;
    /** @brief Konstantinės elemento nuorodos tipas. */
    using const_reference        = const T&;
    /** @brief Rodyklės tipas. */
    using pointer                = typename std::allocator_traits<std::allocator<T>>::pointer;
    /** @brief Konstantinės rodyklės tipas. */
    using const_pointer          = typename std::allocator_traits<std::allocator<T>>::const_pointer;
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
    Vector() { create(); }

    /**
     * @brief Konstruktorius su pradiniu dydžiu ir reikšme.
     *
     * @param n    Pradinių elementų skaičius.
     * @param val  Pradinė visų elementų reikšmė (numatytoji — `T{}`).
     */
    explicit Vector(size_type n, const T& val = T{}) { create(n, val); }

    /**
     * @brief Kopijavimo konstruktorius.
     *
     * Sukuria gilią kopiją kito `Vector` objekto.
     *
     * @param other Kopijuojamas objektas.
     */
    Vector(const Vector& other) { create(other.begin(), other.end()); }

    /**
     * @brief Perkėlimo konstruktorius.
     *
     * Perimamas `other` turinys; po operacijos `other` tampa tuščias.
     *
     * @param other Perkeliamas objektas.
     */
    Vector(Vector&& other) noexcept
        : dat(other.dat), avail(other.avail), limit(other.limit)
    {
        other.dat = other.avail = other.limit = nullptr;
    }

    /**
     * @brief Konstruktorius iš iteratorių diapazono.
     *
     * @tparam InputIt Įvesties iteratoriaus tipas.
     * @param first  Diapazono pradžia.
     * @param last   Diapazono pabaiga (neįskaičiuojama).
     */
    template <std::input_iterator InputIt>
    Vector(InputIt first, InputIt last) { create(first, last); }

    /**
     * @brief Konstruktorius iš inicializavimo sąrašo.
     *
     * @param il Inicializavimo sąrašas, pvz., `{1, 2, 3}`.
     */
    Vector(std::initializer_list<T> il) { create(il.begin(), il.end()); }

    /**
     * @brief Destruktorius. Sunaikina visus elementus ir atlaisvina atmintį.
     */
    ~Vector() { uncreate(); }

    // ── Priskyrimo operatoriai ────────────────────────────────────────────────

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     *
     * Atlieka gilią kopiją. Apsaugo nuo savęs priskyrimo.
     *
     * @param other  Kopijuojamas objektas.
     * @return Nuoroda į šį objektą.
     */
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            uncreate();
            create(other.begin(), other.end());
        }
        return *this;
    }

    /**
     * @brief Perkėlimo priskyrimo operatorius.
     *
     * Perimamas `other` turinys; po operacijos `other` tampa tuščias.
     *
     * @param other  Perkeliamas objektas.
     * @return Nuoroda į šį objektą.
     */
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            uncreate();
            dat   = other.dat;
            avail = other.avail;
            limit = other.limit;
            other.dat = other.avail = other.limit = nullptr;
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
     * @brief Netiesioginis konvertavimas į `std::vector<T>`.
     *
     * Sukuria kopiją visų elementų.
     */
    operator std::vector<T>()        const { return std::vector<T>(dat, avail); }

    /**
     * @brief Netiesioginis konvertavimas į kintamąjį `std::span<T>`.
     */
    operator std::span<T>()                { return std::span<T>(dat, avail); }

    /**
     * @brief Netiesioginis konvertavimas į konstantinį `std::span<const T>`.
     */
    operator std::span<const T>()    const { return std::span<const T>(dat, avail); }

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
        uncreate();
        create(first, last);
    }

    /**
     * @brief Pakeičia turinį `n` kopijų reikšmės `val`.
     *
     * @param n    Elementų skaičius.
     * @param val  Reikšmė, kuria pildoma.
     */
    void assign(size_type n, const value_type& val) {
        uncreate();
        create(n, val);
    }

    /**
     * @brief Pakeičia turinį inicializavimo sąrašo elementais.
     *
     * @param il  Inicializavimo sąrašas.
     */
    void assign(std::initializer_list<value_type> il) {
        uncreate();
        create(il.begin(), il.end());
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
     * @brief Grąžina naudojamą atminties valdytojo kopiją.
     *
     * @return Atminties valdytojas.
     */
    allocator_type get_allocator() const noexcept { return alloc; }

    // ── Prieiga prie elementų ─────────────────────────────────────────────────

    /**
     * @brief Prieiga prie elemento pagal indeksą (be ribų tikrinimo).
     *
     * @param n  Elemento indeksas.
     * @return   Nuoroda į elementą.
     */
    reference       operator[](size_type n)       { return dat[n]; }

    /**
     * @brief Konstantinė prieiga prie elemento pagal indeksą (be ribų tikrinimo).
     *
     * @param n  Elemento indeksas.
     * @return   Konstantinė nuoroda į elementą.
     */
    const_reference operator[](size_type n) const { return dat[n]; }

    /**
     * @brief Prieiga prie elemento pagal indeksą su ribų tikrinimu.
     *
     * @param n  Elemento indeksas.
     * @return   Nuoroda į elementą.
     * @throws std::out_of_range Jei `n >= size()`.
     */
    reference at(size_type n) {
        if (n >= size())
            throw std::out_of_range("Vector::at: index out of range");
        return dat[n];
    }

    /**
     * @brief Konstantinė prieiga prie elemento pagal indeksą su ribų tikrinimu.
     *
     * @param n  Elemento indeksas.
     * @return   Konstantinė nuoroda į elementą.
     * @throws std::out_of_range Jei `n >= size()`.
     */
    const_reference at(size_type n) const {
        if (n >= size())
            throw std::out_of_range("Vector::at: index out of range");
        return dat[n];
    }

    /**
     * @brief Grąžina nuorodą į pirmą elementą.
     * @return Nuoroda į pirmą elementą.
     */
    reference       front()       { return dat[0]; }

    /**
     * @brief Grąžina konstantinę nuorodą į pirmą elementą.
     * @return Konstantinė nuoroda į pirmą elementą.
     */
    const_reference front() const { return dat[0]; }

    /**
     * @brief Grąžina nuorodą į paskutinį elementą.
     * @return Nuoroda į paskutinį elementą.
     */
    reference       back()       { return avail[-1]; }

    /**
     * @brief Grąžina konstantinę nuorodą į paskutinį elementą.
     * @return Konstantinė nuoroda į paskutinį elementą.
     */
    const_reference back() const { return avail[-1]; }

    /**
     * @brief Tiesioginis prieigos prie vidinės atminties rodyklė.
     * @return Rodyklė į pirmą elementą.
     */
    value_type*       data() noexcept       { return dat; }

    /**
     * @brief Konstantinė rodyklė į vidinę atmintį.
     * @return Konstantinė rodyklė į pirmą elementą.
     */
    const value_type* data() const noexcept { return dat; }

    // ── Iteratoriai ───────────────────────────────────────────────────────────

    /** @brief Pradžios iteratorius. */
    iterator       begin()        noexcept { return dat; }
    /** @brief Konstantinis pradžios iteratorius. */
    const_iterator begin()  const noexcept { return dat; }
    /** @brief Konstantinis pradžios iteratorius (`cbegin`). */
    const_iterator cbegin() const noexcept { return dat; }

    /** @brief Pabaigos iteratorius (rodo už paskutinio elemento). */
    iterator       end()        noexcept { return avail; }
    /** @brief Konstantinis pabaigos iteratorius. */
    const_iterator end()  const noexcept { return avail; }
    /** @brief Konstantinis pabaigos iteratorius (`cend`). */
    const_iterator cend() const noexcept { return avail; }

    /** @brief Atvirkštinis pradžios iteratorius (rodo į paskutinį elementą). */
    reverse_iterator       rbegin()        noexcept { return reverse_iterator(end()); }
    /** @brief Konstantinis atvirkštinis pradžios iteratorius. */
    const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }
    /** @brief Konstantinis atvirkštinis pradžios iteratorius (`crbegin`). */
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    /** @brief Atvirkštinis pabaigos iteratorius (rodo prieš pirmą elementą). */
    reverse_iterator       rend()        noexcept { return reverse_iterator(begin()); }
    /** @brief Konstantinis atvirkštinis pabaigos iteratorius. */
    const_reverse_iterator rend()  const noexcept { return const_reverse_iterator(begin()); }
    /** @brief Konstantinis atvirkštinis pabaigos iteratorius (`crend`). */
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    // ── Talpa ─────────────────────────────────────────────────────────────────

    /**
     * @brief Patikrina, ar masyvas tuščias.
     * @return `true`, jei nėra elementų.
     */
    [[nodiscard]] bool      empty()    const noexcept { return dat == avail; }

    /**
     * @brief Grąžina esamą elementų skaičių.
     * @return Elementų skaičius.
     */
    [[nodiscard]] size_type size()     const noexcept { return static_cast<size_type>(avail - dat); }

    /**
     * @brief Grąžina dabartinę talpą (kiek elementų telpa be perskirstymo).
     * @return Talpa elementais.
     */
    [[nodiscard]] size_type capacity() const noexcept { return static_cast<size_type>(limit - dat); }

    /**
     * @brief Grąžina teoriškai maksimalų galimą elementų skaičių.
     * @return Maksimalus skaičius (platformos riba).
     */
    [[nodiscard]] size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

    /**
     * @brief Rezervuoja atmintį bent `n` elementams.
     *
     * Jei dabartinė talpa jau pakankama, nieko nevykdo.
     *
     * @param n  Pageidaujama minimali talpa.
     */
    void reserve(size_type n) {
        if (n > capacity())
            reallocate(n);
    }

    /**
     * @brief Sumažina rezervuotą atmintį iki faktiškai naudojamos.
     *
     * Talpa tampa lygi `size()`. Visi esami elementai perkeliami.
     */
    void shrink_to_fit() {
        if (limit != avail) {
            size_type sz      = size();
            iterator  new_dat = alloc.allocate(sz);
            std::uninitialized_move(dat, avail, new_dat);
            uncreate();
            dat = new_dat;
            avail = limit = dat + sz;
        }
    }

    /**
     * @brief Pakeičia masyvo dydį.
     *
     * - Jei `sz < size()` — pertekliniai elementai sunaikinami.
     * - Jei `sz > size()` — nauji elementai inicializuojami reikšme `val`.
     *
     * @param sz   Pageidaujamas naujas dydis.
     * @param val  Reikšmė naujiems elementams (numatytoji — `value_type()`).
     */
    void resize(size_type sz, const value_type& val = value_type()) {
        if (sz < size()) {
            for (iterator it = dat + sz; it != avail; ++it)
                alloc_traits::destroy(alloc, it);
            avail = dat + sz;
        } else if (sz > size()) {
            if (sz > capacity())
                reallocate(sz);
            std::uninitialized_fill(avail, dat + sz, val);
            avail = dat + sz;
        }
    }

    // ── Keitimo operacijos ────────────────────────────────────────────────────

    /**
     * @brief Prideda elemento kopiją masyvo gale.
     *
     * @param val  Pridedama reikšmė.
     */
    void push_back(const value_type& val) {
        if (avail == limit) grow();
        alloc_traits::construct(alloc, avail++, val);
    }

    /**
     * @brief Perkelia elementą į masyvo galą.
     *
     * @param val  Perkeliama reikšmė.
     */
    void push_back(value_type&& val) {
        if (avail == limit) grow();
        alloc_traits::construct(alloc, avail++, std::move(val));
    }

    /**
     * @brief Sukuria elementą tiesiogiai masyvo gale (be kopijavimo).
     *
     * @tparam Args  Konstruktoriaus argumentų tipai.
     * @param args   Argumentai, perduodami `T` konstruktoriui.
     * @return       Nuoroda į sukurtą elementą.
     */
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (avail == limit) grow();
        alloc_traits::construct(alloc, avail++, std::forward<Args>(args)...);
        return back();
    }

    /**
     * @brief Prideda diapazono elementus masyvo gale (C++23).
     *
     * @tparam R  Įvesties diapazono tipas.
     * @param r   Diapazonas, iš kurio paimami elementai.
     */
    template <std::ranges::input_range R>
    void append_range(R&& r) {
        for (auto&& elem : r)
            push_back(std::forward<decltype(elem)>(elem));
    }

    /**
     * @brief Pašalina paskutinį elementą.
     *
     * Nieko nevykdo, jei masyvas tuščias.
     */
    void pop_back() {
        if (avail != dat)
            alloc_traits::destroy(alloc, --avail);
    }

    /**
     * @brief Sunaikina visus elementus, bet neatlaisvina rezervuotos atminties.
     *
     * Po operacijos `size() == 0`, tačiau `capacity()` lieka nepakitusi.
     */
    void clear() noexcept {
        for (iterator it = dat; it != avail; ++it)
            alloc_traits::destroy(alloc, it);
        avail = dat;
    }

    /**
     * @brief Įterpia vieno elemento kopiją nurodytoje pozicijoje.
     *
     * @param cpos  Iteratorius į poziciją, prieš kurią įterpiama.
     * @param val   Įterpiama reikšmė.
     * @return      Iteratorius į įterptą elementą.
     */
    iterator insert(const_iterator cpos, const value_type& val) {
        return insert(cpos, size_type{1}, val);
    }

    /**
     * @brief Įterpia perkeliamą elementą nurodytoje pozicijoje.
     *
     * @param cpos  Iteratorius į poziciją, prieš kurią įterpiama.
     * @param val   Perkeliama reikšmė.
     * @return      Iteratorius į įterptą elementą.
     */
    iterator insert(const_iterator cpos, value_type&& val) {
        size_type index = static_cast<size_type>(cpos - dat);
        if (avail == limit) grow(size() + 1);
        iterator pos = dat + index;
        shift_right(pos, 1);
        alloc_traits::construct(alloc, pos, std::move(val));
        ++avail;
        return pos;
    }

    /**
     * @brief Įterpia `n` kopijų reikšmės `val` prieš nurodytą poziciją.
     *
     * Naudoja kopijavimo–keitimo strategiją stipriai išimčių garantijai.
     *
     * @param cpos  Iteratorius į poziciją, prieš kurią įterpiama.
     * @param n     Įterpiamų elementų skaičius.
     * @param val   Įterpiama reikšmė.
     * @return      Iteratorius į pirmą įterptą elementą.
     */
    iterator insert(const_iterator cpos, size_type n, const value_type& val) {
        if (n == 0) return const_cast<iterator>(cpos);
        size_type index = static_cast<size_type>(cpos - dat);

        Vector tmp;
        tmp.reallocate(size() + n);
        std::uninitialized_copy(dat, dat + index, tmp.dat);
        std::uninitialized_fill(tmp.dat + index, tmp.dat + index + n, val);
        std::uninitialized_copy(dat + index, avail, tmp.dat + index + n);
        tmp.avail = tmp.dat + size() + n;
        swap(tmp);

        return dat + index;
    }

    /**
     * @brief Įterpia elementus iš iteratorių diapazono prieš nurodytą poziciją.
     *
     * Naudoja kopijavimo–keitimo strategiją stipriai išimčių garantijai.
     *
     * @tparam InputIt  Įvesties iteratoriaus tipas.
     * @param cpos      Iteratorius į poziciją, prieš kurią įterpiama.
     * @param first     Įterpiamo diapazono pradžia.
     * @param last      Įterpiamo diapazono pabaiga (neįskaičiuojama).
     * @return          Iteratorius į pirmą įterptą elementą.
     */
    template <std::input_iterator InputIt>
    iterator insert(const_iterator cpos, InputIt first, InputIt last) {
        size_type index = static_cast<size_type>(cpos - dat);
        size_type n     = static_cast<size_type>(std::distance(first, last));
        if (n == 0) return dat + index;

        Vector tmp;
        tmp.reallocate(size() + n);
        std::uninitialized_copy(dat, dat + index, tmp.dat);
        std::uninitialized_copy(first, last, tmp.dat + index);
        std::uninitialized_copy(dat + index, avail, tmp.dat + index + n);
        tmp.avail = tmp.dat + size() + n;
        swap(tmp);

        return dat + index;
    }

    /**
     * @brief Įterpia inicializavimo sąrašo elementus prieš nurodytą poziciją.
     *
     * @param cpos  Iteratorius į poziciją, prieš kurią įterpiama.
     * @param il    Inicializavimo sąrašas.
     * @return      Iteratorius į pirmą įterptą elementą.
     */
    iterator insert(const_iterator cpos, std::initializer_list<value_type> il) {
        return insert(cpos, il.begin(), il.end());
    }

    /**
     * @brief Įterpia diapazono elementus prieš nurodytą poziciją (C++23).
     *
     * @tparam R    Įvesties diapazono tipas.
     * @param cpos  Iteratorius į poziciją, prieš kurią įterpiama.
     * @param r     Diapazonas, iš kurio paimami elementai.
     * @return      Iteratorius į pirmą įterptą elementą.
     */
    template <std::ranges::input_range R>
    iterator insert_range(const_iterator cpos, R&& r) {
        size_type index = static_cast<size_type>(cpos - dat);
        size_type n     = static_cast<size_type>(std::ranges::distance(r));
        if (n == 0) return dat + index;

        Vector tmp;
        tmp.reallocate(size() + n);
        std::uninitialized_copy(dat, dat + index, tmp.dat);
        std::uninitialized_copy(std::ranges::begin(r), std::ranges::end(r), tmp.dat + index);
        std::uninitialized_copy(dat + index, avail, tmp.dat + index + n);
        tmp.avail = tmp.dat + size() + n;
        swap(tmp);

        return dat + index;
    }

    /**
     * @brief Sukuria elementą tiesiogiai nurodytoje pozicijoje.
     *
     * @tparam Args  Konstruktoriaus argumentų tipai.
     * @param cpos   Iteratorius į poziciją, prieš kurią elementas sukuriamas.
     * @param args   Argumentai, perduodami `T` konstruktoriui.
     * @return       Iteratorius į sukurtą elementą.
     */
    template <typename... Args>
    iterator emplace(const_iterator cpos, Args&&... args) {
        size_type index = static_cast<size_type>(cpos - dat);
        if (avail == limit) grow(size() + 1);
        iterator pos = dat + index;
        shift_right(pos, 1);
        alloc_traits::construct(alloc, pos, std::forward<Args>(args)...);
        ++avail;
        return pos;
    }

    /**
     * @brief Pašalina elementą nurodytoje pozicijoje.
     *
     * @param cpos  Iteratorius į šalinamą elementą.
     * @return      Iteratorius į elementą, buvusį iškart po pašalintojo.
     */
    iterator erase(const_iterator cpos) {
        iterator pos = const_cast<iterator>(cpos);
        std::move(pos + 1, avail, pos);
        alloc_traits::destroy(alloc, --avail);
        return pos;
    }

    /**
     * @brief Pašalina elementus iš diapazono `[cfirst, clast)`.
     *
     * @param cfirst  Iteratorius į pirmą šalinamą elementą.
     * @param clast   Iteratorius už paskutinio šalinamo elemento.
     * @return        Iteratorius į elementą, buvusį iškart po pašalintojo diapazono.
     */
    iterator erase(const_iterator cfirst, const_iterator clast) {
        iterator first     = const_cast<iterator>(cfirst);
        iterator last      = const_cast<iterator>(clast);
        iterator new_avail = std::move(last, avail, first);
        for (iterator it = new_avail; it != avail; ++it)
            alloc_traits::destroy(alloc, it);
        avail = new_avail;
        return first;
    }

    /**
     * @brief Keičia šio masyvo turinį su kito masyvo turiniu.
     *
     * Operacija vykdoma be kopijų, O(1) laikinė sudėtingumas.
     *
     * @param other  Masyvas, su kuriuo keičiamasi.
     */
    void swap(Vector& other) noexcept {
        std::swap(dat,   other.dat);
        std::swap(avail, other.avail);
        std::swap(limit, other.limit);
    }

    // ── Palyginimo operatoriai ────────────────────────────────────────────────

    /**
     * @brief Lygybės operatorius.
     *
     * @param other  Lyginamas masyvas.
     * @return `true`, jei abu masyvai turi vienodus elementus ta pačia tvarka.
     */
    bool operator==(const Vector& other) const {
        return size() == other.size() && std::equal(begin(), end(), other.begin());
    }

    /**
     * @brief Trijų krypčių palyginimo operatorius (C++20, `<=>`).
     *
     * Leksikografinė tvarka.
     *
     * @param other  Lyginamas masyvas.
     * @return Palyginimo kategorija (`std::strong_ordering` arba silpnesnė,
     *         priklausomai nuo `T`).
     */
    auto operator<=>(const Vector& other) const {
        return std::lexicographical_compare_three_way(
            begin(), end(), other.begin(), other.end());
    }

    /** @brief Nelygybės operatorius. */
    bool operator!=(const Vector& other) const { return !(*this == other); }
    /** @brief Mažiau operatorius. */
    bool operator< (const Vector& other) const { return (*this <=> other) < 0; }
    /** @brief Mažiau arba lygu operatorius. */
    bool operator<=(const Vector& other) const { return (*this <=> other) <= 0; }
    /** @brief Daugiau operatorius. */
    bool operator> (const Vector& other) const { return (*this <=> other) > 0; }
    /** @brief Daugiau arba lygu operatorius. */
    bool operator>=(const Vector& other) const { return (*this <=> other) >= 0; }

private:
    /** @brief Rodyklė į pirmą elementą. */
    iterator          dat   = nullptr;
    /** @brief Rodyklė į vietą po paskutinio inicializuoto elemento. */
    iterator          avail = nullptr;
    /** @brief Rodyklė į rezervuoto bloko pabaigą. */
    iterator          limit = nullptr;
    /** @brief Atminties valdytojas. */
    std::allocator<T> alloc;

    /** @brief `allocator_traits` sinoniminė deklaracija patogumui. */
    using alloc_traits = std::allocator_traits<std::allocator<T>>;

    /**
     * @brief Inicializuoja tuščią masyvą (nulinės rodyklės).
     */
    void create() { dat = avail = limit = nullptr; }

    /**
     * @brief Inicializuoja masyvą iš `n` kopijų reikšmės `val`.
     *
     * @param n    Elementų skaičius.
     * @param val  Pradinė reikšmė.
     */
    void create(size_type n, const T& val) {
        dat = alloc.allocate(n);
        limit = avail = dat + n;
        std::uninitialized_fill(dat, limit, val);
    }

    /**
     * @brief Inicializuoja masyvą iš iteratorių diapazono.
     *
     * @tparam InputIt  Įvesties iteratoriaus tipas.
     * @param first     Diapazono pradžia.
     * @param last      Diapazono pabaiga.
     */
    template <typename InputIt>
    void create(InputIt first, InputIt last) {
        size_type n = static_cast<size_type>(std::distance(first, last));
        dat         = alloc.allocate(n);
        limit = avail = std::uninitialized_copy(first, last, dat);
    }

    /**
     * @brief Sunaikina visus elementus ir atlaisvina atmintį.
     *
     * Po kvietimo `dat`, `avail`, `limit` yra `nullptr`.
     */
    void uncreate() {
        if (dat) {
            for (iterator it = avail; it != dat; )
                alloc_traits::destroy(alloc, --it);
            alloc.deallocate(dat, static_cast<size_type>(limit - dat));
        }
        dat = avail = limit = nullptr;
    }

    /**
     * @brief Perkelia visą turinį į naują atminties bloką duotos talpos.
     *
     * Senasis blokas atlaisvinamas.
     *
     * @param new_capacity  Nauja talpa elementais.
     */
    void reallocate(size_type new_capacity) {
        iterator new_dat   = alloc.allocate(new_capacity);
        iterator new_avail = std::uninitialized_move(dat, avail, new_dat);
        uncreate();
        dat   = new_dat;
        avail = new_avail;
        limit = dat + new_capacity;
    }

    /**
     * @brief Automatiškai padidina talpą, kai pritrūksta vietos.
     *
     * Nauja talpa — dvigubai didesnė už esamą (mažiausiai 1 arba `min_capacity`).
     *
     * @param min_capacity  Minimali pageidaujama talpa (numatytoji — 0).
     */
    void grow(size_type min_capacity = 0) {
        size_type new_cap = std::max({ min_capacity, 2 * capacity(), size_type{1} });
        reallocate(new_cap);
    }

    /**
     * @brief Pastumia elementus nuo `pos` iki `avail` dešinėn per `n` pozicijų.
     *
     * Teisingai tvarko ribą tarp inicializuotos ir neinicializuotos atminties prie `avail`.
     *
     * @param pos  Iteratorius į pirmą stumtiną elementą.
     * @param n    Pozicijų skaičius, per kiek stumti.
     */
    void shift_right(iterator pos, size_type n) {
        if (pos == avail) return;
        size_type tail = static_cast<size_type>(avail - pos);
        if (n >= tail) {
            // Visi elementai [pos, avail) patenka į neinicializuotą sritį
            std::uninitialized_move(pos, avail, pos + n);
        } else {
            // Paskutiniai n elementų patenka į neinicializuotą sritį
            std::uninitialized_move(avail - n, avail, avail);
            // Likę elementai stumiami inicializuotoje srityje
            std::move_backward(pos, avail - n, avail);
        }
    }
};

// ── Laisvosios funkcijos ──────────────────────────────────────────────────────

/**
 * @brief Nenarė funkcija keitimuisi dviem `Vector` objektais.
 *
 * Iškviečia `a.swap(b)`, O(1) sudėtingumas.
 *
 * @tparam T  Elementų tipas.
 * @param a   Pirmas masyvas.
 * @param b   Antras masyvas.
 */
template <VectorElement T>
void swap(Vector<T>& a, Vector<T>& b) noexcept { a.swap(b); }

/**
 * @brief Pašalina visus elementus, lygius `value` (C++20).
 *
 * Viduje naudoja `std::remove` + `Vector::erase`.
 *
 * @tparam T      Elementų tipas.
 * @tparam U      Lyginamos reikšmės tipas.
 * @param v       Masyvas, iš kurio šalinama.
 * @param value   Reikšmė, kurią atitinkantys elementai šalinami.
 * @return        Pašalintų elementų skaičius.
 */
template <VectorElement T, typename U>
typename Vector<T>::size_type erase(Vector<T>& v, const U& value) {
    auto it = std::remove(v.begin(), v.end(), value);
    auto n  = static_cast<typename Vector<T>::size_type>(v.end() - it);
    v.erase(it, v.end());
    return n;
}

/**
 * @brief Pašalina visus elementus, tenkinančius predikato sąlygą (C++20).
 *
 * Viduje naudoja `std::remove_if` + `Vector::erase`.
 *
 * @tparam T     Elementų tipas.
 * @tparam Pred  Unarinio predikato tipas.
 * @param v      Masyvas, iš kurio šalinama.
 * @param pred   Predikatas; elementas šalinamas, jei `pred(elem)` grąžina `true`.
 * @return       Pašalintų elementų skaičius.
 */
template <VectorElement T, typename Pred>
typename Vector<T>::size_type erase_if(Vector<T>& v, Pred pred) {
    auto it = std::remove_if(v.begin(), v.end(), pred);
    auto n  = static_cast<typename Vector<T>::size_type>(v.end() - it);
    v.erase(it, v.end());
    return n;
}

#endif // VECTOR_H