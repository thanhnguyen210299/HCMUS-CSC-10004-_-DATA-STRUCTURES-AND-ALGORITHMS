#include <cassert>
#include "SinglyLinkedList.h"
#include "Node.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

// Private area
//////////////////////
Node * SinglyLinkedList::getPointerTo(int pos) const {
	Node * p = head;
	for (int i = 0; i < pos; i++)
		p = p->getNext();
	return p;
}

void SinglyLinkedList::copyList(const SinglyLinkedList & another) {
	Node * p = another.head;
	while (p) {
		insertLast(p->getKey());
		p = p->getNext();
	}
}

// Public area
//////////////////////
SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), itemCount(0) {
}

SinglyLinkedList::SinglyLinkedList(int n) : itemCount(n) {
	for (int i = 0; i < n; i++)
		insertLast(0);
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList & another) : head(nullptr), tail(nullptr), itemCount(0) {
	copyList(another);
}

SinglyLinkedList::~SinglyLinkedList() {
	clear();
}

bool SinglyLinkedList::isEmpty() const {
	return itemCount == 0;
}

int SinglyLinkedList::getLength() const {
	return itemCount;
}

bool SinglyLinkedList::search(const int & k) const {
	Node * p = head;
	while (p) {
		if (p->getKey() == k)
			return true;
		p = p->getNext();
	}
	return false;
}

void SinglyLinkedList::print() const {
	Node * p = head;
	while (p) {
		std::cout << p->getKey() << " ";
		p = p->getNext();
	}
	std::cout << std::endl;
}

int SinglyLinkedList::getFirst() const {
	assert(!isEmpty());
	return head->getKey();
}

int SinglyLinkedList::getLast() const {
	assert(!isEmpty());
	return tail->getKey();
}

int SinglyLinkedList::get(int pos) const {
	assert(0 <= pos && pos < itemCount);
	Node * p = getPointerTo(pos);
	return p->getKey();
}

void SinglyLinkedList::set(const int &k, int pos)
{
	assert(0 <= pos && pos < itemCount);
	Node * p = getPointerTo(pos);
	p->setKey(k);
}

void SinglyLinkedList::insertFirst(const int & k) {
	Node * p = new Node(k);
	if (head == nullptr)
		head = tail = p;
	else {
		p->setNext(head);
		head = p;
	}
	itemCount++;
}

void SinglyLinkedList::insertLast(const int & k) {
	Node * p = new Node(k);
	if (head == nullptr)
		head = tail = p;
	else {
		tail->setNext(p);
		tail = p;
	}
	itemCount++;
}

void SinglyLinkedList::insert(const int & k) {
	int pos = rand() % (getLength() + 1);
	if (pos == 0)
		insertFirst(k);
	else
		if (pos == getLength())
			insertLast(k);
		else {
			Node * p = new Node(k);
			Node * q = getPointerTo(pos - 1);
			p->setNext(q->getNext());
			q->setNext(p);
			itemCount++;
		}
}

void SinglyLinkedList::removeFirst() {
	assert(head != nullptr);
	Node * p = head;
	if (head == tail)
		head = tail = nullptr;
	else
		head = head->getNext();
	delete p;
	itemCount--;
}

void SinglyLinkedList::removeLast() {
	assert(head != nullptr);
	if (head == tail) {
		delete tail;
		head = tail = nullptr;
	}
	else {
		Node * p = getPointerTo(getLength() - 2);
		p->setNext(nullptr);
		delete tail;
		tail = p;
	}
	itemCount--;
}

void SinglyLinkedList::remove(const int & k) {
	assert(head != nullptr);
	if (head->getKey() == k)
		removeFirst();
	else
		if (tail->getKey() == k)
			removeLast();
		else {
			Node * q = head, *p = head->getNext();
			while (p && p->getKey() != k) {
				q = p;
				p = p->getNext();
			}
			if (p) {
				q->setNext(p->getNext());
				delete p;
				itemCount--;
			}
		}
}

void SinglyLinkedList::clear() {
	while (head)
		removeFirst();
}

SinglyLinkedList & SinglyLinkedList::operator=(const SinglyLinkedList & rhs) {
	if (this != &rhs) {
		if (head != nullptr)
			clear();
		copyList(rhs);
	}
	return *this;
}