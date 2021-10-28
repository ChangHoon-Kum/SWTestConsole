/**
 * 
�� ¡�˴ٸ�
A������ B���� ���̿� �볪���� �̷���� ¡�˴ٸ��� �ִ�
�� ¡�˴ٸ����� ������ �����ְ�, ���� �볪������ ���� �볪���� �̵��� �ִ� K��ŭ �̵��Ҽ� �ִ�
¡�˴ٸ��� �ǳ����� �ִ�� ���� �� �ִ� ������ ���϶�

< ��������>
1. N : 1 ~300, 000
2. K : 1 ~N
3. ���� : ��ȣ���ִ� 32bit ������
4. ù������ �������� ������ ��ƾ� �Ѵ�
5. ���� ������ 2�� ���� �� ����.

< �Է�>
2                                // TC
7 2                            // N, K
- 6 - 4 - 6 4 - 4 - 2 9     // �볪�� ����
7 3
- 6 - 4 - 6 4 - 4 - 2 9

< ��� >
#1 1
#2 7

����
T1 : -6 -> - 4 -> 4 -> - 2 -> 9    ���� 1
T2 : -6 -> 4-> 9  ���� 7
*/
#include <iostream>
#include <algorithm>

using namespace std;

long long tree[4 * 300001];
int N, K;


long long update(int start, int end, int idx, long long val, int node = 1)
{
	if (idx < start || idx > end) return tree[node];

	if (start == end) return tree[node] = val;

	int mid = (start + end) / 2;
	return tree[node] = max(update(start, mid, idx, val, node * 2), update(mid + 1, end, idx, val, node * 2 + 1));
}

long long query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || left > end) return -INT_MAX;

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return max(query(start, mid, left, right, node * 2), query(mid + 1, end, left, right, node * 2 + 1));
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		cin >> N >> K;

		long long val;
		cin >> val;
		update(0, N - 1, 0, val);

		long long F;
		for (int i = 1 ; i < N ; i++)
		{
			cin >> val;

			long long F_prime = query(0, N - 1, max(0, i - K), i - 1);
			
			F = F_prime + val;
			update(0, N - 1, i, F);
		}

		cout << "#" << t + 1 << " " << F << "\n";
	}
}