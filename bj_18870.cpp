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

	vector<long long> vcVal, vcVal_org;
	vcVal.resize(N);
	vcVal_org.resize(N);
	for (int n = 0; n < N; n++)
	{
		cin >> vcVal[n];
	}
	vcVal_org = vcVal;

	sort(vcVal.begin(), vcVal.end());
	vcVal.erase(unique(vcVal.begin(), vcVal.end()), vcVal.end());

	
	for (auto it : vcVal_org)
	{
		cout << lower_bound(vcVal.begin(), vcVal.end(), it) - vcVal.begin() << " ";
	}

	return 0;
}