#include <stdio.h>
#include <string.h>

#define INFINITE 127

unsigned int IPNum[90][6];
char network[90][90], dist[91] = { 0 }, prev[90] = { 0 }, check[90] = { 0 };

void main()
{
	int i = 0, j = 0, k = 0, l = 0;
	int IP[4], mask[4], start = 0, end = 0;
	char found = 0;

	memset(IPNum, 0, sizeof(IPNum));
	memset(network, 0, sizeof(network));
	memset(dist, INFINITE, sizeof(dist));
	memset(prev, -1, sizeof(prev));

	#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	#endif

	// INPUT NETWORK

	int computerNum;
	scanf("%d\n", &computerNum);

	for (i = 0; i < computerNum; i++)
	{
		scanf("%d\n", &IPNum[i][0]);

		for (j = 1; j <= IPNum[i][0]; j++)
		{
			scanf("%d.%d.%d.%d %d.%d.%d.%d\n", &IP[3], &IP[2], &IP[1], &IP[0], &mask[3], &mask[2], &mask[1], &mask[0]);
			for (k = 0; k < 4; k++) 
				IPNum[i][j] |= ((mask[k] & IP[k]) << (8 * k));
		}
		
		for (j = 0; j < i; j++)
		{
			found = 0;
			for (k = 1; k <= IPNum[j][0] && found == 0; k++)
				for (l = 1; l <= IPNum[i][0] && found == 0; l++)
					if (IPNum[i][l] == IPNum[j][k]) 
						found = 1;
			if (found == 1)
			{
				network[i][j] = 1; 
				network[j][i] = 1;
			}
		}
	}

	scanf("%d %d", &start, &end); 
	start--; 
	end--;

	// FIND PATH

	dist[end] = 0;
	while (1)
	{
		for (i = computerNum, j = 0; j < computerNum; j++)
			if (check[j] == 0 && dist[j] < dist[i]) 
				i = j;

		if (i == computerNum) 
			break;
		check[i] = 1;
		if (i == start) 
			break;

		for (j = 0; j < computerNum; j++){
			if (check[j] == 1 || network[i][j] == 0) 
				continue;
			if (dist[j] > dist[i] + network[i][j])
			{
				dist[j] = dist[i] + network[i][j];
				prev[j] = i;
			}
		}
	}

	if (dist[start] == INFINITE) 
		printf("No\n");
	else
	{
		printf("Yes\n");
		i = start;
		while (1)
		{
			printf("%d ", i + 1);
			if (i == end) 
				break;
			i = prev[i];
		}
	}
}