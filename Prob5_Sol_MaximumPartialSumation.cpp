/**
 * 
 �� �ִ� �κ���
N���� ������ �̷���� ������ �迭�� �־�����. ���� ���ӵ� ��� ���� �����ؼ� ���� �� �ִ� ���� ū ���� �ִ�κ����̶�� �Ѵ�. ��, ���� �Ѱ� �̻� �����ؾ� �Ѵ�.
���� ��� [-3, -5, 4, -2, 5, 3, -2, -1]��� �迭�� �־����� ���, �ش� �迭�� �ִ� �κ����� [4, -2, 5, 3]������ 10�� �ȴ�.
�� �迭�� �Ϻ� ������ ��Ÿ���� (i,j)���� Q�� �־�����. (1<=i<=j<=N, �� i�� 1�̰� ���ÿ� j�� N�� ���� �־����� �ʴ´�. ) �̶� �� (i,j)�ֿ� ����, �迭���� i~j��° ������ ������ ������ ���������� �ִ� �κ����� ���ϰ�, �� �ִ� �κ��յ��� ���� ���϶�.(�� ���������� ���� �� ����..)
����) [-3, -5, 4, -2, 5, 3, -2, -1]�迭���� ������ (4,6)�� �־����ٸ� [4,6]������ �����ϰ���, [-3,-5,4]�� [-2,1]�� �� ������ �����ȴ�. �̶�, [-3,-5,4]�� �ִ� �κ����� 4�̰�, [-2,1]�� 1�̹Ƿ�, (4,6)������ ���� �ִ� �κ����� 4�� �ȴ�.
<��������>
N: 2~300,000
Q: 2~300,000
�迭�� ���� ����: -10^8 ~ 10^8
<����ð�>
35���� �׽�Ʈ ���̽��� ���� 1.5���̳�

<���� �Է�>
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

<���>
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