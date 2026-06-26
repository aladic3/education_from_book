//
// Created by Dmytrenko Kyrylo on 21.06.2026.
//
module;
#include <vector>
#include <iostream>
#include "./../error.h"
module chapter17;

namespace ch17::ex {

Matrix::Matrix(int rr, int cc): rows_count(rr), column_count(cc){
  rows.resize(rr);

  for (vector<double>& row : rows)
    row.resize(cc);
}
Matrix::Matrix(const Matrix &m): rows(m.rows), column_count(m.column_count), rows_count(m.rows_count){}

Matrix::Matrix(Matrix &&m): column_count(m.column_count), rows_count(m.rows_count), rows(std::move(m.rows)) {
  m.column_count = m.rows_count = 0;
}

Matrix &Matrix::operator=(const Matrix &m) {
  rows = m.rows;
  column_count = m.column_count;
  rows_count = m.rows_count;
}

Matrix &&Matrix::operator=(Matrix &&m) {
  rows = std::move(m.rows);
  column_count = m.column_count;
  rows_count = m.rows_count;
  m.column_count = m.rows_count = 0;
}
double &Matrix::operator[](int rr, int cc) {
  vector<double>& row = rows[rr];
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

bool Matrix::operator==(const Matrix &) const {}

__wrap_iter<vector<vector<double>>::__alloc_traits::pointer> Matrix::begin() {
  return rows.begin();
}
__wrap_iter<vector<vector<double>>::__alloc_traits::pointer> Matrix::end() {
  return rows.end();
}

Matrix::~Matrix() = default;


void print_matrix( Matrix &m) {
   for ( auto& row : m) {
     for ( auto& el : row) {
       std::cout << el << " ";
     }
     std::cout << "\n";
   }
}

Matrix move_test() {
  Matrix m(5,5);

  for (int i = 0; i < m.row_size(); ++i)
    for (int j = 0; j < m.column_size(); ++j) {
      m[i,j] = j + i*m.column_size();
    }

  return m;
}

void test() {
  Matrix m(10,4);
  Matrix m_test1 = move_test();
  Matrix m_test2 = move_test();
  Matrix addition_test = m_test1+m_test2;

  Matrix copy_test = m;

  std::cout << "addition_test:\n";
  print_matrix(addition_test);

  for (int i = 0; i < m.row_size(); ++i)
    for (int j = 0; j < m.column_size(); ++j) {
      m[i,j] = j + i*m.column_size();
    }

  Matrix copy_test2 {m};
  std::cout << "m:\n";
  print_matrix(m);

  std::cout << "m_test1:\n";
  print_matrix(m_test1);

  std::cout << "m_test2:\n";
  print_matrix(m_test2);

  std::cout << "copy_test:\n";
  print_matrix(copy_test);

  std::cout << "copy_test2:\n";
  print_matrix(copy_test2);

  return;
}
}
