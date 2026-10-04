//
// Created by Dmytrenko Kyrylo on 04.10.2026.
//
module;
#include "../error.h"

#include <filesystem>
#include <functional>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <vector>

export module chapter19;

export namespace ch19::try_ {
void test();
void copy_xd(int* f1, const int* e1, int* f2); // copy using only iterator operations

} // namespace ch19::try_
