#include <iostream>
#include <algorithm>


using namespace std;
int N, K;
#define N_MAX 101
#define K_MAX 100001

int W[N_MAX], V[N_MAX];
int dp[N_MAX][K_MAX];


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
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	cin >> N >> K;
	memset(dp, 0, sizeof(int) * N_MAX * K_MAX);

	for (int n = 0 ; n < N ; n++ )
	{
		cin >> W[n] >> V[n];
	}

	cout << knapsack();

	return 0;
}