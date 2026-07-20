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

template <typename T, typename U>
void suspicious();


struct Somethink {
  Somethink();
  ~Somethink();
  Somethink(const Somethink&);
  Somethink( Somethink&&);

  Somethink& operator=(const Somethink&);
  Somethink& operator=( Somethink&&);


private:
  char* field1;
  std::string field2;
};

void test1();
}

export namespace ch18::vector {

template <typename T> struct allocator {
  T *allocate(int size);

  void destroy(T* element);
  void deallocate(T *elements, int size_initialized_elements);
};

 template <typename T, typename A = allocator<T>>
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
template <typename T, typename A = allocator<T>>
void print_v(const Vector<T, A> &v, const std::string &intro = "");
template <typename T, typename A = allocator<T>>
Vector<T,A> create_v(std::initializer_list<T> elements);
} // namespace ch18::vector

namespace ch18::try_ {
template <typename T, typename U>
void suspicious() {
  constexpr int count = 10;
  T* p = static_cast<T*>(operator new (sizeof(T) * count));
  U* q = static_cast<U*>(operator new (sizeof(U) * count));

  try {
    for (int i = 0 ; i < count; ++i) {
      std::construct_at(p+i,static_cast<T>(i+1));
      std::construct_at(q+i, static_cast<U>(i*i));

      std::cout << "p[" << i << "] = " << p[i] << "   "
        << "q[" << i << "] = " << q[i] << std::endl;
    }
    throw std::runtime_error("Error");
  }
  catch (const std::exception& ex) {
    std::cerr << "Caught!";
    operator delete (p);
    operator delete(q);
    throw;
  }

  catch (...) {
    std::destroy(p, p+count);
    std::destroy(q,q+count);
    std::cerr << "Caught!";
    operator delete (p);
    operator delete(q);
    throw;
  }


  std::destroy(p, p+count);
  std::destroy(q,q+count);
  operator delete (p);
  operator delete(q);

}
}


namespace ch18::vector {
template <typename T> T *allocator<T>::allocate(int size) {
  return static_cast<T*>(::operator new(size * sizeof(T)));
}
template <typename T> void allocator<T>::destroy(T *element) {
  element->~T();;
}

// TODO may be deallocate must be shorter(without "if constexpr" block)
template <typename T> void allocator<T>::deallocate(T *elements, int  size_initialized_elements) {
  if constexpr (!std::is_trivially_destructible_v<T>)
    for (int i = size_initialized_elements-1; i >=0 ; --i)
      destroy(&elements[i]);


  ::operator delete(elements);
}

template <typename T, typename A> Vector<T, A>::~Vector() {
  allocator.deallocate(elem,sz);
}

template <typename T, typename A> Vector<T, A>::Vector() : sz(4), cap(sz * 2) {
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