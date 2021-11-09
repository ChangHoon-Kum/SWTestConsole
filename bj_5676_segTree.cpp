#include <iostream>
#include <algorithm>

using namespace std;
#define ARRAY_MAX 100001
//#define UNIT 100000. // prevent overflow

int N, K;
int tree[4 * ARRAY_MAX];

int update(int start, int end, int idx, int val, int node = 1)
{
	if (idx < start || idx > end) return tree[node];

	if (start == end) return tree[node] = val;

	int mid = (start + end) / 2;
	return tree[node] = update(start, mid, idx, val, node * 2) * update(mid + 1, end, idx, val, node * 2 + 1);
}

int query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return 1;

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return query(start, mid, left, right, node * 2) * query(mid + 1, end, left, right, node * 2 + 1);
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	while (true)
	{
		N = K = 0;
		cin >> N >> K;
		if (N == 0 || K == 0) return 0;

		// 0. Init
		fill(tree, tree + 4 * ARRAY_MAX, 0);

		int val;
		for (int n = 0 ; n < N ; n++)
		{
			cin >> val;
			int input = (val == 0) ? 0 : (val > 0) ? 1 : -1;
			update(0, N - 1, n, input);
		}

		for (int k = 0; k < K; k++)
		{
			char op; 
			pair<int, int> pairOp;

			cin >> op >> pairOp.first >> pairOp.second;

			if (op == 'C')
			{
				pairOp.first--;// 0 index
				int input = (pairOp.second == 0) ? 0 : (pairOp.second > 0) ? 1 : -1;
				update(0, N - 1, pairOp.first, input);
			}
			else if (op == 'P')
			{
				pairOp.first--;// 0 index
				pairOp.second--;
				int ans = query(0, N - 1, pairOp.first, pairOp.second);
				char ret = (ans == 0) ? '0' : (ans > 0) ? '+' : '-';
				cout << ret;
			}
		}

		cout << "\n";
	}
	
	return 0;
}
