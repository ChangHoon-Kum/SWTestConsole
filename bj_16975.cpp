#include <iostream>
#include <algorithm>

using namespace std;
#define ARRAY_MAX 100001
long long A[ARRAY_MAX];
long long tree[4 * ARRAY_MAX];

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


int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	fill(tree, tree + 4 * ARRAY_MAX, 0);

	int N, M;
	cin >> N;
	for (int n = 0; n < N; n++)
	{
		cin >> A[n];
	}

	cin >> M;
	for (int m = 0; m < M; m++)
	{
		int q;
		cin >> q;

		if (q == 1)
		{
			int i, j, k;
			cin >> i >> j >> k;
			if (i > j) swap(i, j);
			i--;
			//j--;
			update(0, N, i, k);
			update(0, N, j, -k);
		}
		else // q == 2
		{
			int x;
			cin >> x;
			x--;
			cout << A[x] + query(0, N, 0, x) << "\n";
		}
	}


	return 0;
}