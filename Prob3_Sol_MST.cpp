/**
■ 최소 비용 연결

최소 비용으로 모든 도시를 연결하고자 한다.이때 도시를 연결하는 비용은 x좌표의 차이와 y좌표의 차이 중 더 적은 값이다.
Cost = min(| x1 - x2 | , | y1 - y2 | )

< 제한조건 >
2 <= N <= 100, 000
- 1e9 <= x, y <= 1e9

< 입력 >
첫번째 줄에는 테스트 케이스 수가 주어진다.이후 테스트 케이스가 주어지며, 각 테이스 케이스의 첫번째 줄에는 도시의 수 N, 이후 N개의 좌표가 주어진다.
2
4
-4 3
-2 -4
2 1
4 2
3
2 0
2 2
3 3

< 출력 >
#1 4
#2 1
*/

#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;
#define ARRAY_MAX 100000

struct POINT 
{
	int x;
	int y;
	int id;

	POINT()
	{
		x = y = id = INT_MAX;
	}

	POINT(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

struct EDGE
{
	int firstNode;
	int secondNode;
	int distance;

	EDGE()
	{
		firstNode = secondNode = distance = INT_MAX;
	}

	EDGE(int _node1, int _node2, int _distance)
	{
		if (_node1 < _node2)
		{
			firstNode = _node1;
			secondNode = _node2;
		}
		else
		{
			firstNode = _node2;
			secondNode = _node1;
		}

		distance = _distance;
	}
};

int parent[ARRAY_MAX];

int GetCost(const POINT& pt1, const POINT& pt2)
{
	return min(abs(pt1.x - pt2.x), abs(pt1.y - pt2.y));
}

int getParent(int x)
{
	if (parent[x] == x) return x;
	return parent[x] = getParent(parent[x]);
}

bool findParent(int a, int b)
{
	a = getParent(a);
	b = getParent(b);

	if (a == b) return true;
	else return false;
}

void unionParent(int a, int b)
{
	int parent_a = getParent(a);
	int parent_b = getParent(b);

	if (parent_a != a || parent_b != b)
	{
		unionParent(parent_a, parent_b);
	}

	if (a < b) parent[b] = a;
	else parent[a] = b;
}

bool cmp_x(POINT& p1, POINT& p2)
{
	return p1.x < p2.x;
}

bool cmp_y(POINT& p1, POINT& p2)
{
	return p1.y < p2.y;
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	int N;
	for (int t = 0 ; t < testcase ; t++)
	{
		cin >> N;
		
		vector<POINT> vcNode;
		vcNode.resize(N);

		//vector<EDGE> vcEdge;
		priority_queue<tuple<int/*cost*/, int/*node1*/, int/*node2*/>> pqEdge;
		for (int n = 0 ; n < N ; n++)
		{
			cin >> vcNode[n].x >> vcNode[n].y;
			parent[n] = vcNode[n].id = n;
		}

		sort(vcNode.begin(), vcNode.end(), cmp_x);
		for (int x = 1; x < N ; x++)
		{
			pqEdge.push(make_tuple(-GetCost(vcNode[x], vcNode[x-1]), min(vcNode[x - 1].id, vcNode[x].id), max(vcNode[x - 1].id, vcNode[x].id)));
		}

		sort(vcNode.begin(), vcNode.end(), cmp_y);
		for (int y = 1; y < N; y++)
		{
			pqEdge.push(make_tuple(-GetCost(vcNode[y], vcNode[y - 1]), min(vcNode[y - 1].id, vcNode[y].id), max(vcNode[y - 1].id, vcNode[y].id)));
		}

		int cost = 0;
		while(!pqEdge.empty())
		{
			auto edge = pqEdge.top();
			pqEdge.pop();

			if (!findParent(get<1>(edge), get<2>(edge)))
			{
				cost += -get<0>(edge);
				unionParent(get<1>(edge), get<2>(edge));
			}
		}

		cout << "#" << t + 1 << " " << cost << "\n";
	}

	return 0;
}