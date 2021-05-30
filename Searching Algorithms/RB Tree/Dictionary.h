#include "RBTree.h"
#include <vector>

RBTree * CreateDictionaryFromFile(string &fileName)
{
	RBTree * dic = new RBTree;

	ifstream myFile(fileName.c_str());

	string prev, line;

	Node *node = NULL;
	int startPos, count;
	size_t foundPos;
	char c;
	WORD tmp;

	while (myFile.good())
	{
		getline(myFile, line);
		//cout << line << endl;
		if (line != "")
		{
			if (('A' <= line[0]) && (line[0] <= 'Z') && (line.length() == 1))
			{
				tmp.m_Word = line;
				tmp.m_Meaning = "";
				dic->insert(tmp);
			}
			else
			{
				if (line.find("Usage", 0) != string::npos && line.find("Usage  n.", 0) == string::npos)
				{
					//cout << prev << endl;
					node = dic->search(prev);
					if (node)
						dic->addUsage(node, line);
				}
				else
				{
					if (line.find("  ", 0) != string::npos)
					{
						startPos = 0;
						foundPos = line.find("  ", startPos);

						count = foundPos - startPos;
						c = line[count - 1];
						if ('0' <= c && c <= '9'|| c == '.')
							tmp.m_Word = line.substr(startPos, count - 1);
						else
							tmp.m_Word = line.substr(startPos, count);
						startPos = foundPos + 2;

						count = line.length() - startPos;
						tmp.m_Meaning = line.substr(startPos, count);
						//cout << tmp.m_Word << endl << tmp.m_Meaning << endl;
						prev = tmp.m_Word;

						dic->insert(tmp);
					}
				}
			}
		}
	}
	myFile.close();
	return dic;
}
