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

using namespace std;


#define abs(n) (n>0?n:-n)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
int N, Q, szMap;
int A[64][64] = { 0, };
int Buf[64][64] = { 0, };
int Check[64][64] = { 0, };
int L[1000] = { 0, };
int max_area = 0;

// 상, 하, 좌, 우
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

int _pow(int x, int y)
{
	if (y == 0)
	{
		return 1;
	}

	//except sqrt

	int nRet = x;
	for (int idx = 1; idx < y; idx++)
	{
		nRet *= x;
	}

	return nRet;
}

bool isValidPoint(const int x, const int y)
{
	return x >= 0 && y >= 0 && x < szMap&& y < szMap;
}

void reduceIce()
{
	int sub_x, sub_y;
	for (int j = 0; j < szMap; j++)
	{
		for (int i = 0; i < szMap; i++)
		{
			int nCnt = 0;
			for (int dir = 0; dir < 4; dir++)
			{
				sub_x = i + dx[dir];
				sub_y = j + dy[dir];

				if (isValidPoint(sub_x, sub_y) && A[sub_y][sub_x] > 0)
				{
					nCnt++;
				}
			}

			if (nCnt < 3 && A[j][i] > 0)
			{
				Buf[j][i] = A[j][i] - 1;
			}
			else
			{
				Buf[j][i] = A[j][i];
			}
		}
	}

	for (int j = 0; j < szMap; j++)
	{
		for (int i = 0; i < szMap; i++)
		{
			A[j][i] = Buf[j][i];
		}
	}
}

void fireStrom(const int _L)
{
	const int nSubSize = _pow(2, _L);
	const int nStride = nSubSize / 2;

	for (int j = 0; j < szMap; j += nSubSize)
	{
		for (int i = 0; i < szMap; i += nSubSize)
		{
			// LT
			for (int j_sub = j; j_sub < j + nStride; j_sub++)
			{
				for (int i_sub = i; i_sub < i + nStride; i_sub++)
				{
					Buf[j_sub][i_sub] = A[j_sub][i_sub];
					A[j_sub][i_sub] = A[j_sub + nStride][i_sub];
				}
			}

			// LB
			for (int j_sub = j + nStride; j_sub < j + nSubSize; j_sub++)
			{
				for (int i_sub = i; i_sub < i + nStride; i_sub++)
				{
					A[j_sub][i_sub] = A[j_sub][i_sub + nStride];
				}
			}

			// RB
			for (int j_sub = j + nStride; j_sub < j + nSubSize; j_sub++)
			{
				for (int i_sub = i + nStride; i_sub < i + nSubSize; i_sub++)
				{
					A[j_sub][i_sub] = A[j_sub - nStride][i_sub];
				}
			}

			// RT
			for (int j_sub = j; j_sub < j + nStride; j_sub++)
			{
				for (int i_sub = i + nStride; i_sub < i + nSubSize; i_sub++)
				{
					A[j_sub][i_sub] = Buf[j_sub][i_sub - nStride];
				}
			}
		}
	}
}

void fireStrom_V2(const int _L)
{
	const int nSubSize = _pow(2, _L);
	const int nStride = nSubSize / 2;

	for (int j = 0; j < szMap; j += nSubSize)
	{
		for (int i = 0; i < szMap; i += nSubSize)
		{
			for (int j_sub = j; j_sub < j + nSubSize; j_sub++)
			{
				for (int i_sub = i; i_sub < i + nSubSize; i_sub++)
				{
					Buf[(i_sub - i) + j][abs((nSubSize - 1 - (j_sub - j))) + i] = A[j_sub][i_sub];
				}
			}

			for (int j_sub = j; j_sub < j + nSubSize; j_sub++)
			{
				for (int i_sub = i; i_sub < i + nSubSize; i_sub++)
				{
					A[j_sub][i_sub] = Buf[j_sub][i_sub];
				}
			}
		}
	}
}

int CalcAmountIce()
{
	int nCnt = 0;

	for (int j = 0; j < szMap; j++)
	{
		for (int i = 0; i < szMap; i++)
		{
			nCnt += A[j][i];
		}
	}

	return nCnt;
}

int CalcMaxConnection()
{
	int idx_x, idx_y;
	int sub_x, sub_y;
	for (int j = 0; j < szMap; j++)
	{
		for (int i = 0; i < szMap; i++)
		{
			if (Check[j][i] == 0 && A[j][i] > 0)
			{
				int nArea = 0;
				Check[j][i] = 1;
				queue<pair<int, int>> q;
				q.push(make_pair(i, j));
				while (q.size())
				{
					idx_x = q.front().first;
					idx_y = q.front().second;
					q.pop();
					nArea++;

					for (int dir = 0; dir < 4; dir++)
					{
						sub_x = idx_x + dx[dir];
						sub_y = idx_y + dy[dir];

						if (isValidPoint(sub_x, sub_y) && Check[sub_y][sub_x] == 0 && A[sub_y][sub_x] > 0)
						{
							Check[sub_y][sub_x] = 1;
							q.push(make_pair(sub_x, sub_y));
						}
					}
				}

				max_area = max(max_area, nArea);
			}
		}
	}

	return max_area;
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> Q;
	szMap = _pow(2, N);

	for (int j = 0; j < szMap; j++)
	{
		for (int i = 0; i < szMap; i++)
		{
			cin >> A[j][i];
		}
	}

	for (int idx = 0; idx < Q; idx++)
	{
		cin >> L[idx];
	}

	for (int idx = 0; idx < Q; idx++)
	{
		fireStrom_V2(L[idx]);
		reduceIce();
	}

	cout << CalcAmountIce() << endl;
	cout << CalcMaxConnection() << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}