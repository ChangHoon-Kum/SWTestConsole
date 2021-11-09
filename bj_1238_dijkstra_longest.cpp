#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
#define CITY_MAX 1001
vector<pair<int, int>> vcEdge[CITY_MAX];// dest, cost
vector<pair<int, int>> vcEdge_rev[CITY_MAX];// dest, cost
int N, M, X;
int d[CITY_MAX];
int d_rev[CITY_MAX];

void dijkstra(int start)
{
	priority_queue<pair<int, int>> pq; // cost, node
	d[start] = 0;
	pq.emplace(0, start);

	while (pq.size())
	{
		auto node = pq.top();
		pq.pop();

		int dist = -node.first;
		int nodeNum = node.second;
		if(dist > d[nodeNum]) continue;

		for (auto it : vcEdge[nodeNum])
		{
			int nextDist = dist + it.second;

			if (nextDist < d[it.first])
			{
				d[it.first] = nextDist;
				pq.emplace(-nextDist, it.first);
			}
		}
	}
}

void dijkstra_rev(int start)
{
	priority_queue<pair<int, int>> pq; // cost, node
	d_rev[start] = 0;
	pq.emplace(0, start);

	while (pq.size())
	{
		auto node = pq.top();
		pq.pop();

		int dist = -node.first;
		int nodeNum = node.second;
		if (dist > d_rev[nodeNum]) continue;

		for (auto it : vcEdge_rev[nodeNum])
		{
			int nextDist = dist + it.second;

			if (nextDist < d_rev[it.first])
			{
				d_rev[it.first] = nextDist;
				pq.emplace(-nextDist, it.first);
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	fill(d, d + CITY_MAX, INT_MAX);
	fill(d_rev, d_rev + CITY_MAX, INT_MAX);

	cin >> N >> M >> X;
	for (int m = 0 ; m < M ; m++)
	{
		int s, d, c;
		cin >> s >> d >> c;

		vcEdge[s].emplace_back(d, c);
		vcEdge_rev[d].emplace_back(s, c);
	}

	dijkstra(X);
	dijkstra_rev(X);

	int nMax = 0;
	for (int i = 1; i <= N ; i++)
	{
		if (nMax < d[i] + d_rev[i])
		{
			nMax = d[i] + d_rev[i];
		}
	}

	cout << nMax;

	return 0;
}

