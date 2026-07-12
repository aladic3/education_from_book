//
// Created by Dmytrenko Kyrylo on 11.07.2026.
//
module;
#include "../error.h"

#include <iostream>
#include <ranges>
#include <vector>

export module chapter18;

export namespace ch18::try_ {
  void test1();
}


namespace ch18::vector {

template <typename  T>
struct  allocator {
  T* allocate(int size);
  void deallocate(T* elements, int size);
};


export template <typename  T, typename A = allocator<T>>

    struct Vector {
      Vector();
      explicit Vector(int sz);
      Vector(std::initializer_list<T> lst);

      Vector(const Vector& v);
      Vector(Vector&& v) noexcept;

      Vector& operator=(const Vector& v);
      Vector& operator=(Vector&& v) noexcept;

      void reserve(int new_alloc);
      void resize(int new_size, T def = T{});
      void push_back(T new_el);

      [[nodiscard]] int size() const {return sz;}


      T& operator[](int i);
      const T& operator[](int i) const;

      [[nodiscard]] T* begin() const {return elem;} // iteration support
      [[nodiscard]] T* end() const {return elem+sz;}

      ~Vector();
    private:
      int sz = 0;
      int cap = 0;
      T* elem = nullptr;
      A allocator;

    };

} // namespace ch17::try_


