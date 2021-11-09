#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define ARRAY_MAX 1001

int A[ARRAY_MAX];

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);

	vector<int> res;
	vector<int> backtrace;
	int N;
	cin >> N;
	
	for (int n = 0 ; n < N ; n++)
	{
		cin >> A[n];

		int idx = lower_bound(res.begin(), res.end(), A[n]) - res.begin();

		if (idx == res.size()) res.emplace_back(A[n]);
		else res[idx] = A[n];

		backtrace.emplace_back(idx);
	}

	vector<int> ans;
	int back_idx = res.size() - 1;
	for (int i = backtrace.size() - 1; i >= 0 ; i--)
	{
		if (backtrace.at(i) == back_idx)
		{
			ans.emplace_back(A[i]);
			back_idx--;
		}
	}

	cout << ans.size() << "\n";
	while (ans.size())
	{
		auto it = ans.back();
		ans.pop_back();

		cout << it << " ";
	}
	cout << "\n";

	return 0;
}