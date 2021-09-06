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

int N, M;

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
};

enum DIRECTION { RIGHT = 0, LEFT, TOP, BTM, DIR_MAX };

//			RIGHT = 0, LEFT, TOP, BTM
int dx[DIR_MAX] = { 1, -1,  0, 0 };
int dy[DIR_MAX] = { 0,  0, -1, 1 };

long space[8][8] = { 0, };

void CloneArray(long _pSrc[][8], long _pDst[][8])
{
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			_pDst[j][i] = _pSrc[j][i];
		}
	}
}

struct CCTV_BASE
{
	POINT pos;
	DIRECTION dir;
	int dir_idx;
	int dir_max;

	CCTV_BASE()
	{
		pos = POINT(-1, -1);
		dir = RIGHT;

		dir_idx = 0;
		dir_max = DIR_MAX;
	}

	void OneDirScan(DIRECTION dir, long _array[8][8])
	{
		int nlength = max(N, M);

		for (int idx = 1; idx < nlength; idx++)
		{
			POINT nextPos(pos.x + dx[dir] * idx, pos.y + dy[dir] * idx);
			if (!nextPos.isValidPoint() || _array[nextPos.y][nextPos.x] >= 6)
			{
				break;
			}
			else
			{
				_array[nextPos.y][nextPos.x] = -1; // #
			}
		}
	}

	bool isAllScaned()
	{
		if (dir_idx >= dir_max)
		{
			return true;
		}
		else
		{
			return false;
		}
		return false;
	}

	void ResetDir()
	{
		if (dir_idx >= dir_max)
		{
			dir_idx = 0;
			dir = (DIRECTION)dir_idx;
		}
	}

	virtual void OneTimeScan(long _array[8][8]) = 0;
};

struct CCTV_V1 : CCTV_BASE
{
	CCTV_V1(const POINT _pos)
	{
		pos = _pos;
		dir_max = 4;

		dir_idx = 0;
		dir = (DIRECTION)dir_idx;
	}

	virtual void OneTimeScan(long _array[8][8])
	{
		ResetDir();
		OneDirScan(dir, _array);
		dir_idx++;
		dir = (DIRECTION)dir_idx;
	}
};

struct CCTV_V2 : CCTV_BASE
{
	CCTV_V2(const POINT _pos)
	{
		pos = _pos;
		dir_max = 4;

		dir_idx = 0;
		dir = (DIRECTION)dir_idx;
	}

	virtual void OneTimeScan(long _array[8][8])
	{
		ResetDir();

		OneDirScan(dir, _array);
		OneDirScan((DIRECTION)(dir + 1), _array);

		dir_idx += 2;
		dir = (DIRECTION)dir_idx;
	}
};


struct CCTV_V3 : CCTV_BASE
{
	CCTV_V3(const POINT _pos)
	{
		pos = _pos;
		dir_max = 4;

		dir_idx = 0;
		dir = (DIRECTION)dir_idx;
	}

	virtual void OneTimeScan(long _array[8][8])
	{
		ResetDir();

		if (dir == TOP)
		{
			OneDirScan(TOP, _array);
			OneDirScan(RIGHT, _array);
		}
		else if (dir == RIGHT)
		{
			OneDirScan(RIGHT, _array);
			OneDirScan(BTM, _array);
		}
		else if (dir == BTM)
		{
			OneDirScan(BTM, _array);
			OneDirScan(LEFT, _array);
		}
		else if (dir == LEFT)
		{
			OneDirScan(LEFT, _array);
			OneDirScan(TOP, _array);
		}

		dir_idx++;
		dir = (DIRECTION)dir_idx;
	}
};

struct CCTV_V4 : CCTV_BASE
{
	CCTV_V4(const POINT _pos)
	{
		pos = _pos;
		dir_max = 4;
	}

	virtual void OneTimeScan(long _array[8][8])
	{
		ResetDir();

		if (dir == TOP)
		{
			OneDirScan(TOP, _array);
			OneDirScan(RIGHT, _array);
			OneDirScan(BTM, _array);
		}
		else if (dir == RIGHT)
		{
			OneDirScan(RIGHT, _array);
			OneDirScan(BTM, _array);
			OneDirScan(LEFT, _array);
		}
		else if (dir == BTM)
		{
			OneDirScan(BTM, _array);
			OneDirScan(LEFT, _array);
			OneDirScan(TOP, _array);
		}
		else if (dir == LEFT)
		{
			OneDirScan(LEFT, _array);
			OneDirScan(TOP, _array);
			OneDirScan(RIGHT, _array);
		}

		dir_idx++;
		dir = (DIRECTION)dir_idx;
	}
};

struct CCTV_V5 : CCTV_BASE
{
	CCTV_V5(const POINT _pos)
	{
		pos = _pos;
		dir_max = 1;
	}

	virtual void OneTimeScan(long _array[8][8])
	{
		OneDirScan(TOP, _array);
		OneDirScan(RIGHT, _array);
		OneDirScan(BTM, _array);
		OneDirScan(LEFT, _array);
		dir_idx++;
		dir = (DIRECTION)dir_idx;
	}
};

vector<CCTV_BASE*> vcCCTV;
int minBlindSpot = 64;

void UpdateMinBlindSpot(long _buf[8][8])
{
	int nCount = 0;
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			if (_buf[j][i] == 0)
			{
				nCount++;
			}
		}
	}

	minBlindSpot = min(minBlindSpot, nCount);
}

void Calc(long _buf[8][8], int depth = 0)
{
	if (depth >= vcCCTV.size())
	{
		UpdateMinBlindSpot(_buf);
		return;
	}
	else
	{
		long buf[8][8];
		CloneArray(_buf, buf);
		vcCCTV.at(depth)->OneTimeScan(buf);
		Calc(buf, depth + 1);

		if (!vcCCTV.at(depth)->isAllScaned())
		{
			Calc(_buf, depth);
		}
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			cin >> space[j][i];

			if (space[j][i] > 0 && space[j][i] < 6)
			{
				if (space[j][i] == 1)
				{
					vcCCTV.push_back(new CCTV_V1(POINT(i, j)));
				}
				else if (space[j][i] == 2)
				{
					vcCCTV.push_back(new CCTV_V2(POINT(i, j)));
				}
				else if (space[j][i] == 3)
				{
					vcCCTV.push_back(new CCTV_V3(POINT(i, j)));
				}
				else if (space[j][i] == 4)
				{
					vcCCTV.push_back(new CCTV_V4(POINT(i, j)));
				}
				else if (space[j][i] == 5)
				{
					vcCCTV.push_back(new CCTV_V5(POINT(i, j)));
				}
			}
		}
	}

	Calc(space);

	cout << minBlindSpot << endl;

	for (auto it : vcCCTV)
	{
		delete it;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}