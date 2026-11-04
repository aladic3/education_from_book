//
// Created by Dmytrenko Kyrylo on 04.11.2026.
//
//
// Created by Dmytrenko Kyrylo on 23.10.2026.
//
module;
#include <iostream>


module chapter19;
import chapter18;

namespace ch19::document {
void Document::add_char(char ch) {

}

bool iterator::operator==(const iterator &i) const {
  return i.local_line_iterator == local_line_iterator && i.pos == pos;
}

bool iterator::operator!=(const iterator &i) const {
  return i.local_line_iterator != local_line_iterator || i.pos != pos;
}

iterator &iterator::operator++() {
  if (++pos; pos == local_line_iterator.operator*().end()) {
    ++local_line_iterator;
    pos = local_line_iterator.operator*().begin();
  }

  return *this;

}

iterator &iterator::operator--() {
  if (pos-- == local_line_iterator.operator*().begin()){ // TODO must tested
    local_line_iterator.operator--();
    pos = local_line_iterator.operator*().end() - 1;
  }

  return *this;
}

iterator iterator::operator++(int a) {
  auto old_iterator = {local_line_iterator,pos};
  this->operator++();

  return old_iterator;
}

iterator iterator::operator--(int a) {
  auto old_iterator = {local_line_iterator,pos};
  this->operator--();

  return old_iterator;
}

std::istream &operator>>(std::istream &is, Document &doc) {
  constexpr char term_char = '\n';
  char temp;

  while (is.get(temp) && temp != term_char) {

  }

}
}
