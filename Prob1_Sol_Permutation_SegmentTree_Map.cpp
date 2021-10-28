// ������ �־�����. �ش� �������� ���ӵǴ� ������ min-max���̰� K�� �Ǵ� �ּұ����� ���̿� ������ ���ϰ��� �Ѵ�.
// ���� ��� �Ʒ��� ���� 10���� �������� min max���̰� 10�� �Ǵ� ������ ã�� ����
// 1, 7, 9, 11, 3, 15, 13, 14, 5, 2
// [1, 7, 9, 11] ��[15, 13, 14, 5]�� ���� ���̰� 4�̰� min max���̰� 10�̴�.���� ���� ��������4 ���� 2�̴�

//���Է�
//ù�ٿ� testcase�� ���ڰ� �־�����(1 < T < 45)
//��°�ٿ� ������ ����N��(2 < N < 100000)�� ���̰�K(1, 000, 000, 000)�� �־�����.�ԷµǴ� ���� A�� ������ 1 < A < 1, 000, 000, 000�̸� �ߺ��Ǵ� ���ڴ� ���������ʴ´�
//�����
//�� �׽�Ʈ���̽����� ������ ���� �� ������ ����Ѵ�. �� ������ �������� ���� ��� '-1'�� ����Ѵ�

//[2�� Ǯ��]
//1. ���� Ž�� �κ��� ���� �Է� �ø��� map Ž��
//2. ���׸�Ʈ Ʈ�� ������Ʈ �� �� �� ���� ���� ���� ���� �Է½� ���� ����

#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

struct DATA
{
	int nMaxVal;
	int nMinVal;

	DATA()
	{
		nMaxVal = 0;
		nMinVal = INT_MAX;
	}

	DATA(int n)
	{
		nMinVal = nMaxVal = n;
	}

	DATA(int _min, int _max)
	{
		nMinVal = _min;
		nMaxVal = _max;
	}

	void update(int n)
	{
		nMinVal = min(nMinVal, n);
		nMaxVal = max(nMaxVal, n);
	}
};

#define ARRAY_MAX 100000

int A[ARRAY_MAX];
DATA tree[4 * ARRAY_MAX];

DATA init(int start, int end, int node = 1)
{
	if (start == end) return tree[node] = A[start];

	int mid = (start + end) / 2;
	DATA Lval = init(start, mid, node * 2);
	DATA Rval = init(mid + 1, end, node * 2 + 1);
	return tree[node] = DATA(min(Lval.nMinVal, Rval.nMinVal), max(Lval.nMaxVal, Rval.nMaxVal));
}

DATA calc(int start, int end, int left, int right, int node = 1)
{
	if (right < start || left > end) return DATA();

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	DATA Lval = calc(start, mid, left, right, node * 2);
	DATA Rval = calc(mid + 1, end, left, right, node * 2 + 1);
	return DATA(min(Lval.nMinVal, Rval.nMinVal), max(Lval.nMaxVal, Rval.nMaxVal));
}

void update(int start, int end, int idx, int val, int node = 1)
{
	if (idx < start || idx > end) return;

	tree[node].update(val);

	if (start == end) return;

	int mid = (start + end) / 2;
	update(start, mid, idx, val, node * 2);
	update(mid + 1, end, idx, val, node * 2 + 1);
}

map<int/*Val*/, int/*Idx of Array*/> mapInput;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); // �ݵ�� �߰�

	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	int checkVal[2];
	const int checkminValIdx = 0;
	const int checkmaxValIdx = 1;

	for (int t = 0 ; t < testcase ; t++)
	{
		int N, K;
		cin >> N >> K;

		// Array Init
		{
			memset(A, NULL, sizeof(int) * N);
			DATA initData;
			fill(tree, tree + 4*N, initData);
		}

		pair<int/*length*/, int/*count*/> minSpan = make_pair(INT_MAX, 0);

		DATA data;
		for (int i = 0 ; i < N ; i++)
		{
			cin >> A[i];

			update(0, N-1, i, A[i]);

			checkVal[checkminValIdx] = A[i] - K;
			checkVal[checkmaxValIdx] = A[i] + K;

			for (int j = checkminValIdx ; j <= checkmaxValIdx ; j++)
			{
				if (mapInput.find(checkVal[j]) != mapInput.end())
				{
					int l = mapInput[checkVal[j]];
					int r = i;

					data = calc(0, N-1, l, r);
					int diff = data.nMaxVal - data.nMinVal;
					int span = r - l + 1;

					if (diff == K)
					{
						if (span < minSpan.first)
						{
							minSpan.first = span;
							minSpan.second = 1;
						}
						else if (span == minSpan.first)
						{
							minSpan.second++;
						}
					}
				}
			}

			mapInput[A[i]] = i; // map push
		}

		if (minSpan.second > 0)
		{
			//printf("#%d %d %d \n", t+1, minSpan.first, minSpan.second);
			cout << "#" << t + 1 << " " << minSpan.first << " " << minSpan.second << "\n"; // printf ���� �� ��
		}
		else
		{
			//printf("#%d -1 \n", t+1);
			cout << "#" << t + 1 << " -1\n";
		}
	}

	return 0;
}