#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

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

	bool isValidPoint(int _size)
	{
		return this->x >= 0 && this->y >= 0 && this->x < _size&& this->y < _size;
	}
};

#define abs(n) (n>0?n:-n)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
int N;
int r[20], c[20];
int s[20][20] = { -1, };
int check[20][20] = { -1, };
vector<POINT> vcCheckPt;

struct BabyShark
{
	int szShark;
	int time;
	int stack;
	POINT pos;

	BabyShark()
	{
		szShark = 2;
		time = 0;
		stack = 0;
	}

	bool CanEat(int szfish)
	{
		return szfish != 0 && szfish < this->szShark;
	}

	void Eat(POINT _pt)
	{
		s[pos.y][pos.x] = 0;
		time += (abs((this->pos.x - _pt.x)));
		time += (abs((this->pos.y - _pt.y)));

		this->pos = _pt;

		stack++;

		if (stack >= szShark)
		{
			szShark++;
			stack = 0;
		}
		s[pos.y][pos.x] = 9;
	}
};

BabyShark babyshark;

void InitCheckable()
{
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (s[j][i] == 9 || s[j][i] > babyshark.szShark)
			{
				check[j][i] = 1;
			}
			else
			{
				check[j][i] = 0;
			}
		}
	}
}

// 상, 좌, 우, 하
int dx[4] = { 0, -1, 1, 0 };
int dy[4] = { -1, 0, 0, 1 };

bool CheckFeed(POINT& _pt, int stride)
{
	bool bEat = false;

	vector<POINT>vcTmp;


	POINT stPt(_pt.x, _pt.y - stride);
	POINT edPt(_pt.x, _pt.y + stride);

	vcTmp.push_back(stPt);
	for (int j = stPt.y + 1; j < edPt.y; j++)
	{
		int i = j - stPt.y;
		if (j > _pt.y)
		{
			i = stride - (j - _pt.y);
		}
		vcTmp.push_back(POINT(_pt.x - i, j));
		vcTmp.push_back(POINT(_pt.x + i, j));
	}
	vcTmp.push_back(edPt);

	for (auto it : vcTmp)
	{
		if (it.isValidPoint(N) && check[it.y][it.x] == 0)
		{
			check[it.y][it.x] = 1;
			if (babyshark.CanEat(s[it.y][it.x]))
			{
				bEat = true;
				babyshark.Eat(it);

				break;
			}
		}
	}

	if (!bEat)
	{
		if (stride > (N - 1) * (N - 1))
		{
			return bEat;
		}
		bEat = CheckFeed(_pt, stride + 1);
	}

	return bEat;
}


int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> s[j][i];

			if (s[j][i] == 9)
			{
				babyshark.pos.x = i;
				babyshark.pos.y = j;
			}
		}
	}
	vcCheckPt.push_back(babyshark.pos);


	bool bEat = false;
	do
	{
		InitCheckable();
		POINT curPos = vcCheckPt.at(0);
		vcCheckPt.erase(vcCheckPt.begin());
		bEat = CheckFeed(curPos, 1);
		if (bEat)
		{
			vcCheckPt.clear();
			vcCheckPt.push_back(babyshark.pos);
		}

	} while (bEat);


	cout << babyshark.time << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}