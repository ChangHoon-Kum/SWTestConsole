#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
typedef pair<int, int> MinMax;
#define DVD_MAX 100001

MinMax tree[4 * DVD_MAX];

MinMax update(int start, int end, int idx, MinMax val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end)
	{
		//tree[node].first = min(tree[node].first, val.first);
		//tree[node].second = min(tree[node].second, val.second);
		return tree[node] = val;
	}

	int mid = (start + end) / 2;
	MinMax lval = update(start, mid, idx, val, node * 2);
	MinMax rval = update(mid+1, end, idx, val, node * 2 + 1);
	return tree[node] = make_pair(min(lval.first, rval.first), max(lval.second, rval.second));
}

MinMax query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return make_pair(INT_MAX, INT_MIN);

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	MinMax lval = query(start, mid, left, right, node * 2);
	MinMax rval = query(mid + 1, end, left, right, node * 2 + 1);
	return make_pair(min(lval.first, rval.first), max(lval.second, rval.second));
}


int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	for (int t = 0; t < testcase; t++)
	{
		fill(tree, tree + 4 * DVD_MAX, make_pair(INT_MAX, INT_MIN));
		int N, K;
		cin >> N >> K;

		for (int n = 0 ; n < N ; n++)
		{
			update(0, N - 1, n, make_pair(n, n));
		}

		for (int k = 0 ; k < K ; k++)
		{
			int q, a, b;
			cin >> q >> a >> b;
			if (a > b) swap(a, b);

			if (q == 0)
			{
				MinMax dataA = query(0, N - 1, a, a);
				MinMax dataB = query(0, N - 1, b, b);
				update(0, N - 1, a, make_pair(INT_MAX, INT_MIN));
				update(0, N - 1, b, make_pair(INT_MAX, INT_MIN));
				update(0, N - 1, b, dataA);
				update(0, N - 1, a, dataB);
			}
			else // q == 1
			{
				MinMax data = query(0, N - 1, a, b);

				if (a == data.first && b == data.second)
					cout << "YES\n";
				else
					cout << "NO\n";
			}
		}
	}

	return 0;
}