//
// Created by Dmytrenko Kyrylo on 23.07.2026.
//

module;
#include "../error.h"

#include <iostream>
#include <ranges>
#include <vector>

export module chapter18.vector;

export namespace ch18::vector {

template <typename T> struct allocator {
  virtual ~allocator() = default;
  virtual T *allocate(int size) = 0;

  virtual void destroy(T* element) { element->~T(); }
  virtual void deallocate(T *elements, int size_initialized_elements) = 0;
};

template<typename T> struct simple_allocator : allocator<T>{
  T* allocate(int size) override {
    return static_cast<T*>(malloc(size * sizeof(T)));
  }

  void deallocate(T *elements, int size_initialized_elements) override {
    if constexpr (!std::is_trivially_destructible_v<T>) {
      for (int i = size_initialized_elements-1; i >=0 ; --i) {
        allocator<T>::destroy(&elements[i]);
      }
    }


    free(elements);
  }
};

template <typename T> struct new_allocator : allocator<T>{
  T *allocate(int size) override{
    return static_cast<T*>(::operator new(size * sizeof(T)));
  }

  void deallocate(T *elements, int size_initialized_elements) override {
    if constexpr (!std::is_trivially_destructible_v<T>) {
      for (int i = size_initialized_elements-1; i >=0 ; --i)
        allocator<T>::destroy(&elements[i]);
    }

    ::operator delete(elements);
  }
};

//template <typename T, typename A = new_allocator<T>>
template <typename T, typename A = simple_allocator<T>>
//template <typename T, typename A = allocator<T>>
struct Vector {
  Vector();
  Vector(int sz, T def = T{});
  Vector(std::initializer_list<T> lst);
  ~Vector();

  Vector(const Vector &v);
  Vector(Vector &&v) noexcept;

  Vector &operator=(const Vector &v);
  Vector &operator=(Vector &&v) noexcept;

  void reserve(int new_alloc);
  void reverse();
  void resize(int new_size, T def = T{});
  void push_back(const T& new_el);
  void push_back(T&& new_el);

  [[nodiscard]] int size() const { return sz; }

  T &operator[](int i);
  const T &operator[](int i) const;

  [[nodiscard]] T *begin() const { return elem; } // iteration support
  [[nodiscard]] T *end() const { return elem + sz; }



private:
  A allocator;
  int sz = 0;
  int cap = 0;
  T *elem = nullptr;

};

template <typename T, typename A = new_allocator<T>>
void print_v(const Vector<T, A> &v, const std::string &intro = "");

template <typename T, typename A = new_allocator<T>>
Vector<T,A> create_v(std::initializer_list<T> elements);

template <typename T, typename A = new_allocator<T>>
std::ostream& operator<<(std::ostream& os, const Vector<T,A> &v);

template <typename T, typename A = new_allocator<T>>
std::istream& operator>>(std::istream& is, Vector<T,A> &v);

template <typename T>
void add(Vector<T>& v1, const Vector<T>& v2);

template <typename T, typename U>
requires std::convertible_to<T, double> &&
std::convertible_to<U,double>
double sum_multiply(const Vector<T>& vt, const Vector<U>& vu); // ex 2

} // namespace ch18::vector


namespace ch18::vector {



template <typename T, typename A> Vector<T, A>::~Vector() {
  allocator.deallocate(elem,sz);
  elem = nullptr;
}

template <typename T, typename A> Vector<T, A>::Vector() : sz(0), cap(4 * 2) {
  elem = allocator.allocate(cap);
  for (int i = 0; i < sz; ++i) {
    std::construct_at(elem+i);
  }
}

template <typename T, typename A>
Vector<T, A>::Vector(std::initializer_list<T> lst)
    : sz(static_cast<int>(lst.size())), cap(sz),
elem(allocator.allocate(cap)) {
  int iterator = 0;

  for (const T& val : lst) {
    std::construct_at(elem+iterator,val);
    ++iterator;
  }
}

template <typename T, typename A>
Vector<T, A>::Vector(const Vector &v)
    : sz(v.size()), cap(v.cap), elem(allocator.allocate(cap)) {
  std::uninitialized_copy(v.elem, v.elem+v.size(), elem);
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
  std::uninitialized_copy(v.elem,v.elem+v.sz,new_array);

  allocator.deallocate(elem, sz);
  cap = v.cap;
  sz = v.sz;

  elem = new_array;

  return *this;
}

template <typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(Vector &&v) noexcept {
  allocator.deallocate(elem, sz);
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

  std::uninitialized_move(elem,elem+sz,new_array);

  // TODO may be errors because elements have been uninitialized after move
  allocator.deallocate(elem,sz);

  elem = new_array;
  cap = new_alloc;
}

template <typename T, typename A> void Vector<T, A>::reverse() {
  T* result = allocator.allocate(cap);

  for (int i = 0; i < this->sz; ++i) {
     std::construct_at(result+(sz-(i+1)),elem[i]);
  }

  allocator.deallocate(elem, sz);
  elem = result;

}

template <typename T, typename A>
void Vector<T, A>::resize(int new_size, T def) {
  reserve(new_size);

  for (int i = sz; i < new_size; ++i)
    std::construct_at(elem+i, def);


  sz = new_size;
}

template <typename T, typename A> void Vector<T, A>::push_back(const T& new_el) {
  if (sz == cap)
    reserve(cap==0 ? 1 : sz * 2);

   std::construct_at(elem+sz, new_el);
  ++sz;
}
template <typename T, typename A> void Vector<T, A>::push_back(T &&new_el) {
  if (sz == cap)
    reserve(cap==0 ? 1 : sz * 2);

  *(elem+sz) = std::move(new_el);
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

  for (int i = 0; i < sz; ++i)
    std::construct_at(elem+i,def);

}

template <typename T, typename A> T &Vector<T, A>::operator[](int i) {
  if (i >= sz || i < 0)
    error("bad iterator");

  return elem[i];
}

template <typename T, typename A>
Vector<T,A> create_v(std::initializer_list<T> elements) {
  return Vector<T,A>(elements);
}

template <typename T, typename A>
void print_v(const Vector<T, A> &v, const std::string &intro) {
  std::cout << intro;
  for (const auto &el : v) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

template <typename T, typename A>
std::ostream &operator<<(std::ostream &os, const Vector<T, A> &v) {
  os << "{ ";
  for (const T& element : v) {
    os << element << ", ";
  }
  os << "\b\b }";

  return os;
}


template <typename T, typename A>
std::istream &operator>>(std::istream &is, Vector<T, A> &v) { // { val, val, val} format.
  char separator;
  is >> separator;
  T temp;

  while (is && separator != '}') {
    is >> temp >> separator;
    v.push_back(temp);
  }

  return is;

}

template <typename T>
void add(Vector<T>& v1, const Vector<T>& v2) {
  const int upper_limit = v1.size() <= v2.size() ? v1.size() : v2.size();
  for (int i = 0; i < upper_limit; ++i)
    v1[i] += v2[i];

}


template <typename T, typename U>
requires std::convertible_to<T, double> &&
std::convertible_to<U,double>
double sum_multiply(const Vector<T> &vt, const Vector<U> &vu) {
  double result = 0;
  const int upper_limit = vt.size() <= vu.size() ? vt.size() : vu.size();

  for (int i = 0; i < upper_limit; ++i)
    result += static_cast<double>(vt[i]) * static_cast<double>(vu[i]);

  return result;
}
} // namespace