#include <iostream>

long long dp[1000001][2] = { 0, };
#define UNIT 1000000007

using namespace std;

long long calc(int x)
{
	if (x == 0) return 1;
	if (x == 1) return 2;
	if (x == 2) return 7;

	//if(dp[x][0] > 0) return dp[x][0];

	for (int i = 3; i <= x; i++)
	{
		dp[i][1] = (2 * dp[i - 3][0] + dp[i - 1][1]) % UNIT;
		dp[i][0] = (2 * dp[i - 1][0] + 3 * dp[i - 2][0] + dp[i][1]) % UNIT;
	}

	return dp[x][0];
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	dp[0][0] = 0;
	dp[1][0] = 2;
	dp[2][0] = 7;
	dp[2][1] = 2;

	int x;
	cin >> x;
	long long val = calc(x);

	cout << val;
}