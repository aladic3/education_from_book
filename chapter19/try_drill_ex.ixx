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
void drill();

template <std::forward_iterator iterator>
void increase_by(iterator begin, iterator end, int increase_val);

template<std::forward_iterator iterator>
void print_range(iterator begin, iterator end);

template <std::forward_iterator iterator>
bool string_compare(iterator it, size_t size, const std::string& string_compare_with);

template<std::forward_iterator iterator> // return true if object iteration is first dictionary
bool string_compare_dictionary(iterator it, size_t size, const std::string& string_compare_with);

template<typename T>
auto copy_to_new_object(const T& for_copy);



template <std::forward_iterator iterator>  // dest == destination, dest.size == [begin;end)
void copy_drill(iterator begin, iterator end, iterator dest) {
  for (iterator i = begin; i != end; ++i) {
    *dest = *i;
    ++dest;
  }
}

template <std::forward_iterator iterator>  // print out position
int find_position(iterator begin, iterator end, int val) {
  int result = 0;
  iterator result_operation  = std::find(begin,end,val);

  if (result_operation == end ) return  -1;

  for (iterator it = begin;   it != result_operation; ++it)
    ++result;

  return result;

}

template <std::forward_iterator iterator1, std::forward_iterator iterator2>
void copy_drill(iterator1 begin, iterator1 end, iterator2 dest) {
  for (iterator1 i = begin; i != end; ++i) {
    *dest = *i;
    ++dest;
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


template <std::forward_iterator iterator>
void increase_by(iterator begin, iterator end,  int increase_val) {
  for (iterator it = begin; it != end; ++it) {
    *it += increase_val;
  }
}

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
  std::function<void()> fun ([&]{++it;});
  int module = -1;

  if (a < 0) {
    module = 1;
    fun = [&]{--it;};
  }

  for (int i = a; i != 0; i += module)
      fun();
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

template <typename T> auto copy_to_new_object(const T &for_copy) {
  if constexpr (!std::is_trivially_destructible_v<T>)
    return for_copy;


  if constexpr ((std::is_same_v<std::remove_cv_t<std::remove_extent_t<T>>, char>
    && std::is_array_v<T>) || std::is_same_v<T,char*>) {

    const size_t len = std::strlen(for_copy) + 1;
    auto result = std::make_unique<char[]>(len);
    std::strcpy(result.get(),for_copy);

    return result;
    }

  // for array int (int[])
  // TODO we can impl for int*. But implemented for int[]...
  if constexpr (std::is_same_v<std::remove_cv_t<std::remove_extent_t<T>>, int>
   && std::is_array_v<T>) {
    const size_t len = sizeof(for_copy) / sizeof(int);
    auto result = std::make_unique<int[]>(len);
    std::copy(std::begin(for_copy),std::end(for_copy), result.get());

    return result;
   }
}


template <std::forward_iterator iterator> // but must 'requires symbol or num'
void print_range(iterator begin, iterator end) {
  for (iterator it = begin; it != end; ++it) {
    std::cout << *it << ' ';
  }
  std::cout << std::endl;
}
} // namespace ch19::try_

export namespace ch19::ex {
void ex2_4();
void ex5();

template<typename T>
  requires std::totally_ordered<T>
std::ostream& operator<<(std::ostream& out, const ch18::vector::Vector<T>& vec);

template<typename T>
  requires std::totally_ordered<T>
std::istream& operator>>(std::istream& in, ch18::vector::Vector<T>& vec);

template <std::forward_iterator iterator>
  requires std::totally_ordered<std::iter_value_t<iterator>>
iterator high(iterator begin, iterator end);

template<std::forward_iterator iterator>
  requires std::totally_ordered<std::iter_value_t<iterator>>
iterator high_v2(iterator begin, iterator end); /// using palindrome method

double* get_from_jack(int& count);
std::vector<double> get_from_jill();

template <std::forward_iterator iterator>
  requires std::totally_ordered<std::iter_value_t<iterator>>
iterator high_v2(iterator begin, iterator end) {
  --end;
  iterator high = begin;
  ++begin;

  while (begin < end) {
    if (*begin > *high) high = begin;
    if (*end > *high) high = end;

    ++begin;
    --end;
  }

  return high;
}

template <std::forward_iterator iterator>
    requires std::totally_ordered<std::iter_value_t<iterator>>
iterator high(iterator begin, iterator end) {
  if (begin == end)
    return end;
  iterator high = begin;
  for (iterator it = begin + 1; it != end; ++it) {
    if (*high < *it)
      high = it;
  }

  return high;
}

template <typename T>
  requires std::totally_ordered<T>
std::ostream &operator<<(std::ostream &out,
                         const ch18::vector::Vector<T> &vec) {
  for (const T& el : vec)
    out << el << '\t';

  return out;
}
template <typename T>
  requires std::totally_ordered<T>
std::istream &operator>>(std::istream &in, ch18::vector::Vector<T> &vec) {
  T temp;
  char first_ch = 1;
  //std::cout << "gg input";

  while (in.get(first_ch) && first_ch != '\n') {
    in.putback(first_ch);
    in >> temp;
    vec.push_back(temp);

  }


  return in;
}

} // namespace ch19::ex