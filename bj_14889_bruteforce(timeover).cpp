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
	vector<int> vcTeamStart(setPerson.begin(), setPerson.begin() + N / 2.);
	vector<int> vcTeamLink(setPerson.begin() + N / 2., setPerson.end());

	int nCapaStart = Calc_sub(vcTeamStart);
	int nCapaLink = Calc_sub(vcTeamLink);

	vcResult.push_back(abs(nCapaStart - nCapaLink));
}

// i, j: 서로 교환할 인덱스
void swap(vector<int>& setPerson, int i, int j)
{
	int iVal = setPerson.at(i);
	setPerson.at(i) = setPerson.at(j);
	setPerson.at(j) = iVal;
}

// k: 현재까지 선택된 원소 수
void perm(vector<int>& setPerson, int k = 0)
{
	int nSize = N;
	if (k == N / 2.)
	{
		for (auto it : setPerson)
		{
			cout << it << " ";
		}
		cout << endl;

		Calc(setPerson);
		cout << vcResult.at(vcResult.size() - 1) << endl;
		cout << endl;
		return;
	}
	else
	{
		for (int i = k; i < N; i++)
		{
			swap(setPerson, k, i);
			perm(setPerson, k + 1);
			swap(setPerson, k, i);
		}
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

	perm(vcPerson);

	int nMinVal = *min_element(vcResult.begin(), vcResult.end());

	cout << nMinVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}