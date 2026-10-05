#ifndef MULTILIST_H
#define MULTILIST_H

#include "randomHelper.hpp"

template <typename T>
class MultiList {
public:
    MultiList();
    ~MultiList() noexcept;

    int getSize() const noexcept;

    bool insert(const T&);
    bool erase(const T&);
    bool contains(const T&) const;

private:
    constexpr static int height = 10;
    constexpr static float heightChance = 0.5f;

    struct NodeWithValue; //forward declaration

    struct Node { //Special Node for head
       Node(NodeWithValue**);
       virtual ~Node() noexcept;
       NodeWithValue** next;
    };

    struct NodeWithValue : public Node {
       NodeWithValue(const T&, NodeWithValue**);
       ~NodeWithValue() = default;
       const T value;
    };

    Node* head;

    Node** getPrevs(const T&) const noexcept; //Optional helper function
};

template<typename T>
MultiList<T>::MultiList() {
    NodeWithValue** headNext = new NodeWithValue*[height];

    for (int i=0; i<height; i++) {
       headNext[i] = nullptr;
    }

    head = new Node(headNext);
}

template<typename T>
MultiList<T>::~MultiList() noexcept {

    Node* current = head->next[0];
    while (current != nullptr) {
       Node* nextNode = current->next[0];
       delete current;
       current = nextNode;
    }
    delete head;
}

template<typename T>
int MultiList<T>::getSize() const noexcept {

    int count = 0;
    Node* current = head->next[0];
    while (current != nullptr) {
       count++;
       current = current->next[0];
    }
    return count;
}

template<typename T>
bool MultiList<T>::insert(const T& value) {
    Node** prevs = getPrevs(value);
    NodeWithValue* candidate = prevs[0]->next[0];

    if (candidate != nullptr && candidate->value == value) {
       delete[] prevs;
       return false;
    }

    int newHeight = 1;
    while (newHeight < height && getRandom() < heightChance) {
       newHeight++;
    }

    NodeWithValue** newNexts = new NodeWithValue*[newHeight];
    NodeWithValue* newNode = new NodeWithValue(value, newNexts);

    for (int i = 0; i< newHeight; i++) {
       newNode->next[i] = prevs[i]->next[i];
       prevs[i]->next[i] = newNode;
    }
    delete[] prevs;
    return true;
}

template<typename T>
bool MultiList<T>::erase(const T& value) {

    Node** prevs = getPrevs(value);
    NodeWithValue* candidate = prevs[0]->next[0];

    if (candidate == nullptr || candidate->value != value) {
       delete[] prevs;
       return false;
    }
    for (int i = 0; i< height; i++) {
       if (prevs[i] != nullptr && prevs[i]->next[i] == candidate) {
          prevs[i]->next[i] = candidate->next[i];
       } else {
          break;
       }
    }
    delete candidate;
    delete[] prevs;

    return true;
}

template<typename T>
bool MultiList<T>::contains(const T& value) const {
    Node** prevs = getPrevs(value);
    NodeWithValue* candidate = prevs[0]->next[0];

    bool found = false;
    if (candidate != nullptr && candidate->value == value) {
       found = true;
    }
    delete[] prevs;

    return found;
}

template<typename T>
typename MultiList<T>::Node** MultiList<T>::getPrevs(const T& value) const noexcept {
    Node** prevs = new Node*[height];
    Node* current = head;

    for (int i = height-1; i>=0; i--) {
       while (current->next[i] != nullptr && current->next[i]->value < value) {
          current = current->next[i];
       }
       prevs[i] = current;
    }
    return prevs;
}

template<typename T>
MultiList<T>::Node::Node(NodeWithValue** next_ptr) : next(next_ptr) {
}

template<typename T>
MultiList<T>::Node::~Node() noexcept {
    delete[] next;
}

template<typename T>
MultiList<T>::NodeWithValue::NodeWithValue(const T& val, NodeWithValue** next_prt) : Node(next_prt), value(val) {
}

#endif