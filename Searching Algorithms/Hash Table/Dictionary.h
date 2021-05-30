#include "HashTable.h"
#include <vector>

bool isPrime(int x)
{
	for (int i = 2; i <= x / 2; i++)
		if (x % i == 0)
			return false;
	return true;
}

int PrimeNext(int x)
{
	while (!isPrime(x))
	{
		x++;
	}
	return x;
}

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
		//cout << line << endl;
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
					//cout << prev << endl;
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
						//cout << tmp.m_Word <<  " " << tmp.m_Word.length() << endl;
						countWords++;
						dic.Insert(tmp);

						prev = tmp.m_Word;	
					}
				}
			}
		}
	}
	cout << "Number of Word: " << countWords << endl;
	cout << "Prime Next: " << PrimeNext(countWords) << endl;
	myFile.close();

}