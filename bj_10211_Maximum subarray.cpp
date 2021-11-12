#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		int N;
		cin >> N;
		vector<int> maxsum;
		maxsum.resize(N);
		int cursum = 0;
		for (int n = 0 ; n < N ; n++)
		{
			int val;
			cin >> val;

			if (n == 0)
			{
				maxsum[0] = cursum = val;
			}
			else
			{
				cursum = max(val, val + cursum);
				maxsum[n] = max(maxsum[n - 1], cursum);
			}
		}

		cout << maxsum[N - 1] << "\n";
	}

	return 0;
}