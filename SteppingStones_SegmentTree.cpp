//■ 징검다리
//A마을과 B마을 사이에 통나무로 이루어진 징검다리가 있다
//각 징검다리에는 점수가 적혀있고, 이전 통나무에서 다음 통나무로 이동시 최대 K만큼 이동할수 있다
//징검다리를 건넜을때 최대로 얻을 수 있는 점수를 구하라

//< 제한조건>
//1. N : 1 ~300, 000
//2. K : 1 ~N
//3. 점수 : 부호가있는 32bit 정수형
//4. 첫나무와 끝나무는 무조건 밟아야 한다
//5. 같은 나무를 2번 밟을 수 없다.

//< 입력>
//2                                // TC
//7 2                            // N, K
//- 6 - 4 - 6 4 - 4 - 2 9     // 통나무 점수
//7 3
//- 6 - 4 - 6 4 - 4 - 2 9

//< 출력 >
//#1 1
//#2 7

//예시
//T1 : -6 -> - 4 -> 4 -> - 2 -> 9    합은 1
//T2 : -6 -> 4-> 9  합은 7

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