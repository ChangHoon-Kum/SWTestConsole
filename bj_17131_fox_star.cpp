#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <climits>

using namespace std;
#define DIV_MOD 1000000007
#define STAR_MAX 200001

int N;
map<int, priority_queue<int>> mapPq; // x, map<y>
//vector<pair<int, int>> vcPos; // x, y
vector<int> vcX;
vector<int> vcY;
long long treeL[4 * STAR_MAX];
long long treeR[4 * STAR_MAX];
long long dpSelfCnt[STAR_MAX];

long long update(long long* _tree, int start, int end, int idx, long long val, int node = 1)
{
	if (idx < start || end < idx) return _tree[node];

	if (start == end) return _tree[node] = (_tree[node] + val);

	int mid = (start + end) / 2;
	long long lval = update(_tree, start, mid, idx, val, node * 2);
	long long rval = update(_tree, mid + 1, end, idx, val, node * 2 + 1);

	return _tree[node] = (lval + rval);
}

long long query(long long* _tree, int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return 0;

	if (left <= start && end <= right) return _tree[node];

	int mid = (start + end) / 2;
	long long lval = query(_tree, start, mid, left, right, node * 2);
	long long rval = query(_tree, mid + 1, end, left, right, node * 2 + 1);

	return (lval + rval);
}

long long getSelfCnt(int cnt)
{
	if (cnt <= 1) return 0;

	if (dpSelfCnt[cnt] != 0) return dpSelfCnt[cnt];

	return dpSelfCnt[cnt] = (cnt - 1 + getSelfCnt(cnt - 1)) % DIV_MOD;
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	fill(treeL, treeL + 4 * STAR_MAX, 0);
	fill(treeR, treeR + 4 * STAR_MAX, 0);
	fill(dpSelfCnt, dpSelfCnt + STAR_MAX, 0);

	cin >> N;

	for (int n = 0 ; n < N ; n++)
	{
		int x, y;
		cin >> x >> y;

		mapPq[x].emplace(y);
		vcY.emplace_back(y);
		//vcPos.emplace_back(x, y);
	}

	for (auto it : mapPq)
	{
		vcX.emplace_back(it.first);
	}

	vector<int> vcY_org = vcY;
	sort(vcY.begin(), vcY.end());
	vcY.erase(unique(vcY.begin(), vcY.end()), vcY.end());

	//segment tree
	{
		priority_queue<int> pq_L = mapPq[vcX.front()];
		while (pq_L.size())
		{
			int y = pq_L.top();
			pq_L.pop();

			int idx = lower_bound(vcY.begin(), vcY.end(), y) - vcY.begin();
			update(treeL, 0, vcY.size() - 1, idx, 1);
		}

		for (int x = 2 ; x < vcX.size() ; x++)
		{
			priority_queue<int> pq_R = mapPq[vcX[x]];
			while (pq_R.size())
			{
				int y = pq_R.top();
				pq_R.pop();

				int idx = lower_bound(vcY.begin(), vcY.end(), y) - vcY.begin();
				update(treeR, 0, vcY.size() - 1, idx, 1);
			}
		}
	}

	//sweep
	long long sum = 0;
	for (int x_idx = 1 ; x_idx < vcX.size()-1 ; x_idx++)
	{
		priority_queue<int> pq1 = mapPq[vcX[x_idx]];
		priority_queue<int> pq2 = mapPq[vcX[x_idx]];
		//long long selfCnt = getSelfCnt(pPq->size());
		
		long long local_sum = 0;
		while (pq1.size())
		{
			int y = pq1.top();
			pq1.pop();

			if (y + 1 > vcY.back()) continue;

			int idx = lower_bound(vcY.begin(), vcY.end(), y + 1) - vcY.begin();
			long long cntL = query(treeL, 0, vcY.size() - 1, idx, vcY.size() - 1);
			long long cntR = query(treeR, 0, vcY.size() - 1, idx, vcY.size() - 1);

			local_sum += (cntL * cntR) % DIV_MOD;
		}

		//update tree
		while (pq2.size())
		{
			int y = pq2.top();
			pq2.pop();

			int idx = lower_bound(vcY.begin(), vcY.end(), y) - vcY.begin();
			update(treeL, 0, vcY.size() - 1, idx, 1);
		}

		priority_queue<int> pq3 = mapPq[vcX[x_idx+1]];
		while (pq3.size())
		{
			int y = pq3.top();
			pq3.pop();

			int idx = lower_bound(vcY.begin(), vcY.end(), y) - vcY.begin();
			update(treeR, 0, vcY.size() - 1, idx, -1);
		}

		sum = (sum + local_sum) % DIV_MOD;
	}

	cout << sum;

	return 0;
}