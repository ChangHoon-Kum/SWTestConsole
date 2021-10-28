/**
 * 
 �� ����ũ

N���� �������� �������� ����ũ�� �ִ�. ���� Ŭ���̴� �� ����ũ ������ ���� �����ϴ� ������ �ٸ���. �����ϸ� ���, �Ⱦ��ϸ� �����̴�. ���� Ŭ���̿��� ���� ����������� �ֵ��� ����ũ�� �й��Ϸ��� �Ѵ�.
������, �����ϱ� ������ ���ӵ� �������θ� �ַ��� �Ѵ�.
10���� ������ �Ʒ��� ���� �ִٰ� �ϸ�
�ε���	1	2	3	4	5	6	7	8	9	10
��	-7	-2	-7	-11	-9	13	8	7	13	5
Ŭ����	-9	5	-1	3	-11	0	5	5	-13	5

������ 6��~ 10���������� �й��ϸ� �������� 46�̸�, Ŭ���̿��� 2~4������ �й��ϸ� �������� 7�̸�, ���� 53��ŭ ������ų�� �ִ�.
��ü �������� ���� ���� ����� ��� �������� ����϶�

2<= N <=300,000
-1000 <= M <= 1000
<�Է�>
2            // test case
10          // N, ���� ��
-7 -2 -7 -11 -9 13 8 7 13 5
-9 5 -1 3 -11 0 5 5 -13 5
5
-9 -22 -3 -8 -10
-50 -2 -1 -3 -4
<���>
#1 53
#2 -5
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

//#define ARRAY_MAX 300000
#define CURSUM 0
#define MAXSUM 1

struct TASTE 
{
	vector<array<long long, 2>> LR_DP;
	vector<array<long long, 2>> RL_DP;

	void clear()
	{
		LR_DP.clear();
		RL_DP.clear();
	}

	void resize(int _n)
	{
		LR_DP.resize(_n);
		RL_DP.resize(_n);
	}
};

TASTE JOHN;
TASTE CLOE;

vector<long long> val_john;
vector<long long> val_cloe;

int N;

template<typename T>
void UpdateKadaneDP(TASTE& _taste, vector<T>& _vcVal)
{
	_taste.LR_DP[0][CURSUM] = _taste.LR_DP[0][MAXSUM] = _vcVal[0];

	// Left -> Right
	for (int i = 1 ; i < N ; i++)
	{
		_taste.LR_DP[i][CURSUM] = max(_taste.LR_DP[i-1][CURSUM] + _vcVal[i], _vcVal[i]);
		_taste.LR_DP[i][MAXSUM] = max(_taste.LR_DP[i][CURSUM], _taste.LR_DP[i-1][MAXSUM]);
	}

	_taste.RL_DP[N - 1][CURSUM] = _taste.RL_DP[N - 1][MAXSUM] = _vcVal[N - 1];

	// Right -> Left
	for (int i = N-2 ; i >= 0 ; i--)
	{
		_taste.RL_DP[i][CURSUM] = max(_taste.RL_DP[i + 1][CURSUM] + _vcVal[i], _vcVal[i]);
		_taste.RL_DP[i][MAXSUM] = max(_taste.RL_DP[i][CURSUM], _taste.RL_DP[i + 1][MAXSUM]);
	}
	
}

void InitValiables()
{
	val_john.clear();
	val_cloe.clear();
	JOHN.clear();
	CLOE.clear();

	val_john.resize(N);
	val_cloe.resize(N);
	JOHN.resize(N);
	CLOE.resize(N);
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		cin >> N;

		// 0. init val
		{
			InitValiables();

			for (int n = 0; n < N; n++)
			{
				cin >> val_john[n];
			}

			for (int n = 0; n < N; n++)
			{
				cin >> val_cloe[n];
			}
		}
		
		// 1. Kadane DP
		UpdateKadaneDP(JOHN, val_john);
		UpdateKadaneDP(CLOE, val_cloe);

		long long MaxTaste = LLONG_MIN;
		for (int i = 0 ; i < N-1; i++)
		{
			MaxTaste = max(MaxTaste, max((JOHN.LR_DP[i][MAXSUM] + CLOE.RL_DP[i + 1][MAXSUM]), (CLOE.LR_DP[i][MAXSUM] + JOHN.RL_DP[i + 1][MAXSUM])));
		}

		cout << "#" << t + 1 << " " << MaxTaste << "\n";
	}

	return 0;
}