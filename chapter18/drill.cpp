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

  S<std::string> f5;
  //f4 = Vector<int>(Vector<int>(5,3));
  f2 = '3';
  f3 = 2.33;

  S<Vector<char>> f4 (Vector<char>(5,3));
  S<Vector<int>> f44 (Vector<int>(3,10));
  S<Vector<double>> f444 (Vector<double>(4,2.5));
  //add(f4.access(),f44.access());
  std::cout << f4.access() << std::endl;
  std::cout << f444.access() << std::endl;

  std::cout << "sum_multiply = " << sum_multiply(f4.access(),f444.access()) << std::endl;

  return;
  std::cout << f1.access() << "\n";
  std::cout << f2.access() << "\n";
  std::cout << f3.access() << "\n";

  auto sf4 = f4.access();
  for (const auto& el : sf4) {
    std::cout << el << " ";
  }
  std::cout << "\n";

  std::cout << "Enter double: ";
  read_val(f3.access());
  std::cout << f3.access();
  std::cout << "\n";

  std::cout << "Enter char: ";
  read_val(f2.access());
  std::cout << f2.access();
  std::cout << "\n";

  std::cout << "Enter string: ";
  read_val(f5.access());
  std::cout << f5.access();
  std::cout << "\n";

  std::cout << "Enter int: ";
  read_val(f1.access());
  std::cout << f1.access();
  std::cout << "\n";

  std::cout << "Enter Vector<int>: ";
  read_val(f4.access());
  std::cout << f4.access();
  std::cout << "\n";


}
}