#include "HashTable.h"

HashTable::HashTable()
{
	_HTable = new HashNode *[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		_HTable[i] = NULL;
}

HashTable::~HashTable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		HashNode * tmp = _HTable[i];
		while (tmp != NULL)
		{
			HashNode * prev = tmp;
			tmp = tmp->getNext();
			delete prev;
		}
	}
	delete[] _HTable;
}

bool HashTable::isEmpty()
{
	int count = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
		if (_HTable[i] != NULL)
			return false;
	return true;
}

bool HashTable::Delete(string word)
{
	if (isEmpty())
		return false;
	int key = HashFunc(word);
	if (_HTable[key] == NULL)
		return false;
	else
	{
		if (_HTable[key]->getWord() == word)
		{
			HashNode * tmp = _HTable[key];
			_HTable[key] = _HTable[key]->getNext();
			delete tmp;
			return true;
		}
	}

	HashNode *node = _HTable[key];
	HashNode *tmp = _HTable[key];
	while (tmp != NULL)
	{
		if (tmp->getWord() == word)
			break;
		node = tmp;
		tmp = tmp->getNext();
	}
	if (tmp != NULL)
	{
		node->setNext(tmp->getNext());
		delete tmp;
		return true;
	}
	return false;
}

HashNode * HashTable::Search(string word)
{
	if (isEmpty())
		return NULL;
	int key = HashFunc(word);
	HashNode *tmp = _HTable[key];
	while (tmp != NULL)
	{
		if (tmp->getWord() == word)
			return tmp;
		tmp = tmp->getNext();
	}
	return NULL;
}

void swap(WORD &a, WORD &b)
{
	WORD temp = a;
	a = b;
	b = temp;
}

void QS(WORD *a, int l, int r)
{
	string k = a[(l + r) / 2].m_Word;
	int i = l;
	int j = r;
	while (i < j)
	{
		while (a[i].m_Word < k)
			i++;
		while (a[j].m_Word > k)
			j--;
		if (i <= j)
		{
			if (i < j)
				swap(a[i], a[j]);
			i++;
			j--;
		}
	}

	if (l < j)
		QS(a, l, j);
	if (i < r)
		QS(a, i, r);
}

void HashTable::Display(string fileName)
{
	ofstream file(fileName.c_str());

	if (!file.is_open())
	{
		cout << "Error: Can't open file " << fileName << endl;
		return;
	}

	if (isEmpty())
		return;

	WORD * Dictionary = new WORD[TABLE_SIZE];
	int k = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		HashNode *p = _HTable[i];
		while (p != NULL)
		{
			Dictionary[k].m_Word = p->getWord();
			Dictionary[k].m_Meaning = p->getMeaning();
			k++;

			p = p->getNext();
		}
	}

	QS(Dictionary, 0, k - 1);

	for (int i = 0; i < k; i++)
		file << Dictionary[i].m_Word << " " << Dictionary[i].m_Meaning << endl;

	file.close();
}

void HashTable::addUsage(HashNode *&p, string usage)
{
	p->setMeaning(usage);
}

int HashTable::HashFunc(string word)
{
	unsigned long key = 0;
	for (int i = 0; i < word.length(); i++)
	{
		int temp = 0;
		if ('A' <= word[i] && word[i] <= 'Z')
			temp = word[i] - 64;
		else
			if ('a' <= word[i] && word[i] <= 'z')
				temp = word[i] - 96;

		key = temp + HASH_WEIGHT * key;
	}
	return key % TABLE_SIZE;
}

void HashTable::Insert(const WORD &word)
{
	int key = HashFunc(word.m_Word);
	HashNode * k = new HashNode(word);

	if (_HTable[key] == NULL)
	{
		_HTable[key] = k;
		return;
	}

	HashNode * tmp = _HTable[key];
	HashNode * prev = NULL;
	while (tmp != NULL)
	{
		if (tmp->getWord() == word.m_Word)
		{
			_HTable[key]->setMeaning(word.m_Meaning);
			return;
		}
		prev = tmp;
		tmp = tmp->getNext();
	}

	if (tmp == NULL)
		prev->setNext(k);
}

string HashTable::getMeaning(HashNode *p)
{
	return p->getMeaning();
}

void HashTable::edit(HashNode *&p, string meaning)
{
	return p->changeMeaning(meaning);
}

int HashTable::MaxCollision()
{
	int max = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		int count = 0;
		HashNode *p = _HTable[i];
		while (p != NULL)
		{
			count++;
			p = p->getNext();
		}
		if (count > max)
			max = count;
	}
	return max;
}

