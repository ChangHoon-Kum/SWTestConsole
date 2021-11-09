#include <iostream>
#include <algorithm>

using namespace std;
#define ARRAY_MAX 1000001

long long tree[4 * ARRAY_MAX];

long long update(int start, int end, int idx, long long val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] = val;

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

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	fill(tree, tree + 4 * ARRAY_MAX, 0);

	int N, M, K, QUERY_MAX;
	cin >> N >> M >> K;
	QUERY_MAX = M + K;

	{
		long long val;
		for (int n = 0; n < N; n++)
		{
			cin >> val;
			update(0, N - 1, n, val);
		}
	}
	
	for (int q = 0 ; q < QUERY_MAX ; q++)
	{
		long long a, b, c;
		cin >> a >> b >> c;

		if (a == 1)
		{
			update(0, N - 1, b - 1, c);
		}
		else // a == 2
		{
			cout << query(0, N - 1, b - 1, c - 1) << "\n";
		}
	}


	return 0;
}