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

Document::Document() : lines()  { //std::initializer_list{Line(1,'x')}),
  (*lines.end()).push_back('x');
  _end = std::make_unique<iterator>(
      lines.end(),
    (*lines.end()).begin()
    );
}

void Document::push_back(char ch) {
  this->lines.back().push_back(ch);

  if (ch == separated_char)
    lines.push_back({});

}

void Document::insert(char ch, iterator left) {
  left.get_line_iterator().operator*()
    .insert(left.operator*(),ch);
}

void Document::add_chapter(iterator lhs) {
  _chapters.push_back(lhs);
}

void Document::find_and_replace(const std::string& lhs) {
  iterator find_result = find(lhs);
}

bool match(iterator& start, const iterator _end, const std::string& lhs) {
  auto str_iter = lhs.begin(); // TODO must see for refactor
  for (iterator it = start;
    !(it == _end && str_iter == lhs.end() && *str_iter == **it);
    ++it) {
    ++str_iter;
  }

  return str_iter == lhs.end();
}

iterator Document::find(const std::string& lhs) { // TODO must see for refactor
  if (lhs.size() == 0) return end();
  const char* first = &lhs.front();

  for (iterator it = std::find(begin(),*_end,first);
    !(it == *_end && match(it,*_end,lhs)) ; ++it);
}

iterator Document::begin() {
  auto bb = lines.begin();
  return {bb, bb.operator*().begin()};
}

iterator Document::end() {
  auto ee = lines.begin();
  return {ee,(*ee).begin()};
}

iterator Document::back() const {
  return *_end - 1;
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
  if (pos-- == (*local_line_iterator).begin()){ // TODO must tested
    --local_line_iterator;
    pos = (*local_line_iterator)
          .end() - 1;
  }

  return *this;
}

iterator iterator::operator++(int a) {
  auto old_iterator = iterator{local_line_iterator,pos};
  this->operator++();

  return old_iterator;
}

iterator iterator::operator--(int a) {
  auto old_iterator = iterator{local_line_iterator,pos};
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
  char temp;

  while (is.get(temp)) {
    doc.push_back(temp);
  }

  return is;
}
}
