#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <tuple>
#include <climits>
//#include <array>

using namespace std;
int N, M, K; // 공항 수, 돈, 티켓 정보 수
#define AIRPORT_MAX 101
#define COST_MAX 10001
typedef tuple<int, int, int> tIII;
vector<tIII> vcEdge[AIRPORT_MAX]; // dest, cost, time
int d[AIRPORT_MAX][COST_MAX]; //time, cost

void init()
{
	for (int i = 0 ; i < AIRPORT_MAX ; i++)
	{
		vcEdge[i].clear();
		fill(d[i], d[i] + COST_MAX, 10001);
	}
}

void dijkstra(int start)
{
	priority_queue<tIII, vector<tIII>, less<tIII>> pq; // time, cost, node

	for (int i = 0 ; i <= M ; i++)
	{
		d[start][i] = 0;
	}
	
	pq.emplace(0, 0, start);

	while (pq.size())
	{
		int cur_time, cur_cost, cur;
		tie(cur_time, cur_cost, cur) = pq.top();
		pq.pop();

		if(cur_time > d[cur][cur_cost] || cur_cost > M) continue;

		for (auto node : vcEdge[cur])
		{
			int dest, cost, time;
			tie(dest, cost, time) = node;

			int nextTime = d[cur][cur_cost] + time;
			int nextCost = cur_cost + cost;
			if (nextTime < d[dest][nextCost] && nextCost <= M)
			{
				for (int j = nextCost; j <= M; j++)
				{
					if (d[dest][j] <= nextTime) break;
					d[dest][j] = nextTime;
				}
				
				pq.emplace(nextTime, nextCost, dest);
			}

		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		init();

		cin >> N >> M >> K;

		for (int k = 0; k < K ; k++)
		{
			int u, v, c, d; // 출발, 도착, 비용, 시간
			cin >> u >> v >> c >> d;

			vcEdge[u].emplace_back(v, c, d);
		}

		dijkstra(1);

		int minTime = INT_MAX;
		for (int i = 1 ; i <= M ; i++)
		{
			minTime = min(minTime, d[N][i]);
		}

		if (minTime <= 1000)
			cout << minTime << "\n";
		else
			cout << "Poor KCM\n";
	}

	return 0;
}