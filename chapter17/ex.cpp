//
// Created by Dmytrenko Kyrylo on 21.06.2026.
//
module;
#include <vector>
#include <iostream>
module chapter17;

namespace ch17::ex {

Matrix::Matrix(int rr, int cc){
  rows.resize(rr);

  for (vector<double>*& row : rows)
    row = new vector<double>(cc);
}
double &Matrix::operator[](int rr, int cc) {
  vector<double>*& row = rows[rr];
  return (*row)[cc];
}
vector<double> *&Matrix::begin() {
  return *rows.begin();
}
vector<double> *&Matrix::end() {
  return *rows.end();
}

Matrix::~Matrix(){
  for (auto row: rows)
    delete row;
}

// TODO must leart iterator topic
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
  m[0,0] = 10;
  print_matrix(m);
  return;
}
}
