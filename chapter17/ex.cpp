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

Matrix::Matrix(int rr, int cc): rows_count(rr), column_count(cc){
  rows.resize(rr);

  for (int i = 0; i < rr; ++i)
    rows[i] = new double[cc];
}
Matrix::Matrix(const Matrix &m): column_count(m.column_count), rows_count(m.rows_count) {
  rows.resize(rows_count);
  for (int i = 0; i < rows_count; ++i) {
    rows[i] = new double[column_count];

    for (int j = 0; j < column_count; ++j) {
      rows[i][j] = m.rows[i][j];
    }
  }
}

Matrix::Matrix(Matrix &&m): column_count(m.column_count), rows_count(m.rows_count) {
  rows.resize(rows_count);
  for (int i = 0; i < m.rows_count; ++i) {
    rows[i] = m.rows[i];
    m.rows[i] = nullptr;
  }
  m.column_count = m.rows_count = 0;
  m.rows.clear();
}

Matrix &Matrix::operator=(const Matrix &m) {
  clear_matrix();
  column_count = m.column_count;
  rows_count = m.rows_count;
  rows.resize(rows_count);

  for (int i = 0; i < rows_count; ++i) {
    rows[i] = new double[column_count];

    for (int j = 0; j < column_count; ++j) {
      rows[i][j] = m.rows[i][j];
    }
  }

  return *this;
}

Matrix& Matrix::operator=(Matrix &&m) {
  clear_matrix();
  rows.resize(m.rows_count);
  column_count = m.column_count;
  rows_count = m.rows_count;

  for (int i = 0; i < m.rows_count; ++i) {
    rows[i] = m.rows[i];
    m.rows[i] = nullptr;
  }

  m.rows.clear();
  m.column_count = m.rows_count = 0;

  return *this;
}



double &Matrix::operator[](int rr, int cc) {
  double*& row = rows[rr];
  return row[cc];
}
double Matrix::operator[](int row, int coll) const {
  return rows[row][coll];
}

Matrix Matrix::operator+(const Matrix &m) const {
  if (column_count != m.column_count || rows_count != m.rows_count) {
    error("can't summ matrix with different sizes");
    throw;
  }

  Matrix result{*this};
  for (int i = 0; i < rows_count; ++i) {
    for (int j = 0; j < column_count; ++j)
      result[i,j] += m[i,j];
  }

  return result;
}

bool Matrix::operator==(const Matrix & m) const {
  if (this == &m)
    return true;
  if (column_count != m.column_count || rows_count != m.rows_count)
    return false;

  for (int i = 0; i < rows_count; ++i)
    for (int j = 0; j < column_count; ++j)
      if (rows[i][j] != m.rows[i][j])
        return false;

  return true;
}

__wrap_iter<vector<double*>::__alloc_traits::pointer> Matrix::begin() {
  return rows.begin();
}
__wrap_iter<vector<double*>::__alloc_traits::pointer> Matrix::end() {
  return rows.end();
}
__wrap_iter<vector<double *>::__alloc_traits::const_pointer>
Matrix::begin() const {
  return rows.begin();
}
__wrap_iter<vector<double *>::__alloc_traits::const_pointer>
Matrix::end() const {
  return rows.end();
}

Matrix::~Matrix() {
  for (auto& row : rows) {
    delete [] row;
  }
}

void Matrix::clear_matrix() {
  for (auto& row : rows) {
    delete[] row;
    row = nullptr;
  }
  rows.clear();
  column_count = rows_count = 0;
}

void print_matrix(std::ostream& os, const Matrix &m) {
   for (const auto & row : m) {
     for (int j = 0; j < m.column_count_(); ++j) {
       os << row[j] << " ";
     }
     os << "\n";
   }
}

Matrix move_test() {
  Matrix m(5,5);

  for (int i = 0; i < m.rows_count_(); ++i)
    for (int j = 0; j < m.column_count_(); ++j) {
      m[i,j] = j + i*m.column_count_();
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
    << "Count of rows: " << matrix.rows_count_() << "\n"
    << "Count of columns: " << matrix.column_count_() << "\n";

  for (int i = 0; i < matrix.rows_count_(); ++i) {
      *os << "Inputting of " << i << " row: \n";

      for (int j = 0; j < matrix.column_count_(); ++j) {
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


  Matrix m(10,4);
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

  for (int i = 0; i < m.rows_count_(); ++i)
    for (int j = 0; j < m.column_count_(); ++j) {
      m[i,j] = j + i*m.column_count_();
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
