//
// Created by Dmytrenko Kyrylo on 11.07.2026.
//
module;
#include "../error.h"

#include <iostream>
#include <ranges>
#include <vector>



export module chapter18;
export import chapter18.vector;


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


export namespace ch18::drill {
void test();

template <class T>
struct S {
  S() : val(){}
  S(const T& v) : val(v){}
  ~S(){val.~T();}
  T& access();
  const T& access() const;

  S& operator=(const T&);

private:
  T val;
};

template<typename T>
void read_val(T& v);


} // namespace ch18::drill

namespace ch18::drill {
template <class T> T &S<T>::access() {
  return val;
}
template <class T> const T &S<T>::access() const {
  return val;
}
template <class T> S<T>& S<T>::operator=(const T & for_copy) {
  T temp = for_copy;
  std::swap(temp,val);
  return *this;
}
template <typename T> void read_val(T &v) {
  std::cin >> v;
}
}

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


