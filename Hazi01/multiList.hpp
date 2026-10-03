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
}

template<typename T>
MultiList<T>::~MultiList() noexcept {

}

template<typename T>
int MultiList<T>::getSize() const noexcept {

}

template<typename T>
bool MultiList<T>::insert(const T& value) {
	
}

template<typename T>
bool MultiList<T>::erase(const T& value) {
	
}

template<typename T>
bool MultiList<T>::contains(const T& value) const {
	
}

template<typename T>
MultiList<T>::Node** MultiList<T>::getPrevs(const T& value) const noexcept {
	
}

template<typename T>
MultiList<T>::Node::Node(NodeWithValue** next) {
}

template<typename T>
MultiList<T>::Node::~Node() noexcept {
}

template<typename T>
MultiList<T>::NodeWithValue::NodeWithValue(const T& value, NodeWithValue** next) {
}

#endif