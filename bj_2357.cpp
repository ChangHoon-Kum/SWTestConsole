#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
#define ARRAY_MAX 100001

typedef pair<int, int> DATA; // min, max

DATA tree[4 * ARRAY_MAX];

DATA update(int start, int end, int idx, DATA val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] = val;

	int mid = (start + end) / 2;
	DATA lval = update(start, mid, idx, val, node * 2);
	DATA rval = update(mid + 1, end, idx, val, node * 2 + 1);
	return tree[node] = make_pair(min(lval.first, rval.first), max(lval.second, rval.second));
}

DATA query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return make_pair(INT_MAX, INT_MIN);

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	DATA lval = query(start, mid, left, right, node * 2);
	DATA rval = query(mid + 1, end, left, right, node * 2 + 1);
	return make_pair(min(lval.first, rval.first), max(lval.second, rval.second));
}



int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int N, M;
	cin >> N >> M;

	fill(tree, tree + 4 * ARRAY_MAX, make_pair(INT_MAX, INT_MIN));

	for (int n = 0 ; n < N ; n++)
	{
		int val;
		cin >> val;
		update(0, N - 1, n, make_pair(val, val));
	}

	for (int m = 0 ; m < M ; m++)
	{
		int i, j;
		cin >> i >> j;
		i--;
		j--;

		DATA val = query(0, N - 1, i, j);

		cout << val.first << " " << val.second << "\n";
	}


	return 0;
}