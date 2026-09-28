#ifndef ADATSZERK_L03_FIXEDSTACK_HPP
#define ADATSZERK_L03_FIXEDSTACK_HPP

#include "exceptions.hpp"
#include <iostream>

template <class T> class FixedStack {
public:
  FixedStack() : array() {
    head = 0;
  }

  ~FixedStack() = default;

  bool isEmpty() const {
    return head == 0;
  }

  void push(T new_item) {
    if (head >= CAPACITY) {
      throw OverflowException();
    }
    array[head] = new_item;
    head++;
  }

  T top() const {
    if (isEmpty()) {
      throw UnderflowException();
    }
    return array[head - 1];
  }

  T pop() {
    if (isEmpty()) {
      throw UnderflowException();
    }
    head--;
    return array[head];
  }

  void print() const {
    for (int i = 0; i < head; i++) {
      std::cout << array[i] << (i == head - 1 ? "" : ", ");
    }
  }

private:
  static const int CAPACITY = 10;
  T array[CAPACITY];
  int head;
};

#endif // ADATSZERK_L03_FIXEDSTACK_HPP