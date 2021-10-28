#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

vector<array<long long, 2>> DP;
#define CURSUM 0
#define MAXSUM 1

int N;

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	cin >> N;

	DP.clear();
	DP.resize(N);

	long long val;
	cin >> val;
	DP[0][CURSUM] = DP[0][MAXSUM] = val;

	for (int n = 1 ; n < N ; n++)
	{
		cin >> val;
		DP[n][CURSUM] = max(DP[n - 1][CURSUM] + val, val);
		DP[n][MAXSUM] = max(DP[n][CURSUM], DP[n - 1][MAXSUM]);
	}

	cout << DP[N - 1][MAXSUM];

	return 0;
}