//
// Created by Dmytrenko Kyrylo on 23.10.2026.
//
module;
#include <iostream>
#include <list>
#include <vector>
#include <span>

module chapter19;
import chapter18;

namespace ch19::ex {
void ex2() {
  std::vector<ch18::try_::Somethink> a3 (3);
  std::array<int, 5> a1 {1,2,3,4,5};
  std::vector<int> a2 {};

  auto ia1 = high(a1.begin(),a1.end());
  auto ia2 = high(a2.begin(),a2.end());
  //auto ia3 = high(a3.begin(),a3.end());
}
}