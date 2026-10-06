//
// Created by Dmytrenko Kyrylo on 06.10.2026.
//
module;
#include <algorithm>

export module chapter19.list;


export namespace ch19::list {
template<typename T>
struct Link;





template<typename T>
struct List {
  struct iterator;

  List();

private:

  Link<T>* first;
  Link<T>* last;
};

template<typename T>
struct Link {
  Link(T&& el = T{}, Link* prev = nullptr, Link* next = nullptr) : _prev(prev),
  _next(next), _element(std::move(el)){}



  Link* insert(Link* next);

  Link* erase();

  T& element(){return _element;}
  Link* prev() {return _prev;}
  Link* next() {return _next;}

private:
  Link* _prev ;
  Link* _next ;
  T _element;
};

template <typename T> List<T>::List() {
  this->first = new Link<T>();
  this->last = new Link<T>();

  first->_next = this->last;
  last->_prev = this->first;
}

template <typename T>
Link<T> *Link<T>::insert(Link *next) {
  auto temp = next->prev();
  next->prev() = this;
  temp->next() = this;
  this->next() = next;
  this->prev() = temp;
  return this;
}

template <typename T> Link<T> * Link<T>::erase() {
  this->next()->prev() = this->prev();
  this->prev()->next() = this->next();
  this->next() = nullptr;
  this->prev() = nullptr;
  return this;
}



template <typename T>
struct List<T>::iterator {
  iterator(const Link<T>* el): link(el){}

  bool operator==(const iterator & i) const{return i.link == link;}
  bool operator!=(const iterator & i) const {return i.link != link;}

  iterator operator++(){return link->next();}
  iterator operator--(){return link->prev();}
private:
  Link<T>* link;
};

}