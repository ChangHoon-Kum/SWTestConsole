#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <array>
#include <map>
#include <queue>
#include <list>

using namespace std;

#define abs(n) (n>0?n:-n)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

#define ARR_LIMIT	20
#define COLOR_LIMIT	5

#define EMPTY_NUM -2
#define BLACK_NUM -1
#define RAINBOW_NUM 0

enum DIRECTION { TOP = 0, BOTTOM, LEFT, RIGHT, DIRMAX = 4 };

// 상, 하, 좌, 우
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1, 0,0 };

int N, M;  // N - 격자 크기, M - 색상의 갯수

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

	bool isValidPoint()
	{
		return x >= 0 && y >= 0 && x < N&& y < N;
	}

	bool operator==(const POINT& _r)
	{
		return this->x == _r.x && this->y == _r.y;
	}
};

int A[ARR_LIMIT][ARR_LIMIT] = { EMPTY_NUM, };
int buf[ARR_LIMIT][ARR_LIMIT] = { EMPTY_NUM, };

struct GROUP
{
	int nColor;
	POINT refPt;
	vector<POINT> vcBlock;

	int GetRainboeCnt()
	{
		int nCnt = 0;
		for (auto it : vcBlock)
		{
			if (A[it.y][it.x] == RAINBOW_NUM)
			{
				nCnt++;
			}
		}
		return nCnt;
	}
};


int nScore = 0;

void GetGroup(vector<GROUP>& _vcGroup)
{
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (A[j][i] <= RAINBOW_NUM || buf[j][i] < RAINBOW_NUM)
			{
				continue;
			}

			GROUP tmpGroup;
			tmpGroup.nColor = A[j][i];
			tmpGroup.vcBlock.push_back(POINT(i, j));

			queue<POINT> q;
			q.push(POINT(i, j));
			buf[j][i] = EMPTY_NUM;//checked
			while (q.size())
			{
				POINT pt = q.front();
				q.pop();

				for (int dir = 0; dir < DIRMAX; dir++)
				{
					POINT nxtPt(pt.x + dx[dir], pt.y + dy[dir]);

					if (nxtPt.isValidPoint())
					{
						if (A[nxtPt.y][nxtPt.x] == RAINBOW_NUM || A[nxtPt.y][nxtPt.x] == tmpGroup.nColor)
						{
							if (buf[nxtPt.y][nxtPt.x] >= RAINBOW_NUM) // unchecked
							{
								q.push(nxtPt);
								tmpGroup.vcBlock.push_back(nxtPt);

								buf[nxtPt.y][nxtPt.x] = EMPTY_NUM;//checked
							}
						}
					}
				}
			}

			POINT minPt(N, N);
			for (auto it : tmpGroup.vcBlock)
			{
				// keep rainbow block unchecked
				if (A[it.y][it.x] == RAINBOW_NUM)
				{
					buf[it.y][it.x] = RAINBOW_NUM;
				}
				else
				{
					if (it.y < minPt.y)
					{
						minPt = it;
					}
					else if (it.y == minPt.y)
					{
						if (it.x < minPt.x)
						{
							minPt = it;
						}
					}
				}
			}
			tmpGroup.refPt = minPt;
			if (tmpGroup.vcBlock.size() >= 2UL)
			{
				_vcGroup.push_back(tmpGroup);
			}

		}
	}
}

bool SortGroup(GROUP& _l, GROUP& _r)
{
	if (_l.vcBlock.size() == _r.vcBlock.size())
	{
		int nLeftRB = _l.GetRainboeCnt();
		int nRightRB = _r.GetRainboeCnt();
		if (nLeftRB == nRightRB)
		{
			if (_l.refPt.y == _r.refPt.y)
			{
				return _l.refPt.x > _r.refPt.x;
			}
			else
			{
				return _l.refPt.y > _r.refPt.y;
			}
		}
		else
		{
			return nLeftRB > nRightRB;
		}
	}
	else
	{
		return _l.vcBlock.size() > _r.vcBlock.size();
	}

	return _l.vcBlock.size() > _r.vcBlock.size();
}

void SelGroup(vector<GROUP>& _vcGroup, GROUP& _group)
{
	if (_vcGroup.size() == 1UL)
	{
		_group = _vcGroup.front();
	}
	else
	{
		sort(_vcGroup.begin(), _vcGroup.end(), SortGroup);
		_group = _vcGroup.front();
	}
}

void PangGroup(GROUP& _group)
{
	int nSize = _group.vcBlock.size();
	nScore += (nSize * nSize);
	for (auto it : _group.vcBlock)
	{
		A[it.y][it.x] = EMPTY_NUM;
	}
}

void Gravity()
{
	for (int col = 0; col < N; col++)
	{
		int nBtm = N - 1;
		for (int row = N - 1; row >= 0; row--)
		{
			if (A[row][col] == EMPTY_NUM)
			{
				continue;
			}
			else if (A[row][col] == BLACK_NUM)
			{
				nBtm = row - 1;
				continue;
			}
			else //stack
			{
				if (row < nBtm)
				{
					A[nBtm][col] = A[row][col];
					A[row][col] = EMPTY_NUM;
				}

				nBtm--;
				while (A[nBtm][col] >= BLACK_NUM)
				{
					nBtm--;
					if (nBtm < 0)
					{
						nBtm = 0;
						break;
					}
				}
				row = nBtm;
			}
		}
	}

	/*for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cout << A[j][i] << "	";
		}
		cout << endl;
	}
	cout << endl;*/
}

void RotateMap()
{
	int B[ARR_LIMIT][ARR_LIMIT] = { EMPTY_NUM, };

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			B[j][i] = A[j][i];
		}
	}

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			A[N - 1 - i][j] = B[j][i];
		}
	}

	/*for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cout << A[j][i] << "	";
		}
		cout << endl;
	}
	cout << endl;*/
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M;

	// 0. Init map
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> A[j][i];
			buf[j][i] = A[j][i];
		}
	}

	while (true)
	{
		// 0. buf clear
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				buf[j][i] = A[j][i];
			}
		}
		vector<GROUP> vcGroup;
		GetGroup(vcGroup);
		if (vcGroup.size() <= 0UL)
		{
			break;
		}
		GROUP selGroup;
		SelGroup(vcGroup, selGroup);
		PangGroup(selGroup);
		Gravity();
		RotateMap();
		Gravity();
	}


	cout << nScore << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}