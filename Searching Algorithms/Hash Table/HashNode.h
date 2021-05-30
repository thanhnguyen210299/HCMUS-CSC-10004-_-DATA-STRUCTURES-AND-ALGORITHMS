#ifndef _HashNode_H_
#define _HashNode_H_

#include <string>

using namespace std;

struct WORD
{
	string m_Word;
	string m_Meaning;
};

class HashNode
{
private:
	WORD _Word;
	HashNode * _Next;
public:
	HashNode();
	HashNode(WORD);
	string getWord();
	string getMeaning();
	HashNode * getNext();
	void setNext(HashNode *);
	void setMeaning(string);
	void changeMeaning(string);

	//HashNode* operator = (const HashNode *);
};

#endif