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
void test_4();
void test_5();

template <std::forward_iterator iterator>
bool string_compare(iterator it, size_t size, const std::string& string_compare_with);

template<std::forward_iterator iterator> // return true if object iteration is first dictionary
bool string_compare_dictionary(iterator it, size_t size, const std::string& string_compare_with);

template<typename T>
auto copy_to_new_object(const T& for_copy) {
  if constexpr (!std::is_trivially_destructible_v<T>)
    return for_copy;


  if constexpr ((std::is_same_v<std::remove_cv_t<std::remove_extent_t<T>>, char>
    && std::is_array_v<T>) || std::is_same_v<T,char*>) {

    const size_t len = std::strlen(for_copy) + 1;
    auto result = std::make_unique<char[]>(len);
    std::strcpy(result.get(),for_copy);

    return result;
  }

  // for array int
  // TODO we can impl for int*. But implemented for int[].
  if constexpr (std::is_same_v<std::remove_cv_t<std::remove_extent_t<T>>, int>
   && std::is_array_v<T>) {
    const size_t len = sizeof(for_copy) / sizeof(int);
    auto result = std::make_unique<int[]>(len);
    std::copy(std::begin(for_copy),std::end(for_copy), result.get());

    return result;
   }




}

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


template <std::forward_iterator iterator>
bool string_compare_dictionary(iterator it, size_t size,
                               const std::string &string_compare_with) {
  const size_t usual_size = size > string_compare_with.size() ? string_compare_with.size() : size;
  for (int i = 0; i < usual_size; ++i) {
    if (*it != string_compare_with[i])
      return *it < string_compare_with[i];
    ++it;
  }

  return true;
}

template <std::forward_iterator iterator>
bool string_compare(iterator it, const size_t size,
                    const std::string &string_compare_with) {
  if (size != string_compare_with.size())
    return false;

  for (int i = 0; i < size; ++i) {
    if (string_compare_with[i] != *it)
      return false;
    ++it;
  }

  return true;
}
} // namespace ch19::try_
