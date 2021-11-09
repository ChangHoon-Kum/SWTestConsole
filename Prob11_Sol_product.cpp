#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define NUM_MAX 100001
long long tree[4 * NUM_MAX];

long long update(int start, int end, int idx, long long val, int node = 1)
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

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		fill(tree, tree + 4 * NUM_MAX, 0);

		int N, K, L;
		cin >> N >> K >> L;
		
		int nMaxB = 0; // 필요시 좌표압축 구현
		vector<pair<int, int>> vcProduct; // A, B
		for (int n = 0 ; n < N ; n++)
		{
			int a, b;
			cin >> a >> b;
			vcProduct.emplace_back(a, b);
			nMaxB = max(nMaxB, b);
		}

		sort(vcProduct.begin(), vcProduct.end());

		int NumofProducts = vcProduct.size();
		int del_idx = 0;
		update(1, nMaxB, vcProduct[0].second, 1);

		long long sum = 0;
		for (int i = 1 ; i < NumofProducts ; i++)
		{
			int k = max(1, vcProduct[i].first - K);
			int idx_limit = lower_bound(vcProduct.begin(), vcProduct.end(), pair<int, int>(k, 0)) - vcProduct.begin();
			for (; del_idx < idx_limit; del_idx++)
			{
				update(1, nMaxB, vcProduct[del_idx].second, -1);
			}

			int limit_l = vcProduct[i].second - L;
			int limit_r = vcProduct[i].second + L;
			if(limit_l >= 1)
				sum += query(1, nMaxB, 1, limit_l);
			if(limit_r <= nMaxB)
				sum += query(1, nMaxB, limit_r, nMaxB);

			update(1, nMaxB, vcProduct[i].second, 1);
		}

		cout << "#" << t + 1 << " " << sum << "\n";
	}

	return 0;
}