//
// Created by Dmytrenko Kyrylo on 18.06.2026.
//
module;

module chapter17;
#include "../error.h"

namespace ch17::drill {
    Ptr::Ptr() {
      elem = new double;
    }
    Ptr::Ptr(double val) {
       elem = new double(val);
    }

    Ptr::~Ptr() {
      delete elem;
    }

    Ptr::Ptr(Ptr &ptr) {
      elem = new double(*ptr.elem);
    }

    Ptr::Ptr(Ptr &&ptr)  noexcept {
      elem = ptr.elem;
      ptr.elem = nullptr;
    }

    Ptr& Ptr::operator=(const Ptr &ptr) {
      if (this == &ptr) return *this;
      delete elem;
      elem = new double(*ptr.elem);
      return *this;
    }
    Ptr &Ptr::operator=(Ptr &&ptr)  noexcept {
      if (this == &ptr) return *this;
      delete elem;
      elem = ptr.elem;
      ptr.elem = nullptr;
      return *this;
    }

    void test() {
      Ptr* p = new Ptr(3);

      delete p;
    }

    } // namespace ch17::drill