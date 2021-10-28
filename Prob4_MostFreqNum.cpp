/**
 * 
 ■ 최빈수 찾기

배열 A가 주어진다. Ex) [1, 2, 4, 2, 3, 3, 5]
부분 수열 원소 개수 K가 주어진다. Ex) 5
위 예시의 경우 아래 3개의 부분 수열을 가질수 있다.
[1, 2, 4, 2, 3] : 최빈수 2
[2, 4, 2, 3, 3] : 최빈수 3
[4, 2, 3, 3, 5] : 최빈수 3
각 부분 수열의 최빈수는 2, 3, 3이며 각 부분 수열의 최빈수 중에서 최빈수와 그 개수를 출력하라
*최빈수 : 부분 수열에서 가장 많은 원소가 최빈수 이며, 최빈수의 개수가 같다면 원소의 크기가 큰 값이 최빈수이다.
해당 예시의 최빈수는 3이며 2개 이므로 #1 3 2가 출력된다.

각 테스트 케이스마다 배열의 최빈수와 그 최빈수의 갯수를 출력하라

<입력>
첫째줄에 테스트 케이스의 수가 나타난다 .
다음으로 N(<=300,000)과 K(3<=K<=N)가 주어진다.
다음 N개의 원소A가 주어진다. 원소 범위 (1<=A <= 1e9)

3
7 5
1 2 4 2 3 3 5
10 3
2 2 3 3 5 1 7 4 9 10
6 3
1 1000000000 100 100000 100 100000

<출력>
#1 3 2
#2 7 2
#3 1000000000 2

<이해를 돕기 위한 세번째 테스트 케이스 설명>
부분 수열
[1 1000000000 100]                          :  최빈수 1000000000
[1000000000 100 100000]                    : 최빈수 1000000000
[100 100000 100]                              : 최빈수 100
[100000 100 100000]                          : 최빈수 100000
 부분 수열의 최빈수는 [1000000000, 1000000000, 100, 100000]이며 이중 최빈수는 1000000000이고 2개이다. 따라서 답은
#3 1000000000 2
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#define ARRAY_MAX 300001
using namespace std;

int A[ARRAY_MAX];
vector<int> vcVal;

typedef pair<int, int> PII; // first: 빈도 수, second: 수열 원소
PII tree[4 * ARRAY_MAX];

int N, K;

PII update(int start, int end, int idx, int diff, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end)
	{
		tree[node].first += diff;
		tree[node].second = vcVal[idx];

		return tree[node];
	}

	int mid = (start + end) / 2;
	PII lval = update(start, mid, idx, diff, node * 2);
	PII rval = update(mid+1, end, idx, diff, node * 2 + 1);

	return tree[node] = max(lval, rval);
}

PII query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return make_pair(INT_MIN, INT_MIN);

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	PII lval = query(start, mid, left, right, node * 2);
	PII rval = query(mid + 1, end, left, right, node * 2 + 1);

	return max(lval, rval);
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase; cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		cin >> N >> K;
		vcVal.clear();
		vcVal.resize(N);
		fill(A, A + N, 0);
		fill(tree, tree + 4 * N, make_pair(0, 0));

		for (int n = 0 ; n < N ; n++)
		{
			cin >> A[n];
			vcVal[n] = A[n];
		}

		sort(vcVal.begin(), vcVal.end());
		vcVal.erase(unique(vcVal.begin(), vcVal.end()), vcVal.end());

		map<int, int> mapMaxFreqPart; // val , cnt
		for (int n = 0 ; n < N ; n++)
		{
			int idx = lower_bound(vcVal.begin(), vcVal.end(), A[n]) - vcVal.begin();
			update(0, N - 1, idx, 1);

			if (n >= K) // 지우기
			{
				int delidx = lower_bound(vcVal.begin(), vcVal.end(), A[n-K]) - vcVal.begin();
				update(0, N - 1, delidx, -1);
			}

			if (n >= K - 1) // 부분 최빈
			{
				PII partMaxFreq = query(0, N - 1, 0, N - 1);

				mapMaxFreqPart[partMaxFreq.second]++;
			}
		}

		int maxFreqCnt = INT_MIN;
		int maxFreqVal = INT_MIN;
		for (auto it : mapMaxFreqPart)
		{
			if (it.second > maxFreqCnt)
			{
				maxFreqCnt = it.second;
				maxFreqVal = it.first;
			}
			else if(it.second == maxFreqCnt)
			{
				maxFreqVal = max(maxFreqVal, it.first);
			}
		}


		cout << "#" << t + 1 << " " << maxFreqVal << " " << maxFreqCnt << "\n";
	}

	return 0;
}