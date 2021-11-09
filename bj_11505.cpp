#include <iostream>
#include <algorithm>

using namespace std;
#define ARRAY_SIZE 1000001
typedef long long int P;
#define DIV_V 1000000007

P tree[4 * ARRAY_SIZE];

P update(int start, int end, int idx, P val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] = val % DIV_V;

	int mid = (start + end) / 2;
	P lval = update(start, mid, idx, val, node << 1);
	P rval = update(mid + 1, end, idx, val, node << 1 | 1);
	return tree[node] = (lval * rval) % DIV_V;
}

P query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return 1;

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	P lval = query(start, mid, left, right, node << 1);
	P rval = query(mid + 1, end, left, right, node << 1 | 1);
	return (lval * rval) % DIV_V;
}


int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int N, M, K, QUERY_MAX;
	cin >> N >> M >> K;
	QUERY_MAX = M + K;

	fill(tree, tree + 4 * N, 1);

	for (int n = 0; n < N; n++)
	{
		P val;
		cin >> val;
		update(0, N - 1, n, val);
	}

	for (int q = 0 ; q < QUERY_MAX ; q++)
	{
		P a, b, c;
		cin >> a >> b >> c;

		if (a == 1)
		{
			update(0, N - 1, b - 1, c);
		}
		else // a == 2
		{
			int i, j;
			i = b - 1;
			j = c - 1;
			if (i > j) swap(i, j);
			i = max(i, 0);
			j = min(j, N - 1);
			cout << query(0, N - 1, i, j) << "\n";
		}
	}


	return 0;
}
