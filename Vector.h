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

// ── Concept: T must be movable to live in a Vector ───────────────────────────
template <typename T>
concept VectorElement = std::movable<T>;

template <VectorElement T>
class Vector {
public:
    // ── Member types ─────────────────────────────────────────────────────────
    using value_type             = T;
    using allocator_type         = std::allocator<T>;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = typename std::allocator_traits<std::allocator<T>>::pointer;
    using const_pointer          = typename std::allocator_traits<std::allocator<T>>::const_pointer;
    using iterator               = T*;
    using const_iterator         = const T*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // ── Constructors ─────────────────────────────────────────────────────────

    Vector() { create(); }

    explicit Vector(size_type n, const T& val = T{}) { create(n, val); }

    Vector(const Vector& other) { create(other.begin(), other.end()); }

    Vector(Vector&& other) noexcept
        : dat(other.dat), avail(other.avail), limit(other.limit)
    {
        other.dat = other.avail = other.limit = nullptr;
    }

    template <std::input_iterator InputIt>
    Vector(InputIt first, InputIt last) { create(first, last); }

    Vector(std::initializer_list<T> il) { create(il.begin(), il.end()); }

    ~Vector() { uncreate(); }

    // ── Assignment ───────────────────────────────────────────────────────────

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            uncreate();
            create(other.begin(), other.end());
        }
        return *this;
    }

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

    Vector& operator=(std::initializer_list<T> il) {
        uncreate();
        create(il.begin(), il.end());
        return *this;
    }

    // Implicit conversions
    operator std::vector<T>()        const { return std::vector<T>(dat, avail); }
    operator std::span<T>()                { return std::span<T>(dat, avail); }
    operator std::span<const T>()    const { return std::span<const T>(dat, avail); }

    // ── assign ───────────────────────────────────────────────────────────────

    template <std::input_iterator InputIt>
    void assign(InputIt first, InputIt last) {
        uncreate();
        create(first, last);
    }

    void assign(size_type n, const value_type& val) {
        uncreate();
        create(n, val);
    }

    void assign(std::initializer_list<value_type> il) {
        uncreate();
        create(il.begin(), il.end());
    }

    // assign_range (C++23)
    template <std::ranges::input_range R>
    void assign_range(R&& r) {
        uncreate();
        create(std::ranges::begin(r), std::ranges::end(r));
    }

    // ── get_allocator ────────────────────────────────────────────────────────

    allocator_type get_allocator() const noexcept { return alloc; }

    // ── Element access ───────────────────────────────────────────────────────

    reference       operator[](size_type n)       { return dat[n]; }
    const_reference operator[](size_type n) const { return dat[n]; }

    reference at(size_type n) {
        if (n >= size())
            throw std::out_of_range("Vector::at: index out of range");
        return dat[n];
    }
    const_reference at(size_type n) const {
        if (n >= size())
            throw std::out_of_range("Vector::at: index out of range");
        return dat[n];
    }

    reference       front()       { return dat[0]; }
    const_reference front() const { return dat[0]; }

    reference       back()       { return avail[-1]; }
    const_reference back() const { return avail[-1]; }

    value_type*       data() noexcept       { return dat; }
    const value_type* data() const noexcept { return dat; }

    // ── Iterators ────────────────────────────────────────────────────────────

    iterator       begin()        noexcept { return dat; }
    const_iterator begin()  const noexcept { return dat; }
    const_iterator cbegin() const noexcept { return dat; }

    iterator       end()        noexcept { return avail; }
    const_iterator end()  const noexcept { return avail; }
    const_iterator cend() const noexcept { return avail; }

    reverse_iterator       rbegin()        noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    reverse_iterator       rend()        noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend()  const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    // ── Capacity ─────────────────────────────────────────────────────────────

    [[nodiscard]] bool      empty()    const noexcept { return dat == avail; }
    [[nodiscard]] size_type size()     const noexcept { return static_cast<size_type>(avail - dat); }
    [[nodiscard]] size_type capacity() const noexcept { return static_cast<size_type>(limit - dat); }
    [[nodiscard]] size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

    void reserve(size_type n) {
        if (n > capacity())
            reallocate(n);
    }

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

    // ── Modifiers ────────────────────────────────────────────────────────────

    void push_back(const value_type& val) {
        if (avail == limit) grow();
        alloc_traits::construct(alloc, avail++, val);
    }

    void push_back(value_type&& val) {
        if (avail == limit) grow();
        alloc_traits::construct(alloc, avail++, std::move(val));
    }

    // emplace_back: construct the object in-place, zero copies
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (avail == limit) grow();
        alloc_traits::construct(alloc, avail++, std::forward<Args>(args)...);
        return back();
    }

    // append_range (C++23)
    template <std::ranges::input_range R>
    void append_range(R&& r) {
        for (auto&& elem : r)
            push_back(std::forward<decltype(elem)>(elem));
    }

    void pop_back() {
        if (avail != dat)
            alloc_traits::destroy(alloc, --avail);
    }

    void clear() noexcept {
        for (iterator it = dat; it != avail; ++it)
            alloc_traits::destroy(alloc, it);
        avail = dat;
    }

    // insert: single lvalue
    iterator insert(const_iterator cpos, const value_type& val) {
        return insert(cpos, size_type{1}, val);
    }

    // insert: single rvalue
    iterator insert(const_iterator cpos, value_type&& val) {
        size_type index = static_cast<size_type>(cpos - dat);
        if (avail == limit) grow(size() + 1);
        iterator pos = dat + index;
        shift_right(pos, 1);
        alloc_traits::construct(alloc, pos, std::move(val));
        ++avail;
        return pos;
    }

    // insert: n copies — strong exception guarantee via copy-and-swap
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

    // insert: iterator range — strong exception guarantee via copy-and-swap
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

    // insert: initializer_list
    iterator insert(const_iterator cpos, std::initializer_list<value_type> il) {
        return insert(cpos, il.begin(), il.end());
    }

    // insert_range (C++23)
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

    // emplace: construct in-place at arbitrary position
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

    iterator erase(const_iterator cpos) {
        iterator pos = const_cast<iterator>(cpos);
        std::move(pos + 1, avail, pos);
        alloc_traits::destroy(alloc, --avail);
        return pos;
    }

    iterator erase(const_iterator cfirst, const_iterator clast) {
        iterator first     = const_cast<iterator>(cfirst);
        iterator last      = const_cast<iterator>(clast);
        iterator new_avail = std::move(last, avail, first);
        for (iterator it = new_avail; it != avail; ++it)
            alloc_traits::destroy(alloc, it);
        avail = new_avail;
        return first;
    }

    void swap(Vector& other) noexcept {
        std::swap(dat,   other.dat);
        std::swap(avail, other.avail);
        std::swap(limit, other.limit);
    }

    // ── Comparison operators ─────────────────────────────────────────────────

    bool operator==(const Vector& other) const {
        return size() == other.size() && std::equal(begin(), end(), other.begin());
    }

    // operator<=> (C++20 three-way comparison)
    auto operator<=>(const Vector& other) const {
        return std::lexicographical_compare_three_way(
            begin(), end(), other.begin(), other.end());
    }

    // Legacy relational operators (derived from <=>)
    bool operator!=(const Vector& other) const { return !(*this == other); }
    bool operator< (const Vector& other) const { return (*this <=> other) < 0; }
    bool operator<=(const Vector& other) const { return (*this <=> other) <= 0; }
    bool operator> (const Vector& other) const { return (*this <=> other) > 0; }
    bool operator>=(const Vector& other) const { return (*this <=> other) >= 0; }

private:
    iterator          dat   = nullptr;
    iterator          avail = nullptr;
    iterator          limit = nullptr;
    std::allocator<T> alloc;
    using alloc_traits = std::allocator_traits<std::allocator<T>>;

    void create() { dat = avail = limit = nullptr; }

    void create(size_type n, const T& val) {
        dat = alloc.allocate(n);
        limit = avail = dat + n;
        std::uninitialized_fill(dat, limit, val);
    }

    template <typename InputIt>
    void create(InputIt first, InputIt last) {
        size_type n = static_cast<size_type>(std::distance(first, last));
        dat         = alloc.allocate(n);
        limit = avail = std::uninitialized_copy(first, last, dat);
    }

    void uncreate() {
        if (dat) {
            for (iterator it = avail; it != dat; )
                alloc_traits::destroy(alloc, --it);
            alloc.deallocate(dat, static_cast<size_type>(limit - dat));
        }
        dat = avail = limit = nullptr;
    }

    void reallocate(size_type new_capacity) {
        iterator new_dat   = alloc.allocate(new_capacity);
        iterator new_avail = std::uninitialized_move(dat, avail, new_dat);
        uncreate();
        dat   = new_dat;
        avail = new_avail;
        limit = dat + new_capacity;
    }

    void grow(size_type min_capacity = 0) {
        size_type new_cap = std::max({ min_capacity, 2 * capacity(), size_type{1} });
        reallocate(new_cap);
    }

    // Shift [pos, avail) right by n slots, correctly handling the
    // initialized/uninitialized boundary at avail.
    void shift_right(iterator pos, size_type n) {
        if (pos == avail) return;
        size_type tail = static_cast<size_type>(avail - pos);
        if (n >= tail) {
            // All of [pos, avail) moves into uninitialized space
            std::uninitialized_move(pos, avail, pos + n);
        } else {
            // Back n elements move into uninitialized space
            std::uninitialized_move(avail - n, avail, avail);
            // Remaining elements shift within initialized space
            std::move_backward(pos, avail - n, avail);
        }
    }
};

// ── Non-member swap ───────────────────────────────────────────────────────────
template <VectorElement T>
void swap(Vector<T>& a, Vector<T>& b) noexcept { a.swap(b); }

// ── Non-member erase / erase_if (C++20) ──────────────────────────────────────
template <VectorElement T, typename U>
typename Vector<T>::size_type erase(Vector<T>& v, const U& value) {
    auto it = std::remove(v.begin(), v.end(), value);
    auto n  = static_cast<typename Vector<T>::size_type>(v.end() - it);
    v.erase(it, v.end());
    return n;
}

template <VectorElement T, typename Pred>
typename Vector<T>::size_type erase_if(Vector<T>& v, Pred pred) {
    auto it = std::remove_if(v.begin(), v.end(), pred);
    auto n  = static_cast<typename Vector<T>::size_type>(v.end() - it);
    v.erase(it, v.end());
    return n;
}

#endif // VECTOR_H