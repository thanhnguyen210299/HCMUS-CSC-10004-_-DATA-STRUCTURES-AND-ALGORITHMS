#include <cstddef>
#include "Node.h"

Node::Node() : next(nullptr) {
}

Node::Node(const int & k) : key(k), next(nullptr) {
}

Node::Node(const int & k, Node * nextPtr) : key(k),
next(nextPtr) {
}

void Node::setKey(const int & k) {
	key = k;
}

void Node::setNext(Node * nextPtr) {
	next = nextPtr;
}

int Node::getKey() const {
	return key;
}

Node * Node::getNext() const {
	return next;
}
