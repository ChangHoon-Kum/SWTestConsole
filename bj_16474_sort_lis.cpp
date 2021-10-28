#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define ARRAY_MAX 2001

int LeftTable[ARRAY_MAX];
int RightTable[ARRAY_MAX];

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int N, M;

	cin >> N >> M;

	int temp;
	for (int n = 0 ; n < N ; n++)
	{
		cin >> temp;
		LeftTable[temp] = n+1;
	}

	for (int m = 0; m < M; m++)
	{
		cin >> temp;
		RightTable[temp] = m+1;
	}

	int K;
	vector<pair<int, int>> vcLine;
	cin >> K;

	int l, r;
	for (int k = 0 ; k < K ; k++)
	{
		cin >> l >> r;
		vcLine.push_back(make_pair(LeftTable[l], RightTable[r]));
	}

	sort(vcLine.begin(), vcLine.end());

	vector<int> res;

	for (int i = 0 ; i < K ; i++)
	{
		int lo = lower_bound(res.begin(), res.end(), vcLine[i].second) - res.begin();

		if (lo == res.size())
			res.push_back(vcLine[i].second);
		else
			res[lo] = vcLine[i].second;
	}

	cout << K - res.size();

	return 0;
}