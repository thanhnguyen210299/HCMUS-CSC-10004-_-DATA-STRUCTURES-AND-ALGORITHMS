#ifndef NODE_H
#define NODE_H

class Node
{
private:
	int key;
	Node *next;
public:
	Node();
	Node(const int & k);
	Node(const int & k, Node * nextPtr);
	void setKey(const int & k);
	void setNext(Node * nextPtr);
	int getKey() const;
	Node * getNext() const;
}; 

#endif