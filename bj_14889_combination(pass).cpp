#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>

using namespace std;


int N;
vector<vector<int>> vcCapa;
vector<int> vcPerson;
vector<int> vcResult;

int Calc_sub(vector<int>& setTeam)
{
	int nVal = 0;
	for (int j = 0; j < N / 2.; j++)
	{
		for (int i = 0; i < N / 2.; i++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{
				nVal += vcCapa.at(setTeam.at(j)).at(setTeam.at(i));
			}
		}
	}

	return nVal;
}

void Calc(vector<int>& setPerson)
{
	vector<int> vcTeamStart(setPerson.begin(), setPerson.end());
	vector<int> vcTeamLink;
	for (int i = 0; i < N; i++)
	{
		bool bStart = false;
		for (int j = 0; j < N / 2.; j++)
		{
			if (vcPerson.at(i) == vcTeamStart.at(j))
			{
				bStart = true;
				break;
			}
		}

		if (!bStart)
		{
			vcTeamLink.push_back(vcPerson.at(i));
		}
	}

	int nCapaStart = Calc_sub(vcTeamStart);
	int nCapaLink = Calc_sub(vcTeamLink);

	vcResult.push_back(abs(nCapaStart - nCapaLink));
}

void Combination(vector<int>& setPerson, vector<int>& comb, int r, int index, int depth)
{
	if (r == 0)
	{
		/*for (auto it : comb)
		{
			cout << it.GetString() << " ";
		}
		cout << endl;*/

		Calc(comb);
	}
	else if (depth == setPerson.size())  // depth == n // 계속 안뽑다가 r 개를 채우지 못한 경우는 이 곳에 걸려야 한다.
	{
		return;
	}
	else
	{
		comb.at(index) = setPerson.at(depth);
		Combination(setPerson, comb, r - 1, index + 1, depth + 1);

		Combination(setPerson, comb, r, index, depth + 1);
	}
}


int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init
	{
		int idx, j, i;
		cin >> N;
		vcCapa.resize(N);
		for (j = 0; j < N; j++)
		{
			vcPerson.push_back(j);
			vcCapa.at(j).resize(N);
			for (i = 0; i < N; i++)
			{
				cin >> vcCapa.at(j).at(i);
			}
		}
	}

	vector<int> comb(N / 2.);
	Combination(vcPerson, comb, N / 2., 0, 0);

	int nMinVal = *min_element(vcResult.begin(), vcResult.end());

	cout << nMinVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}