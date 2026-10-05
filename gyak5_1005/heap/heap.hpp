#ifndef HEAP_HPP
#define HEAP_HPP

#include "heap_exceptions.hpp"
#include <cmath>
#include <iostream>
#include <vector>

template<class I>
bool validateHeap(I first, I last);

template<class T>
class Heap {
    static const int MAX_SIZE = 12;
    T array[MAX_SIZE];
    size_t size;

    std::size_t _parent(std::size_t index);
    std::size_t _left(std::size_t index);
    std::size_t _right(std::size_t index);
    void lift_down(std::size_t index);
    void lift_up(std::size_t index);

public:
    Heap();
    bool isempty();
    void insert(T a);
    T delmax();
    T max();
};

template<class T>
Heap<T>::Heap() {
    size = 0;
}

template<class T>
bool Heap<T>::isempty() {
    return true;
}

template<class T>
T Heap<T>::max() {
    if (size==0)
        throw HeapOverflow();
    return array[0];
}

template<class T>
std::size_t Heap<T>::_parent(std::size_t index) {
    index = (index-1) / 2;
    return index;
}

template<class T>
std::size_t Heap<T>::_left(std::size_t index) {
    index = (index + 1) / 2;
    return index;
}

template<class T>
std::size_t Heap<T>::_right(std::size_t index) {
    index = (index + 2) / 2;
    return index;
}

template<class T>
void Heap<T>::lift_up(std::size_t index) {
    while (index > 0) {
        array[index] = array[_parent(index)];
        swap(array[index], array[_parent(index)]);
        index = _parent(index);
    }
}

template<class T>
void Heap<T>::lift_down(std::size_t index) {
    while (_right(index) < size && max(array[_right(index)], array[_left(index)] > array[_right(index)])) {
        if (array[_left(index)] > array[_right(index)]) {
            swap(array[_left(index)]);
        } else {
            swap(array[_right(index)]);
        }
    }
}

template<class T>
void Heap<T>::insert(T a) {
    array[size] = a;
    size++;
    lift_up(size-1);
}

template<class T>
T Heap<T>::delmax() {
    T tmp = array[0];
    swap(array[0], array[--size]);
    return tmp;
}


template<class I>
bool validateHeap(I first, I last) {
    if (last > first) {
        for (int i = 0; i < (last - first) / 2; ++i) {
            if ((first + 2 * i + 1) < last && *(first + i) < *(first + 2 * i + 1))
                return false;
            if ((first + 2 * i + 2) < last && *(first + i) < *(first + 2 * i + 2))
                return false;
        }
        return true;
    } else
        throw InvalidIterator();
}

#endif // HEAP_HPP
