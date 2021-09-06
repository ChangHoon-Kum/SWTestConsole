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

int N;

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
};

enum DIRECTION { RIGHT = 0, LEFT, TOP, BTM, DIR_MAX };

//			RIGHT = 0, LEFT, TOP, BTM
int dx[DIR_MAX] = { 1, -1,  0, 0 };
int dy[DIR_MAX] = { 0,  0, -1, 1 };

char U[3][3] = { 'w', };
char D[3][3] = { 'y', };
char F[3][3] = { 'r', };
char B[3][3] = { 'o', };
char L[3][3] = { 'g', };
char R[3][3] = { 'b', };

void Turn2DMatrix(char _pRgFace[][3], char dir)
{
	char buf[3][3] = { 0, };

	if (dir == '+')
	{
		buf[0][0] = _pRgFace[2][0];
		buf[0][1] = _pRgFace[1][0];
		buf[0][2] = _pRgFace[0][0];

		buf[1][2] = _pRgFace[0][1];
		buf[2][2] = _pRgFace[0][2];

		buf[2][1] = _pRgFace[1][2];
		buf[2][0] = _pRgFace[2][2];

		buf[1][0] = _pRgFace[2][1];
		buf[1][1] = _pRgFace[1][1];
	}
	else // dir == '-'
	{
		buf[0][0] = _pRgFace[0][2];
		buf[0][1] = _pRgFace[1][2];
		buf[0][2] = _pRgFace[2][2];

		buf[1][2] = _pRgFace[2][1];
		buf[2][2] = _pRgFace[2][0];

		buf[2][1] = _pRgFace[1][0];
		buf[2][0] = _pRgFace[0][0];

		buf[1][0] = _pRgFace[0][1];
		buf[1][1] = _pRgFace[1][1];
	}
}

void TurnArray(string cmd)
{
	char face = cmd[0];
	char dir = cmd[1];

	char(*pRgFace)[3];
	char(*pRgPlane1)[3];
	char(*pRgPlane2)[3];
	char(*pRgPlane3)[3];
	char(*pRgPlane4)[3];

	pair<POINT, POINT> modIdxL[3];
	pair<POINT, POINT> modIdxR[3];
	pair<POINT, POINT> modIdxT[3];
	pair<POINT, POINT> modIdxB[3];
	if (face == 'L')
	{
		pRgFace = L;
		if (dir == '+')
		{
			pRgPlane1 = U;
			pRgPlane2 = F;
			pRgPlane3 = D;
			pRgPlane4 = B;
		}
		else // dir == '-'
		{
			pRgPlane1 = U;
			pRgPlane2 = B;
			pRgPlane3 = D;
			pRgPlane4 = F;
		}

		modIdxL[0] = make_pair(POINT(0, 0), POINT(0, 2));
		modIdxL[1] = make_pair(POINT(0, 1), POINT(0, 1));
		modIdxL[2] = make_pair(POINT(0, 2), POINT(0, 0));

		modIdxR[0] = make_pair(POINT(0, 0), POINT(0, 0));
		modIdxR[1] = make_pair(POINT(0, 1), POINT(0, 1));
		modIdxR[2] = make_pair(POINT(0, 2), POINT(0, 2));

		modIdxT[0] = make_pair(POINT(0, 0), POINT(0, 0));
		modIdxT[1] = make_pair(POINT(0, 1), POINT(0, 1));
		modIdxT[2] = make_pair(POINT(0, 2), POINT(0, 2));

		modIdxB[0] = make_pair(POINT(0, 0), POINT(0, 2));
		modIdxB[1] = make_pair(POINT(0, 1), POINT(0, 1));
		modIdxB[2] = make_pair(POINT(0, 2), POINT(0, 0));
	}
	else if (face == 'R')
	{
		pRgFace = R;
		if (dir == '+')
		{
			pRgPlane1 = U;
			pRgPlane2 = B;
			pRgPlane3 = D;
			pRgPlane4 = F;
		}
		else // dir == '-'
		{
			pRgPlane1 = U;
			pRgPlane2 = F;
			pRgPlane3 = D;
			pRgPlane4 = B;
		}

		modIdxL[0] = make_pair(POINT(2, 0), POINT(2, 0));
		modIdxL[1] = make_pair(POINT(2, 1), POINT(2, 1));
		modIdxL[2] = make_pair(POINT(2, 2), POINT(2, 2));

		modIdxR[0] = POINT(2, 0);
		modIdxR[1] = POINT(2, 1);
		modIdxR[2] = POINT(2, 2);

		modIdxT[0] = POINT(2, 0);
		modIdxT[1] = POINT(2, 1);
		modIdxT[2] = POINT(2, 2);

		modIdxB[0] = POINT(2, 0);
		modIdxB[1] = POINT(2, 1);
		modIdxB[2] = POINT(2, 2);
	}
	else if (face == 'U')
	{
		pRgFace = U;
		if (dir == '+')
		{
			pRgPlane1 = B;
			pRgPlane2 = R;
			pRgPlane3 = F;
			pRgPlane4 = L;
		}
		else // dir == '-'
		{
			pRgPlane1 = B;
			pRgPlane2 = L;
			pRgPlane3 = F;
			pRgPlane4 = R;
		}

		modIdxL[0] = POINT(0, 0);
		modIdxL[1] = POINT(1, 0);
		modIdxL[2] = POINT(2, 0);

		modIdxR[0] = POINT(0, 0);
		modIdxR[1] = POINT(1, 0);
		modIdxR[2] = POINT(2, 0);

		modIdxT[0] = POINT(0, 0);
		modIdxT[1] = POINT(1, 0);
		modIdxT[2] = POINT(2, 0);

		modIdxB[0] = POINT(0, 0);
		modIdxB[1] = POINT(1, 0);
		modIdxB[2] = POINT(2, 0);
	}
	else if (face == 'D')
	{
		pRgFace = B;
		if (dir == '+')
		{
			pRgPlane1 = F;
			pRgPlane2 = R;
			pRgPlane3 = B;
			pRgPlane4 = L;
		}
		else // dir == '-'
		{
			pRgPlane1 = F;
			pRgPlane2 = L;
			pRgPlane3 = B;
			pRgPlane4 = R;
		}

		modIdxL[0] = POINT(0, 2);
		modIdxL[1] = POINT(1, 2);
		modIdxL[2] = POINT(2, 2);

		modIdxR[0] = POINT(0, 2);
		modIdxR[1] = POINT(1, 2);
		modIdxR[2] = POINT(2, 2);

		modIdxT[0] = POINT(0, 2);
		modIdxT[1] = POINT(1, 2);
		modIdxT[2] = POINT(2, 2);

		modIdxB[0] = POINT(0, 2);
		modIdxB[1] = POINT(1, 2);
		modIdxB[2] = POINT(2, 2);
	}
	else if (face == 'F')
	{
		pRgFace = F;
		if (dir == '+')
		{
			pRgPlane1 = U;
			pRgPlane2 = R;
			pRgPlane3 = D;
			pRgPlane4 = L;

			modIdxR[0] = POINT(0, 0);
			modIdxR[1] = POINT(0, 1);
			modIdxR[2] = POINT(0, 2);

			modIdxL[0] = POINT(2, 0);
			modIdxL[1] = POINT(2, 1);
			modIdxL[2] = POINT(2, 2);
		}
		else // dir == '-'
		{
			pRgPlane1 = U;
			pRgPlane2 = L;
			pRgPlane3 = D;
			pRgPlane4 = R;

			modIdxL[0] = POINT(0, 0);
			modIdxL[1] = POINT(0, 1);
			modIdxL[2] = POINT(0, 2);

			modIdxR[0] = POINT(2, 0);
			modIdxR[1] = POINT(2, 1);
			modIdxR[2] = POINT(2, 2);
		}

		modIdxT[0] = POINT(0, 2);
		modIdxT[1] = POINT(1, 2);
		modIdxT[2] = POINT(2, 2);

		modIdxB[0] = POINT(0, 0);
		modIdxB[1] = POINT(1, 0);
		modIdxB[2] = POINT(2, 0);
	}
	else //if (face == 'B')
	{
		pRgFace = B;
		if (dir == '+')
		{
			pRgPlane1 = U;
			pRgPlane2 = L;
			pRgPlane3 = D;
			pRgPlane4 = R;

			modIdxR[0] = POINT(0, 0);
			modIdxR[1] = POINT(0, 1);
			modIdxR[2] = POINT(0, 2);

			modIdxL[0] = POINT(2, 0);
			modIdxL[1] = POINT(2, 1);
			modIdxL[2] = POINT(2, 2);
		}
		else // dir == '-'
		{
			pRgPlane1 = U;
			pRgPlane2 = R;
			pRgPlane3 = D;
			pRgPlane4 = L;

			modIdxL[0] = POINT(0, 0);
			modIdxL[1] = POINT(0, 1);
			modIdxL[2] = POINT(0, 2);

			modIdxR[0] = POINT(2, 0);
			modIdxR[1] = POINT(2, 1);
			modIdxR[2] = POINT(2, 2);
		}

		modIdxT[0] = POINT(0, 0);
		modIdxT[1] = POINT(1, 0);
		modIdxT[2] = POINT(2, 0);

		modIdxB[0] = POINT(0, 2);
		modIdxB[1] = POINT(1, 2);
		modIdxB[2] = POINT(2, 2);
	}


	Turn2DMatrix(pRgFace, dir);

	char buf[3];
	buf[0] = pRgPlane4[modIdxL[0].y][modIdxL[0].x];
	buf[1] = pRgPlane4[modIdxL[1].y][modIdxL[1].x];
	buf[2] = pRgPlane4[modIdxL[2].y][modIdxL[2].x];

	pRgPlane4[modIdxL[0].y][modIdxL[0].x] = pRgPlane3[modIdxB[0].y][modIdxB[0].x];
	pRgPlane4[modIdxL[1].y][modIdxL[1].x] = pRgPlane3[modIdxB[1].y][modIdxB[1].x];
	pRgPlane4[modIdxL[2].y][modIdxL[2].x] = pRgPlane3[modIdxB[2].y][modIdxB[2].x];

	pRgPlane3[modIdxB[0].y][modIdxB[0].x] = pRgPlane2[modIdxR[0].y][modIdxR[0].x];
	pRgPlane3[modIdxB[1].y][modIdxB[1].x] = pRgPlane2[modIdxR[1].y][modIdxR[1].x];
	pRgPlane3[modIdxB[2].y][modIdxB[2].x] = pRgPlane2[modIdxR[2].y][modIdxR[2].x];

	pRgPlane2[modIdxR[0].y][modIdxR[0].x] = pRgPlane1[modIdxT[0].y][modIdxT[0].x];
	pRgPlane2[modIdxR[1].y][modIdxR[1].x] = pRgPlane1[modIdxT[1].y][modIdxT[1].x];
	pRgPlane2[modIdxR[2].y][modIdxR[2].x] = pRgPlane1[modIdxT[2].y][modIdxT[2].x];

	pRgPlane1[modIdxT[0].y][modIdxT[0].x] = buf[0];
	pRgPlane1[modIdxT[1].y][modIdxT[1].x] = buf[1];
	pRgPlane1[modIdxT[2].y][modIdxT[2].x] = buf[2];
}

void Reset()
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			U[j][i] = 'w';
			D[j][i] = 'y';
			F[j][i] = 'r';
			B[j][i] = 'o';
			L[j][i] = 'g';
			R[j][i] = 'b';
		}
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N;

	for (int test_case = 0; test_case < N; test_case++)
	{
		Reset();

		int nTurn;
		string strCmd;
		cin >> nTurn;


		for (int idx = 0; idx < nTurn; idx++)
		{
			cin >> strCmd;
			TurnArray(strCmd);
		}

		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				cout << U[j][i];
			}
			cout << endl;
		}
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}