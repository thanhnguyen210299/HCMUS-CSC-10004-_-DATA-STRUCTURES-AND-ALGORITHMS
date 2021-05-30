#include <iostream>
#include <stdio.h>
#include <queue>
#include <memory.h>

using namespace std;

const int ax[] = { -1, 1, 0, 0 };
const int ay[] = { 0, 0, -1, 1 };


char map[35][35];
bool check[35][35];

int bfs(int x, int y)
{
	if (check[x][y])
		return 0;

	queue<int> qx, qy;
	qx.push(x);
	qy.push(y);
	check[x][y] = true;

	int count = 0;
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

			if (!check[tx][ty] && map[tx][ty] == '.')
			{
				check[tx][ty] = true;
				qx.push(tx);
				qy.push(ty);
			}
			else
				if (map[tx][ty] == '#')
					count++;
		}
	}
	return count;
}

void main()
{
	int n;
	cin >> n;
	memset(map, '#', sizeof(map));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	}

	map[0][1] = map[1][0] = map[n][n + 1] = map[n + 1][n] = '!';
	memset(check, false, sizeof(check));
	cout << 9 * (bfs(1, 1) + bfs(n, n));
}