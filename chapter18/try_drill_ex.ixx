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


export namespace ch18::vector {

template <typename  T>
struct  allocator {

};

template<typename  T, typename A = allocator<T>>

    struct Vector {
      Vector();
      explicit Vector(int sz);
      Vector(std::initializer_list<double> lst);

      Vector(const Vector& v);
      Vector(Vector&& v) noexcept;

      Vector& operator=(const Vector& v);
      Vector& operator=(Vector&& v) noexcept;

      void reserve(int new_alloc);
      void resize(int new_size);
      void push_back(double new_el);

      [[nodiscard]] int size() const {return sz;}


      double& operator[](int i);
      const double& operator[](int i) const;

      [[nodiscard]] double* begin() const {return elem;} // iteration support
      [[nodiscard]] double* end() const {return elem+sz;}

      ~Vector();
    private:
      int sz = 0;
      int cap = 0;
      double* elem = nullptr;

    };

} // namespace ch17::try_


