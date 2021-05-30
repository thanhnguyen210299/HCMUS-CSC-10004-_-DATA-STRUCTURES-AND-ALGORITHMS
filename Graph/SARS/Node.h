#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>

class Node
{
private:
	int _value;
	Node * _next;
public:
	Node();
	Node(int);
	int getValue();
	void setValue(int);
	Node * getNext();
	void setNext(Node *);
};

#endif


