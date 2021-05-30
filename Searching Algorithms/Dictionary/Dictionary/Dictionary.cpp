#include "Dictionary.h"
#include <qmessagebox.h>

HashTable Dictionary::dic;

void CreateDictionaryFromFile(string fileName, HashTable &dic)
{
	ifstream myFile(fileName.c_str());

	string prev, line;
	int countWords = 0;

	HashNode *node = NULL;
	int startPos, count;
	size_t foundPos;
	char c;
	WORD tmp;

	while (myFile.good())
	{
		getline(myFile, line);
		if (line != "")
		{
			if (('A' <= line[0]) && (line[0] <= 'Z') && (line.length() == 1))
			{
				tmp.m_Word = line;
				tmp.m_Meaning = "";
				dic.Insert(tmp);
				countWords++;
			}
			else
			{
				if (line.find("Usage", 0) != string::npos && line.find("Usage  n.", 0) == string::npos)
				{
					node = dic.Search(prev);
					if (node)
						dic.addUsage(node, line);
				}
				else
				{
					if (line.find("  ", 0) != string::npos)
					{
						startPos = 0;
						foundPos = line.find("  ", startPos);

						count = foundPos - startPos;
						c = line[count - 1];
						if ('0' <= c && c <= '9' || c == '.')
							tmp.m_Word = line.substr(startPos, count - 1);
						else
							tmp.m_Word = line.substr(startPos, count);
						startPos = foundPos + 2;

						count = line.length() - startPos;
						tmp.m_Meaning = line.substr(startPos, count);
						countWords++;
						dic.Insert(tmp);

						prev = tmp.m_Word;
					}
				}
			}
		}
	}
	myFile.close();
}

Dictionary::Dictionary(QWidget *parent)
	: QMainWindow(parent)
{
	bool kt = true;
	int ch = 0;
	string fileName = "Oxford-English-Dictionary.txt";
	CreateDictionaryFromFile(fileName, dic);
	QMessageBox::information(this, "Message", "Begin Now...", QMessageBox::Ok);

	ui.setupUi(this);
}

void Dictionary::AddWord()
{
	add.show();
}

void Dictionary::PrintFile()
{
	string fileName = "Dictionary.txt";
	dic.Display(fileName);
	QMessageBox::information(this, "Message", "Print to file sucessfully!", QMessageBox::Ok);
}

void Dictionary::SearchWord()
{
	search.show();
}

void Dictionary::EditWord()
{
	edit.show();
}

void Dictionary::DeleteWord()
{
	Delete.show();
}