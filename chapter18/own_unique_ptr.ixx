//
// Created by Dmytrenko Kyrylo on 08.08.2026.
//


module;

#include "../error.h"

#include <iostream>
#include <ranges>
#include <vector>


export module chapter18.own_unique_ptr;
import chapter18.vector;


export namespace ch18::own_unique_ptr {



template<typename T, typename A = vector::simple_allocator<T>>
struct unique_ptr {
  // TODO implement only constructor, destructor, release(); operators ->, *; delete copy constructor and assigment

  unique_ptr() {
    element = allocator.allocate();
    std::construct_at(element);
  }

  unique_ptr(T&& el) {
    element = allocator.allocate();
    std::construct_at(element,std::move(el));
  }

  ~unique_ptr() {
    allocator.deallocate(element);
  }

  T& operator*(){return element;}
  T* operator->(){return element;}


  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;



  T* release() {
    T* pointer = element;
    element = nullptr;
    return pointer;
  }


private:
  A allocator;
  T* element;
};

// TODO can == must improve.
//TODO Control Block, split allocator::deallocate on destroy and deallocate (two different mechanisms in such one object is trivial resolve)
template<typename T, typename A = vector::new_allocator<T>>
struct Counted_ptr{
  Counted_ptr() = default;
  Counted_ptr(T&& el) : ptr(new unique_ptr<T, A>(std::move(el))){}

  Counted_ptr(const Counted_ptr& cp) : ptr(cp.ptr), count_pointers(cp.count_pointers){
    ++ *count_pointers;
  }

  ~Counted_ptr() {
    if (*count_pointers > 1) {
      -- *count_pointers;
    }
    else {
      delete ptr;
      delete count_pointers;
    }
  }


  T& operator*(){return ptr->operator*();}
  T* operator->(){return ptr->operator->();}

private:
  unique_ptr<T,A>* ptr = new unique_ptr<T, A>();
  int* count_pointers = new int(1);

};

}
