//
// Created by Dmytrenko Kyrylo on 04.10.2026.
//
module;
#include "../error.h"

#include <filesystem>
#include <functional>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <vector>

export module chapter19;
import chapter18.vector;

export namespace ch19::try_ {
void test();
void test_2();
void test_3();
void copy_xd(int* f1, const int* e1, int* f2); // copy using only iterator operations

template<std::forward_iterator iterator>
void advance(int a, iterator& it);

using namespace ch18::vector;

template <typename T, typename A = simple_allocator<T>>
struct Try_vector : Vector<T,A> {
  using  Vector<T,A>::Vector;

  void push_front(const T &new_el);
  void push_front(T &&new_el);

};

template <typename T, typename A>
void Try_vector<T, A>::push_front(const T &new_el) {
  if (Vector<T,A>::sz == Vector<T,A>::cap)
    Vector<T,A>::reserve(Vector<T,A>::cap == 0 ? 8 : Vector<T,A>::sz * 2);

  for (T* el = Vector<T,A>::elem+Vector<T,A>::sz; el>=Vector<T,A>::elem ;--el)
    *(el+1) = *std::move(el);


  std::construct_at(Vector<T,A>::elem, new_el);

  ++Vector<T,A>::sz;
}


template <typename T, typename A>
void Try_vector<T, A>::push_front(T &&new_el) {
  if (Vector<T,A>::sz == Vector<T,A>::cap)
    Vector<T,A>::reserve(Vector<T,A>::cap == 0 ? 8 : Vector<T,A>::sz * 2);

  for (T* el = Vector<T,A>::elem+Vector<T,A>::sz; el>=Vector<T,A>::elem ;--el)
    *(el+1) = *std::move(el);

  *(Vector<T,A>::elem) = std::move(new_el);
  ++Vector<T,A>::sz;
}


template <std::forward_iterator iterator>
void advance(int a, iterator& it) {
  int module = -1;
  std::function<void()> fun ([&]{++it;});

  if (a < 0) {
    module = 1;
    fun = [&]{--it;};
  }

  for (int i = a; i != 0; i += module) {
    fun();
  }
}
} // namespace ch19::try_
