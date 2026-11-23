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
  _end = std::make_unique<document_iterator>(
      lines.end(),
    (*lines.end()).begin()
    );
}
Document::Concatenation_info::Concatenation_info(char *p_new_line,
                                                 const std::string &old_str,
                                                 const std::string &new_str,
                                                 document_iterator pos_doc,
                                                 Line *old_line)
  : p_new_line(p_new_line), old_line(old_line), new_str(new_str),
position(pos_doc), old_str(old_str)
{}



void Document::push_back(char ch) {
  this->lines.back().push_back(ch);

  if (ch == separated_char)
    lines.push_back({});

}

void Document::insert(char ch, document_iterator left) {
  left.get_line_iterator().operator*()
    .insert(left.operator->(),ch);
}

void Document::add_chapter(const document_iterator lhs) {
  _chapters.push_back(lhs);
}

template <std::forward_iterator iter>
iter copy(iter begin, iter end, iter res) {
  for (iter it = begin; it != end; ++it) {
    *res = *it;
    ++res;
  }
  return res;
}

document_iterator Document::replace(document_iterator position,
  const std::string& old_str, const std::string& new_str) {
      Line* old_line = &*position.get_line_iterator();
      constexpr unsigned long buf = 256;
      std::array<char, buf> new_line_gen{};
      auto* p_new_line = new_line_gen.begin();
      Concatenation_info info {p_new_line,old_str,new_str,position,old_line};

      p_new_line = concatenation(info);

      *old_line = ch18::vector::Vector<char>( {new_line_gen.begin(),p_new_line});

      position.set_position(*old_line->begin());
      return position;
}



void Document::find_and_replace(const std::string& old_str, const std::string& new_str) {
  document_iterator found_result = find(old_str);

  if (found_result == *_end) return;

  auto res_replace = replace(found_result,old_str,new_str);

}

int Document::get_count_chars() const {
  int result = 0;
  for (auto el: *this) {
    ++result;
  }

  return result;
}

void Document::delete_line(document_iterator line) {
  this->lines.erase(line.get_line_iterator());
}

char *Document::concatenation(Concatenation_info& info) {
  auto* p_new_line = info.p_new_line;
  auto old_line = info.old_line;
  const auto& new_str = info.new_str;
  auto position = info.position;
  const auto& old_str = info.old_str;

  p_new_line = copy(old_line->begin(),position.operator->(),p_new_line);
  p_new_line = std::ranges::copy(new_str, p_new_line).out;

  auto* end_replaced_part = position.operator->() + old_str.size();

  if (end_replaced_part < old_line->end()) {
    p_new_line = copy(end_replaced_part,old_line->end(),p_new_line);
  } else {
    p_new_line = copy(position.next_line().operator->(),
        position.get_line_iterator().operator*().end(),p_new_line);
    auto to_delete = position;
    delete_line(to_delete);
  }

  return p_new_line;
}

// if not matched start become last comparison position
bool match(document_iterator& start, const document_iterator _end, const std::string& comp_str) {
  auto str_iter = comp_str.begin();
  document_iterator it = start;
  for (;it != _end && str_iter != comp_str.end() &&
     *str_iter == *it; ++it){
    ++str_iter;
  }

  start = str_iter == comp_str.end() ? start : it;

  return str_iter == comp_str.end();
}

document_iterator Document::find(const std::string& lhs) { // TODO must see for refactor
  if (lhs.empty()) return end();
  char first = lhs.front();
  document_iterator it = std::find(begin(),*_end,first);

  for (;it != *_end && !match(it,*_end,lhs);
    it = std::find(it,*_end,first)) {

  }

  return it;

}

document_iterator Document::begin() {
  auto bb = lines.begin();
  return {bb, bb.operator*().begin()};
}

document_iterator Document::end() {
  auto ee = lines.begin();
  return {ee,(*ee).begin()};
}
document_iterator Document::begin() const {
  auto bb = lines.begin();
  return {bb, bb.operator*().begin()};
}

document_iterator Document::back() const {
  return *_end - 1;
}

bool document_iterator::operator==(const document_iterator &i) const {
  return i.local_line_iterator == local_line_iterator && i.pos == pos;
}

bool document_iterator::operator!=(const document_iterator &i) const {
  return i.local_line_iterator != local_line_iterator || i.pos != pos;
}

list::List<Line>::iterator document_iterator::get_line_iterator() const  {
  return local_line_iterator;
}
document_iterator& document_iterator::next_line() {
  ++local_line_iterator;
  pos = local_line_iterator.operator*().begin();

  return *this;
}

document_iterator &document_iterator::operator++() {
  if (++pos; pos == local_line_iterator.operator*().end()) {
    ++local_line_iterator;
    pos = local_line_iterator.operator*().begin();
  }

  return *this;

}

document_iterator &document_iterator::operator--() {
  if (pos-- == (*local_line_iterator).begin()){ // TODO must tested
    --local_line_iterator;
    pos = (*local_line_iterator)
          .end() - 1;
  }

  return *this;
}

document_iterator document_iterator::operator++(int a) {
  auto old_iterator = document_iterator{local_line_iterator,pos};
  this->operator++();

  return old_iterator;
}

document_iterator document_iterator::operator--(int a) {
  auto old_iterator = document_iterator{local_line_iterator,pos};
  this->operator--();

  return old_iterator;
}

document_iterator document_iterator::operator-(int i) const {
  auto result = *this;
  while (i > 0) {
    result.operator--();
    --i;
  }

  return result;
}

document_iterator document_iterator::operator+(int i) const{
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
