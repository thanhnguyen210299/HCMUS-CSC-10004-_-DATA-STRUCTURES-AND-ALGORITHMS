#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

enum Color {RED, BLACK, DOUBLE_BLACK};

struct WORD
{
	string m_Word;
	string m_Meaning;
};

struct Node
{
	WORD _Word;
	int _Color;
	Node *_Left, *_Right, *_Parent;

	Node(WORD p)
	{
		_Word.m_Word = p.m_Word;
		_Word.m_Meaning = p.m_Meaning;
		_Color = RED;
		_Left = _Right = _Parent = NULL;
	}
};

class RBTree
{
private:
	Node *root;
protected:
	void rotateLeft(Node *&);
	void rotateRight(Node *&);
	void fixInsert(Node *&);
	void fixDelete(Node *&);
	void inorderBST(Node *&, ofstream&);
	int getColor(Node *&);
	void setColor(Node *&, int);
	Node *minValue(Node *&);
	Node *maxValue(Node *&);
	Node *insertBST(Node *&, Node *&);
	Node *deleteBST(Node *&, WORD);
	int getBlackHeight(Node *);
	void clear(Node *&);
	int getHeight(Node *);
public:
	static int countWords;
	RBTree() { root = NULL; }
	void insert(const WORD &);
	void remove(WORD);
	void inorder(string fileName);
	Node* search(string);
	void addUsage(Node *&, string);
	void edit(Node *&, string);
	string getMeaning(Node *);
	int getHeight();
	~RBTree();
};

