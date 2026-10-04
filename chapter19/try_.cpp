//
// Created by Dmytrenko Kyrylo on 04.10.2026.
//
module;
#include <iostream>
module chapter19;

namespace ch19::try_ {

void test() {
  constexpr size_t size = 5;
  std::array<int,size> first{1,2,3,4,5};
  std::array<int,size> second{};
  copy_xd(first.begin(),first.end(),second.begin());


  std::cout << "test successfully";
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