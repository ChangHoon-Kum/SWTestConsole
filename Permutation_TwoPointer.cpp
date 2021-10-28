// ������ �־�����. �ش� �������� ���ӵǴ� ������ min-max���̰� K�� �Ǵ� �ּұ����� ���̿� ������ ���ϰ��� �Ѵ�.
// ���� ��� �Ʒ��� ���� 10���� �������� min max���̰� 10�� �Ǵ� ������ ã�� ����
// 1, 7, 9, 11, 3, 15, 13, 14, 5, 2
// [1, 7, 9, 11] ��[15, 13, 14, 5]�� ���� ���̰� 4�̰� min max���̰� 10�̴�.���� ���� ��������4 ���� 2�̴�

//���Է�
//ù�ٿ� testcase�� ���ڰ� �־�����(1 < T < 45)
//��°�ٿ� ������ ����N��(2 < N < 100000)�� ���̰�K(1, 000, 000, 000)�� �־�����.�ԷµǴ� ���� A�� ������ 1 < A < 1, 000, 000, 000�̸� �ߺ��Ǵ� ���ڴ� ���������ʴ´�
//�����
//�� �׽�Ʈ���̽����� ������ ���� �� ������ ����Ѵ�. �� ������ �������� ���� ��� '-1'�� ����Ѵ�

//��Ǯ��
//Two Pointer ������� ���� �˻�
//�ð� ���⵵: O(N) ����

#include <stdio.h>
#include <iostream>

using namespace std;
#define ARRAY_MAX 10000

int A[ARRAY_MAX];

int main(void)
{
	freopen("input.txt", "r", stdin);

	int testcase, N, K;
	cin >> testcase >> N >> K;

	for (int t = 0 ; t < testcase ; t++)
	{
		// 0. Initialize
		memset(A, 0, sizeof(int) * ARRAY_MAX);

		for (size_t i = 0; i < N; i++)
		{
			cin >> A[i];
		}

		int min_length = INT_MAX;
		int min_count = 0;

		// 1. Two point
		int s = 0;
		int e = s;

		while (true)
		{
			if (A[s] <= A[e])
			{
				if ((A[e] - A[s]) == K)
				{
					int cur_length = (e - s) + 1;
					if (cur_length < min_length)
					{
						min_length = cur_length;
						min_count = 1;
					}
					else if (cur_length == min_length)
					{
						min_count++;
					}

					s = e + 1;
					e = s;
				} 
				else if((A[e] - A[s]) < K)
				{
					e++;
				}
				else
				{
					s = e;
				}
			}
			else
			{
				s = e;
			}

			if (s >= N || e >= N)
			{
				break;
			}
		}
		
		// 2. Output
		if (min_count > 0)
		{
			printf("%d, %d\n", min_length, min_count);
		}
		else
		{
			printf("-1\n");
		}
	}

	return 0;
}