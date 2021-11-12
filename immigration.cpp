#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;
#define JUDGE_MAX 100001

typedef pair<long long, int> pli;
pli tree[4 * JUDGE_MAX];

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
	pli rval = update(mid+1, end, idx, val, node * 2 + 1);
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

long long solution(int n, vector<int> times) {
	long long answer = 0;

	fill(tree, tree + 4 * JUDGE_MAX, make_pair(0, -1));

	int NumofJudge = times.size();
	for (int i = 0; i < NumofJudge ; i++)
	{
		update(0, NumofJudge - 1, i, times[i]);
	}

	answer = *max_element(times.begin(), times.end());
	for (int i = NumofJudge ; i < n ; i++)
	{
		pli cur = query(0, NumofJudge - 1, 0, NumofJudge - 1);
		answer += (cur.first + times[cur.second] - answer);
		update(0, NumofJudge - 1, cur.second, times[cur.second]);
	}

	return answer;
}

int main(void)
{
	int n = 6;
	vector<int> times;
	times.emplace_back(7);
	times.emplace_back(10);

	cout << solution(n, times);

	return 0;
}