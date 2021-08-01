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
int dx[4] = { -1,0,1, };
int dy[4] = { 0,1,0,-1 };

vector<vector<int>> vcRoom_Init;
vector<vector<int>> vcRoom_Buf;
vector<POINT> vcEmpty;
vector<POINT> vcVirus_Init;
vector<POINT> vcVirus;
vector<POINT> vcWallSel;
vector<int> vcCntEmpty;

bool isCorrectPos(int j, int i, int N, int M)
{
	return j >= 0 && i >= 0 && j < N&& i < M;
}

void Infection()
{
	const int _N = vcRoom_Buf.size();
	const int _M = vcRoom_Buf.at(0).size();

	vcVirus = vcVirus_Init;
	vector<POINT> vcVirus_pre;

	int idx, dir;
	do
	{
		vcVirus_pre = vcVirus;
		int szVirus = vcVirus_pre.size();
		for (idx = 0; idx < szVirus; idx++)
		{
			for (dir = 0; dir < 4; dir++)
			{
				POINT pt = vcVirus_pre.at(idx);
				pt.x += dx[dir];
				pt.y += dy[dir];

				if (isCorrectPos(pt.y, pt.x, _N, _M))
				{
					if (vcRoom_Buf.at(pt.y).at(pt.x) == 0)
					{
						vcRoom_Buf.at(pt.y).at(pt.x) = 2;
						vcVirus.push_back(pt);
					}
				}
			}
		}
	} while (vcVirus_pre.size() != vcVirus.size());
}

void CheckEmpty()
{
	vcRoom_Buf = vcRoom_Init;
	const int _N = vcRoom_Buf.size();
	const int _M = vcRoom_Buf.at(0).size();

	int szWallSel = vcWallSel.size();
	for (int idx = 0; idx < szWallSel; idx++)
	{
		POINT ptMakeWall = vcWallSel.at(idx);
		vcRoom_Buf.at(ptMakeWall.y).at(ptMakeWall.x) = 1;
	}

	Infection();

	int nCount = 0;
	for (int j = 0; j < _N; j++)
	{
		for (int i = 0; i < _M; i++)
		{
			if (vcRoom_Buf.at(j).at(i) == 0)
			{
				nCount++;
			}
		}
	}
	vcCntEmpty.push_back(nCount);
}

void Sel3Walls(vector<POINT>& _vcEmpty)
{
	const int szEmpty = _vcEmpty.size();
	for (int i = 0; i < szEmpty - 2; i++)
	{
		for (int j = i + 1; j < szEmpty - 1; j++)
		{
			for (int k = j + 1; k < szEmpty; k++)
			{
				vcWallSel.clear();
				vcWallSel.push_back(vcEmpty.at(i));
				vcWallSel.push_back(vcEmpty.at(j));
				vcWallSel.push_back(vcEmpty.at(k));

				CheckEmpty();
			}
		}
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init Map
	int idx = 0, idx_sub = 0;
	int j = 0, i = 0;
	int N = 0, M = 0;
	cin >> N >> M;
	vcRoom_Init.resize(N); // 세로
	for (idx = 0; idx < N; idx++)
	{
		vcRoom_Init.at(idx).resize(M); // 가로
	}

	for (j = 0; j < N; j++)
	{
		for (i = 0; i < M; i++)
		{
			cin >> vcRoom_Init.at(j).at(i);
			if (vcRoom_Init.at(j).at(i) == 0)
			{
				vcEmpty.push_back(POINT(i, j));
			}
			else if (vcRoom_Init.at(j).at(i) == 2)
			{
				vcVirus_Init.push_back(POINT(i, j));
			}
		}
	}

	Sel3Walls(vcEmpty);

	int nMaxEmpty = *max_element(vcCntEmpty.begin(), vcCntEmpty.end());

	cout << nMaxEmpty << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}