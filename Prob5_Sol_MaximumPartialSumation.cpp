/**
 * 
 ■ 최대 부분합
N개의 정수로 이루어진 임의의 배열이 주어진다. 이중 연속된 몇개의 수를 선태해서 구할 수 있는 가장 큰 합을 최대부분합이라고 한다. 단, 수는 한개 이상 선택해야 한다.
예를 들어 [-3, -5, 4, -2, 5, 3, -2, -1]라는 배열이 주어졌을 경우, 해당 배열의 최대 부분합은 [4, -2, 5, 3]구간인 10이 된다.
한 배열의 일부 구간을 나타내는 (i,j)쌍이 Q개 주어진다. (1<=i<=j<=N, 단 i가 1이고 동시에 j가 N인 경우는 주어지지 않는다. ) 이때 각 (i,j)쌍에 대해, 배열에서 i~j번째 구간을 제외한 나머지 구간에서의 최대 부분합을 구하고, 그 최대 부분합들의 합을 구하라.(각 쿼리에서의 답을 다 더함..)
예시) [-3, -5, 4, -2, 5, 3, -2, -1]배열에서 쿼리가 (4,6)이 주어진다면 [4,6]구간을 제외하고나면, [-3,-5,4]와 [-2,1]의 두 구간이 생성된다. 이때, [-3,-5,4]의 최대 부분합은 4이고, [-2,1]은 1이므로, (4,6)쿼리에 대한 최대 부분합은 4가 된다.
<제한조건>
N: 2~300,000
Q: 2~300,000
배열의 원소 범위: -10^8 ~ 10^8
<실행시간>
35개의 테스트 케이스에 대해 1.5초이내

<예제 입력>
2
8 3
3 -5 4 -2 5 3 -2 1
4 6 //4
1 3 //8
3 6 //3
2 2
-100000000 100000000
1 1 //100000000
2 2 //-100000000

<출력>
#1 15
#2 0
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

#define ARRAY_MAX 300000

#define CURSUM 0
#define MAXSUM 1
vector<array<long long, 2>> LR_DP;
vector<array<long long, 2>> RL_DP;
int A[ARRAY_MAX];

int N, K;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	for (int t = 0; t < testcase; t++)
	{
		LR_DP.clear(); RL_DP.clear();
		cin >> N >> K;
		
		LR_DP.resize(N);
		RL_DP.resize(N);
		fill(A, A + N, 0);

		// Kadane
		// 1. Nomarl
		// First Element
		long long val;
		cin >> val;
		LR_DP[0][CURSUM] = LR_DP[0][MAXSUM] = A[0] = val;

		// Others
		for (int i = 1 ; i < N ; i++)
		{
			cin >> val;
			LR_DP[i][CURSUM] = max(LR_DP[i - 1][CURSUM] + val, val);
			LR_DP[i][MAXSUM] = max(LR_DP[i - 1][MAXSUM], LR_DP[i][CURSUM]);

			A[i] = val;

			
		}

		// 2. Reverse
		RL_DP[N - 1][CURSUM] = RL_DP[N - 1][MAXSUM] = A[N - 1];

		for (int i = N-2 ; i >= 0 ; i--)
		{
			RL_DP[i][CURSUM] = max(RL_DP[i+1][CURSUM] + (long long)A[i], (long long)A[i]);
			RL_DP[i][MAXSUM] = max(RL_DP[i+1][MAXSUM], RL_DP[i][CURSUM]);
		}

		// Get Query and Partial max sum
		int x, y;
		int sum = 0;
		int LVal, RVal;
		for (int k = 0; k < K ; k++)
		{
			cin >> x >> y;

			LVal = (x-2 >= 0) ? LR_DP[x-2][MAXSUM] : INT_MIN;
			RVal = (y <= N - 1) ? RL_DP[y][MAXSUM] : INT_MIN;

			sum += max(LVal, RVal);
		}

		cout << "#" << t + 1 << " " << sum << "\n";
	}

	return 0;
}