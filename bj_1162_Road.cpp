#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>

#define CITY_MAX 10001
#define TIME_LIMIT 1000001
using namespace std;

vector<pair<int, int>> vcEdge[CITY_MAX]; // destination, cost
long long d[21][CITY_MAX];
int N, M, K;




void dijkstra(int start)
{
	priority_queue<tuple<long long, int, int>> pq; // cost, next node, 포장 도로 수

	pq.emplace(0, start, 0);
	for (int k = 0 ; k <= K ; k++)
	{
		d[k][start] = 0;
	}

	while (pq.size())
	{
		long long distance, node, roads;
		tie(distance, node, roads) = pq.top();
		pq.pop();

		distance = -distance;

		if(distance > d[roads][node]) continue;

		for (auto nextNode : vcEdge[node])
		{
			// 포장
			if(roads < K)
			{
				long long nextDistance = distance;// +nextNode.second;
				if (nextDistance < d[roads + 1][nextNode.first])
				{
					d[roads + 1][nextNode.first] = nextDistance;
					pq.emplace(-nextDistance, nextNode.first, roads + 1);
				}
			}

			//비포장
			{
				long long nextDistance = distance + nextNode.second;
				if (nextDistance < d[roads][nextNode.first])
				{
					d[roads][nextNode.first] = nextDistance;
					pq.emplace(-nextDistance, nextNode.first, roads);
				}
			}
		}
	}
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	cin >> N >> M >> K;

	for (int k = 0; k <= K; k++)
	{
		fill(d[k], d[k] + CITY_MAX, TIME_LIMIT);
	}

	for (int m = 0; m < M ; m++)
	{
		int i, j, dist;
		cin >> i >> j >> dist;

		vcEdge[i].emplace_back(j, dist);
		vcEdge[j].emplace_back(i, dist);
	}

	dijkstra(1);

	long long MinCost = d[0][N];
	for (int k = 1; k <= K; k++)
	{
		MinCost = min(MinCost, d[k][N]);
	}

	cout << MinCost;

	return 0;
}