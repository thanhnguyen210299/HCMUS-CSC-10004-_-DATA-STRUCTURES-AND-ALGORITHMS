#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

class WORD
{
public:
	string m_Word;
	string m_Meaning;
};

class Dictionary
{
public:

	int _Count;
	WORD _Word;
	Dictionary * _Left;
	Dictionary * _Right;
	int height;
public:
	Dictionary();
	const string& GetMeaning();
	Dictionary * Insert(WORD& p);
	Dictionary * Delete(string& p);
	Dictionary * Search(string& word);
	void Edit(string& meaning);
	void AddUsage(string &meaning);

	Dictionary * RR();
	Dictionary * LL();
	Dictionary * RL();
	Dictionary * LR();

	Dictionary * RotateRight();
	Dictionary * RotateLeft();

	void PrintToFile(string &fileName);
	void PrintToFile(ofstream& file);

	int Height();
	int BF();

	void Clear();

	~Dictionary();
};

#endif