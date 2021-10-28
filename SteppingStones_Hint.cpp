#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 300001;

typedef long long ll;	//�� ������ 32bit int���̸�, ¡�� �ٸ� ���� 300,000�̱� ������ long long �ʿ�

int N, K;

ll tree[MAX_N * 4];

// update �Լ� �Ʒ� ���� ��õ..diff �����Ϸ��� tree[node]=val  �κ� tree[node]+= val�� ����..
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

ll dp[MAX_N];	// dp �� �迭.. �Է� ���ڸ��� ó���ҰŶ� �Է� �迭 ��� X, ����� �뵵 ��� Ǯ�̿� ���� ����..

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
			// �Է¹�����.. dp �迭����..
			ll ret = query(0, N - 1, max(0, i - K), i - 1);

			// ���� dp�� ����Ʈ���� ������Ʈ
			dp[i] = ret + n;
			update(0, N - 1, i, ret + n);
		}

		cout << "#" << t << " " << query(0, N - 1, N - 1, N - 1) << "\n";
		//		printf("%d\n", point); ���� cin�̶� printf �� ���� ���� ����.. 
	}

	return 0;
}