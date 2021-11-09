#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;


int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int N;
	cin >> N;

	vector<int> res;
	for (int n = 0; n < N; n++)
	{
		int val;
		cin >> val;

		int idx = lower_bound(res.begin(), res.end(), val) - res.begin();

		if (idx == res.size())
			res.push_back(val);
		else
			res[idx] = val;
	}


	cout << res.size();

	return 0;
}