#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

struct POINT
{
	int x;
	int y;

	POINT()
	{
		this->x = this->y = 0;
	}

	POINT(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
	}

	bool operator== (POINT& rval)
	{
		return this->x == rval.x && this->y == rval.y;
	}

	bool operator!= (POINT& rval)
	{
		return !(this->x == rval.x && this->y == rval.y);
	}

	string GetString()
	{
		char buffer[100];
		snprintf(buffer, 100, "(%d, %d) ", x, y);
		return string(buffer);
	}
};

// 좌, 하, 우, 상
int dust_dx[4] = { -1,0,1, 0 };
int dust_dy[4] = { 0,1,0,-1 };

int top_dx[4] = { 1, 0, -1, 0 };
int top_dy[4] = { 0, -1, 0, 1 };

int btm_dx[4] = { 1, 0, -1, 0 };
int btm_dy[4] = { 0, 1, 0, -1 };

vector<vector<int>> vcMap_Init;
vector<vector<int>> vcMap;

bool isCorrectPos(int j, int i, int N, int M)
{
	return j >= 0 && i >= 0 && j < N&& i < M;
}

bool isCorrectPos(POINT& _pt, int Row, int Col)
{
	return isCorrectPos(_pt.y, _pt.x, Row, Col);
}

/*void ShowVcMap()
{
	int nVal = 0;
	for (int j = 0 ; j < vcMap.size() ; j++)
	{
		for (int i = 0 ; i < vcMap.at(j).size() ; i++)
		{
			cout << vcMap.at(j).at(i) << "	";
			nVal += vcMap.at(j).at(i);
		}
		cout << endl;
	}
	nVal += 2;

	cout << nVal << endl;
	cout << endl;
}*/

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init Map
	int idx = 0, idx_sub = 0;
	int j, i, d1, d2, j_sub, i_sub;
	int R = 0, C = 0, T = 0;
	POINT ptTOP(-1, -1);
	POINT ptBTM(-1, -1);
	POINT ptTmp;

	cin >> R >> C >> T;
	vcMap_Init.resize(R);
	for (idx = 0; idx < R; idx++)
	{
		vcMap_Init.at(idx).resize(C);
	}
	for (j = 0; j < R; j++)
	{
		for (i = 0; i < C; i++)
		{
			cin >> vcMap_Init.at(j).at(i);
			if (vcMap_Init.at(j).at(i) == -1 && ptTOP.x == -1)
			{
				ptTOP.x = i;
				ptTOP.y = j;
				ptBTM = ptTOP;
				ptBTM.y++;
			}
		}
	}
	vcMap = vcMap_Init;
	//ShowVcMap();

	// for time < T
	int dir;
	for (int t = 0; t < T; t++)
	{
		// 1. Spread Dust
		{
			int nDustTmp;
			for (j = 0; j < R; j++)
			{
				for (i = 0; i < C; i++)
				{
					if (vcMap_Init.at(j).at(i) > 0)
					{
						nDustTmp = vcMap_Init.at(j).at(i) / 5.;
						for (dir = 0; dir < 4; dir++)
						{
							ptTmp.x = i + dust_dx[dir];
							ptTmp.y = j + dust_dy[dir];

							if (isCorrectPos(ptTmp, R, C))
							{
								if (vcMap.at(ptTmp.y).at(ptTmp.x) >= 0)
								{
									vcMap.at(ptTmp.y).at(ptTmp.x) += nDustTmp;
									vcMap.at(j).at(i) -= nDustTmp;
								}
							}
							//ShowVcMap();
						}
					}
				}
			}
		}

		// 2. Circulation, reverse indexing
		// Top part Right, Top, Left, Bottom -> Bottom, Left, Top, Right
		//  - Bottom
		for (j = ptTOP.y; j > 0; j--)
		{
			if (j == ptTOP.y)
			{
				vcMap.at(j - 1).at(ptTOP.x) = 0;
			}
			else
			{
				vcMap.at(j).at(ptTOP.x) += vcMap.at(j - 1).at(ptTOP.x);
				vcMap.at(j - 1).at(ptTOP.x) = 0;
			}
		}
		//ShowVcMap();

		//  - Left
		for (i = 0; i < C - 1; i++)
		{
			vcMap.at(0).at(i) += vcMap.at(0).at(i + 1);
			vcMap.at(0).at(i + 1) = 0;
		}
		//ShowVcMap();

		//  - Top
		for (j = 0; j < ptTOP.y; j++)
		{
			vcMap.at(j).at(C - 1) += vcMap.at(j + 1).at(C - 1);
			vcMap.at(j + 1).at(C - 1) = 0;
		}
		//ShowVcMap();

		//  - Right
		for (i = C - 1; i > 0; i--)
		{
			if (vcMap.at(ptTOP.y).at(i - 1) > 0)
			{
				vcMap.at(ptTOP.y).at(i) += vcMap.at(ptTOP.y).at(i - 1);
				vcMap.at(ptTOP.y).at(i - 1) = 0;
			}
		}
		//ShowVcMap();

		// Btm part Right, Bottom, Left, Top -> Top, Left, Bottom, Right
		//  - Top
		for (j = ptBTM.y; j < R - 1; j++)
		{
			if (j == ptBTM.y)
			{
				vcMap.at(j + 1).at(ptBTM.x) = 0;
			}
			else
			{
				vcMap.at(j).at(0) += vcMap.at(j + 1).at(0);
				vcMap.at(j + 1).at(0) = 0;
			}
		}
		//ShowVcMap();

		//  - Left
		for (i = 0; i < C - 1; i++)
		{
			vcMap.at(R - 1).at(i) += vcMap.at(R - 1).at(i + 1);
			vcMap.at(R - 1).at(i + 1) = 0;
		}
		//ShowVcMap();

		//  - Bottom
		for (j = R - 1; j > ptBTM.y; j--)
		{
			vcMap.at(j).at(C - 1) += vcMap.at(j - 1).at(C - 1);
			vcMap.at(j - 1).at(C - 1) = 0;
		}
		//ShowVcMap();

		//  - Right
		for (i = C - 1; i > 0; i--)
		{
			if (vcMap.at(ptBTM.y).at(i - 1) > 0)
			{
				vcMap.at(ptBTM.y).at(i) += vcMap.at(ptBTM.y).at(i - 1);
				vcMap.at(ptBTM.y).at(i - 1) = 0;
			}
		}
		//ShowVcMap();

		vcMap_Init = vcMap;
	}

	// 3. Calc Sum of Dust
	int nVal = 0;
	for (j = 0; j < R; j++)
	{
		for (i = 0; i < C; i++)
		{
			if (vcMap.at(j).at(i) > 0)
			{
				nVal += vcMap.at(j).at(i);
			}
		}
	}
	cout << nVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}