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

#define ARR_LIMIT	49


enum DIRECTION { LEFT = 0, BOTTOM, RIGHT, TOP, DIRMAX = 4 };

// 좌, 하, 우, 상
int dx[4] = { -1,0,1, 0 };
int dy[4] = { 0,1,0,-1 };

int N, M;  // N - 격자 크기, M - 색상의 갯수

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

	bool operator!=(const POINT& _r)
	{
		return this->x != _r.x && this->y != _r.y;
	}
};

int A[ARR_LIMIT][ARR_LIMIT] = { 0, };
vector<pair<POINT, int>> vcBall;

int nScore[3] = { 0, };

void GetLinearMap()
{
	POINT refPt;
	refPt.x = refPt.y = N / 2.;

	int dir = LEFT;
	int stride = 1;
	int step = 0;
	vector<pair<POINT, int>> vcBallTmp;
	while (true)
	{
		if (refPt == POINT(0, 0))
		{
			break;
		}

		refPt.x += dx[dir];
		refPt.y += dy[dir];

		if (A[refPt.y][refPt.x] > 0)
		{
			vcBallTmp.push_back(make_pair(refPt, A[refPt.y][refPt.x]));
		}

		step++;
		if (step == stride)
		{
			dir++;
			dir = dir % DIRMAX;
			if (dir == RIGHT || dir == LEFT)
			{
				stride++;
			}
			step = 0;
		}
	}

	vcBall = vcBallTmp;
}

void LinearMapTo2DArr()
{
	POINT refPt;
	refPt.x = refPt.y = N / 2.;

	int dir = LEFT;
	int stride = 1;
	int step = 0;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			A[j][i] = 0;
		}
	}

	for (auto& it : vcBall)
	{
		refPt.x += dx[dir];
		refPt.y += dy[dir];

		A[refPt.y][refPt.x] = it.second;
		it.first = refPt; // update Coordinate

		step++;
		if (step == stride)
		{
			dir++;
			dir = dir % DIRMAX;
			if (dir == RIGHT || dir == LEFT)
			{
				stride++;
			}
			step = 0;
		}
	}
}

void GetContinuousBall(vector<int>& _IdxRemove)
{
	const int ThrCntContinue = 4;

	int nSize = vcBall.size();
	int nBallType = 0;
	vector<int> vcTmpBall;
	for (int idx = 0; idx < nSize; idx++)
	{
		if (idx == 0)
		{
			nBallType = vcBall.at(idx).second;
			vcTmpBall.push_back(idx);
			continue;
		}

		if (nBallType == vcBall.at(idx).second)
		{
			vcTmpBall.push_back(idx);

			if (idx >= nSize - 1 && vcTmpBall.size() > ThrCntContinue)
			{
				for (auto it_sub : vcTmpBall)
				{
					_IdxRemove.push_back(it_sub);
				}
				vcTmpBall.clear();
			}
		}
		else
		{
			if (vcTmpBall.size() >= ThrCntContinue)
			{
				for (auto it_sub : vcTmpBall)
				{
					_IdxRemove.push_back(it_sub);
				}
				vcTmpBall.clear();
			}

			nBallType = vcBall.at(idx).second;
			vcTmpBall.clear();
			vcTmpBall.push_back(idx);
		}
	}
}

/*struct GROUP
{
	int nType;
	int nCnt;
};*/

void GetContinuousBallGroup(vector<int>& _vcGroup)
{
	int nSize = vcBall.size();
	int nBallType = 0;
	vector<int> vcTmpBall;
	for (int idx = 0; idx < nSize; idx++)
	{
		if (idx == 0)
		{
			nBallType = vcBall.at(idx).second;
			vcTmpBall.push_back(idx);
			continue;
		}

		if (nBallType == vcBall.at(idx).second)
		{
			vcTmpBall.push_back(idx);

			if (idx >= nSize - 1)
			{
				_vcGroup.push_back(vcTmpBall.size());
				_vcGroup.push_back(nBallType);

				vcTmpBall.clear();
			}
		}
		else
		{
			_vcGroup.push_back(vcTmpBall.size());
			_vcGroup.push_back(nBallType);

			nBallType = vcBall.at(idx).second;
			vcTmpBall.clear();
			vcTmpBall.push_back(idx);

			if (idx >= nSize - 1)
			{
				_vcGroup.push_back(vcTmpBall.size());
				_vcGroup.push_back(nBallType);

				vcTmpBall.clear();
			}
		}
	}
}

void NewMapping()
{
	vector<int> vcGroup;
	GetContinuousBallGroup(vcGroup);

	POINT refPt;
	refPt.x = refPt.y = N / 2.;

	int dir = LEFT;
	int stride = 1;
	int step = 0;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			A[j][i] = 0;
		}

	}

	for (auto it : vcGroup)
	{
		if (refPt == POINT(0, 0))
		{
			break;
		}

		refPt.x += dx[dir];
		refPt.y += dy[dir];

		A[refPt.y][refPt.x] = it;

		step++;
		if (step == stride)
		{
			dir++;
			dir = dir % DIRMAX;
			if (dir == RIGHT || dir == LEFT)
			{
				stride++;
			}
			step = 0;
		}
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> A[j][i];
		}
	}

	POINT ctPt;
	ctPt.x = ctPt.y = N / 2.;

	for (int time = 0; time < M; time++)
	{
		DIRECTION dir;
		int distance;
		//dir
		{
			int dirTmp;
			cin >> dirTmp;
			switch (dirTmp)
			{
			case 1:
				dir = TOP;
				break;
			case 2:
				dir = BOTTOM;
				break;
			case 3:
				dir = LEFT;
				break;
			case 4:
			default:
				dir = RIGHT;
				break;
			}
		}
		cin >> distance;

		//vector<POINT> vcBlizzard;
		{
			POINT refPt = ctPt;
			for (int s = 0; s < distance; s++)
			{
				refPt.x += dx[dir];
				refPt.y += dy[dir];

				//nScore[A[refPt.y][refPt.x] - 1]++;
				A[refPt.y][refPt.x] = 0;
			}
		}

		GetLinearMap();
		LinearMapTo2DArr();

		vector<int> vcRm;
		do
		{
			vcRm.clear();
			GetContinuousBall(vcRm);

			vector<pair<POINT, int>> vcBallTmp;
			auto it_rm = vcRm.begin();
			for (int idx = 0; idx < vcBall.size(); idx++)
			{
				if (it_rm != vcRm.end())
				{
					if (*it_rm == idx)
					{
						nScore[A[vcBall.at(idx).first.y][vcBall.at(idx).first.x] - 1]++;
						it_rm++;
						continue;
					}
				}

				vcBallTmp.push_back(vcBall.at(idx));
			}
			vcBall = vcBallTmp;

		} while (vcRm.size());
		LinearMapTo2DArr();

		NewMapping();
	}

	int totalScore = nScore[0] + (2 * nScore[1]) + (3 * nScore[2]);
	cout << totalScore << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}