#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>

using namespace std;

struct POINT
{
	int x;
	int y;

	POINT(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
	}

	string GetString()
	{
		char buffer[100];
		snprintf(buffer, 100, "(%d, %d) ", x, y);
		return string(buffer);
	}
};

int N, M;
vector<vector<int>> vcMap;
vector<POINT> vcHouse;
vector<POINT> vcShop;
vector<int> vcChickenDistance;

int Calc_Sub(POINT pt1, POINT pt2)
{
	return abs(pt1.x - pt2.x) + abs(pt1.y - pt2.y);
}

void Calc(vector<POINT>& _vcShop)
{
	int nSzShop = M;// vcShop.size();
	int nSzHouse = vcHouse.size();
	int nVal = 0;
	for (int idx = 0; idx < nSzHouse; idx++)
	{
		vector<int> vcChickenDistance_sub;
		for (int idx_sub = 0; idx_sub < nSzShop; idx_sub++)
		{
			vcChickenDistance_sub.push_back(Calc_Sub(vcHouse.at(idx), _vcShop.at(idx_sub)));
		}
		nVal += *min_element(vcChickenDistance_sub.begin(), vcChickenDistance_sub.end());
	}

	vcChickenDistance.push_back(nVal);
}

// i, j: 서로 교환할 인덱스
void swap(vector<POINT>& _vcShop, int i, int j)
{
	POINT iVal = _vcShop.at(i);
	_vcShop.at(i) = _vcShop.at(j);
	_vcShop.at(j) = iVal;
}

// k: 현재까지 선택된 원소 수
void perm(vector<POINT>& _vcShop, int k = 0)
{
	int nSize = _vcShop.size();
	if (k == M)
	{
		/*for (auto it : setOp)
		{
			cout << it << " ";
		}
		cout << endl;*/

		Calc(_vcShop);
		return;
	}
	else
	{
		for (int i = k; i < nSize; i++)
		{
			swap(_vcShop, k, i);
			perm(_vcShop, k + 1);
			swap(_vcShop, k, i);
		}
	}
}


int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init
	{
		cin >> N >> M;
		vcMap.resize(N);
		for (int j = 0; j < N; j++)
		{
			vcMap.at(j).resize(N);
			for (int i = 0; i < N; i++)
			{
				cin >> vcMap.at(j).at(i);

				if (vcMap.at(j).at(i) == 1)
				{
					vcHouse.push_back(POINT(i, j));
				}
				else if (vcMap.at(j).at(i) == 2)
				{
					vcShop.push_back(POINT(i, j));
				}
			}
		}

	}

	perm(vcShop);

	int nMinVal = *min_element(vcChickenDistance.begin(), vcChickenDistance.end());
	cout << nMinVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}