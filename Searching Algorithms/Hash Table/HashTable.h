#pragma once
#include "HashNode.h"
#include <fstream>
#include <iostream>

#define TABLE_SIZE 36433
#define HASH_WEIGHT 31

class HashTable
{
private:
	HashNode ** _HTable;
public:
	HashTable();
	int MaxCollision();
	bool isEmpty();
	int HashFunc(string);
	void Insert(const WORD &);
	void Delete(string);
	HashNode * Search(string);
	void Display(string fileName);
	void addUsage(HashNode *&, string);
	string getMeaning(HashNode *);
	void edit(HashNode *&, string);
	~HashTable();
};

