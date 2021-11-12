#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <queue>
#include <tuple>

using namespace std;
typedef tuple<int, int> tii;
#define NODE_MAX 20001
vector<pair<int, int>> vcEdge[NODE_MAX]; // dest, weight
int d[NODE_MAX];

int V, E;

void dijkstra(int start)
{
	priority_queue<tii, vector<tii>, greater<tii>> pq; // weight, node
	pq.emplace(0, start);
	d[start] = 0;

	while (pq.size())
	{
		int weight, node;
		tie(weight, node) = pq.top();
		pq.pop();

		if(weight > d[node]) continue;

		for (auto next : vcEdge[node])
		{
			int nextNode = next.first;
			int nextWeight = d[node] + next.second;
			if (nextWeight < d[nextNode])
			{
				d[nextNode] = nextWeight;
				pq.emplace(nextWeight, nextNode);
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	fill(d, d + NODE_MAX, INT_MAX);

	cin >> V >> E;

	int startNode;
	cin >> startNode;

	for (int e = 0; e < E ; e++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		vcEdge[u].emplace_back(v, w);
	}

	dijkstra(startNode);

	for (int v = 1 ; v <= V ; v++)
	{
		if (d[v] < INT_MAX)
			cout << d[v] << "\n";
		else
			cout << "INF\n";
	}

	return 0;
}