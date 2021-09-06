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

#define MAXDIST 401

int N, M;
int A[20][20] = { 0, };


void cloneInitArray(int _src[][20], int _dst[][20])
{
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (_src[j][i] == 0)
			{
				_dst[j][i] = MAXDIST;
			}
			else
			{
				_dst[j][i] = _src[j][i];
			}
		}
	}
}

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

enum DIRECTION { RIGHT = 0, LEFT, TOP, BTM, DIR_MAX };

//			RIGHT = 0, LEFT, TOP, BTM
int dx[DIR_MAX] = { 1, -1,  0, 0 };
int dy[DIR_MAX] = { 0,  0, -1, 1 };

struct PASSENSER
{
	POINT ptStart;
	POINT ptEnd;
};

struct TAXI
{
	POINT pos;
	int cur_fuel;
};

TAXI taxi;
vector<PASSENSER> vcPassenser;

void CalcDistMap(const POINT& ptSt, int _buf[][20], POINT* pPt = nullptr)
{
	cloneInitArray(A, _buf);


	queue<POINT> q;
	q.push(ptSt);
	_buf[ptSt.y][ptSt.x] = 0;

	while (q.size())
	{
		POINT ptRef = q.front();
		q.pop();

		if (pPt != nullptr && ptRef == *pPt)
		{
			break;
		}

		for (int dir = 0; dir < DIR_MAX; dir++)
		{
			POINT ptNxt(ptRef.x + dx[dir], ptRef.y + dy[dir]);

			if (!ptNxt.isValidPoint() || A[ptNxt.y][ptNxt.x] == -1)
			{
				continue;
			}

			if (_buf[ptNxt.y][ptNxt.x] > _buf[ptRef.y][ptRef.x] + 1)
			{
				_buf[ptNxt.y][ptNxt.x] = _buf[ptRef.y][ptRef.x] + 1;
				q.push(ptNxt);
			}
		}
	}
}

int CalcPt2Pt(const POINT& ptSt, const POINT& ptEd)
{
	int buf[20][20] = { 0, };
	cloneInitArray(A, buf);


	queue<POINT> q;
	q.push(ptSt);
	buf[ptSt.y][ptSt.x] = 0;

	while (q.size())
	{
		POINT ptRef = q.front();
		q.pop();

		if (ptRef == ptEd)
		{
			break;
		}

		for (int dir = 0; dir < DIR_MAX; dir++)
		{
			POINT ptNxt(ptRef.x + dx[dir], ptRef.y + dy[dir]);

			if (!ptNxt.isValidPoint() || A[ptNxt.y][ptNxt.x] == -1)
			{
				continue;
			}

			if (buf[ptNxt.y][ptNxt.x] > buf[ptRef.y][ptRef.x] + 1)
			{
				buf[ptNxt.y][ptNxt.x] = buf[ptRef.y][ptRef.x] + 1;
				q.push(ptNxt);
			}
		}
	}

	return buf[ptEd.y][ptEd.x];
}

bool PickupPassenser(PASSENSER& _pickedup, int& _dist)
{
	int buf[20][20] = { 0, };
	CalcDistMap(taxi.pos, buf);

	int mindist = MAXDIST;
	int minIdx = 0;
	PASSENSER minPassenser;
	for (int idx = 0; idx < vcPassenser.size(); idx++)
	{
		int dist = buf[vcPassenser.at(idx).ptStart.y][vcPassenser.at(idx).ptStart.x];

		if (dist < mindist)
		{
			mindist = dist;
			minIdx = idx;
			minPassenser = vcPassenser.at(idx);
		}
		else if (dist == mindist)
		{
			if (vcPassenser.at(idx).ptStart.y < minPassenser.ptStart.y)
			{
				mindist = dist;
				minIdx = idx;
				minPassenser = vcPassenser.at(idx);
			}
			else if (vcPassenser.at(idx).ptStart.y == minPassenser.ptStart.y && vcPassenser.at(idx).ptStart.x < minPassenser.ptStart.x)
			{
				mindist = dist;
				minIdx = idx;
				minPassenser = vcPassenser.at(idx);
			}
		}
	}

	if (mindist == MAXDIST)
	{
		_dist = MAXDIST;
		return false;
	}

	_pickedup = vcPassenser.at(minIdx);
	_dist = mindist;

	vcPassenser.erase(vcPassenser.begin() + minIdx);

	return true;
}

void DrivePassenser(PASSENSER& _pickedup, int& _dist)
{
	_dist = CalcPt2Pt(_pickedup.ptStart, _pickedup.ptEnd);
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M >> taxi.cur_fuel;


	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> A[j][i];

			if (A[j][i] == 1)
			{
				A[j][i] = -1;
			}
		}
	}

	cin >> taxi.pos.y >> taxi.pos.x;
	taxi.pos.y--;
	taxi.pos.x--;

	for (int idx = 0; idx < M; idx++)
	{
		PASSENSER tmpP;
		cin >> tmpP.ptStart.y >> tmpP.ptStart.x >> tmpP.ptEnd.y >> tmpP.ptEnd.x;

		tmpP.ptStart.y--;
		tmpP.ptStart.x--;
		tmpP.ptEnd.y--;
		tmpP.ptEnd.x--;

		vcPassenser.push_back(tmpP);
	}

	while (vcPassenser.size())
	{
		PASSENSER pickedUp;
		int dist2Start;
		bool bPickUp = PickupPassenser(pickedUp, dist2Start);
		if (!bPickUp)
		{
			taxi.cur_fuel = -1;
			break;
		}
		taxi.pos = pickedUp.ptStart;
		taxi.cur_fuel -= dist2Start;
		if (taxi.cur_fuel <= 0)
		{
			taxi.cur_fuel = -1;
			break;
		}

		int dist2End;
		DrivePassenser(pickedUp, dist2End);
		if (dist2End == MAXDIST)
		{
			taxi.cur_fuel = -1;
			break;
		}
		taxi.pos = pickedUp.ptEnd;
		taxi.cur_fuel -= dist2End;
		if (taxi.cur_fuel < 0)
		{
			taxi.cur_fuel = -1;
			break;
		}
		else
		{
			taxi.cur_fuel += (2 * dist2End);
		}
	}

	if (vcPassenser.size() > 0)
	{
		taxi.cur_fuel = -1;
	}

	cout << taxi.cur_fuel << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}