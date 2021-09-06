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
int A[ARR_LIMIT][ARR_LIMIT] = { 0, };


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

struct FARM
{
	int nutrient;
	vector<list<TREE>::iterator> vcTree;

	FARM()
	{
		nutrient = 5;
	}
};

list<TREE> lstTree;
FARM farm[ARR_LIMIT][ARR_LIMIT];
bool bCheck[ARR_LIMIT][ARR_LIMIT];

bool SortIterTreeAge(const list<TREE>::iterator& _l, const list<TREE>::iterator& _r)
{
	return _l->age < _r->age;
}

bool SortAscendTreePos(const TREE& _l, const TREE& _r)
{
	return _l.pos.y * ARR_LIMIT + _l.pos.x < _r.pos.y* ARR_LIMIT + _r.pos.x;
}

void Spring_Summer()
{
	lstTree.sort(SortAscendTreePos);

	for (auto it = lstTree.begin(); it != lstTree.end();)
	{
		const int j = it->pos.y;
		const int i = it->pos.x;

		if (bCheck[j][i] == false)
		{
			bCheck[j][i] = true;

			int NumofTree = farm[j][i].vcTree.size();
			if (NumofTree > 0)
			{// eat nutrient
				if (NumofTree > 1)
				{
					std::sort(farm[j][i].vcTree.begin(), farm[j][i].vcTree.end(), SortIterTreeAge);
				}

				int tree = 0;
				for (tree = 0; tree < NumofTree; tree++)
				{
					if (farm[j][i].vcTree.at(tree)->age <= farm[j][i].nutrient)
					{
						farm[j][i].nutrient -= farm[j][i].vcTree.at(tree)->age;
						farm[j][i].vcTree.at(tree)->age++;
					}
					else
					{
						break;
					}
				}

				for (int deadTree = tree; deadTree < NumofTree; deadTree++)
				{
					farm[j][i].nutrient += (int)(farm[j][i].vcTree.at(deadTree)->age / 2.);
					it = lstTree.erase(farm[j][i].vcTree.at(deadTree));
				}

				if (tree < NumofTree)
				{
					farm[j][i].vcTree.erase(farm[j][i].vcTree.begin() + tree, farm[j][i].vcTree.end());
					continue;
				}
			}
		}

		it++;
	}
}

bool SortDescendTreeAge(const TREE& _l, const TREE& _r)
{
	return _l.age > _r.age;
}

void Fall()
{
	lstTree.sort(SortDescendTreeAge);

	auto Iter = lstTree.begin();
	for (; Iter->age >= 5; Iter++)
	{
		if (Iter->age % 5 == 0)
		{
			for (int dir = 0; dir < DIRMAX; dir++)
			{
				POINT pt(Iter->pos.x + dx[dir], Iter->pos.y + dy[dir]);

				if (pt.isValidPoint())
				{
					lstTree.push_back(TREE(pt, 1));
					auto endIt = lstTree.end();
					endIt--;
					farm[pt.y][pt.x].vcTree.push_back(endIt);
				}
			}
		}
	}
}

void Winter()
{
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			farm[j][i].nutrient += A[j][i];
		}
	}
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
		}
	}

	for (int idx = 0; idx < M; idx++)
	{
		int x, y, z;
		cin >> y >> x >> z;
		x--;
		y--;
		lstTree.push_back(TREE(POINT(x, y), z));
		auto endIt = lstTree.end();
		endIt--;
		farm[y][x].vcTree.push_back(endIt);
	}

	for (int year = 0; year < K; year++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				bCheck[j][i] = false;
			}
		}
		Spring_Summer();
		Fall();
		Winter();
	}

	cout << lstTree.size() << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}