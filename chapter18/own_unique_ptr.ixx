//
// Created by Dmytrenko Kyrylo on 08.08.2026.
//


module;
#include "../error.h"

#include <iostream>
#include <ranges>
#include <vector>

export module chapter18.own_unique_ptr;

export namespace ch18::own_unique_ptr {

template<typename T>
struct unique_ptr {
  // TODO implement only constructor, destructor, release(); operators ->, *; delete copy constructor and assigment

  unique_ptr() {
    element = static_cast<T*>(operator new(sizeof(T)));
    std::construct_at(element);
  }

  unique_ptr(T&& el) {
    element = static_cast<T*>(operator new(sizeof(T)));
    std::construct_at(element,std::move(el));
  }

  ~unique_ptr() {
    std::destroy_at(element);
    operator delete(element);
  }

  T* operator*(){return element;}
  T* operator->(){return element;}


  unique_ptr(const T&) = delete;
  unique_ptr& operator=(const T&) = delete;



  T* release() {
    T* pointer = element;
    element = nullptr;
    return pointer;
  }


private:
  T* element;
};

}
