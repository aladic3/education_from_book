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

Document::Document() : lines(std::initializer_list{Line(1,'')}),
  _end(lines.end(),nullptr) {}

void Document::push_back(char ch) {
  this->lines.back().push_back(ch);

  if (ch == separated_char)
    lines.push_back({1,''});

}

void Document::insert(char ch, iterator left) {
  left.get_line_iterator().operator*().insert(left.operator*(),ch);
}

iterator Document::begin() {
  auto bb = lines.begin();
  return {bb, bb.operator*().begin()};
}

iterator Document::back() const {
  return _end - 1;
}

bool iterator::operator==(const iterator &i) const {
  return i.local_line_iterator == local_line_iterator && i.pos == pos;
}

bool iterator::operator!=(const iterator &i) const {
  return i.local_line_iterator != local_line_iterator || i.pos != pos;
}

list::List<Line>::iterator iterator::get_line_iterator() const  {
  return local_line_iterator;
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

iterator iterator::operator-(int i) const {
  auto result = *this;
  while (i > 0) {
    result.operator--();
    --i;
  }

  return result;
}

iterator iterator::operator+(int i) const{
  auto result = *this;
  while (i > 0) {
    result.operator++();
    --i;
  }
  return result;
}

std::istream &operator>>(std::istream &is, Document &doc) {
  constexpr char term_char = '\n';
  char temp;

  while (is.get(temp) && temp != term_char) {

  }

}
}
