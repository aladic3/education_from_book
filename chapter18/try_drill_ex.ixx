//
// Created by Dmytrenko Kyrylo on 11.07.2026.
//
module;
#include "../error.h"

#include <iomanip>
#include <iostream>
#include <ranges>
#include <vector>

export module chapter18;
export import chapter18.vector;

export namespace ch18::try_ {

template <typename T, typename U> void suspicious();

struct Somethink {
  Somethink();
  ~Somethink();
  Somethink(const Somethink &);
  Somethink(Somethink &&);

  Somethink &operator=(const Somethink &);
  Somethink &operator=(Somethink &&);

private:
  char *field1;
  std::string field2;
};

void test1();
} // namespace ch18::try_

export namespace ch18::drill {
void test();

template <class T> struct S {
  S() : val() {}
  S(const T &v) : val(v) {}
  ~S() { val.~T(); }
  T &access();
  const T &access() const;

  S &operator=(const T &);

private:
  T val;
};

template <typename T> void read_val(T &v);

} // namespace ch18::drill

export namespace ch18::ex {
void test();
void test_4();
void test_5();
void test_6();
void test_7();

template <typename T, typename U>
  requires(std::convertible_to<T, std::string> ||
           std::convertible_to<T, char>) &&
          std::convertible_to<U, double>
struct Pair {
  T name;
  U val;
};

template <typename T, typename U>
std::istream &operator>>(std::istream &is,
                         vector::Vector<Pair<T, U>> &var_table);

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os,
                         const vector::Vector<Pair<T, U>> &var_table);

template <class God>
requires std::equality_comparable<God>
struct Link {
  Link &operator=(const Link &) = delete;
  Link(const Link &) = delete;
  Link() : element("BEGIN") {}

  ~Link();

  Link *insert(const God &, Link *right_link) const; // create and insert by
  Link *insert(const God &, int index);     // create and insert by index
  Link *erase(const God&);         // by obj
  Link *move_on_this(Link *element, int n); // move backward or forward
  void add(const God &);

  [[nodiscard]] Link *find(const God &); // by name
  [[nodiscard]] const Link *find(const God &) const;
  [[nodiscard]] const God &get_value() const;

  Link *operator[](int iterator) const;
  God * operator[](int iterator);


  [[nodiscard]] int size() const;

private:
  Link(God);             // create without left and right pointers
  Link(God, Link *left); // in end link
  Link(God, Link *left, Link *right);

  Link *move_right(Link *el);
  Link *move_left(Link *el);

  God element;
  Link *left = nullptr;
  Link *right = nullptr;
};



struct Int {
  Int() = default;
  Int(int);
  Int(const Int&);


  Int& operator=(const Int&);

  Int& operator=(int);

  int operator*(int) const;
  int operator/(int) const;
  int operator-(int) const;
  int operator+(int) const;

  std::ostream& operator<<(std::ostream& os) const;
  std::istream& operator>>(std::istream& is);

private:
  int element = 0;
};


template<typename T>
requires std::floating_point<T> || std::integral<T>
struct Number {
  Number() = default;
  Number(T tt);
  Number(const Number& nn);



  Number& operator=(const Number& nn);

  Number& operator=(T tt);

  T operator*(T tt) const;
  T operator/(T tt) const;
  T operator-(T tt) const;
  T operator+(T tt) const;
  T operator%(T tt) const;


  operator T() const{ return element;}

  friend std::ostream& operator<<(std::ostream& os, const Number& nn){
    os << nn.element;
    return os;
  }
  friend std::istream& operator>>(std::istream& is, Number& nn){
    is >> nn.element;
    return is;
  }

private:
  T element = 0;
};

} // namespace ch18::ex

/***********************
 ***********************
 ***********************
 *    IMPLEMENTATIONS   *
 ***********************
 ***********************
 ***********************/

namespace ch18::ex {









/*****************************
 *****************************
 *****************************
 *begin Number class impl*****
 *****************************
 *****************************
 *****************************/

template <typename T>
  requires std::floating_point<T> || std::integral<T>
Number<T>::Number(T tt) : element(tt){}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
Number<T>::Number(const Number &nn) : element(nn.element) {}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
Number<T> &Number<T>::operator=(const Number &nn) {
  element = nn.element;
  return *this;
}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
Number<T> &Number<T>::operator=(T tt) {
  element = tt;
  return *this;
}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
T Number<T>::operator*(T tt) const {
  return element * tt;
}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
T Number<T>::operator/(T tt) const {
  return element / tt;
}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
T Number<T>::operator-(T tt) const {
  return element - tt;
}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
T Number<T>::operator+(T tt) const {
  return element + tt;
}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
T percent_operator_for_double(T first_el, T second_el) {
  int iterator = 0;
  while (first_el != static_cast<int>(first_el)) {
    first_el*=10;
    second_el*=10;
    ++iterator;
  }

  T result = static_cast<int>(first_el) % static_cast<int>(second_el);

  for (int i = 0; i < iterator; ++i) {
    result/=10;
  }

  return result;
}

template <typename T>
  requires std::floating_point<T> || std::integral<T>
T Number<T>::operator%(T tt) const {
  if constexpr (std::integral<T>)
    return element % tt;

  return percent_operator_for_double(element,tt);
}






/*****************************
 *****************************
 *****************************
 *  end Number class impl ****
 *****************************
 *****************************
 *****************************/



/***********************
 ***********************
 ***********************
 * begin Int class impl*
 ***********************
 ***********************
 ***********************/

Int::Int(int ii) : element(ii) {}

Int::Int(const Int & ii): element(ii.element) {}

Int &Int::operator=(const Int & ii) = default;

Int &Int::operator=(int ii) {
  element = ii;
  return *this; }

int Int::operator*(int ii) const {
  return ii * element;
}

int Int::operator/(int ii) const {
  return element/ii;
}

int Int::operator-(int ii) const {
  return element - ii;
}

int Int::operator+(int ii) const {
  return element + ii;
}
std::ostream &Int::operator<<(std::ostream &os) const {
  os << element;
  return os;
}

std::istream &Int::operator>>(std::istream &is) {
  is >> element;
  return is;
}

/***********************
 ***********************
 ***********************
 *  end Int class impl *
 ***********************
 ***********************
 ***********************/







/***********************
 ***********************
 ***********************
 *begin Link class impl*
 ***********************
 ***********************
 ***********************/

template <class God> requires std::equality_comparable<God>
Link<God>::Link(God val) : element(std::move(val)) {}

template <class God> requires std::equality_comparable<God>
Link<God>::Link(God val, Link *left) : element(std::move(val)), left(left) {}

template <class God> requires std::equality_comparable<God>
Link<God>::Link(God val, Link *left, Link *right)
    : element(std::move(val)), left(left), right(right) {}

// ReSharper disable once CppMemberFunctionMayBeStatic
template <class God> requires std::equality_comparable<God>
Link<God> *Link<God>::move_right(Link *el) {
  if (el->right == nullptr)
    return nullptr;

  el->left->right = el->right;
  el->right->left = el->left;

  Link *right_el = el->right;
  el->left = right_el;
  el->right = right_el->right;
  right_el->right = el;

  if (el->right)
    el->right->left = el;

  return el;
}

template <class God> requires std::equality_comparable<God>
Link<God> *Link<God>::move_left(Link *el) {
  if (el->left == this)
    return nullptr;

  el->left->right = el->right;
  if (el->right)
    el->right->left = el->left;

  Link *left_el = el->left;
  el->right = left_el;
  el->left = left_el->left;
  left_el->left = el;

  el->left->right = el;

  return el;
}

template <class God> requires std::equality_comparable<God>
Link<God>::~Link() {
  if (left)
    left->right = nullptr;

  delete right;
}

template <class God> requires std::equality_comparable<God>
Link<God> *Link<God>::insert(const God &val, Link *right_link) const {
  if (right_link == nullptr)
    return nullptr;

  Link *temp = right_link->left;
  right_link->left = new Link(val, right_link->left, right_link);
  temp->right = right_link->left;

  return right_link->left;
}

template <class God> requires std::equality_comparable<God>
Link<God> *Link<God>::insert(const God &val, int index) {
  Link *right_link = this->operator[](index);
  return insert(val, right_link);
}


template <class God> requires std::equality_comparable<God>
Link<God> *Link<God>::erase(const God &val) {
  Link *element = find(val);

  if (element == nullptr)
    return nullptr;

  if (element->right)
    element->right->left = element->left;

  if (element->left)
    element->left->right = element->right;

  element->left = nullptr;
  element->right = nullptr;

  return element;
}

template <class God> requires std::equality_comparable<God>
Link<God> *Link<God>::move_on_this(Link *element, int n) {
  if (element == nullptr || n == 0)
    return nullptr;

  Link *res_moving = element;
  int increment_i = 1;

  if (n < 0)
    increment_i = -1;

  if (increment_i > 0)
    for (int i = 0; i != n && res_moving; i += increment_i)
      res_moving = move_right(element);
  else
    for (int i = 0; i != n && res_moving; i += increment_i)
      res_moving = move_left(element);

  return element;
}

template <class God> requires std::equality_comparable<God>
void Link<God>::add(const God &val) {

  // ReSharper disable once CppDFANotInitializedField
  if (right)
    return right->add(val);

  right = new Link(val, this);
}





template <class God> requires std::equality_comparable<God>
Link<God> *Link<God>::find(const God &val) {
  Link *temp = this->right;

  for (int i = 0; i < size(); i++) {
    if (val == temp->get_value())
      return temp;
    temp = temp->right;
  }

  return nullptr;
}

template <class God> requires std::equality_comparable<God>
const Link<God> *Link<God>::find(const God &val) const {
  Link *temp = this->right;

  for (int i = 0; i < size(); i++) {
    if (val == temp->get_value())
      return temp;
    temp = temp->right;
  }

  return nullptr;
}

template <class God> requires std::equality_comparable<God>
const God &Link<God>::get_value() const {
  return element;
}

template <class God> requires std::equality_comparable<God>
Link<God> *Link<God>::operator[](int iterator) const {
  if (iterator >= size())
    error("out of range");

  Link *temp = this->right;

  for (int i = 0; i < iterator; i++)
    temp = temp->right;

  return temp;
}

template <class God> requires std::equality_comparable<God>
God * Link<God>::operator[](int iterator) {
  if (iterator >= size())
    error("out of range");

  Link *temp = this->right;

  for (int i = 0; i < iterator; i++)
    temp = temp->right;

  return temp->element;
}


template <class God> requires std::equality_comparable<God>
int Link<God>::size() const {
  const Link *temp = this;
  int count = 0;

  while (temp->right) {
    ++count;
    temp = temp->right;
  }

  return count;
}


/***********************
 ***********************
 ***********************
 *end Link class impl  *
 ***********************
 ***********************
 ***********************/


void test() {
  using vector::Vector;

  Vector<Pair<char, unsigned short int>> var_table;

  std::cout << "Enter var_table as { name val, name2 val2 }:";
  std::cin >> var_table;

  std::cout << var_table;
}


void test_4() {
  Link<std::string> bam;
  bam.add("Biba");
  bam.add("Albam");
  bam.add("Boba");
  bam.erase("Albam");
  bam.erase("Albam");

}

std::ostream& operator<<(std::ostream & lhs, const Int & int_) {
  return int_.operator<<(lhs);
}

std::istream& operator>>(std::istream & is, Int & int_) {
  return int_.operator>>(is);
}




void test_7() {
  using namespace ch18::vector;

  Vector<Number<double>> d_vector(2,2.1);
  Vector<Number<int>> i_vector(2,4);

  std::cout << sum_multiply(d_vector,i_vector);
}

void test_6() {
  Number<double> dd (3.5);
  Number<int> ii(10);

  using  namespace  std;

  cout << dd << '\t' << ii << '\n';
  auto k = dd%2.;
  cout << (dd % 2.) << '\t';
  cout << ii % 3;
}

void test_5() {
  Int i(Int(10));
  using namespace std;

  cout << i << endl;
  cin >> i;
  cout << i << endl;

  cout << i + 3 << '\t' << i * 4 << '\t' << i / 3 << '\t' << i - 5<< '\n' ;

  i = Int(10);

  cout << i;

}

template <typename T, typename U>
std::istream &operator>>(std::istream &is,
                         vector::Vector<Pair<T, U>> &var_table) {
  // input format: { name val, name2 val2 , name3 val3 }
  char separator;
  Pair<T, U> temp;
  is >> separator;

  while (is >> temp.name >> temp.val >> separator) {
    var_table.push_back(temp);

    if (separator == '}') {
      break;
    }
  }
  return is;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os,
                         const vector::Vector<Pair<T, U>> &var_table) {
  for (const auto &el : var_table) {
    os << el.name << " = " << el.val << std::endl;
  }

  return os;
}
} // namespace ch18::ex

namespace ch18::drill {
template <class T> T &S<T>::access() { return val; }
template <class T> const T &S<T>::access() const { return val; }
template <class T> S<T> &S<T>::operator=(const T &for_copy) {
  T temp = for_copy;
  std::swap(temp, val);
  return *this;
}
template <typename T> void read_val(T &v) { std::cin >> v; }
} // namespace ch18::drill

namespace ch18::try_ {
template <typename T, typename U> void suspicious() {
  constexpr int count = 10;
  T *p = static_cast<T *>(operator new(sizeof(T) * count));
  U *q = static_cast<U *>(operator new(sizeof(U) * count));

  try {
    for (int i = 0; i < count; ++i) {
      std::construct_at(p + i, static_cast<T>(i + 1));
      std::construct_at(q + i, static_cast<U>(i * i));

      std::cout << "p[" << i << "] = " << p[i] << "   "
                << "q[" << i << "] = " << q[i] << std::endl;
    }
    throw std::runtime_error("Error");
  } catch (const std::exception &ex) {
    std::cerr << "Caught!";
    operator delete(p);
    operator delete(q);
    throw;
  }

  catch (...) {
    std::destroy(p, p + count);
    std::destroy(q, q + count);
    std::cerr << "Caught!";
    operator delete(p);
    operator delete(q);
    throw;
  }

  std::destroy(p, p + count);
  std::destroy(q, q + count);
  operator delete(p);
  operator delete(q);
}
} // namespace ch18::try_
