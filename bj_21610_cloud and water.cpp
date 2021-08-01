#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

enum DIRECTION { LEFT = 0, TOPLEFT, TOP, TOPRIGHT, RIGHT, BOTTOMRIGHT, BOTTOM, BOTTOMLEFT, DIRMAX = 8 };

//      LEFT = 0, TOPLEFT, TOP, TOPRIGHT, RIGHT, BOTTOMRIGHT, BOTTOM, BOTTOMLEFT
int dx[8] = { -1,  -1,      0,      1,       1,         1,        0,       -1 };
int dy[8] = { 0,   -1,     -1,     -1,       0,         1,        1,        1 };

struct POINT
{
	int x;
	int y;

	POINT()
	{
		this->x = this->y = 0;
	}

	POINT(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
	}

	bool operator== (POINT& rval)
	{
		return this->x == rval.x && this->y == rval.y;
	}

	bool operator!= (POINT& rval)
	{
		return !(this->x == rval.x && this->y == rval.y);
	}

	string GetString()
	{
		char buffer[100];
		snprintf(buffer, 100, "(%d, %d) ", x, y);
		return string(buffer);
	}
};

bool isCorrectPt(POINT _pt, int _N)
{
	return _pt.x >= 0 && _pt.y >= 0 && _pt.x < _N&& _pt.y < _N;
}

void CLOUD_MOVE(POINT& pt, int _N, int _dir, int _stride)
{
	pt.x += dx[_dir] * _stride;
	pt.y += dy[_dir] * _stride;

	do
	{
		if (pt.x < 0) pt.x += _N;
		else if (pt.x >= _N) pt.x -= _N;

		if (pt.y < 0) pt.y += _N;
		else if (pt.y >= _N) pt.y -= _N;
	} while (!isCorrectPt(pt, _N));
}

int water_dx[4] = { -1,  1, -1, 1 };
int water_dy[4] = { -1, -1,  1, 1 };

int main(int argc, char** argv)
{
	//freopen("input.txt", "r", stdin);

	//Init Map
	int idx = 0, idx_sub = 0;
	int N = 0, M = 0;
	int j = 0, i = 0;
	cin >> N >> M;

	if (N > 50) N = 50;
	if (M > 100) M = 100;

	vector<vector<int>> A;
	A.resize(N);
	for (idx = 0; idx < N; idx++)
	{
		A.at(idx).resize(N);
	}

	{
		int nVal = 0;
		for (j = 0; j < N; j++)
		{
			for (i = 0; i < N; i++)
			{
				cin >> nVal;
				if (nVal > 100) nVal = 100;
				else if (nVal < 0) nVal = 0;
				A.at(j).at(i) = nVal;
			}
		}
	}

	vector<pair<int/*d*/, int/*s*/>> vcMove;
	{
		int d = 0, s = 0;
		for (idx = 0; idx < M; idx++)
		{
			cin >> d >> s;

			if (d > 8) d = 8;
			else if (d < 1) d = 1;

			if (s > 50) s = 50;
			else if (s < 1) s = 1;

			vcMove.push_back(make_pair(d - 1, s)); // direction is corrected for index
		}
	}

	vector<POINT> vcCLOUD;
	vcCLOUD.push_back(POINT(0, N - 2));
	vcCLOUD.push_back(POINT(1, N - 2));
	vcCLOUD.push_back(POINT(0, N - 1));
	vcCLOUD.push_back(POINT(1, N - 1));

	while (vcMove.size() > 0UL)
	{
		int d = vcMove.at(0).first;
		int s = vcMove.at(0).second;
		vcMove.erase(vcMove.begin());

		int szCLOUD = vcCLOUD.size();

		// 1. Cloud Move
		for (idx = 0; idx < szCLOUD; idx++)
		{
			CLOUD_MOVE(vcCLOUD.at(idx), N, d, s);
		}

		// 2. Raining & Water Check
		vector<POINT> vcCLOUD_prior = vcCLOUD;
		for (idx = szCLOUD - 1; idx >= 0; idx--)
		{
			A.at(vcCLOUD.at(idx).y).at(vcCLOUD.at(idx).x)++;
			vcCLOUD.erase(vcCLOUD.begin() + idx);
		}

		for (idx = szCLOUD - 1; idx >= 0; idx--)
		{
			int nWater = 0;
			POINT waterpt;
			for (idx_sub = 0; idx_sub < 4; idx_sub++)
			{
				waterpt.x = vcCLOUD_prior.at(idx).x + water_dx[idx_sub];
				waterpt.y = vcCLOUD_prior.at(idx).y + water_dy[idx_sub];

				if (isCorrectPt(waterpt, N))
				{
					if (A.at(waterpt.y).at(waterpt.x) > 0)
					{
						nWater++;
					}
				}
			}

			A.at(vcCLOUD_prior.at(idx).y).at(vcCLOUD_prior.at(idx).x) += nWater;
		}

		// 3. Make new Cloud
		for (j = 0; j < N; j++)
		{
			for (i = 0; i < N; i++)
			{
				if (A.at(j).at(i) >= 2)
				{
					POINT pt(i, j);
					bool bCheckPriorCLOUD = false;
					for (idx = 0; idx < szCLOUD; idx++)
					{
						if (vcCLOUD_prior.at(idx) == pt)
						{
							bCheckPriorCLOUD = true;
							break;
						}
					}

					if (!bCheckPriorCLOUD)
					{
						A.at(j).at(i) -= 2;
						vcCLOUD.push_back(pt);
					}
				}
			}
		}

	}

	int nSum = 0;
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < N; i++)
		{
			nSum += A.at(j).at(i);
		}
	}

	cout << nSum << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}