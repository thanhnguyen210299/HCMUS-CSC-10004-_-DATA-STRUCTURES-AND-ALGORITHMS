#include "AVLTree.h"

Dictionary::Dictionary()
{
	_Left = _Right = NULL;
	_Count = 0;
}

const string& Dictionary::GetMeaning()
{
	return _Word.m_Meaning;
}

Dictionary * Dictionary::Insert(WORD& p)
{
	Dictionary *newRoot = this;
	if (_Count == 0) 
	{
		//Dictionary * newRoot = new Dictionary;
		newRoot->_Word.m_Word = p.m_Word;
		newRoot->_Word.m_Meaning = p.m_Meaning;
		newRoot->_Count = 1;
		return newRoot;
	}
	
	//Dictionary *newRoot = this;

	if (p.m_Word > _Word.m_Word) 
	{
		if (_Right == NULL) 
			_Right = new Dictionary;

		_Right = _Right->Insert(p);

		if (BF() <= -2)
			newRoot = (p.m_Word > _Right->_Word.m_Word) ? RR() : RL();
	}
	else 
		if (p.m_Word < _Word.m_Word)
		{
			if (_Left == NULL)
				_Left = new Dictionary;

			_Left = _Left->Insert(p);
			if (BF() >= 2)
				newRoot = (p.m_Word < _Left->_Word.m_Word) ? LL() : LR();
		}
		else
		{
			if (_Word.m_Meaning.find(p.m_Meaning, 0) == string::npos)
			{
				_Word.m_Meaning += "\n";
				_Word.m_Meaning += p.m_Meaning;
			}
		}

	return newRoot;
}

Dictionary * Dictionary::Delete(string& p)
{
	if (!this)
		return NULL;
	Dictionary *newRoot = this;
	if (p == _Word.m_Word)
	{
		if (!_Right && !_Left) //Check if this is the leaf node
			newRoot = NULL;
		else
		{
			if (!_Right)
			{
				Dictionary * t = _Left;
				_Right = t->_Left;
				_Left = t->_Left;
				_Word.m_Word = t->_Word.m_Word;
				_Word.m_Meaning = t->_Word.m_Meaning;

				delete t;
			}
			else
			{
				if (!_Left)
				{
					Dictionary * t = _Right;
					_Left = t->_Right;
					_Right = t->_Right;
					_Word.m_Word = t->_Word.m_Word;
					_Word.m_Meaning = t->_Word.m_Meaning;

					delete t;
				}
				else
				{	// Delete the leaf from right subtree
					Dictionary *t;
					for (t = _Right; t->_Left; t = t->_Left);
					_Word.m_Word = t->_Word.m_Word;
					_Word.m_Meaning = t->_Word.m_Meaning;

					// Delete the leaf from subtree
					t = _Right->Delete(p);
					if (t == NULL)
						delete _Right;

					_Right = t;

					if (BF() >= 2)
						newRoot = (_Left->BF() >= 0) ? LL() : LR();
				}
			}
		}
	}
	else
	{
		if (_Right && p > _Word.m_Word)
		{
			Dictionary *t;
			t = _Right->Delete(p);
			if (t == NULL)
				delete _Right;

			_Right = t;

			if (BF() >= 2)
				newRoot = (_Left->BF() >= 0) ? LL() : LR();
		}
		else
		{
			if (_Left && p < _Word.m_Word)
			{
				Dictionary *t;
				t = _Left->Delete(p);
				if (t == NULL)
					delete _Left;

				_Left = t;

				if (BF() <= -2)
					newRoot = (_Right->BF() <= 0) ? RR() : RL();
			}
		}
	}
	return newRoot;
}

void Dictionary::Edit(string& meaning)
{
	_Word.m_Meaning = meaning;
}

void Dictionary::AddUsage(string &meaning)
{
	if (_Word.m_Meaning.find(meaning, 0) == string::npos)
		_Word.m_Meaning = _Word.m_Meaning + "\n" + meaning;
}

Dictionary* Dictionary::LL()
{
	return RotateRight();
}

Dictionary* Dictionary::RR()
{
	return RotateLeft();
}

Dictionary* Dictionary::LR()
{
	if (_Left)
		_Left = _Left->RotateLeft();
	return RotateRight();
}

Dictionary* Dictionary::RL()
{
	if (_Right)
		_Right = _Right->RotateRight();
	return RotateLeft();
}

Dictionary * Dictionary::RotateRight()
{
	Dictionary *newRoot = _Left;
	_Left = newRoot->_Right;
	newRoot->_Right = this;
	return newRoot;
}

Dictionary * Dictionary::RotateLeft()
{
	Dictionary *newRoot = _Right;
	_Right = newRoot->_Left;
	newRoot->_Left = this;

	return newRoot;
}

int Dictionary::BF()
{
	int lh, rh;
	lh = (_Left) ? _Left->Height() : 0;
	rh = (_Right) ? _Right->Height() : 0;

	return (lh - rh);
}

void Dictionary::PrintToFile(string &fileName)
{
	ofstream file(fileName.c_str());

	if (!file.is_open())
	{
		cout << "Error: Can't open file " << fileName << endl;
		return;
	}

	PrintToFile(file);

	file.close();
}

Dictionary * Dictionary::Search(string& word)
{
	if (this == NULL) 
		return NULL;
	if (_Count && word == _Word.m_Word)
		return this;
	if (word > _Word.m_Word)
		return (_Right) ? _Right->Search(word) : NULL;
	else
		return (_Left) ? _Left->Search(word) : NULL;
}

void Dictionary::PrintToFile(ofstream& file)
{
	if (_Count)
	{
		if (_Left)
			_Left->PrintToFile(file);
		file << _Word.m_Word << "  " << _Word.m_Meaning << endl;
		if (_Right)
			_Right->PrintToFile(file);
	}
}

int Dictionary::Height()
{
	int lh, rh;
	if (_Count == 0)
		return 0;
	lh = (_Left) ? _Left->Height() : 0;
	rh = (_Right) ? _Right->Height() : 0;
	return (lh > rh) ? lh + 1 : rh + 1;
}

void Dictionary::Clear()
{
	if (this != NULL)
	{
		_Left->Clear();
		_Right->Clear();
		delete this;
	}
}

Dictionary::~Dictionary()
{
	Clear();
}
