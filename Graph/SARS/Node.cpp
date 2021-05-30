#include "Node.h"

Node::Node()
{
	_value = 0;
	_next = NULL;
}

Node::Node(int value)
{
	_value = value;
	_next = NULL;
}

int Node::getValue()
{
	return _value;
}

void Node::setValue(int value)
{
	_value = value;
}

Node * Node::getNext()
{
	return _next;
}

void Node::setNext(Node * p)
{
	_next = p;
}