#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<pair<int, int>> vcIsland; // x , y
vector<int> vcY;

#define ISLAND_SIZE 75001
int ySize;
long long tree[4 * ISLAND_SIZE]; // y좌표마다 Count를 저장
int N;

long long update(int start, int end, int idx, int val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] += val;

	int mid = (start + end) / 2;
	long long lval = update(start, mid, idx, val, node * 2);
	long long rval = update(mid + 1, end, idx, val, node * 2 + 1);

	return tree[node] = lval + rval;
}

long long query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return 0;

	if (left <= start && end <= right) return tree[node];
	
	int mid = (start + end) / 2;
	long long lval = query(start, mid, left, right, node * 2);
	long long rval = query(mid + 1, end, left, right, node * 2 + 1);

	return lval + rval;
}


bool cmp(pair<int, int>& _l, pair<int, int>& _r)
{
	if (_l.first == _r.first)
		return _l.second > _r.second;
	else
		return _l.first < _r.first;
}

void treePushIsland(pair<int, int> _pos, int val = 1)
{
	int idx = lower_bound(vcY.begin(), vcY.end(), _pos.second) - vcY.begin();

	update(0, ySize - 1, idx, val);
}

int main(void)
{
	fastio;
	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		vcIsland.clear();
		vcY.clear();
		fill(tree, tree + 4 * ISLAND_SIZE, 0);
		cin >> N;
		
		for (int n = 0 ; n < N ; n++)
		{
			int x, y;
			cin >> x >> y;

			vcIsland.emplace_back(x, y);
			vcY.emplace_back(y);
		}

		sort(vcIsland.begin(), vcIsland.end(), cmp);
		
		sort(vcY.begin(), vcY.end());
		vcY.erase(unique(vcY.begin(), vcY.end()), vcY.end());
		ySize = vcY.size();

		treePushIsland(vcIsland.front());
		long long sum = 0;
		for (int n = 1 ; n < N ; n++)
		{
			auto island = vcIsland.at(n);
			int idx = lower_bound(vcY.begin(), vcY.end(), island.second) - vcY.begin();
			sum += query(0, ySize - 1, idx, ySize - 1);
			treePushIsland(island);
		}

		cout << sum << "\n";
	}
	return 0;
}