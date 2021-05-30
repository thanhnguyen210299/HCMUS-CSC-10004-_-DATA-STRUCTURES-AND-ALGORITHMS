#include "AVLTree.h"
#include <vector>

WORD Parse(string line, string seperator)
{
	WORD tmp;

	int startPos = 0;
	size_t foundPos = line.find(seperator, startPos);

	int count = foundPos - startPos;
	char c = line[count - 1];
	if ('0' <= c && c <= '9')
		tmp.m_Word = line.substr(startPos, count - 1);
	else
		tmp.m_Word = line.substr(startPos, count);
	startPos = foundPos + seperator.length();

	count = line.length() - startPos;
	tmp.m_Meaning = line.substr(startPos, count);
	//cout << tokens[0] << endl;

	return tmp;
}

Dictionary * CreateDictionaryFromFile(string &fileName)
{
	Dictionary * root = new Dictionary;
	
	ifstream myFile(fileName.c_str());

	string prev, line;
	
	Dictionary * node = NULL;

	int count = 0;
	while (myFile.good())
	{
		getline(myFile, line);
		//cout << line << endl;
		if (line != "")
		{
			WORD tmp;
			if (('A' <= line[0]) && (line[0] <= 'Z') && (line.length() == 1))
			{
				tmp.m_Word = line;
				tmp.m_Meaning = "";
				count++;
				root = root->Insert(tmp);
			} 
			else
			{
				if (line.find("Usage", 0) != string::npos && line.find("Usage  n.", 0) == string::npos)
				{
					Dictionary * node = NULL;
					//cout << prev << endl;
					node = root->Search(prev);
					node->AddUsage(line);
				}
				else
				{
					if (line.find("  ", 0) != string::npos)
					{
						tmp = Parse(line, "  ");
						prev = tmp.m_Word;
						count++;
						root = root->Insert(tmp);
					}
				}
			}
		}
	}
	myFile.close();
	return root;
}
