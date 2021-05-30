#include <vector>
#include <string>
#include <fstream>

using namespace std;

void ReadCityFile(vector<string> &a)
{
	ifstream f("cityFile");

	string tmp;
	while (getline(f, tmp))
		a.push_back(tmp);
}

int FindID(string a, vector<string> b)
{
	for (int i = 0; i < b.size(); i++)
		if (a == b[i])
			return i;
	return -1;
}

string FindCity(int i, vector<string> b)
{
	return b[i];
}

void FindEdge(int u, int v, vector<Link> a, vector<string> cities, int &sumCost, int &sumDuration)
{
	for (int i = 0; i < a.size(); i++)
		if (u == a[i].u && v == a[i].v)
		{
			sumCost += a[i].Cost;
			sumDuration += a[i].Duration;
			cout << "Flight #" << a[i].FlightNumber << " from " << FindCity(a[i].u, cities) << " to " << FindCity(a[i].v, cities) << " Cost : $" << a[i].Cost << " Duration : " << a[i].Duration << " hours" << endl;
			return;
		}
}

void ReadFlightFile(vector<Link> &a, vector<string> b)
{
	ifstream f("flightFile");

	string line, source, destination;
	Link tmp;
	int startPos;
	while (getline(f, line))
	{
		size_t foundPos = line.find(',', 0);
		source = line.substr(0, foundPos);
		tmp.u = FindID(source, b);

		int pos = startPos = foundPos + 2;
		foundPos = line.find(' ', startPos);

		while (foundPos != string::npos && (line[foundPos + 1] > '9' || line[foundPos + 1] < '0'))
		{
			startPos = foundPos + 1;
			foundPos = line.find(' ', startPos);
		}
		destination = line.substr(pos, foundPos - pos);
		//cout << destination << endl;
		tmp.v = FindID(destination, b);

		startPos = foundPos + 1;
		foundPos = line.find(' ', startPos);
		tmp.FlightNumber = stoi(line.substr(startPos, foundPos - startPos));

		startPos = foundPos + 1;
		foundPos = line.find(' ', startPos);
		tmp.Cost = stoi(line.substr(startPos, foundPos - startPos));

		startPos = foundPos + 1;
		tmp.Duration = stoi(line.substr(startPos, line.length() - startPos));

		a.push_back(tmp);
	}
}