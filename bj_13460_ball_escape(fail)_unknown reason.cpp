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

#define ARR_LIMIT	10


enum DIRECTION { LEFT = 0, BOTTOM, RIGHT, TOP, DIRMAX = 4 };

// 좌, 하, 우, 상
int dx[4] = { -1,0,1, 0 };
int dy[4] = { 0,1,0,-1 };

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
		return x >= 0 && y >= 0 && x < M&& y < N;
	}

	bool operator==(const POINT& _r)
	{
		return this->x == _r.x && this->y == _r.y;
	}

	bool operator!=(const POINT& _r)
	{
		return this->x != _r.x && this->y != _r.y;
	}
};

char A[ARR_LIMIT][ARR_LIMIT] = { ' ', };

struct BALL
{
	POINT pos;
	bool bExit;

	BALL()
	{
		bExit = false;
	}

	void Move(const DIRECTION& dir)
	{
		POINT nxtPos(pos.x + dx[dir], pos.y + dy[dir]);
		while (nxtPos.isValidPoint()
			&& A[nxtPos.y][nxtPos.x] != '#')
		{
			pos = nxtPos;
			if (A[nxtPos.y][nxtPos.x] == 'O')
			{
				bExit = true;
				break;
			}

			nxtPos.x += dx[dir];
			nxtPos.y += dy[dir];
		}
	}
};

#define TURN_END 10
int nTurn = TURN_END;
BALL m_Red, m_Blue;

void run(int _depth, DIRECTION _dir, BALL _r, BALL _b)
{
	if (_depth >= TURN_END)
	{
		return;
	}
	else
	{
		POINT ptRPrev = _r.pos;
		POINT ptBPrev = _b.pos;
		_r.Move(_dir);
		_b.Move(_dir);

		if (_r.pos == ptRPrev && _b.pos == ptBPrev)
		{
			return;
		}

		if (_r.pos == _b.pos)
		{
			DIRECTION sub_dir;
			switch (_dir)
			{
			case LEFT:
				sub_dir = RIGHT;
				break;
			case BOTTOM:
				sub_dir = TOP;
				break;
			case RIGHT:
				sub_dir = LEFT;
				break;
			case TOP:
			default:
				sub_dir = BOTTOM;
				break;
			}
			int distR = abs((_r.pos.x - ptRPrev.x)) + abs((_r.pos.y - ptRPrev.y));
			int distB = abs((_b.pos.x - ptBPrev.x)) + abs((_b.pos.y - ptBPrev.y));

			if (distB > distR)
			{
				_b.pos.x += dx[sub_dir];
				_b.pos.y += dy[sub_dir];
			}
			else
			{
				_r.pos.x += dx[sub_dir];
				_r.pos.y += dy[sub_dir];
			}
		}

		if (_r.bExit && !_b.bExit)
		{
			nTurn = min(_depth + 1, nTurn);
			return;
		}
		else if (_b.bExit)
		{
			return;
		}
		else
		{
			vector<DIRECTION> vcNxtDir;
			switch (_dir)
			{
			case LEFT:
				vcNxtDir.push_back(TOP);
				vcNxtDir.push_back(BOTTOM);
				if (_depth == 0)
				{
					vcNxtDir.push_back(RIGHT);
				}
				break;
			case BOTTOM:
				vcNxtDir.push_back(LEFT);
				vcNxtDir.push_back(RIGHT);
				if (_depth == 0)
				{
					vcNxtDir.push_back(TOP);
				}
				break;
			case RIGHT:
				vcNxtDir.push_back(TOP);
				vcNxtDir.push_back(BOTTOM);
				if (_depth == 0)
				{
					vcNxtDir.push_back(LEFT);
				}
				break;
			case TOP:
			default:
				vcNxtDir.push_back(LEFT);
				vcNxtDir.push_back(RIGHT);
				if (_depth == 0)
				{
					vcNxtDir.push_back(BOTTOM);
				}
				break;
			}

			for (auto it : vcNxtDir)
			{
				run(_depth + 1, it, _r, _b);
			}
		}
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M;

	char chTmp;
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			cin >> chTmp;

			if (chTmp == 'R')
			{
				m_Red.pos.x = i;
				m_Red.pos.y = j;
				A[j][i] = '.';
			}
			else if (chTmp == 'B')
			{
				m_Blue.pos.x = i;
				m_Blue.pos.y = j;
				A[j][i] = '.';
			}
			else
			{
				A[j][i] = chTmp;
			}
		}
	}

	for (int dir = 0; dir < DIRMAX; dir++)
	{
		run(0, (DIRECTION)dir, m_Red, m_Blue);
	}

	if (nTurn > TURN_END)
		nTurn = -1;

	cout << nTurn << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}