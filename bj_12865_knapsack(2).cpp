#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 10001
using namespace std;

int dp[MAX];
int N, K;
vector<pair<int, int> > thing;

int main(void) 
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.txt", "r", stdin);

	cin >> N >> K;

	for (int n = 0 ; n < N ; n++)
	{
		int w, v;
		cin >> w >> v;
		thing.emplace_back(w, v);
	}

	for (auto it : thing)
	{
		for (int j = K ; j >= it.first ; j--)
		{
			dp[j] = max(dp[j], dp[j - it.first] + it.second);
		}
	}

	cout << dp[K];

	return 0;
}