#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;
#define ARRAY_MAX 100001
typedef tuple<int, long long, int> DATA; // lis order(backtrace), cost, idx
DATA tree[4 * ARRAY_MAX];

DATA update(int start, int end, int idx, DATA val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] = val;// max(tree[node], val);

	int mid = (start + end) / 2;
	DATA lval = update(start, mid, idx, val, node * 2);
	DATA rval = update(mid + 1, end, idx, val, node * 2 + 1);
	return tree[node] = max(lval, rval);
}

DATA query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return make_tuple(-1, 0, -1);

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	DATA lval = query(start, mid, left, right, node * 2);
	DATA rval = query(mid + 1, end, left, right, node * 2 + 1);
	return max(lval, rval);
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	fill(tree, tree + 4 * ARRAY_MAX, make_tuple(-1, 0, -1));

	int N;
	cin >> N;

	vector<tuple<long long, long long, long long>> vcPoint; //x, y, cost
	for (int n = 0 ; n < N ; n++)
	{
		long long x, y, score;
		cin >> x >> y >> score;
		vcPoint.emplace_back(x, y, score);
	}

	sort(vcPoint.begin(), vcPoint.end());

	vector<long long> lis;
	vector<int> backtrace;
	for (auto it : vcPoint)
	{
		auto val = get<1>(it);
		int idx = lower_bound(lis.begin(), lis.end(), val) - lis.begin();

		if (idx == lis.size())
		{
			lis.emplace_back(val);
		}
		else
		{
			lis[idx] = val;
		}
		backtrace.emplace_back(idx);
	}

	for (int i = 0 ; i < N ; i++)
	{
		update(0, N - 1, i, make_tuple(backtrace[i], get<2>(vcPoint[i]), i));
	}

	int Count = lis.size() - 1;
	int del_idx = N - 1;
	vector<long long> ans;
	//typedef tuple<int, long long, int> DATA; // lis order(backtrace), cost, idx
	while (Count >= 0)
	{
		DATA val = query(0, N - 1, 0, N - 1);
		if (get<0>(val) == Count)
		{
			ans.emplace_back(get<1>(val));

			for (; del_idx >= get<2>(val); del_idx--)
			{
				update(0, N - 1, del_idx, make_tuple(-1, 0, -1));
			}

			Count--;
		}
		else
		{
			update(0, N - 1, get<2>(val), make_tuple(-1, 0, -1));
		}		
	}

	long long sum = 0;
	for (auto it : ans)
	{
		sum += it;
	}

	cout << ans.size() << " " << sum;

	return 0;
}