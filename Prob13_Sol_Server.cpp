#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <queue>


using namespace std;
#define SERVER_MAX 100001

typedef pair<long long, int> pli;
pli tree[4 * SERVER_MAX];

pli update(int start, int end, int idx, long long val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];
	if (start == end)
	{
		tree[node].first += val;
		tree[node].second = idx;
		return tree[node];
	}

	int mid = (start + end) / 2;
	pli lval = update(start, mid, idx, val, node * 2);
	pli rval = update(mid + 1, end, idx, val, node * 2 + 1);
	return tree[node] = min(lval, rval);
}

pli query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return make_pair(LLONG_MAX, -1);

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	pli lval = query(start, mid, left, right, node * 2);
	pli rval = query(mid + 1, end, left, right, node * 2 + 1);
	return min(lval, rval);
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		fill(tree, tree + 4 * SERVER_MAX, make_pair(0, -1));

		vector<int> vcServer;
		queue<int> q;
		int K, N, Q;
		cin >> K >> N >> Q;
		vcServer.resize(N);
		for (int k = 0; k < K; k++)
		{
			int val;
			cin >> val;
			if (k < N)
			{
				vcServer[k] = val;
				update(0, N - 1, k, val);
			}
			else
				q.emplace(val);
		}

		long long ans = 0;
		for (int idx = 0 ; idx < Q ; idx++)
		{
			int qSvrNo, qTime;
			cin >> qSvrNo >> qTime;
			qSvrNo--;//zero base
			pli minServer = query(0, N - 1, 0, N - 1);
			if (qTime <= minServer.first)
			{
				ans += (vcServer[qSvrNo] - qTime);
			}
			else
			{
				while (q.size() && qTime > minServer.first)
				{
					int nTime = q.front();
					q.pop();

					vcServer[minServer.second] += nTime;
					update(0, N - 1, minServer.second, nTime);
					minServer = query(0, N - 1, 0, N - 1);
				}

				if (qTime <= minServer.first)
				{
					ans += (vcServer[qSvrNo] - qTime);
				}
			}
		}

		cout << ans;
	}

	return 0;
}