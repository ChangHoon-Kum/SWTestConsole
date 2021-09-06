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

	POINT()
	{
		x = y = -1;
	}

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

void Combination(vector<POINT>& _vcShop, vector<POINT>& comb, int r, int index, int depth)
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
	else if (depth == _vcShop.size())  // depth == n // 계속 안뽑다가 r 개를 채우지 못한 경우는 이 곳에 걸려야 한다.
	{
		return;
	}
	else
	{
		comb.at(index) = _vcShop.at(depth);
		Combination(_vcShop, comb, r - 1, index + 1, depth + 1);

		Combination(_vcShop, comb, r, index, depth + 1);
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

	vector<POINT> comb(M);
	Combination(vcShop, comb, M, 0, 0);

	int nMinVal = *min_element(vcChickenDistance.begin(), vcChickenDistance.end());
	cout << nMinVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}