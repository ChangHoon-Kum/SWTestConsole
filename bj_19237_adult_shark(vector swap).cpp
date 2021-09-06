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
#define TIME_LIMIT	1000


enum DIRECTION { TOP = 0, BOTTOM, LEFT, RIGHT, DIRMAX = 4 };

// 상, 하, 좌, 우
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1, 0,0 };

int N, M, k; // k- 냄새 내구도, M-상어의 갯수

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

struct SHARK
{
	int sharknum;
	POINT pos;
	DIRECTION curDir;
	bool bAlive;

	DIRECTION priority[DIRMAX][DIRMAX];

	SHARK()
	{
		sharknum = 0;
		curDir = DIRMAX;
		bAlive = true;
	}

	SHARK(int _num, POINT _pos)
	{
		this->sharknum = _num;
		this->pos = _pos;
		curDir = DIRMAX;
		bAlive = true;
	}

	SHARK(int _num, DIRECTION _dir)
	{
		this->sharknum = _num;
		curDir = _dir;
		bAlive = true;
	}
};

bool SharkSort(const SHARK& _l, const SHARK& _r)
{
	return _l.sharknum < _r.sharknum;
}

struct SMELL
{
	int sharknum;
	int nDuration;

	SMELL()
	{
		this->sharknum = -1;
		this->nDuration = 0;
	}

	void SmellDecrease()
	{
		this->nDuration--;
		if (this->nDuration <= 0)
		{
			this->sharknum = -1;
		}
	}
};

struct ROOM
{
	SMELL smell;
	vector<SHARK> vcShark;

	void push_back(const SHARK& _shark)
	{
		/*if (smell.sharknum < 0)
		{
			smell.sharknum = _shark.sharknum;
			smell.nDuration = k;
		}
		else //if ()
		{
			smell.sharknum = __min(smell.sharknum, _shark.sharknum);
		}*/

		vcShark.push_back(_shark);
	}

	SHARK GetStrongShark()
	{
		SHARK strongShark = *std::min_element(vcShark.begin(), vcShark.end(), SharkSort);
		smell.sharknum = strongShark.sharknum;
		smell.nDuration = k;
		vcShark.clear();
		vcShark.push_back(strongShark);
		return strongShark;
	}
};

vector<SHARK> vcShark;
ROOM mapShark[ARR_LIMIT][ARR_LIMIT];



void SharkMove(const POINT& _src, const POINT& _dst, SHARK& _shark, DIRECTION _dir)
{
	mapShark[_src.y][_src.x].vcShark.clear();
	_shark.curDir = _dir;
	_shark.pos = _dst;
	mapShark[_dst.y][_dst.x].push_back(_shark);
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M >> k;

	// 0. Room Info
	{
		int num;
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				cin >> num;
				if (num > 0)
				{
					vcShark.push_back(SHARK(num, POINT(i, j)));
				}
			}
		}
	}

	std::sort(vcShark.begin(), vcShark.end(), SharkSort);
	// 0. Shark Info, update Shark map
	{
		int dirTmp;
		for (int idx = 0; idx < M; idx++)
		{
			cin >> dirTmp;
			vcShark.at(idx).curDir = (DIRECTION)(dirTmp - 1);
		}

		for (int idx = 0; idx < M; idx++)
		{
			for (int dir = 0; dir < DIRMAX; dir++)
			{
				for (int dir_sub = 0; dir_sub < DIRMAX; dir_sub++)
				{
					cin >> dirTmp;
					vcShark.at(idx).priority[dir][dir_sub] = (DIRECTION)(dirTmp - 1);
				}
			}

			const POINT& pos = vcShark.at(idx).pos;
			mapShark[pos.y][pos.x].push_back(vcShark.at(idx));
			mapShark[pos.y][pos.x].smell.sharknum = vcShark.at(idx).sharknum;
			mapShark[pos.y][pos.x].smell.nDuration = k;
		}
	}

	int nTime = 0;
	for (nTime = 0; nTime < TIME_LIMIT; nTime++)
	{
		// 1. SharkMove
		for (auto& it : vcShark)
		{
			bool bMoved = false;
			for (int dir = 0; dir < DIRMAX; dir++)
			{
				DIRECTION nxtDir = it.priority[it.curDir][dir];
				POINT nxtPos(it.pos.x + dx[nxtDir], it.pos.y + dy[nxtDir]);

				if (nxtPos.isValidPoint() && mapShark[nxtPos.y][nxtPos.x].smell.sharknum <= 0)
				{
					SharkMove(it.pos, nxtPos, it, (DIRECTION)nxtDir);
					bMoved = true;
					break;
				}
			}

			if (!bMoved)
			{
				for (int dir = 0; dir < DIRMAX; dir++)
				{
					DIRECTION nxtDir = it.priority[it.curDir][dir];
					POINT nxtPos(it.pos.x + dx[nxtDir], it.pos.y + dy[nxtDir]);

					if (nxtPos.isValidPoint() && mapShark[nxtPos.y][nxtPos.x].smell.sharknum == it.sharknum)
					{
						SharkMove(it.pos, nxtPos, it, (DIRECTION)nxtDir);
						bMoved = true;
						break;
					}
				}
			}
		}

		// 2. Shark Out // 3. smell decrease
		vector<SHARK> tmpVcShark;
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				if (mapShark[j][i].vcShark.size() < 1UL)
				{
					mapShark[j][i].smell.SmellDecrease();
				}
				else if (mapShark[j][i].vcShark.size() == 1UL)
				{
					const SHARK& shark = mapShark[j][i].vcShark.front();
					mapShark[j][i].smell.sharknum = shark.sharknum;
					mapShark[j][i].smell.nDuration = k;
					tmpVcShark.push_back(shark);
				}
				else
				{
					tmpVcShark.push_back(mapShark[j][i].GetStrongShark());
				}
			}
		}


		vcShark = tmpVcShark;

		//for debug
		/*cout << nTime << endl;
		cout << ("smell num") << endl;
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				cout << mapShark[j][i].smell.sharknum << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << ("smell duration") << endl;
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				cout << mapShark[j][i].smell.nDuration << " ";
			}
			cout << endl;
		}*/


		if (vcShark.size() <= 1UL)
		{
			cout << nTime + 1 << endl;
			exit(0);
		}
	}


	cout << -1 << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}