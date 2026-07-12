//
// Created by Dmytrenko Kyrylo on 11.07.2026.
//
module;
#include "../error.h"

#include <iostream>
#include <vector>

module chapter18;


namespace ch18::vector{
template <typename T>
T* allocator<T>::allocate(int size) {
    T* el = new T[size];
    return el;
}

template <typename T>
void allocator<T>::deallocate(T* elements, int size) {
    for (int i = 0; i < size; ++i) {
        delete elements[i];
    }
}

template <typename T, typename A = allocator<T>>
Vector<T,A>::~Vector() {
        allocator.deallocate(elem,cap);
    }


template <typename T, typename A = allocator<T>>
Vector<T,A>::Vector() : sz(4), cap(sz*2) {
        elem = allocator.allocate(cap);
        for (int i = 0; i < sz; ++i) {
            elem[i] = T{};
        }
    }

template <typename T, typename A = allocator<T>>
Vector<T,A>::Vector(std::initializer_list<T> lst) : sz(static_cast<int>(lst.size())),
        cap(sz), elem(new double[cap]){
            int iterator = 0;

            for (T val : lst) {
                elem[iterator] = val;
                ++iterator;
            }
    }

template <typename T, typename A = allocator<T>>
Vector<T,A>::Vector(const Vector &v): sz(v.size()), cap(v.cap),
elem(allocator.allocate(cap)) {
        for (int i = 0; i < sz; ++i)
            elem[i] = v.elem[i];
    }

template <typename T, typename A = allocator<T>>
Vector<T,A>::Vector(Vector &&v) noexcept : sz(v.size()), cap(v.cap), elem(v.elem) {
        v.elem = nullptr;
        v.sz = 0;
        v.cap = 0;
    }

template <typename T, typename A = allocator<T>>
    Vector<T,A>& Vector<T,A>::operator=(const Vector &v) {
        T* new_array = allocator.allocate(v.cap);

        for (int i = 0; i < v.sz; ++i)
             new_array[i] = v.elem[i];

        allocator.deallocate(elem,cap);
        cap = v.cap;
        sz = v.sz;

        elem = new_array;

        return *this;
    }

template <typename T, typename A = allocator<T>>
    Vector<T,A>& Vector<T,A>::operator=(Vector &&v) noexcept{
        allocator.deallocate(elem,cap);
        sz = v.sz;
        cap = v.cap;

        elem = v.elem;

        v.elem = nullptr;
        v.sz = 0;
        v.cap = 0;

        return *this;
    }

template <typename T, typename A = allocator<T>>
    void Vector<T,A>::reserve(int new_alloc) {
        if (new_alloc <= cap) return;

        T* new_array = allocator.allocate(new_alloc);

        for (int i = 0; i < size(); ++i) {
            new_array[i] = elem[i];
        }
        allocator.deallocate(elem,cap);

        elem = new_array;
        cap = new_alloc;

    }


template <typename T, typename A = allocator<T>>
    void Vector<T,A>::resize(int new_size, T def) {
        reserve(new_size);

        for (int i = sz; i < new_size; ++i)
            elem[i] = def;

        sz = new_size;
    }


template <typename T, typename A = allocator<T>>
    void Vector<T,A>::push_back(T new_el) {
        if (sz == cap)
            reserve(sz*2);

        elem[sz] = new_el;
        ++sz;
    }


template <typename T, typename A = allocator<T>>
    const T& Vector<T,A>::operator[](int i) const {
        if (i >= sz || i < 0 )
            error("bad iterator");

        return elem[i];
    }


template <typename T, typename A = allocator<T>>
    Vector<T,A>::Vector(int s) {
        if (s < 0)
            error("bad size");
        sz = s;
        elem = allocator.allocate(sz);
        cap = s;
    }


template <typename T, typename A = allocator<T>>
    T& Vector<T,A>::operator[](int i) {
        if (i >= sz || i < 0 )
            error("bad iterator");

        return elem[i];
    }


template <typename T, typename A = allocator<T>>
    Vector<T,A> create_v(std::initializer_list<T> elements) {
        return Vector(elements);
    }

template <typename T, typename A = allocator<T>>
    void print_v(const Vector<T,A>& v, const std::string & intro = "") {
        std::cout << intro;
        for (const auto& el : v) {
            std::cout << el << '\t';
        }
        std::cout << '\n';
    }
}