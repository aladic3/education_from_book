//
// Created by Dmytrenko Kyrylo on 06.10.2026.
//
module;
#include <algorithm>

export module chapter19.list;


export namespace ch19::list {
template<typename T>
struct Link {
  Link(T&& el = T{}, Link* prev = nullptr, Link* next = nullptr) : _prev(prev),
  _next(next), _element(std::move(el)){}



  [[nodiscard]] static Link* insert_static(Link* next, T&& el);
  [[nodiscard]] static Link* insert_static(Link* next, const T& el);
  Link* insert(Link* next);

  void set_next(Link* next){_next = next;}
  void set_prev(Link* prev){_prev = prev;}

  Link* erase();
  T& get_value(){return _element;}
  const T& get_value() const {return _element;}

  T& element(){return _element;}
  Link* prev() {return _prev;}
  Link* next() {return _next;}

private:
  Link* _prev ;
  Link* _next ;
  T _element;
};






template<typename T>
struct List {

  struct iterator {


    iterator( Link<T>* el): link(el){}


    bool operator==(const iterator & i) const{return i.link == link;}
    bool operator!=(const iterator & i) const {return i.link != link;}

    T& operator*(){return link->get_value();}
    const T& operator*() const {return link->get_value();}

    iterator& operator++(){link = link->next(); return *this;}
    iterator& operator--(){link = link->prev(); return *this;}
    iterator& operator+=(int a){if }

    Link<T>* get_link() {return link;}
  private:
    Link<T>* link;
  };

  List();
  ~List();

  void pop_back();
  void pop_front();

  T& front();
  T& back();

  iterator erase(iterator);

  iterator push_back(T&&);
  iterator push_back(const T&);

  iterator push_front(T&&);
  iterator push_front(const T&);

  iterator insert(T&&, iterator next);
  iterator insert(const T&, iterator next);


  iterator begin();
  iterator end();

private:

  Link<T>* first; // first and last are empty
  Link<T>* last;
};


template <typename T> List<T>::List() {
  this->first = new Link<T>();
  this->last = new Link<T>();

  first->set_next(this->last);
  last->set_prev(this->first);
}

template <typename T> List<T>::~List() {
  Link<T>* temp = this->first;
  for (Link<T>* current = temp; current != nullptr; current = temp) {
    temp = temp->next();
    delete current;
  }
}

template <typename T> void List<T>::pop_back() {
  delete this->end().operator--().get_link()->erase();
}

template <typename T> void List<T>::pop_front() {
  delete this->begin().get_link()->erase();
}

template <typename T> T &List<T>::front() {
  return begin().get_link()->get_value();
}

template <typename T> T &List<T>::back() {
  return end().operator--().get_link()->get_value();
}

template <typename T> typename List<T>::iterator List<T>::erase(iterator it) {
  return it.get_link()->erase();
}

template <typename T>  List<T>::iterator List<T>::push_back(T && el) {
  return Link<T>::insert_static(this->last,std::move(el));
}

template <typename T>
 List<T>::iterator List<T>::push_back(const T & el) {
  return Link<T>::insert_static(this->last,el);
}

template <typename T> typename List<T>::iterator List<T>::push_front(T && el) {
  return Link<T>::insert_static((++iterator(this->first)).get_link(),
    std::move(el));
}

template <typename T>
typename List<T>::iterator List<T>::push_front(const T & el) {
  T copy_el = el;
  return Link<T>::insert_static((++iterator(this->first)).get_link(),
    std::move(copy_el));
}

template <typename T>

typename List<T>::iterator List<T>::insert(T && el, typename List<T>::iterator next) {
  return Link<T>::insert_static(next.get_link(),
    std::move(el));
}

template <typename T>
typename List<T>::iterator List<T>::insert(const T & el, typename List<T>::iterator next) {
  T copy_el = el;
  return Link<T>::insert_static(next.get_link(),
    std::move(copy_el));
}

template <typename T>
List<T>::iterator List<T>::begin() {
  return this->first->next();
}

template <typename T> typename List<T>::iterator List<T>::end() {
  return this->last;
}



template <typename T>
[[nodiscard]] Link<T> *Link<T>::insert_static(Link *next, T &&el) {
  Link * result = new Link(std::move(el));
  result->insert(next);
  return result;
}

template <typename T>
Link<T> *Link<T>::insert_static(Link *next, const T &el) {
  T copy_el = el;
  Link * result = new Link(std::move(copy_el));
  result->insert(next);
  return result;
}

template <typename T>
Link<T> *Link<T>::insert(Link *next) {
  auto temp = next->prev();
  next->set_prev(this);
  temp->set_next(this);
  this->set_next(next);
  this->set_prev(temp);
  return this;
}

template <typename T> Link<T> * Link<T>::erase() {
  this->next()->set_prev(this->prev());
  this->prev()->set_next(this->next());
  this->set_next(nullptr);
  this->set_prev(nullptr);
  return this;
}






}