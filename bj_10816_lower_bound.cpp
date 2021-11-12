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

	vector<long long> vcCard;
	vcCard.resize(N);
	for (int n = 0; n < N; n++)
	{
		cin >> vcCard[n];
	}

	sort(vcCard.begin(), vcCard.end());

	int M;
	cin >> M;
	for (int m = 0; m < M; m++)
	{
		long long val;
		cin >> val;

		if (val < vcCard[0] || val > vcCard[N - 1])
		{
			cout <<"0 ";
			continue;
		}

		int lo = lower_bound(vcCard.begin(), vcCard.end(), val) - vcCard.begin();
		int up = lower_bound(vcCard.begin(), vcCard.end(), val+1) - vcCard.begin();

		if (lo != up)
		{
			cout << up - lo << " ";
		}
		else
		{
			cout << "0 ";
		}
	}
	return 0;
}