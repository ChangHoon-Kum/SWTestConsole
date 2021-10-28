#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define ARRAY_MAX 100001

int A[ARRAY_MAX];

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase;
	cin >> testcase;

	for (int t = 0; t < testcase; t++)
	{
		int N;
		cin >> N;

		int MaxVal = INT_MIN;
		int MaxPos = INT_MIN;
		for (int n = 0 ; n < N ; n++)
		{
			cin >> A[n];

			if (A[n] > MaxVal)
			{
				MaxVal = A[n];
				MaxPos = n;
			}
		}
		
		// left part lis
		vector<int> res;

		for (int i = 0 ; i < MaxPos ; i++)
		{
			int lo = lower_bound(res.begin(), res.end(), A[i]) - res.begin();

			if (lo == (int)res.size())
				res.push_back(A[i]);
			else
				res[lo] = A[i];
		}
		
		// right part lis
		vector<int> res2;

		for (int i = N-1; i > MaxPos ; i--)
		{
			int lo = lower_bound(res2.begin(), res2.end(), A[i]) - res2.begin();

			if (lo == (int)res2.size())
				res2.push_back(A[i]);
			else
				res2[lo] = A[i];
		}

		// 갯수만 구하면 되므로 sort하지 않음.

		cout << "#" << t + 1 << " " << res.size() + res2.size() + 1 << "\n";
	}
	return 0;
}