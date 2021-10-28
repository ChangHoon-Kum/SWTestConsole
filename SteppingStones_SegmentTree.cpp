//�� ¡�˴ٸ�
//A������ B���� ���̿� �볪���� �̷���� ¡�˴ٸ��� �ִ�
//�� ¡�˴ٸ����� ������ �����ְ�, ���� �볪������ ���� �볪���� �̵��� �ִ� K��ŭ �̵��Ҽ� �ִ�
//¡�˴ٸ��� �ǳ����� �ִ�� ���� �� �ִ� ������ ���϶�

//< ��������>
//1. N : 1 ~300, 000
//2. K : 1 ~N
//3. ���� : ��ȣ���ִ� 32bit ������
//4. ù������ �������� ������ ��ƾ� �Ѵ�
//5. ���� ������ 2�� ���� �� ����.

//< �Է�>
//2                                // TC
//7 2                            // N, K
//- 6 - 4 - 6 4 - 4 - 2 9     // �볪�� ����
//7 3
//- 6 - 4 - 6 4 - 4 - 2 9

//< ��� >
//#1 1
//#2 7

//����
//T1 : -6 -> - 4 -> 4 -> - 2 -> 9    ���� 1
//T2 : -6 -> 4-> 9  ���� 7

#include <iostream>
#include <algorithm>

using namespace std;
#define ARRAY_MAX 300000

struct DATA
{
	int nMaxVal;
	int nIdx;

	DATA()
	{
		nMaxVal = nIdx = -INT_MAX;
	}

	DATA(int _nMax, int _nIdx)
	{
		nMaxVal = _nMax;
		nIdx = _nIdx;
	}

	void Update(int _nMax, int _nIdx)
	{
		if (_nMax > nMaxVal)
		{
			nMaxVal = _nMax;
			nIdx = _nIdx;
		}
	}
};

int N, K;
int A[ARRAY_MAX];

DATA tree[4 * ARRAY_MAX];

DATA init(int start, int end, int node = 1)
{
	if (start == end) return tree[node] = DATA(A[start], start);

	int mid = (start + end) / 2;
	DATA LVal = init(start, mid, node * 2);
	DATA RVal = init(mid + 1, end, node * 2 + 1);

	return tree[node] = LVal.nMaxVal > RVal.nMaxVal ? LVal : RVal;
}

DATA calc(int start, int end, int left, int right, int node = 1)
{
	if (right < start || left > end) return DATA();

	if (left <= start && right >= end) return tree[node];

	int mid = (start + end) / 2;
	DATA LVal = calc(start, mid, left, right, node * 2);
	DATA RVal = calc(mid + 1, end, left, right, node * 2 + 1);

	return LVal.nMaxVal > RVal.nMaxVal ? LVal : RVal;
}

void update(int start, int end, int index, int val, int node = 1)
{
	if (index < start || index > end) return;

	tree[node].Update(val, index);

	if (start == end) return;

	int mid = (start + end) / 2;
	update(start, mid, index, val, node * 2);
	update(mid + 1, end, index, val, node * 2 + 1);
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		memset(A, 0, sizeof(int) * ARRAY_MAX);
		memset(tree, 0, sizeof(DATA) * 4 * ARRAY_MAX);

		cin >> N >> K;

		for (int i = 0 ; i < N ; i++)
		{
			cin >> A[i];
		}

		init(0, N - 1);

		int s = 0; 
		int e = s;
		int point = A[s];
		DATA data;

		while (true)
		{
			e = min(s + K, N - 1);

			data = calc(0, N - 1, s + 1, e);
			point += data.nMaxVal;
			s = data.nIdx;

			if (s >= N - 1) break;
		}

		printf("%d\n", point);
	}

	return 0;
}