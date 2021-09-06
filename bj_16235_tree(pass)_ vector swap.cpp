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
#define ARR_LIMIT 10

int N, M, K;

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

enum DIRECTION { TOP = 0, TOPLEFT, LEFT, BOTTOMLEFT, BOTTOM, BOTTOMRIGHT, RIGHT, TOPRIGHT, DIRMAX = 8 };

//      TOP = 0, TOPLEFT, LEFT, BOTTOMLEFT, BOTTOM, BOTTOMRIGHT, RIGHT, TOPRIGHT
int dx[8] = { 0,  -1,      -1,      -1,       0,         1,        1,       1 };
int dy[8] = { -1, -1,       0,       1,       1,         1,        0,      -1 };


struct TREE
{
	POINT pos;
	int age;

	TREE()
	{
		pos = POINT(-1, -1);
		age = 0;
	}

	TREE(const POINT& _pos, const int _age)
	{
		this->pos = _pos;
		this->age = _age;
	}

	bool operator<(const TREE& _r)
	{
		return this->age < _r.age;
	}
};


vector<TREE> vcTree[2];
int A[ARR_LIMIT][ARR_LIMIT] = { 0, };
int nutrient[ARR_LIMIT][ARR_LIMIT] = { 0, };

int tin = 0;

bool SortTreeAge(const TREE& _l, const TREE& _r)
{
	return _l.age < _r.age;
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M >> K;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> A[j][i];
			nutrient[j][i] = 5;
		}
	}

	for (int idx = 0; idx < M; idx++)
	{
		int x, y, z;
		cin >> y >> x >> z;
		x--;
		y--;
		vcTree[0].push_back(TREE(POINT(x, y), z));
	}
	sort(vcTree[0].begin(), vcTree[0].end(), SortTreeAge);

	for (int year = 0; year < K; year++)
	{
		vector<TREE>& T = vcTree[tin];
		vector<TREE>& T2 = vcTree[1 - tin];

		T2.clear();

		for (auto& it : T)
		{
			if (it.age <= nutrient[it.pos.y][it.pos.x])
			{
				nutrient[it.pos.y][it.pos.x] -= it.age;
				it.age++;

				if (it.age % 5 == 0)
				{
					for (int dir = 0; dir < DIRMAX; dir++)
					{
						POINT nxtPos(it.pos.x + dx[dir], it.pos.y + dy[dir]);
						if (nxtPos.isValidPoint())
						{
							T2.push_back(TREE(nxtPos, 1));
						}
					}
				}
			}
			else
			{
				it.age = -it.age;
			}
		}

		for (auto& it : T)
		{
			if (it.age < 0)
			{
				nutrient[it.pos.y][it.pos.x] += (int)(-it.age / 2.);
			}
			else
			{
				T2.push_back(it);
			}
		}

		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				nutrient[j][i] += A[j][i];
			}
		}

		tin = 1 - tin;
	}

	cout << vcTree[tin].size() << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}