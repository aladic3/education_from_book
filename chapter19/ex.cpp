//
// Created by Dmytrenko Kyrylo on 23.10.2026.
//
module;
#include <iostream>
#include <list>
#include <vector>
#include <span>
#include <__filesystem/path.h>

module chapter19;
import chapter18;

namespace ch19::ex {
void ex2_4() {
  //std::vector<ch18::try_::Somethink> a3 (3);
  //std::array<int, 5> a1 {1,2,3,4,5};
  //std::vector<int> a2 {};
  /*const auto path =
    std::filesystem::path(PROJECT_SOURCE_DIR) / "data" / "file1.txt";*/
  /*std::cout << path.string() <<
    '\t' << path.filename() << '\n';*/
  //std::ifstream file(path);

  //ch18::ex::File_handle file1 {path};
  //auto a = file1.get_separated_words_from_file();
  //ch19::try_::print_range(a.begin(),a.end());
  //auto ia1 = high(a1.begin(),a1.end());
  //auto ia2 = high(a2.begin(),a2.end());
  //auto ia3 = high(a3.begin(),a3.end());
  //ds
  int count = 0;
  double* jack_array = get_from_jack(count);
  auto jill_vector = get_from_jill();

  double* jack_high = high_v2(jack_array, jack_array + count);
  auto jill_high = high_v2(jill_vector.begin(), jill_vector.end());

  std::cout << "Jack high: " << *jack_high << "\nJill high: " << *jill_high;
  delete[] jack_array;
}

void ex5() {



  ch18::vector::Vector<std::string> str_v;
  ch18::vector::Vector<int> int_v;
  ch18::vector::Vector<float> float_v;

  std::cout << "input str v: ";
  std::cin >> str_v;
  std::cout << str_v;
  std::cout << "input int v: ";
  std::cin >> int_v;
  std::cout << int_v;
  std::cout << "input float v: ";
  std::cin >> float_v;
  std::cout << float_v;
}

std::vector<double> get_from_jill() {
  std::vector<double> result;
  result.reserve(10);
  const auto path =
    std::filesystem::path(PROJECT_SOURCE_DIR) / "data" / "jill.txt";
  ch18::ex::File_handle file_handle {path};

  auto* file = file_handle.get_file();
  double temp = 0;

  while (*file >> temp)
    result.push_back(temp);

  return result;
}

double * get_from_jack(int &count) {
  count = 0;
  const auto path =
    std::filesystem::path(PROJECT_SOURCE_DIR) / "data" / "jack.txt";
  ch18::ex::File_handle file_handle {path};

  auto* file = file_handle.get_file();
  double temp;

  while (*file >> temp) ++count;

  file->clear();
  file->seekg(0);
  auto* array = new double[count];

  for (int i = 0; i < count; ++i) {
    *file >> temp; // for debug
    array[i] = temp;
  }

  return array;
}

}