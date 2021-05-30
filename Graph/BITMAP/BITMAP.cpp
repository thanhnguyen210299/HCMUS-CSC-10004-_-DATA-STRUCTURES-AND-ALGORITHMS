#include <iostream>
#include <conio.h>
#include <fstream>
#include <queue>

using namespace std;

const int ax[] = { -1, 1, 0, 0 };
const int ay[] = { 0, 0, -1, 1 };

int g[255][255];

void bfs(int x, int y)
{
	if (g[x][y] != 1)
		return;

	queue<int> qx, qy;
	qx.push(x);
	qy.push(y);
	g[x][y] = -1;

	while (!qx.empty())
	{
		int nx = qx.front();
		int ny = qy.front();
		qx.pop();
		qy.pop();

		for (int i = 0; i < 4; i++)
		{
			int tx = nx + ax[i];
			int ty = ny + ay[i];

			if (g[tx][ty] == 1)
			{
				g[tx][ty] = -1;
				qx.push(tx);
				qy.push(ty);
			}
		}
	}
}


void main()
{
	// Doc du lieu tu file
	ifstream fin("BITMAP.INP");
	int m, n;
	fin >> n >> m;

	// Khoi tao ma tran
	memset(g, 0, sizeof(g));

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			fin >> g[i][j];
	fin.close();

	// Duyet bang de dem so doi tuong
	int count = 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			if (g[i][j] == 1)
			{
				count++;
				bfs(i, j);
			}

	// In so doi tuong ra file
	ofstream fout("BITMAP.OUT");
	fout << count;
	fout.close();
}