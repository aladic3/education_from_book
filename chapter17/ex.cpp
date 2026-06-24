//
// Created by Dmytrenko Kyrylo on 21.06.2026.
//
module;
#include <vector>
#include <iostream>
module chapter17;

namespace ch17::ex {

Matrix::Matrix(int rr, int cc): rs(rr), cs(cc){
  rows.resize(rr);

  for (vector<double>& row : rows)
    row.resize(cc);
}
double &Matrix::operator[](int rr, int cc) {
  vector<double>& row = rows[rr];
  return row[cc];
}
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

void test() {
  Matrix m(10,4);
  for (int i = 0; i < m.row_size(); ++i)
    for (int j = 0; j < m.column_size(); ++j) {
      m[i,j] = j + i*m.column_size();
    }
  print_matrix(m);

  return;
}
}
