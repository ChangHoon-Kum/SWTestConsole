// 수열이 주어진다. 해당 수열에서 연속되는 구간의 min-max차이가 K가 되는 최소구간의 길이와 갯수를 구하고자 한다.
// 예를 들어 아래와 같은 10개의 수열에서 min max차이가 10이 되는 구간을 찾아 보자
// 1, 7, 9, 11, 3, 15, 13, 14, 5, 2
// [1, 7, 9, 11] 과[15, 13, 14, 5]는 구간 길이가 4이고 min max차이가 10이다.따라서 답은 구간길이4 갯수 2이다

//○입력
//첫줄에 testcase의 숫자가 주어진다(1 < T < 45)
//둘째줄에 수열의 갯수N과(2 < N < 100000)와 차이값K(1, 000, 000, 000)가 주어진다.입력되는 수열 A의 범위는 1 < A < 1, 000, 000, 000이며 중복되는 숫자는 존재하지않는다
//○출력
//각 테스트케이스마다 구간의 길이 및 갯수를 출력한다. 단 정답이 존재하지 않을 경우 '-1'을 출력한다

//[2차 풀이]
//1. 이중 탐색 부분을 숫자 입력 시마다 map 탐색
//2. 세그먼트 트리 업데이트 할 때 한 번에 하지 말고 숫자 입력시 마다 업뎃

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
	ios_base::sync_with_stdio(false); cin.tie(nullptr); // 반드시 추가

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
			cout << "#" << t + 1 << " " << minSpan.first << " " << minSpan.second << "\n"; // printf 섞지 말 것
		}
		else
		{
			//printf("#%d -1 \n", t+1);
			cout << "#" << t + 1 << " -1\n";
		}
	}

	return 0;
}