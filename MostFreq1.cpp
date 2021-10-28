/**
 * 
 ������ N(1~100��)���� �־�����. ������ ������ (1~1000)�̴�..
�� �������� ���� ������ �־����� �� ���� ���������� �ִ� �󵵼��� �� ���ڸ� ����϶�
Query �� M�� �־�����, ����a~b �� �Է����� �־�����.
���� ��� 1, 2, 3, 4, 4, 5, 5 �� �־�������
���� ���� 3~5�ȿ� �ִ� �ֺ����? �� �󵵼��� �ش� ���ڸ� ����϶�
  -> �ش� ���� ������ �ִ� ���ڴ� 3 4 4 5 5 �̰�, 4�� 2��, 5�� 2�� �̱⶧���� �� ���������� 5
����Ʈ���θ� ����...
input
20 3
1 3 4 3 2 5 6 7 8 7 5 5 2 4 8 3 4 7 5 9
1 10
3 5
7 9
���
5 4
5 4
7 3
�߰�.. �� �������� N�� 10000, �̰� ���� ������ 1~1e9���???
=> �� �������� ��ǥ �������� �����ϸ� Ǯ�� ����... try~

 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define ARRAY_MAX 10000

vector<int> vcVal;
int tree[4 * ARRAY_MAX];
int A[ARRAY_MAX];

int update(int start, int end, int idx, int diff, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] += diff;

	int mid = (start + end) / 2;
	int lval = update(start, mid, idx, diff, node * 2);
	int rval = update(mid+1, end, idx, diff, node * 2 + 1);
	return max(lval, rval);
}

int query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return INT_MIN;

	if (left <= start && end >= right) return tree[node];

	int mid = (start + end) / 2;
	int lval = query(start, mid, left, right, node * 2);
	int rval = query(mid + 1, end, left, right, node * 2 + 1);
	return max(lval, rval);
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int N, K; // �Է� ���� ��, ���� ��
	cin >> N >> K;
	
	for (int n = 0 ; n < N ; n++)
	{
		cin >> A[n];
		update(0, N - 1, A[n], 1);
	}


	return 0;
}