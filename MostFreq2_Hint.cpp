#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

const int MAX_N = 1001;
typedef pair<int, int> PII;

int N, M;
int arr[MAX_N]; // 입력받는 숫자 갯수..
PII tree[MAX_N * 4];	// 트리는 숫자 범위로 구축...


PII update(int start, int end, int index, int diff, int node = 1)
{
	if (index < start || index > end) return tree[node];

	if (start == end)
	{	// leaf 노드..
		tree[node].first += diff;
		tree[node].second = index;
		return tree[node];
	}

	int mid = (start + end) / 2;
	PII L = update(start, mid, index, diff, node * 2);
	PII R = update(mid + 1, end, index, diff, node * 2 + 1);

	return tree[node] = max(L, R);	// pair는 compare가 내장되어있음..첫번째 인자대로 비교 진행..
}

PII query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || left > end) return { 0, 0 };

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;

	return max(query(start, mid, left, right, node * 2), query(mid + 1, end, left, right, node * 2 + 1));
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		int n; cin >> arr[i];

		// 현재값 업데이트
		update(1, MAX_N, arr[i], 1);

		if (i >= M)
		{
			//지나간값 삭제
			update(1, MAX_N, arr[i - M], -1);
		}

		if (i >= M - 1) // 정답 구하기
		{
			cout << query(1, MAX_N, 1, MAX_N).second << "\n";
		}
	}

	return 0;
}