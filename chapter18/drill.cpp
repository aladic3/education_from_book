//
// Created by Dmytrenko Kyrylo on 11.07.2026.
//
module;
#include "../error.h"

#include <iostream>
#include <ranges>
#include <vector>

module chapter18;

namespace ch18::drill {

void test() {
  using namespace ch18::vector;
  S<int> f1(10);
  S<char> f2('x');
  S<double> f3;
  S<Vector<int>> f4;
  f4 = Vector<int>(Vector<int>(100,3));
  f2 = '3';
  f3 = 2.33;

  std::cout << f1.access() << "\n";
  std::cout << f2.access() << "\n";
  std::cout << f3.access() << "\n";

  auto sf4 = f4.access();
  for (const auto& el : sf4) {
    std::cout << el << " ";
  }
  std::cout << "\n";



}
}