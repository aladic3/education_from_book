//
// Created by Dmytrenko Kyrylo on 11.07.2026.
//
module;

#include <iostream>

module chapter18;

namespace ch18::try_ {
void test1() {
  using namespace ch18::vector;
  using std::string;

  std::cout << "Good!\n";
  Vector<double> default_resize_test;
  Vector push_test = {1, 2, 3, 4};
  Vector<string> string_tmpl(3, "X");

  *(string_tmpl.end()-1) = "End";
  *(string_tmpl.begin()) = "begin";

  Vector char_template(10,'*');

  print_v(char_template, string("char_template: "));

  print_v(default_resize_test, string("default_resize_test: "));
  print_v(push_test, string("push_test: "));
  print_v(string_tmpl, string("string_tmpl: "));

  push_test.push_back(5);
  string_tmpl.reverse();
  default_resize_test.push_back(1);

  print_v(default_resize_test, string("default_resize_test after push: "));
  print_v(push_test, string("push_test after push: "));
  print_v(string_tmpl, string("string_tmpl after reverse: "));

  push_test.reserve(100);
  print_v(push_test, string("push_test after reserve: "));

  default_resize_test.resize(40);

  print_v(default_resize_test, string("default_resize_test after resize: "));

  Vector copy_test = push_test;
  Vector move_test = create_v({5, 4, 3, 2, 1});

  print_v(copy_test, string("copy_test: "));
  print_v(move_test, string("move_test: "));
}
} // namespace ch18::try_
