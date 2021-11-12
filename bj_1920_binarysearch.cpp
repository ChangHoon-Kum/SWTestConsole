#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	freopen("input.txt", "r", stdin);
	
	int N;
	cin >> N;

	vector<long long> vcVal;
	vcVal.resize(N);
	for (int n = 0 ; n < N ; n++)
	{
		cin >> vcVal[n];
	}

	sort(vcVal.begin(), vcVal.end());

	int M;
	cin >> M;
	for (int m = 0 ; m < M ; m++)
	{
		long long val;
		cin >> val;

		cout << binary_search(vcVal.begin(), vcVal.end(), val) ? "1" : "0";
		cout << "\n";
	}
	return 0;
}