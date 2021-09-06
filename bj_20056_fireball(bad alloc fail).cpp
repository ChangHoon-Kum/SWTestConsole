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

struct FireBallMap
{
	int cnt;
	vector<list<FireBall>::iterator> vcFireBallIter;

	FireBallMap()
	{
		cnt = 0;
	}

	void EraseIterator(const list<FireBall>::iterator& _it)
	{
		for (auto it = vcFireBallIter.begin(); it != vcFireBallIter.end();)
		{
			if (*it == _it)
			{
				it = vcFireBallIter.erase(it);
				cnt--;
				break;
			}
			else
			{
				++it;
			}
		}
	}

	void Push(list<FireBall>::iterator _it)
	{
		vcFireBallIter.push_back(_it);
		cnt++;
	}

	/*void Push(list<FireBall>& _lstFireBall)
	{
		for (auto it = _lstFireBall.begin() ; it != _lstFireBall.end() ; it++)
		{
			Push(it);
		}
	}*/

	void clear(list<FireBall>& _lstfireball)
	{
		for (int idx = this->vcFireBallIter.size() - 1; idx >= 0; idx--)
		{
			_lstfireball.erase(this->vcFireBallIter.at(idx));
		}

		cnt = 0;
		this->vcFireBallIter.clear();
	}
};

int N, M, K;
FireBallMap mapFireBall[50][50];
list<FireBall> lstFireBall;

bool isValidPoint(const int x, const int y)
{
	return x >= 0 && y >= 0 && x < N&& y < N;
}

void CmdFireBall()
{
	// 1. Move all fireball with their own properties.
	for (auto it = lstFireBall.begin(); it != lstFireBall.end(); it++)
	{
		mapFireBall[it->r][it->c].EraseIterator(it);

		it->c = it->c + dx[it->d] * it->s;
		it->r = it->r + dy[it->d] * it->s;

		while (it->r < 0)
		{
			it->r += N;
		}

		while (it->c < 0)
		{
			it->c += N;
		}

		while (it->r >= N)
		{
			it->r -= N;
		}

		while (it->c >= N)
		{
			it->c -= N;
		}

		mapFireBall[it->r][it->c].Push(it);
	}

	// 2. Check merge fireball
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (mapFireBall[j][i].cnt > 1)
			{
				int m = 0, s = 0, nDirOdd = 0, nDirEven = 0;
				for (int idx = 0; idx < mapFireBall[j][i].cnt; idx++)
				{
					m += mapFireBall[j][i].vcFireBallIter.at(idx)->m;
					s += mapFireBall[j][i].vcFireBallIter.at(idx)->s;

					if (mapFireBall[j][i].vcFireBallIter.at(idx)->d % 2 == 0)
					{
						nDirEven++;
					}
					else
					{
						nDirOdd++;
					}
				}

				m /= 5.;
				s /= (double)mapFireBall[j][i].cnt;
				int InitDir = (nDirEven == 0 || nDirOdd) == 0 ? 0 : 1;

				mapFireBall[j][i].clear(lstFireBall);
				if (m > 0)
				{
					for (int sub_idx = 0; sub_idx < 4; sub_idx++)
					{
						lstFireBall.push_back(FireBall(j, i, m, InitDir, s));
						auto it_end = lstFireBall.end();
						it_end--;
						mapFireBall[j][i].Push(it_end);

						InitDir += 2;
					}
				}
			}
		}
	}
}

int CalcAmountM()
{
	int nRet = 0;
	for (auto& it : lstFireBall)
	{
		nRet += it.m;
	}

	return nRet;
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M >> K;

	// input fireball  info 
	{
		lstFireBall.resize(M);
		list<FireBall>::iterator it = lstFireBall.begin();
		for (int idx = 0; idx < M; idx++)
		{
			cin >> it->r >> it->c >> it->m >> it->s >> it->d;
			it++;
		}
	}

	// 0. Init Map
	for (auto it = lstFireBall.begin(); it != lstFireBall.end(); it++)
	{
		mapFireBall[it->r][it->c].Push(it);
	}

	for (int idx = 0; idx < K; idx++)
	{
		CmdFireBall();
	}




	cout << CalcAmountM() << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}