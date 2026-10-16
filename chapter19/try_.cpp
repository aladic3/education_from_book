//
// Created by Dmytrenko Kyrylo on 04.10.2026.
//
module;
#include <iostream>
#include <list>
#include <vector>
#include <span>

module chapter19;
import chapter19.list;

namespace ch19::try_ {

void test() {
  constexpr size_t size = 5;
  std::array<int,size> first{1,2,3,4,5};
  std::array<int,size> second{};
  copy_xd(first.begin(),first.end(),second.begin());


  std::cout << "test successfully";
}


void test_3() {
  using it = list::List<int>::iterator;
  list::List<int> mlst;// ({1,2,3,4,5,6,7});



  int x = 20;
  mlst.push_back(10);
  it e30 = mlst.push_back(30);
  mlst.push_back(x);
  mlst.push_front(5);
  mlst.push_front(x);
  mlst.push_front(777);

  mlst.insert(666,e30);
  it f_ad_it = mlst.begin();
  std::cerr << f_ad_it.get_link()->get_value() << '\t' ;
  advance(100,f_ad_it);
  std::cerr << f_ad_it.get_link()->get_value() << '\t' ;
  advance(-3,f_ad_it);
  std::cerr << f_ad_it.get_link()->get_value() << '\n' ;
  std::cerr << mlst.front() << '\t' << mlst.back();

  mlst.pop_back();
  mlst.pop_front();

  delete mlst.erase(e30).get_link();

  for (auto& el: mlst) {
    std::cout << el << '\t';
  }
}

template<typename T>
void inspect(const T& value)
{
  static_assert(std::is_same_v<T, char*>);
  static_assert(std::is_array_v<T>);
  static_assert(std::extent_v<T> == 6);
}


void drill() {
  std::initializer_list init_lst  {0,1,2,3,4,5,6,7,8,9};
  std::array<int,10> arr {0,1,2,3,4,5,6,7,8,9};
  std::vector<int> vec {init_lst};
  std::list<int> lst {init_lst};

  auto arr2 = std::array<int,10>(arr); arr2[0] = 111;
  auto vec2 = vec;
  auto lst2 = lst;

}

void test_5() {
  int str1 [] {1, 2, 3, 4, 5};
  int* p1 = &str1[0];

  std::vector<int> str2 {1,2,3,4,5};
  for (auto& el : str2) {
    std::cerr << el;
  }
  std::list<int> str3 {std::initializer_list{1, 2, 3, 4, 5}};
  std::string str4 {"12345"};

  std::cout << string_compare(p1, std::size(str1), str4)
      << string_compare(str2.begin(), str2.size(), str4)
      << string_compare(str3.begin(), str3.size(), str4)
      << string_compare(str4.begin(), str4.size(), str4)
      << std::endl
      << string_compare_dictionary(p1, std::size(str1), str4)
      << string_compare_dictionary(str2.begin(), str2.size(), "Howdy")
      << string_compare_dictionary(str3.begin(), str3.size(), "Howdy")
      << string_compare_dictionary(str4.begin(), str4.size(), "Howdy");

  //auto str111 = copy_to_new_object(p1);
  auto str11 = copy_to_new_object(str1);
  std::cout << std::endl;
  for (int i = 0; i < std::size(str1); ++i) {
    std::cout << str11.get()[i];
  }

  std::vector<int> str22 = copy_to_new_object(str2);
  std::list<int> str33 = copy_to_new_object(str3);
  std::string str44 = copy_to_new_object(str4);
}

void test_4() {
  char str1 [] {"Hello"};
  char* p1 = &str1[0];

  std::vector<char> str2 {std::initializer_list{'H','e','l','l','o'}};
  std::list<char> str3 {std::initializer_list{'H','e','l','l','o'}};
  std::string str4 {"Hello"};

  std::cout << string_compare(p1,std::strlen(str1),"Hello")
    << string_compare(str2.begin(),str2.size(),"Hello")
    << string_compare(str3.begin(),str3.size(),"Hello")
    << string_compare(str4.begin(),str4.size(),"Hello")
    << std::endl
    << string_compare_dictionary(p1,std::strlen(str1),"Hello")
    << string_compare_dictionary(str2.begin(),str2.size(),"Howdy")
    << string_compare_dictionary(str3.begin(),str3.size(),"Howdy")
    << string_compare_dictionary(str4.begin(),str4.size(),"Howdy");

  auto str111 = copy_to_new_object(p1);
  auto str11 = copy_to_new_object(str1);
  std::cout << std::endl;
  for (int i = 0; i < std::strlen(str111.get()); ++i) {
    std::cout << str111.get()[i];
  }

  //inspect(str1);
  //inspect(p1);

  std::vector<char> str22 = copy_to_new_object(str2);


  std::list<char> str33 = copy_to_new_object(str3);
  std::string str44 = copy_to_new_object(str4);
}

void test_2() {
  Try_vector<int> v({1,2,3,4,5,6,7,8,9,10});
  v.push_front(12);
  ch18::vector::print_v(v, "pamapam");
  v.push_front(0); print_v(v, "pamapam");
  v.push_front(666); print_v(v, "pamapam");

}

void copy_xd(int *f1, const int *e1, int *f2)
// copy from [f1:e1) to [f2:f2+(e1-f1)) e1 is end() using iter operations only
{
  for (int* p = f1; p != e1; ++p) {
    *f2 = *p;
    ++f2;
  }
}
}