#include <iostream>
#include <algorithm>

using namespace std;
#define ARRAY_MAX 1001

typedef pair<int, int> PII; // first: 빈도 수, second: 트리 인덱스, 입력 배열 원소
PII tree[4 * ARRAY_MAX];
int A[ARRAY_MAX];

PII update(int start, int end, int idx, int diff, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) 
	{
		tree[node].first += diff;
		tree[node].second = idx;
		return tree[node];
	}

	int mid = (start + end) / 2;
	PII lval = update(start, mid, idx, diff, node * 2);
	PII rval = update(mid + 1, end, idx, diff, node * 2 + 1);
	return tree[node] = max(lval, rval);
}

PII query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return make_pair(INT_MIN, INT_MIN);

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	PII lval = query(start, mid, left, right, node * 2);
	PII rval = query(mid + 1, end, left, right, node * 2 + 1);
	return max(lval, rval);
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int N, K;
	cin >> N >> K;

	for (int n = 0 ; n < N ; n++)
	{
		cin >> A[n];
		update(0, N - 1, A[n], 1);

		if (n >= K) // 지나간 것 지우기
		{
			update(0, N - 1, A[n-K], -1);
		}

		if (n >= K - 1) // 정답
		{
			cout << query(0, N - 1, 0, N - 1).second << "\n";
		}
	}

	return 0;
}