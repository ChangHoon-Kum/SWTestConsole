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
int s[20][20] = { 0, };
vector<array<int, 5>> vcList;

// 좌, 하, 우, 상
int dx[4] = { -1,0,1, 0 };
int dy[4] = { 0,1,0,-1 };

int GetCntAdjacentEmpty(POINT& _pt)
{
	POINT tmpPt;

	int nEmpty = 0;
	for (int i = 0; i < 4; i++)
	{
		tmpPt.x = _pt.x + dx[i];
		tmpPt.y = _pt.y + dy[i];

		if (tmpPt.isValidPoint(N))
		{
			if (s[tmpPt.y][tmpPt.x] <= 0)
			{
				nEmpty++;
			}
		}
	}

	return nEmpty;
}

int GetCntAdjacentFavorite(POINT& _pt, array<int, 5>& _list)
{
	POINT tmpPt;

	bool bFavorite[5] = { false, }; // ignore first index
	for (int i = 0; i < 4; i++)
	{
		tmpPt.x = _pt.x + dx[i];
		tmpPt.y = _pt.y + dy[i];

		if (tmpPt.isValidPoint(N))
		{
			for (int j = 1; j <= 4; j++)
			{
				if (!bFavorite[j] && s[tmpPt.y][tmpPt.x] == _list.at(j))
				{
					bFavorite[j] = true;
					break;
				}
			}
		}
	}

	int nFavorite = 0;
	if (bFavorite[1]) nFavorite++;
	if (bFavorite[2]) nFavorite++;
	if (bFavorite[3]) nFavorite++;
	if (bFavorite[4]) nFavorite++;

	return nFavorite;
}

int GetFavoriteScore(POINT& _pt, array<int, 5>& _list)
{
	POINT tmpPt;

	bool bFavorite[5] = { false, }; // ignore first index
	for (int i = 0; i < 4; i++)
	{
		tmpPt.x = _pt.x + dx[i];
		tmpPt.y = _pt.y + dy[i];

		if (tmpPt.isValidPoint(N))
		{
			for (int j = 1; j <= 4; j++)
			{
				if (!bFavorite[j] && s[tmpPt.y][tmpPt.x] == _list[j])
				{
					bFavorite[j] = true;
					break;
				}
			}
		}
	}

	int nFavorite = 0;
	if (bFavorite[1]) nFavorite++;
	if (bFavorite[2]) nFavorite++;
	if (bFavorite[3]) nFavorite++;
	if (bFavorite[4]) nFavorite++;

	return nFavorite == 4 ? 1000 : nFavorite == 3 ? 100 : nFavorite == 2 ? 10 : nFavorite == 1 ? 1 : 0;
}

bool opFunc(array<int, 5>& _l, array<int, 5>& _r)
{
	return _l[0] < _r[0];
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N;

	{
		array<int, 5> input;
		for (int i = 0; i < N * N; ++i)
		{
			cin >> input[0] >> input[1] >> input[2] >> input[3] >> input[4];
			vcList.push_back(input);
		}
	}

	// make seat
	for (int idx = 0; idx < N * N; idx++)
	{
		if (idx == 0)
		{
			s[1][1] = vcList.at(idx)[0];
			continue;
		}

		int nFavorit = 0, nEmpty = 0;
		POINT ptSeat(-1, -1);

		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				if (s[j][i] > 0) continue;

				POINT pt(i, j);
				if (!ptSeat.isValidPoint(N))
				{
					ptSeat = pt;
				}

				int nF_sub = GetCntAdjacentFavorite(pt, vcList.at(idx));

				if (nF_sub > nFavorit)
				{
					nFavorit = nF_sub;
					ptSeat = pt;
					nEmpty = GetCntAdjacentEmpty(pt);
				}
				else if (nF_sub == nFavorit)
				{
					int nE_sub = GetCntAdjacentEmpty(pt);
					if (nE_sub > nEmpty)
					{
						nEmpty = nE_sub;
						ptSeat = pt;
					}
				}
			}
		}

		s[ptSeat.y][ptSeat.x] = vcList.at(idx)[0];
	}

	sort(vcList.begin(), vcList.end(), opFunc);
	// make score
	int score = 0;
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			POINT pt(i, j);
			score += GetFavoriteScore(pt, vcList.at(s[j][i] - 1));
		}
	}

	cout << score << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}