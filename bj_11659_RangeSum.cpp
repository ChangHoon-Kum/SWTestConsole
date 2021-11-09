#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr);

#define NUM_MAX 100001
long long tree[4 * NUM_MAX];

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
	fastio;

	int N, M;// ¼ýÀÚ °¹¼ö, Äõ¸® ¼ö
	cin >> N >> M;

	fill(tree, tree + NUM_MAX, 0);

	for (int n = 0 ; n < N ; n++)
	{
		int val;
		cin >> val;
		update(0, N - 1, n, val);
	}

	for (int m = 0; m < M; m++)
	{
		int i, j;
		cin >> i >> j;

		cout << query(0, N - 1, i-1, j-1) << "\n";
	}

	return 0;
}