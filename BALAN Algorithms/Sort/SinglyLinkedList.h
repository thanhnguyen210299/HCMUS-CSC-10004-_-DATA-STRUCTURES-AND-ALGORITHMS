#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include "Node.h"

class SinglyLinkedList {
protected:
	Node * head;
	Node * tail;
	int itemCount;
	Node * getPointerTo(int) const;
	void copyList(const SinglyLinkedList &);
public:
	SinglyLinkedList();
	SinglyLinkedList(int);
	SinglyLinkedList(const SinglyLinkedList &);
	virtual ~SinglyLinkedList();
	bool isEmpty() const;
	int getLength() const;
	bool search(const int &) const;
	void print() const;
	int getFirst() const;
	int getLast() const;
	int get(int) const;
	void set(const int &, int);
	void insertFirst(const int &);
	void insertLast(const int &);
	void insert(const int &);
	void removeFirst();
	void removeLast();
	void remove(const int &);
	void clear();
	SinglyLinkedList & operator=(const SinglyLinkedList &);
};

#endif