#ifndef ADATSZERK_L03_DYNAMICINTSTACK_HPP
#define ADATSZERK_L03_DYNAMICINTSTACK_HPP

#include <iostream>
#include "exceptions.hpp"

class DynamicIntStack {
public:
  DynamicIntStack() { pHead = nullptr; }

  ~DynamicIntStack() {
    while (!isEmpty()) {
      pop();
    }
  }

  bool isEmpty() const {
    return pHead == nullptr;
  }

  void push(int new_item) {
    // Új elem létrehozása; az új elem a régi pHead-re fog mutatni,
    // és a pHead mostantól az új elem lesz.
    pHead = new Node(new_item, pHead);
  }

  int top() const {
    if (isEmpty()) {
      throw UnderflowException(); // Ha üres, kivételt dobunk
    }
    return pHead->value;
  }

  int pop() {
    if (isEmpty()) {
      throw UnderflowException(); // Ha üres, kivételt dobunk
    }

    int popped_value = pHead->value; // Kimentjük a visszaadandó értéket
    Node* old_head = pHead;          // Eltároljuk a törlendő node címét
    pHead = pHead->pNext;            // A verem teteje mostantól a következő elem
    delete old_head;                 // Felszabadítjuk a memóriát

    return popped_value;
  }

  void print() const {
    for (const Node *i = pHead; i != nullptr; i = i->pNext) {
      std::cout << i->value << " ";
    }
  }

  DynamicIntStack(const DynamicIntStack &other) {
    if (nullptr != other.pHead) {
      pHead = new Node(other.pHead->value);
      Node *copied = pHead;
      for (Node *i = other.pHead->pNext; i != nullptr; i = i->pNext) {
        copied->pNext = new Node(i->value);
        copied = copied->pNext;
      }
    }
  }

  DynamicIntStack(DynamicIntStack &&other) noexcept {
    // pHead = std::exchange(other.pHead, nullptr);
    pHead = other.pHead;
    other.pHead = nullptr;
  }

  DynamicIntStack &operator=(const DynamicIntStack &rhs) {
    if (this != &rhs) {
      while (!isEmpty()) {
        pop();
      }
      if (nullptr != rhs.pHead) {
        pHead = new Node(rhs.pHead->value);
        Node *copied = pHead;
        for (Node *i = rhs.pHead->pNext; i != nullptr; i = i->pNext) {
          copied->pNext = new Node(i->value);
          copied = copied->pNext;
        }
      }
    }
    return *this;
  }

  DynamicIntStack &operator=(DynamicIntStack &&rhs) noexcept {
    if (this != &rhs) {
      while (!isEmpty()) {
        pop();
      }
      // pHead = std::exchange(other.pHead, nullptr);
      pHead = rhs.pHead;
      rhs.pHead = nullptr;
    }
    return *this;
  }

private:
  class Node {
  public:
    int value;
    Node *pNext;

    Node() : value(0), pNext(nullptr) {}
    Node(const int &_value) : value(_value), pNext(nullptr) {}
    Node(const int &_value, Node *_pNext) : value(_value), pNext(_pNext) {}
  };
  Node *pHead;
};

#endif // ADATSZERK_L03_DYNAMICINTSTACK_HPP