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

template <typename T> struct allocator {
  T *allocate(int size);
  void deallocate(T *elements);
};

 template <typename T, typename A = allocator<T>>
struct Vector {
  Vector();
   Vector(int sz, T def = T{});
  Vector(std::initializer_list<T> lst);

  Vector(const Vector &v);
  Vector(Vector &&v) noexcept;

  Vector &operator=(const Vector &v);
  Vector &operator=(Vector &&v) noexcept;

  void reserve(int new_alloc);
   void reverse();
  void resize(int new_size, T def = T{});
  void push_back(T new_el);

  [[nodiscard]] int size() const { return sz; }

  T &operator[](int i);
  const T &operator[](int i) const;

  [[nodiscard]] T *begin() const { return elem; } // iteration support
  [[nodiscard]] T *end() const { return elem + sz; }

  ~Vector();

private:
  int sz = 0;
  int cap = 0;
  T *elem = nullptr;
  A allocator;
};
template <typename T, typename A = allocator<T>>
void print_v(const Vector<T, A> &v, const std::string &intro = "");
template <typename T, typename A = allocator<T>>
Vector<T,A> create_v(std::initializer_list<T> elements);
} // namespace ch18::vector


namespace ch18::vector {
template <typename T> T *allocator<T>::allocate(int size) {
  T *el = new T[size];
  return el;
}

template <typename T> void allocator<T>::deallocate(T *elements) {
    delete[] elements;
}

template <typename T, typename A> Vector<T, A>::~Vector() {
  allocator.deallocate(elem);
}

template <typename T, typename A> Vector<T, A>::Vector() : sz(4), cap(sz * 2) {
  elem = allocator.allocate(cap);
  for (int i = 0; i < sz; ++i) {
    elem[i] = T{};
  }
}

template <typename T, typename A>
Vector<T, A>::Vector(std::initializer_list<T> lst)
    : sz(static_cast<int>(lst.size())), cap(sz),
elem(allocator.allocate(cap)) {
  int iterator = 0;

  for (T val : lst) {
    elem[iterator] = val;
    ++iterator;
  }
}

template <typename T, typename A>
Vector<T, A>::Vector(const Vector &v)
    : sz(v.size()), cap(v.cap), elem(allocator.allocate(cap)) {
  for (int i = 0; i < sz; ++i)
    elem[i] = v.elem[i];
}

template <typename T, typename A>
Vector<T, A>::Vector(Vector &&v) noexcept
    : sz(v.size()), cap(v.cap), elem(v.elem) {
  v.elem = nullptr;
  v.sz = 0;
  v.cap = 0;
}

template <typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(const Vector &v) {
  T *new_array = allocator.allocate(v.cap);

  for (int i = 0; i < v.sz; ++i)
    new_array[i] = v.elem[i];

  allocator.deallocate(elem, cap);
  cap = v.cap;
  sz = v.sz;

  elem = new_array;

  return *this;
}

template <typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(Vector &&v) noexcept {
  allocator.deallocate(elem, cap);
  sz = v.sz;
  cap = v.cap;

  elem = v.elem;

  v.elem = nullptr;
  v.sz = 0;
  v.cap = 0;

  return *this;
}

template <typename T, typename A> void Vector<T, A>::reserve(int new_alloc) {
  if (new_alloc <= cap)
    return;

  T *new_array = allocator.allocate(new_alloc);

  for (int i = 0; i < size(); ++i) {
    new_array[i] = elem[i];
  }
  allocator.deallocate(elem);

  elem = new_array;
  cap = new_alloc;
}

template <typename T, typename A> void Vector<T, A>::reverse() {
  T* result = allocator.allocate(cap);

  for (int i = 0; i < this->sz; ++i) {
    result[sz-(i+1)] = elem[i];
  }

  allocator.deallocate(elem);
  elem = result;

}

template <typename T, typename A>
void Vector<T, A>::resize(int new_size, T def) {
  reserve(new_size);

  for (int i = sz; i < new_size; ++i)
    elem[i] = def;

  sz = new_size;
}

template <typename T, typename A> void Vector<T, A>::push_back(T new_el) {
  if (sz == cap)
    reserve(sz * 2);

  elem[sz] = new_el;
  ++sz;
}

template <typename T, typename A>
const T &Vector<T, A>::operator[](int i) const {
  if (i >= sz || i < 0)
    error("bad iterator");

  return elem[i];
}



template <typename T, typename A> Vector<T, A>::Vector(int s, T def) {
  if (s < 0)
    error("bad size");
  sz = s;
  elem = allocator.allocate(sz);
  cap = s;

  for (int i = 0; i < sz; ++i) elem[i] = def;

}

template <typename T, typename A> T &Vector<T, A>::operator[](int i) {
  if (i >= sz || i < 0)
    error("bad iterator");

  return elem[i];
}

template <typename T, typename A>
Vector<T,A> create_v(std::initializer_list<T> elements) {
  return Vector<T>(elements);
}

template <typename T, typename A>
void print_v(const Vector<T, A> &v, const std::string &intro) {
  std::cout << intro;
  for (const auto &el : v) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

} // namespace