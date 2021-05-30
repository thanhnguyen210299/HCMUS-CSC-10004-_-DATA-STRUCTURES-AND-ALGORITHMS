#include "HashNode.h"

HashNode::HashNode()
{
	_Next = NULL;
}

HashNode::HashNode(WORD word)
{
	_Word.m_Word = word.m_Word;
	_Word.m_Meaning = word.m_Meaning;
	_Next = NULL;
}

string HashNode::getWord()
{
	return _Word.m_Word;
}

string HashNode::getMeaning()
{
	return _Word.m_Meaning;
}

void HashNode::setMeaning(string meaning)
{
	if (_Word.m_Meaning.find(meaning, 0) == string::npos)
	{
		_Word.m_Meaning += "\n";
		_Word.m_Meaning += meaning;
	}
}

void HashNode::changeMeaning(string meaning)
{
	_Word.m_Meaning = meaning;
}

HashNode * HashNode::getNext()
{
	return _Next;
}

void HashNode::setNext(HashNode * p)
{
	_Next = p;
}