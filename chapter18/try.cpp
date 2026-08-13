//
// Created by Dmytrenko Kyrylo on 11.07.2026.
//
module;

#include <iostream>

module chapter18;
import chapter18.vector;

namespace ch18::try_ {



Somethink::Somethink() {
  char ch []  = "Default";
  field1 = static_cast<char*>( operator new(sizeof(char) * (std::strlen(ch) + 1)));
  std::uninitialized_move_n(ch,std::strlen(ch) + 1,field1);

  field2 = std::string(field1);
  std::cerr << "struct 'Somethink' default constructor\n";
}
Somethink::Somethink(const std::string &str) : field2(str){
  field1 = static_cast<char*>( operator new(sizeof(char) * (str.length() + 1)));
  std::uninitialized_copy(str.begin(), str.end(),field1);

  std::cerr << "struct 'Somethink' constructor with field >>" << field2  <<  " <<\n";
}

Somethink::~Somethink() {

  std::cerr << "struct 'Somethink' destructor with fields >>" << field2 << "<< \n";
  ::operator delete(field1);



}
Somethink::Somethink(const Somethink & el) :
field1(static_cast<char*>(::operator new((std::strlen(el.field1)+1) * sizeof(char)))),
field2(el.field2) {
  std::uninitialized_copy(el.field1,el.field1+std::strlen(el.field1)+1,field1);
  std::cerr << "struct 'Somethink' copy constructor\n";
}
Somethink::Somethink( Somethink && el) noexcept :
field1(el.field1),
field2(std::move(el.field2))
{
  el.field1 = nullptr;
  std::cerr << "struct 'Somethink' move constructor\n";
}
Somethink &Somethink::operator=(const Somethink & el) {
  operator delete(field1);
  field1 = static_cast<char*>(operator new((std::strlen(el.field1) + 1) * sizeof(char)));
  std::uninitialized_copy(el.field1,el.field1+std::strlen(el.field1) + 1,field1);
  field2 = el.field2;

  std::cerr << "struct 'Somethink' copy assigment\n";
  return *this;
}
Somethink &Somethink::operator=(Somethink && el) noexcept {
  operator delete(field1);
  field1 = el.field1;
  el.field1 = nullptr;
  field2 = std::move(el.field2);

  std::cerr << "struct 'Somethink' move assigment\n";

  return *this;
}
void test1() {
  using namespace ch18::vector;
  using std::string;
  {
    Vector<Somethink> constructor_destructor_test;
    constructor_destructor_test.push_back(Somethink());
  }


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
