#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 300001;

typedef long long ll;	//수 범위가 32bit int형이며, 징검 다리 수가 300,000이기 때문에 long long 필요

int N, K;

ll tree[MAX_N * 4];

// update 함수 아래 형식 추천..diff 전파하려면 tree[node]=val  부분 tree[node]+= val로 수정..
ll update(int start, int end, int index, ll val, int node = 1)
{
	if (index < start || index > end) return tree[node];

	if (start == end)
		return tree[node] = val;

	int mid = (start + end) / 2;
	return tree[node] = max(update(start, mid, index, val, node * 2), update(mid + 1, end, index, val, node * 2 + 1));
}

ll query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || left > end) return LLONG_MIN;

	if (left <= start && right >= end) return tree[node];

	int mid = (start + end) / 2;

	return max(query(start, mid, left, right, node * 2), query(mid + 1, end, left, right, node * 2 + 1));
}

ll dp[MAX_N];	// dp 용 배열.. 입력 받자마자 처리할거라 입력 배열 사용 X, 디버깅 용도 없어도 풀이에 문제 없음..

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase;
	cin >> testcase;

	for (int t = 1; t <= testcase; t++)
	{
		memset(dp, 0, sizeof(dp));
		memset(tree, 0, sizeof(tree));

		cin >> N >> K;
		int n; cin >> n;

		dp[0] = n;
		update(0, N - 1, 0, n);

		for (int i = 1; i < N; i++)
		{
			cin >> n;
			// 입력받으면.. dp 배열쿼리..
			ll ret = query(0, N - 1, max(0, i - K), i - 1);

			// 현재 dp값 세그트리에 업데이트
			dp[i] = ret + n;
			update(0, N - 1, i, ret + n);
		}

		cout << "#" << t << " " << query(0, N - 1, N - 1, N - 1) << "\n";
		//		printf("%d\n", point); 절대 cin이랑 printf 류 섞어 쓰지 말것.. 
	}

	return 0;
}