//
// Created by Dmytrenko Kyrylo on 18.06.2026.
//
module;
#include "../error.h"
module chapter17;


namespace ch17::drill {
    Ptr::Ptr() {
      elem = new double(0);
    }
    Ptr::Ptr(double val) {
       elem = new double(val);
    }

    Ptr::~Ptr() {
      delete elem;
      elem = nullptr;
    }

    Ptr::Ptr(Ptr &ptr) {
      elem = new double(*ptr.element());
    }

    Ptr::Ptr(Ptr &&ptr) {
      elem = ptr.elem;
      ptr.elem = nullptr;
    }

    Ptr& Ptr::operator=(const Ptr &ptr) {
      if (this == &ptr) return *this;
      delete elem;
      elem = new double(*ptr.elem);
      return *this;
    }
    Ptr &Ptr::operator=(Ptr &&ptr)  {
      if (this == &ptr) return *this;
      delete elem;
      elem = ptr.elem;
      ptr.elem = nullptr;
      return *this;
    }
    double *Ptr::element() {
      return elem;
    }

    void test() {
      Ptr* p = new Ptr(3);
      Ptr j = *p;
      *j.element() = 10;
      *p->element() = 2;
      delete p;
    }

    } // namespace ch17::drill