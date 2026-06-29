//
// Created by Dmytrenko Kyrylo on 21.06.2026.
//
module;
#include <vector>
#include <iostream>
#include "./../error.h"

#include <sstream>
module chapter17;

namespace ch17::ex {

Matrix::Matrix() : _rows(0), c_count(0), r_count(0){}

Matrix::Matrix(initializer_list<initializer_list<double>> init_list):
    r_count(static_cast<int>(init_list.size())),
    c_count(static_cast<int>(init_list.begin()->size())),
    _rows(r_count){

  int rows_iterator = 0;

  for (auto row : init_list) {
    if (row.size() != c_count)
      error("each row must be with one size");

    int cols_iterator = 0;
    _rows[rows_iterator] = new double[column_count()];
    for (double el : row) {
      operator[](rows_iterator,cols_iterator) = el;
      ++cols_iterator;
    }

    ++rows_iterator;
  }
}

Matrix::Matrix(int rows, int cols, double val) : r_count(rows), c_count(cols),
    _rows(r_count) {
  for (auto& row : _rows) {
    row = new double[c_count];

    for (int i = 0; i < c_count; ++i)
      row[i] = val;

  }
}

Matrix &Matrix::operator+=(const Matrix &m) {
  if (m.rows_count() > r_count || m.column_count() > c_count)
    error("cant add bigger matrix");

  for (int i = 0; i < m.rows_count(); ++i) {
    for (int j = 0; j < m.column_count(); ++j) {
      operator[](i,j) += m[i,j];
    }
  }

  return *this;
}

Matrix &Matrix::operator-=(const Matrix &m) {
  if (m.rows_count() > r_count || m.column_count() > c_count)
    error("cant minus bigger matrix");

  for (int i = 0; i < m.rows_count(); ++i) {
    for (int j = 0; j < m.column_count(); ++j) {
      operator[](i,j) -= m[i,j];
    }
  }

  return *this;
}

Matrix &Matrix::operator+=(double el) {
  for (auto& row : _rows) {
    for (int i = 0; i < c_count; ++i)
      row[i] += el;

  }

  return *this;
}

Matrix &Matrix::operator-=(double el) {
  for (auto& row : _rows) {
    for (int i = 0; i < c_count; ++i)
      row[i] -= el;

  }

  return *this;
}

bool Matrix::operator!=(const Matrix & m) const {
  return !(*this==m);
}

void Matrix::resize(int new_rows, int new_columns) {
  double default_value = 0;
  if (new_rows < rows_count() || new_columns < column_count())
    return;

  vector<double*> new_matrix(new_rows);

  for (auto& row : new_matrix) {
    row = new double[new_columns];
    for (int i = 0; i < new_columns; ++i)
      row[i] = default_value;
  }

  for (int i = 0; i < r_count; ++i) { // copy from old
    for (int j = 0; j < c_count; ++j)
      new_matrix[i][j] = operator[](i,j);
  }

  clear_matrix();
  _rows = std::move(new_matrix);
  r_count = new_rows;
  c_count = new_columns;
}
void Matrix::transpose() {
  vector<double*> new_matrix(c_count);

  for (int i = 0; i < c_count; ++i) {
    new_matrix[i]= new double[rows_count()];
    for (int j = 0; j < rows_count(); ++j) {
      new_matrix[i][j] = operator[](j,i);
    }

  }

  int new_rows = c_count;
  int new_columns = r_count;

  clear_matrix();
  _rows = std::move(new_matrix);
  r_count = new_rows;
  c_count = new_columns;
}

void Matrix::fill(double el) {
  for (auto& row : _rows) {
    for (int i = 0; i < c_count; ++i) {
      row[i] = el;
    }
  }
}

Matrix::Matrix(int rr, int cc): r_count(rr), c_count(cc){
  _rows.resize(rr);

  for (int i = 0; i < rr; ++i)
    _rows[i] = new double[cc];
}
Matrix::Matrix(const Matrix &m): c_count(m.c_count), r_count(m.r_count) {
  _rows.resize(r_count);
  for (int i = 0; i < r_count; ++i) {
    _rows[i] = new double[c_count];

    for (int j = 0; j < c_count; ++j) {
      _rows[i][j] = m._rows[i][j];
    }
  }
}

Matrix::Matrix(Matrix &&m): c_count(m.c_count), r_count(m.r_count) {
  _rows.resize(r_count);
    for (int i = 0; i < m.r_count; ++i) {
      _rows[i] = m._rows[i];
      m._rows[i] = nullptr;
    }

    m.c_count = m.r_count = 0;
    m._rows.clear();
}

std::vector<double> Matrix::row(int i) const {
    std::vector<double> result(c_count);
    for (int j = 0; j < c_count; ++j) {
      result[j] = operator[](i,j);
    }

    return result;
}

std::vector<double> Matrix::column(int i) const {
  std::vector<double> result(r_count);
  for (int j = 0; j < r_count; ++j) {
    result[j] = operator[](j,i);
  }

  return result;
}

Matrix &Matrix::operator=(const Matrix &m) {
  clear_matrix();
  c_count = m.c_count;
  r_count = m.r_count;
  _rows.resize(r_count);

  for (int i = 0; i < r_count; ++i) {
    _rows[i] = new double[c_count];

    for (int j = 0; j < c_count; ++j) {
      _rows[i][j] = m._rows[i][j];
    }
  }

  return *this;
}

Matrix& Matrix::operator=(Matrix &&m) {
  clear_matrix();
  _rows.resize(m.r_count);
  c_count = m.c_count;
  r_count = m.r_count;

  for (int i = 0; i < m.r_count; ++i) {
    _rows[i] = m._rows[i];
    m._rows[i] = nullptr;
  }

  m._rows.clear();
  m.c_count = m.r_count = 0;

  return *this;
}



double &Matrix::operator[](int rr, int cc) {
  double*& row = _rows[rr];
  return row[cc];
}
double Matrix::operator[](int row, int coll) const {
  return _rows[row][coll];
}

Matrix Matrix::operator+(const Matrix &m) const {
  if (c_count != m.c_count || r_count != m.r_count) {
    error("can't summ matrix with different sizes");
    throw;
  }

  Matrix result{*this};
  for (int i = 0; i < r_count; ++i) {
    for (int j = 0; j < c_count; ++j)
      result[i,j] += m[i,j];
  }

  return result;
}

bool Matrix::operator==(const Matrix & m) const {
  if (this == &m)
    return true;
  if (c_count != m.c_count || r_count != m.r_count)
    return false;

  for (int i = 0; i < r_count; ++i)
    for (int j = 0; j < c_count; ++j)
      if (_rows[i][j] != m._rows[i][j])
        return false;

  return true;
}

__wrap_iter<vector<double*>::__alloc_traits::pointer> Matrix::begin() {
  return _rows.begin();
}
__wrap_iter<vector<double*>::__alloc_traits::pointer> Matrix::end() {
  return _rows.end();
}
__wrap_iter<vector<double *>::__alloc_traits::const_pointer>
Matrix::begin() const {
  return _rows.begin();
}
__wrap_iter<vector<double *>::__alloc_traits::const_pointer>
Matrix::end() const {
  return _rows.end();
}

Matrix::~Matrix() {
  for (auto& row : _rows) {
    delete [] row;
  }
}

void Matrix::clear_matrix() {
  for (auto& row : _rows) {
    delete[] row;
    row = nullptr;
  }
  _rows.clear();
  c_count = r_count = 0;
}

void print_matrix(std::ostream& os, const Matrix &m) {
   for (const auto & row : m) {
     for (int j = 0; j < m.column_count(); ++j) {
       os << row[j] << " ";
     }
     os << "\n";
   }
}

Matrix move_test() {
  Matrix m(5,5);

  for (int i = 0; i < m.rows_count(); ++i)
    for (int j = 0; j < m.column_count(); ++j) {
      m[i,j] = j + i*m.column_count();
    }

  return m;
}


std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
  print_matrix(os, matrix);
  return os;
}

std::istream &operator>>(std::istream &is, Matrix &matrix) {
  std::ostream* os = &std::cout;
  std::ostringstream trash;
  if (&is != &std::cin) os = &trash;

  *os << "Process of inputting each element matrix...\n"
    << "Count of rows: " << matrix.rows_count() << "\n"
    << "Count of columns: " << matrix.column_count() << "\n";

  for (int i = 0; i < matrix.rows_count(); ++i) {
      *os << "Inputting of " << i << " row: \n";

      for (int j = 0; j < matrix.column_count(); ++j) {
        std::string input;
        is >> input;

        if (!is) return is;

        if (input.size() == 1 && !std::isdigit(input[0]))
          return is;

        std::istringstream field {input};// from one space/tab/new_line to another
        double value_of_matrix;

        if (!(field >> value_of_matrix) )
          error("bad input.");

        matrix[i,j] = value_of_matrix;
      }
  }


  return is;

}

void test() {

  Matrix mm;
  Matrix m_init_list{{1,2,3},{4,5,6}};

  std::vector<double> column = m_init_list.column(2);
  std::vector<double> row = m_init_list.row(1);

  std::cout << "column";
  for (auto el : column)
    std::cout << el << ' ';
  std::cout << "\n";

  std::cout << "row";
  for (auto el : row)
    std::cout << el << ' ';
  std::cout << "\n";
  //Matrix m_init_list2{{1,2},{4,5,6}};

  std::cout << m_init_list;
  m_init_list.transpose();
  std::cout << m_init_list;
  m_init_list.resize(5,10);
  std::cout << m_init_list;
  m_init_list.transpose();
  std::cout << m_init_list;



  Matrix m(10,4,10);
  //m_init_list+=m;
  m_init_list-=m;
  std::cout << m_init_list;
  m_init_list+=1;
  std::cout << m_init_list;
  m_init_list-=11;
  std::cout << m_init_list;


  mm.resize(10,3);
  mm.fill(1);

  std::cout << mm;

  std::cin >> m;
  std::cout << m;

  std::cout << "istringstream input_str:\n";
  std::istringstream input_str {"1.2 3.4 5"};
  input_str >> m;
  std::cout << m;

  Matrix m_test1 = move_test();
  Matrix m_test2 = move_test();
  Matrix addition_test = m_test1+m_test2;

  Matrix copy_test = m;

  std::cout << "addition_test:\n";
  print_matrix(std::cout,addition_test);

  for (int i = 0; i < m.rows_count(); ++i)
    for (int j = 0; j < m.column_count(); ++j) {
      m[i,j] = j + i*m.column_count();
    }

  Matrix copy_test2 {m};
  std::cout << "m:\n";
  print_matrix(std::cout,m);

  std::cout << "m_test1:\n";
  print_matrix(std::cout,m_test1);

  std::cout << "m_test2:\n";
  print_matrix(std::cout,m_test2);

  std::cout << "copy_test:\n";
  print_matrix(std::cout,copy_test);

  std::cout << "copy_test2:\n";
  print_matrix(std::cout,copy_test2);

  std::cout << "operator== test:" << (copy_test2 == copy_test) << " " <<
    (copy_test2 == m) <<  (m == m) <<'\n';

  return;
}
}
