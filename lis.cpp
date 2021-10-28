#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

int lis(vector <int>& v)
{
	vector <int> res;

	for (int i = 0 ; i < N ; i++)
	{
		int lo = lower_bound(res.begin(), res.end(), v[i]) - res.begin();

		if (lo == (int)res.size())
		{
			res.push_back(v[i]);
		}
		else
		{
			res[lo] = v[i];
		}
	}

	return (int)res.size();
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	cin >> N;
	vector<int> vcVal;
	vcVal.resize(N);

	for (int n = 0 ; n < N ; n++)
	{
		cin >> vcVal[n];
	}

	cout << lis(vcVal);

	return 0;
}