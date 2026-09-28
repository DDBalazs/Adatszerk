#ifndef ADATSZERK_L03_FIXEDINTSTACK_HPP
#define ADATSZERK_L03_FIXEDINTSTACK_HPP

#include "exceptions.hpp"
#include <iostream>

class FixedIntStack {
public:
  FixedIntStack() : array() {
    head = 0;
  }

  ~FixedIntStack() = default;

  bool isEmpty() const {
    return head == 0;
  }

  void push(int new_item) {
    if (head >= CAPACITY) {
      throw OverflowException(); // Ha tele van a verem, kivételt dobunk
    }
    array[head] = new_item;
    head++; // Növeljük a head értékét, miután betettük az elemet
  }

  int top() const {
    if (isEmpty()) {
      throw UnderflowException(); // Ha üres, kivételt dobunk
    }
    return array[head - 1];
  }

  int pop() {
    if (isEmpty()) {
      throw UnderflowException(); // Ha üres, kivételt dobunk
    }
    head--; // Csökkentjük a head-et
    return array[head]; // Visszaadjuk a kivett elemet
  }

  void print() const {
    for (int i = 0; i < head; i++) {
      // A szintaktikai hiba javítva: "head - 1" a "head 1" helyett
      std::cout << array[i] << (i == head - 1 ? "" : ", ");
    }
  }

private:
  static const int CAPACITY = 10;
  int array[CAPACITY];
  int head;
};

#endif // ADATSZERK_L03_FIXEDINTSTACK_HPP