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

//			TOP, RT, RIGHT, RB, BTM, LB, LEFT, LT
int dx[8] = { 0,  1,	1,	 1,	 0,	  -1,  -1, -1 };
int dy[8] = { -1, -1,	0,   1,  1,   1,   0,  -1 };

struct FireBall
{
	int r;
	int c;
	int m;
	int d;
	int s;

	FireBall()
	{
		r = c = -1;
		m = d = s = 0;
	}

	FireBall(const int _r, const int _c, const int _m, const int _d, const int _s)
	{
		this->r = _r;
		this->c = _c;
		this->m = _m;
		this->d = _d;
		this->s = _s;
	}
};

int N, M, K;
vector<FireBall> mapFireBall[50][50];
vector<FireBall> vcFireBall;
void UpdateMap();

bool isValidPoint(const int x, const int y)
{
	return x >= 0 && y >= 0 && x < N&& y < N;
}

void CmdFireBall()
{
	// 1. Move all fireball with their own properties.
	for (auto& it : vcFireBall)
	{
		int nMove = it.s % N;
		it.c = it.c + dx[it.d] * nMove;
		it.r = it.r + dy[it.d] * nMove;

		while (it.r < 0)
		{
			it.r += N;
		}

		while (it.c < 0)
		{
			it.c += N;
		}

		while (it.r >= N)
		{
			it.r -= N;
		}

		while (it.c >= N)
		{
			it.c -= N;
		}
	}
	UpdateMap();

	// 2. Check merge fireball
	vector<FireBall> vcTemp;
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (mapFireBall[j][i].size() == 0UL)
			{
				continue;
			}
			else if (mapFireBall[j][i].size() == 1UL)
			{
				vcTemp.push_back(mapFireBall[j][i].at(0));
				continue;
			}

			int m = 0, s = 0, nDirOdd = 0, nDirEven = 0;
			for (int idx = 0; idx < mapFireBall[j][i].size(); idx++)
			{
				m += mapFireBall[j][i].at(idx).m;
				s += mapFireBall[j][i].at(idx).s;

				if (mapFireBall[j][i].at(idx).d % 2 == 0)
				{
					nDirEven++;
				}
				else
				{
					nDirOdd++;
				}
			}

			m /= 5.;
			s /= (double)mapFireBall[j][i].size();
			int InitDir = (nDirEven == 0 || nDirOdd == 0) ? 0 : 1;

			if (m > 0)
			{
				for (int sub_idx = 0; sub_idx < 4; sub_idx++)
				{
					vcTemp.push_back(FireBall(j, i, m, InitDir, s));

					InitDir += 2;
				}
			}
		}
	}

	vcFireBall = vcTemp;
}

int CalcAmountM()
{
	int nRet = 0;
	for (auto& it : vcFireBall)
	{
		nRet += it.m;
	}

	return nRet;
}

void UpdateMap()
{
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			mapFireBall[j][i].clear();
		}
	}

	for (auto it = vcFireBall.begin(); it != vcFireBall.end(); it++)
	{
		mapFireBall[it->r][it->c].push_back(*it);
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M >> K;

	// input fireball  info 
	{
		vcFireBall.resize(M);
		vector<FireBall>::iterator it = vcFireBall.begin();
		for (int idx = 0; idx < M; idx++)
		{
			cin >> it->r >> it->c >> it->m >> it->s >> it->d;
			it++;
		}
	}

	for (int idx = 0; idx < K; idx++)
	{
		CmdFireBall();
	}




	cout << CalcAmountM() << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}