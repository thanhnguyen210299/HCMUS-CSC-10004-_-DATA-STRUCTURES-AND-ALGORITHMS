#include "AVLTree.h"
#include "DictionarySearch.h"
#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

void main()
{
	Dictionary *root = NULL;
	bool kt = true;
	int ch = 0;
	do
	{
		cout << "***********************************************************************" << endl;
		cout << "1. Load Dictionary" << endl;
		cout << "2. Search In Dictionary" << endl;
		cout << "3. Insert into Dictionary" << endl;
		cout << "4. Edit word's meaning" << endl;
		cout << "5. Delete from Dictionary" << endl;
		cout << "6. Save to File" << endl;
		cout << "7. Exit" << endl;
		cout << "\nEnter choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
		{
			string fileName = "Oxford-English-Dictionary.txt";
			root = CreateDictionaryFromFile(fileName);
			cout << "Load file sucessfully" << endl;
		}
		break;
		case 2:
		{
			string word;
			Dictionary * node = NULL;
			if (!root)
			{
				cout << "Dictionary not yet created" << endl;
				break;
			}
			cout << "\nEnter the word to search: ";
			cin >> word;
			node = root->Search(word);
			if (node)
				cout << "Meaning of word " << word << " is: " << endl << node->GetMeaning() << endl;
			else
				cout << "The word " << word << " not found in the dictionary" << endl;
		}
		break;
		case 3:
		{
			WORD word;

			cout << "\nEnter the word: ";
			cin >> word.m_Word;
			cout << "\nEnter the meaning: ";
			cin >> word.m_Meaning;

			root = root->Insert(word);
			cout << "Insert sucessfully" << endl;
		}
		break;
		case 4:
		{
			if (!root)
			{
				cout << "Dictionary not yet created" << endl;
				break;
			}

			WORD word;

			cout << "\nEnter the word: ";
			cin >> word.m_Word;

			Dictionary * node = NULL;
			node = root->Search(word.m_Word);
			if (node)
			{
				cout << "\nEnter the meaning: ";
				cin >> word.m_Meaning;
				node->Edit(word.m_Meaning);
				cout << "Edit sucessfully" << endl;
			}
			else
				cout << "The word " << word.m_Word << " not found in the dictionary" << endl;
		}
		break;
		case 5:
		{
			if (!root)
			{
				cout << "Dictionary not yet created" << endl;
				break;
			}
			string word;
			cout << "\nEnter the word to delete: ";
			cin >> word;
			root = root->Delete(word);
			cout << "Delete sucessfully" << endl;
		}
		break;
		case 6:
		{
			if (!root)
			{
				cout << "Dictionary not yet created" << endl;
				break;
			}
			string fileName = "Dictionary.txt";
			root->PrintToFile(fileName);
			cout << "Print to file sucessfully" << endl;
		}
		break;
		case 7:
		{
			cout << "The End!!!" << endl;
			cout << "***********************************************************************" << endl;
		}
		break;
		default:
			cout << "Invalid choice" << endl;
			kt = false;
		}
		
	} while (ch != 7 && kt) ;

	_getch();
}