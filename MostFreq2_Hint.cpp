#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

const int MAX_N = 1001;
typedef pair<int, int> PII;

int N, M;
int arr[MAX_N]; // �Է¹޴� ���� ����..
PII tree[MAX_N * 4];	// Ʈ���� ���� ������ ����...


PII update(int start, int end, int index, int diff, int node = 1)
{
	if (index < start || index > end) return tree[node];

	if (start == end)
	{	// leaf ���..
		tree[node].first += diff;
		tree[node].second = index;
		return tree[node];
	}

	int mid = (start + end) / 2;
	PII L = update(start, mid, index, diff, node * 2);
	PII R = update(mid + 1, end, index, diff, node * 2 + 1);

	return tree[node] = max(L, R);	// pair�� compare�� ����Ǿ�����..ù��° ���ڴ�� �� ����..
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

		// ���簪 ������Ʈ
		update(1, MAX_N, arr[i], 1);

		if (i >= M)
		{
			//�������� ����
			update(1, MAX_N, arr[i - M], -1);
		}

		if (i >= M - 1) // ���� ���ϱ�
		{
			cout << query(1, MAX_N, 1, MAX_N).second << "\n";
		}
	}

	return 0;
}