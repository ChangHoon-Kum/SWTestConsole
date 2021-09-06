#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <array>
#include <map>

using namespace std;

struct CHART
{
	int duration;
	int cost;

	CHART()
	{
		duration = cost = 0;
	}
};

#define abs(n) (n>0?n:-n)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
int N;
vector<CHART> vcDays;
int maxCost = 0;

void Calc(vector<CHART>& comb)
{
	int sum_cost = 0;
	for (auto it : comb)
	{
		sum_cost += it.cost;
	}

	maxCost = max(maxCost, sum_cost);
}

void Combination(vector<CHART>& comb, int depth)
{
	if (depth >= N)
	{
		Calc(comb);
	}
	else
	{
		int nSize = comb.size();
		comb.push_back(vcDays.at(depth));
		if (depth + (vcDays.at(depth).duration) > N)
		{
			comb.pop_back();
			Calc(comb);
		}
		else if (depth + (vcDays.at(depth).duration) == N)
		{
			Calc(comb);
		}
		else
		{
			Combination(comb, depth + (vcDays.at(depth).duration));
		}

		if (nSize >= 0)
		{
			comb.erase(comb.begin() + nSize, comb.end());
		}
		/*else
		{
			comb.clear();
		}*/
		Combination(comb, depth + 1);
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N;
	vcDays.resize(N);

	for (int idx = 0; idx < N; idx++)
	{
		cin >> vcDays.at(idx).duration >> vcDays.at(idx).cost;
	}

	vector<CHART> comb;
	Combination(comb, 0);

	cout << maxCost << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}