#include "RBTree.h"
#include <string>
#include <math.h>

using namespace std;
int RBTree::countWords = 0;

void RBTree::rotateLeft(Node *&ptr)
{
	Node *right_child = ptr->_Right;
	ptr->_Right = right_child->_Left;

	if (ptr->_Right != NULL)
		ptr->_Right->_Parent = ptr;

	right_child->_Parent = ptr->_Parent;

	if (ptr->_Parent == NULL)
		root = right_child;
	else
	{
		if (ptr == ptr->_Parent->_Left)
			ptr->_Parent->_Left = right_child;
		else
			ptr->_Parent->_Right = right_child;
	}

	right_child->_Left = ptr;
	ptr->_Parent = right_child;
}

void RBTree::rotateRight(Node *&ptr)
{
	Node *left_child = ptr->_Left;
	ptr->_Left = left_child->_Right;

	if (ptr->_Left != NULL)
		ptr->_Left->_Parent = ptr;

	left_child->_Parent = ptr->_Parent;

	if (ptr->_Parent == NULL)
		root = left_child;
	else
	{
		if (ptr == ptr->_Parent->_Left)
			ptr->_Parent->_Left = left_child;
		else
			ptr->_Parent->_Right = left_child;
	}

	left_child->_Right = ptr;
	ptr->_Parent = left_child;
}

void RBTree::fixInsert(Node *&ptr)
{
	Node * parent = NULL;
	Node *grand = NULL;
	while (ptr != root && getColor(ptr) == RED && getColor(ptr->_Parent) == RED)
	{
		parent = ptr->_Parent;
		grand = parent->_Parent;
		if (parent == grand->_Left)
		{
			Node *uncle = grand->_Right;
			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grand, RED);
				ptr = grand;
			}
			else
			{
				if (ptr == parent->_Right)
				{
					rotateLeft(parent);
					ptr = parent;
					parent = ptr->_Parent;
				}
				rotateRight(grand);
				swap(parent->_Color, grand->_Color);
				ptr = parent;
			}
		}
		else
		{
			Node *uncle = grand->_Left;
			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grand, RED);
				ptr = grand;
			}
			else
			{
				if (ptr == parent->_Left)
				{
					rotateRight(parent);
					ptr = parent;
					parent = ptr->_Parent;
				}
				rotateLeft(grand);
				swap(parent->_Color, grand->_Color);
				ptr = parent;
			}
		}
	}
	setColor(root, BLACK);
}

void RBTree::fixDelete(Node *&ptr)
{
	if (ptr == NULL)
		return;

	if (ptr == root)
	{
		root = NULL;
		return;
	}

	if (getColor(ptr) == RED || getColor(ptr->_Left) == RED || getColor(ptr->_Right) == RED)
	{
		Node *child = (ptr->_Left != NULL) ? ptr->_Left : ptr->_Right;
		if (ptr == ptr->_Parent->_Left)
		{
			ptr->_Parent->_Left = child;
			if (child != NULL)
				child->_Parent = ptr->_Parent;
			setColor(child, BLACK);
			delete(ptr);
		}
		else
		{
			ptr->_Parent->_Right = child;
			if (child != NULL)
				child->_Parent = ptr->_Parent;
			setColor(child, BLACK);
			delete(ptr);
		}
	}
	else
	{
		Node *sibling = NULL;
		Node *parent = NULL;
		Node *node = ptr;
		setColor(ptr, DOUBLE_BLACK);
		while (ptr != root && getColor(ptr) == DOUBLE_BLACK)
		{
			parent = ptr->_Parent;
			if (ptr == parent->_Left)
			{
				sibling = parent->_Right;
				if (getColor(sibling) == RED)
				{
					setColor(sibling, BLACK);
					setColor(parent, BLACK);
					rotateLeft(parent);
				}
				else
				{
					if (getColor(sibling->_Left) == BLACK && getColor(sibling->_Right) == BLACK)
					{
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else
					{
						if (getColor(sibling->_Right) == BLACK)
						{
							setColor(sibling->_Left, BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->_Right;
						}
						setColor(sibling, parent->_Color);
						setColor(parent, BLACK);
						setColor(sibling->_Right, BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else
			{
				sibling = parent->_Left;
				if (getColor(sibling) == RED)
				{
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				}
				else
				{
					if (getColor(sibling->_Left) == BLACK && getColor(sibling->_Right) == BLACK)
					{
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else
					{
						if (getColor(sibling->_Left) == BLACK)
						{
							setColor(sibling->_Right, BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->_Left;
						}
						setColor(sibling, parent->_Color);
						setColor(parent, BLACK);
						setColor(sibling->_Left, BLACK);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (node == node->_Parent->_Left)
			node->_Parent->_Left = NULL;
		else
			node->_Parent->_Right = NULL;
		delete(node);
		setColor(root, BLACK);
	}
}

void RBTree::inorderBST(Node *&ptr, ofstream& file)
{
	if (ptr == NULL)
		return;

	inorderBST(ptr->_Left, file);
	file << ptr->_Word.m_Word << "  " << ptr->_Word.m_Meaning << endl;
	inorderBST(ptr->_Right, file);
}

int RBTree::getColor(Node *&p)
{
	if (p == NULL)
		return BLACK;
	return p->_Color;
}

void RBTree::setColor(Node *&p, int color)
{
	if (p == NULL)
		return;
	p->_Color = color;
}

Node *RBTree::minValue(Node *&node)
{
	Node *ptr = node;
	while (ptr->_Left != NULL)
		ptr = ptr->_Left;
	return ptr;
}

Node *RBTree::maxValue(Node *&node)
{
	Node *ptr = node;
	while (ptr->_Right != NULL)
		ptr = ptr->_Right;
	return ptr;
}

Node * RBTree::insertBST(Node *&root, Node *&ptr)
{
	if (root == NULL)
	{
		countWords++;
		return ptr;
	}
	if (ptr->_Word.m_Word < root->_Word.m_Word)
	{
		root->_Left = insertBST(root->_Left, ptr);
		root->_Left->_Parent = root;
	}
	else
	{
		if (ptr->_Word.m_Word > root->_Word.m_Word)
		{
			root->_Right = insertBST(root->_Right, ptr);
			root->_Right->_Parent = root;
		}
		else
		{
			if (root->_Word.m_Meaning.find(ptr->_Word.m_Meaning, 0) == string::npos)
			{
				root->_Word.m_Meaning += "\n";
				root->_Word.m_Meaning += ptr->_Word.m_Meaning;
			}
		}
	}
	return root;
}

Node *RBTree::deleteBST(Node *&root, WORD word)
{
	if (root == NULL)
		return root;
	if (word.m_Word < root->_Word.m_Word)
		return deleteBST(root->_Left, word);
	if (word.m_Word > root->_Word.m_Word)
		return deleteBST(root->_Right, word);
	if (root->_Left == NULL || root->_Right == NULL)
		return root;

	Node *tmp = minValue(root->_Right);
	root->_Word.m_Word = tmp->_Word.m_Word;
	root->_Word.m_Meaning = tmp->_Word.m_Meaning;
	return deleteBST(root->_Right, tmp->_Word);
}

int RBTree::getBlackHeight(Node *ptr)
{
	int blackHeight = 0;
	while (ptr != NULL)
	{
		if (getColor(ptr) == BLACK)
			blackHeight++;
		ptr = ptr->_Left;
	}
	return blackHeight;
}

void RBTree::insert(const WORD &p)
{
	Node *node = new Node(p);
	root = insertBST(root, node);
	fixInsert(node);
}

void RBTree::remove(WORD word)
{
	Node *node = deleteBST(root, word);
	fixDelete(node);
}

void RBTree::inorder(string fileName)
{
	ofstream file(fileName.c_str());

	if (!file.is_open())
	{
		cout << "Error: Can't open file " << fileName << endl;
		return;
	}

	inorderBST(root, file);

	file.close();
}

Node *RBTree::search(string word)
{
	Node *node = root;
	while (node)
	{
		if (node->_Word.m_Word > word)
			node = node->_Left;
		else
		{
			if (node->_Word.m_Word < word)
				node = node->_Right;
			else
				return node;
		}
	}
	return NULL;
}

void RBTree::clear(Node *&root)
{
	if (root != NULL)
	{
		clear(root->_Left);
		clear(root->_Right);
		delete root;
	}
}

void RBTree::addUsage(Node *&ptr, string meaning)
{
	if (ptr->_Word.m_Meaning.find(meaning, 0) == string::npos)
		ptr->_Word.m_Meaning = ptr->_Word.m_Meaning + "\n" + meaning;
}

void RBTree::edit(Node *&ptr, string meaning)
{
	ptr->_Word.m_Meaning = meaning;
}

string RBTree::getMeaning(Node *ptr)
{
	return ptr->_Word.m_Meaning;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int RBTree::getHeight(Node *node)
{
	if (node == NULL)
		return 0;
	return 1 + max(getHeight(node->_Left), getHeight(node->_Right));
}

int RBTree::getHeight()
{
	return getHeight(root);
}

RBTree::~RBTree()
{
	clear(root);
}