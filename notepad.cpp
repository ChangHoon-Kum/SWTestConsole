#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define N_MAX 101
int W[N_MAX], V[N_MAX];
int dp[N_MAX][100001];
int N, K;

int knapsack(int i = 0, int w = 0)
{
	if (dp[i][w] > 0) return dp[i][w];
	if (i == N) return 0;

	int n1 = 0;
	if (w + W[i] <= K)
	{
		n1 = knapsack(i + 1, w + W[i]) + V[i];
	}
	int n2 = knapsack(i + 1, w);

	return dp[i][w] = max(n1, n2);
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	for (int i = 0 ; i < N_MAX ; i++)
	{
		fill(dp[i], dp[i] + 100001, 0);
	}

	cin >> N >> K;
	for (int n = 0 ; n < N ; n++)
	{
		cin >> W[n] >> V[n];
	}

	cout << knapsack();

	return 0;
}