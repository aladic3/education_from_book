//
// Created by Dmytrenko Kyrylo on 04.10.2026.
//
module;
#include <iostream>
#include <list>

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
  list::List<int> mlst;
  int x = 20;
  mlst.push_back(10);
  it e30 = mlst.push_back(30);
  mlst.push_back(x);
  mlst.push_front(5);
  mlst.push_front(x);

  mlst.insert(666,e30);

  for (auto& el: mlst) {
    std::cout << el << '\t';
  }
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