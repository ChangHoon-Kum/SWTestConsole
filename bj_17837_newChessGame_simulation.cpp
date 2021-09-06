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

int N, K;

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
};

enum DIRECTION { RIGHT = 0, LEFT, TOP, BTM, DIR_MAX };

//			RIGHT = 0, LEFT, TOP, BTM
int dx[DIR_MAX] = { 1, -1,  0, 0 };
int dy[DIR_MAX] = { 0,  0, -1, 1 };

DIRECTION reverseDirection(const DIRECTION _dir)
{
	if (_dir == LEFT)
	{
		return RIGHT;
	}
	else if (_dir == RIGHT)
	{
		return LEFT;
	}
	else if (_dir == TOP)
	{
		return BTM;
	}
	else //if (_dir == BTM)
	{
		return TOP;
	}
}

struct HORSE
{
	POINT pos;
	DIRECTION dir;

	HORSE()
	{
		pos = POINT(-1, -1);
		dir = LEFT;
	}

	HORSE(POINT _pos, DIRECTION _dir)
	{
		pos = _pos;
		dir = _dir;
	}

	POINT GetNextPos()
	{
		return POINT(pos.x + dx[dir], pos.y + dy[dir]);
	}
};

struct SPACE
{
	long type;
	vector<long> vcIdxHorse;

	SPACE()
	{
		type = 0;
	}

	SPACE(long _type)
	{
		type = _type;
	}
};

map<long, HORSE> mapHorse;
SPACE chessboard[12][12];
int maxStack = 0;

void pickupHorse(const long _horsenum, const HORSE _horse, vector<long>& _pickedupIdx)
{
	SPACE* pSpace = &chessboard[_horse.pos.y][_horse.pos.x];

	for (int idx = 0; idx < pSpace->vcIdxHorse.size(); idx++)
	{
		if (pSpace->vcIdxHorse.at(idx) == _horsenum)
		{
			_pickedupIdx.insert(_pickedupIdx.begin(), pSpace->vcIdxHorse.begin() + idx, pSpace->vcIdxHorse.end());
			pSpace->vcIdxHorse.erase(pSpace->vcIdxHorse.begin() + idx, pSpace->vcIdxHorse.end());

			return;
		}
	}
}

void placeHorse_Sub(const vector<long>& _pickedupIdx)
{
	HORSE* pHorse = &mapHorse[_pickedupIdx.at(0)];

	POINT nextPt = pHorse->GetNextPos();

	if (chessboard[nextPt.y][nextPt.x].type == 1)
	{
		vector<long> vcHand;
		for (int idx = 0; idx < _pickedupIdx.size(); idx++)
		{
			vcHand.insert(vcHand.begin(), _pickedupIdx[idx]);
		}

		for (int idx = 0; idx < vcHand.size(); idx++)
		{
			mapHorse[vcHand[idx]].pos = nextPt;
			chessboard[nextPt.y][nextPt.x].vcIdxHorse.push_back(vcHand[idx]);
		}
	}
	else //chessboard[nextPt.y][nextPt.x].type == 0
	{
		for (int idx = 0; idx < _pickedupIdx.size(); idx++)
		{
			mapHorse[_pickedupIdx[idx]].pos = nextPt;
			chessboard[nextPt.y][nextPt.x].vcIdxHorse.push_back(_pickedupIdx[idx]);
		}
	}

	maxStack = max(maxStack, chessboard[nextPt.y][nextPt.x].vcIdxHorse.size());
}

void placeHorse(const vector<long>& _pickedupIdx)
{
	HORSE* pHorse = &mapHorse[_pickedupIdx.at(0)];

	POINT nextPt = pHorse->GetNextPos();

	if (!nextPt.isValidPoint() || chessboard[nextPt.y][nextPt.x].type == 2)
	{
		pHorse->dir = reverseDirection(pHorse->dir);
		POINT nextPtNew = pHorse->GetNextPos();
		if (!nextPtNew.isValidPoint() || chessboard[nextPtNew.y][nextPtNew.x].type == 2)
		{
			for (int idx = 0; idx < _pickedupIdx.size(); idx++)
			{
				chessboard[pHorse->pos.y][pHorse->pos.x].vcIdxHorse.push_back(_pickedupIdx[idx]);
			}

			return;
		}
		else
		{
			placeHorse_Sub(_pickedupIdx);
		}
	}
	else
	{
		placeHorse_Sub(_pickedupIdx);
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> K;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			long type;
			cin >> type;
			chessboard[j][i] = type;
		}
	}

	for (int idx = 0; idx < K; idx++)
	{
		int row, col, dir;
		cin >> row >> col >> dir;
		row--;
		col--;
		dir--;

		mapHorse[idx] = HORSE(POINT(col, row), (DIRECTION)dir);
		chessboard[row][col].vcIdxHorse.push_back(idx);
	}

	int nTurn = 0;

	while (nTurn < 1000 && maxStack < 4)
	{
		for (auto it : mapHorse)
		{
			vector<long> pickedUp;
			pickupHorse(it.first, it.second, pickedUp);
			placeHorse(pickedUp);

			if (maxStack >= 4)
			{
				break;
			}
		}

		nTurn++;
	}

	if (nTurn >= 1000)
		cout << -1 << endl;
	else
		cout << nTurn << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}