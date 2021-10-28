// ������ �־�����. �ش� �������� ���ӵǴ� ������ min-max���̰� K�� �Ǵ� �ּұ����� ���̿� ������ ���ϰ��� �Ѵ�.
// ���� ��� �Ʒ��� ���� 10���� �������� min max���̰� 10�� �Ǵ� ������ ã�� ����
// 1, 7, 9, 11, 3, 15, 13, 14, 5, 2
// [1, 7, 9, 11] ��[15, 13, 14, 5]�� ���� ���̰� 4�̰� min max���̰� 10�̴�.���� ���� ��������4 ���� 2�̴�

//���Է�
//ù�ٿ� testcase�� ���ڰ� �־�����(1 < T < 45)
//��°�ٿ� ������ ����N��(2 < N < 100000)�� ���̰�K(1, 000, 000, 000)�� �־�����.�ԷµǴ� ���� A�� ������ 1 < A < 1, 000, 000, 000�̸� �ߺ��Ǵ� ���ڴ� ���������ʴ´�
//�����
//�� �׽�Ʈ���̽����� ������ ���� �� ������ ����Ѵ�. �� ������ �������� ���� ��� '-1'�� ����Ѵ�

#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;
#define ARRAY_MAX 100000

int A[ARRAY_MAX];

struct DATA {
	int nMax;
	int nMin;

	DATA()
	{
		nMax = 0;
		nMin = INT_MAX;
	}

	DATA(int n)
	{
		nMin = nMax = n;
	}

	DATA(int _nMin, int _nMax)
	{
		nMin = _nMin;
		nMax = _nMax;
	}

	void Update(int n)
	{
		nMin = min(nMin, n);
		nMax = max(nMax, n);
	}

	int GetDiff()
	{
		return nMax - nMin;
	}
};

DATA tree[4 * ARRAY_MAX];

DATA init(int start, int end, int node = 1)
{
	if (start == end) return tree[node] = DATA(A[start]);
	int mid = (start + end) / 2;

	DATA LVAL = init(start, mid, node * 2);
	DATA RVAL = init(mid+1, end, node * 2+1);

	return tree[node] = DATA(min(LVAL.nMin,RVAL.nMin), max(LVAL.nMax,RVAL.nMax));
}

DATA calc(int start, int end, int left, int right, int node = 1)
{
	if (right < start || left > end) return DATA(INT_MAX,0);

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	
	DATA LVAL = calc(start, mid, left, right, node * 2);
	DATA RVAL = calc(mid+1, end, left, right, node * 2 + 1);

	return DATA(min(LVAL.nMin, RVAL.nMin), max(LVAL.nMax, RVAL.nMax));
}

void update(int start, int end, int index, int val, int node = 1)
{
	if (index < start || index > end) return;

	tree[node].Update(val);

	if (start == end) return;

	int mid = (start + end) / 2;
	update(start, mid, index, val, node * 2);
	update(mid + 1, end, index, val, node * 2 + 1);
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	int testcase, N, K;
	cin >> testcase >> N >> K;

	for (int t = 0; t < testcase; t++)
	{
		// 0. Initialize
		memset(A, 0, sizeof(int) * ARRAY_MAX);
		memset(tree, 0, sizeof(pair<int, int>) * 4 * ARRAY_MAX);

		for (size_t i = 0; i < N; i++)
		{
			cin >> A[i];
		}

		init(0, N - 1);

		int min_length = INT_MAX;
		int min_count = 0;
		DATA data;

		for (int s = 0 ; s < N ; s++)
		{
			for (int e = s ; e < N ; e++)
			{
				data = calc(0, N - 1, s, e);
				int diff = data.GetDiff();
				if (diff == K)
				{
					int length = e - s + 1;
					if (length < min_length)
					{
						min_length = length;
						min_count = 1;
					}
					else if (length == min_length)
					{
						min_count++;
					}
				}
			}
		}

		// 2. Output
		if (min_count > 0)
		{
			printf("%d, %d\n", min_length, min_count); // cin ���� ��ü�� ��
		}
		else
		{
			printf("-1\n");
		}
	}

	return 0;
}