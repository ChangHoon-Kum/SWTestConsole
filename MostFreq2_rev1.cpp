// MostFreq2_rev0 -> 좌표압축 적용

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define ARRAY_MAX 1001

vector<int> vcVal;
int A[ARRAY_MAX]; //그냥 더 큰 거 씀

typedef pair<int, int> PII; // first: 빈도 수, second: 수열 원소
vector<PII> tree;

PII update(int start, int end, int idx, int diff, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end)
	{
		tree[node].first += diff;
		tree[node].second = vcVal[idx];

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

	int N, K; // 숫자 갯수, 구간 길이
	cin >> N >> K;
	vcVal.resize(N);
	tree.resize(4 * N);

	for (int n = 0 ; n < N ; n++)
	{
		cin >> A[n];
		vcVal[n] = A[n];
	}

	sort(vcVal.begin(), vcVal.end());
	vcVal.erase(unique(vcVal.begin(), vcVal.end()), vcVal.end());

	for (int n = 0 ; n < N ; n++)
	{
		int idx = lower_bound(vcVal.begin(), vcVal.end(), A[n]) - vcVal.begin();
		update(0, N - 1, idx, 1);

		if (n >= K) // 지우기
		{
			int delidx = lower_bound(vcVal.begin(), vcVal.end(), A[n-K]) - vcVal.begin();
			update(0, N - 1, delidx, -1);
		}

		if (n >= K - 1) // 정답
		{
			cout << query(0, N - 1, 0, N - 1).second << "\n";
		}
	}

	return 0;
}