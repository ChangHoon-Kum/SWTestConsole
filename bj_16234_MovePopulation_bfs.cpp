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
int N, L, R;
int A[50][50] = { 0, };
int Check[50][50] = { 0, };


// 상, 하, 좌, 우
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

bool isValidPoint(const int x, const int y)
{
	return x >= 0 && y >= 0 && x < N&& y < N;
}

int MovePopulation()
{
	int epoch = 0;
	bool bMoved = false;
	do
	{
		int idx_x, idx_y;
		int sub_x, sub_y;
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				Check[j][i] = 0;
			}
		}
		bMoved = false;

		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				int nSum = 0;
				if (Check[j][i] == 0)
				{
					int nArea = 0;
					Check[j][i] = 1;
					queue<pair<int, int>> q;
					q.push(make_pair(i, j));
					vector<pair<int, int>> vc;
					vc.push_back(make_pair(i, j));

					while (q.size())
					{
						idx_x = q.front().first;
						idx_y = q.front().second;
						q.pop();
						nArea++;

						int nPeople = A[idx_y][idx_x];
						nSum += nPeople;

						for (int dir = 0; dir < 4; dir++)
						{
							sub_x = idx_x + dx[dir];
							sub_y = idx_y + dy[dir];

							if (isValidPoint(sub_x, sub_y) && Check[sub_y][sub_x] == 0
								&& abs((A[sub_y][sub_x] - nPeople)) >= L && abs((A[sub_y][sub_x] - nPeople)) <= R)
							{
								Check[sub_y][sub_x] = 1;
								q.push(make_pair(sub_x, sub_y));
								vc.push_back(make_pair(sub_x, sub_y));
							}
						}
					}

					if (vc.size() > 1)
					{
						int nNewPeople = nSum / (double)vc.size();

						for (auto& it : vc)
						{
							A[it.second][it.first] = nNewPeople;
						}

						bMoved = true;
					}
				}
			}
		}

		if (bMoved)
		{
			epoch++;
		}

	} while (bMoved);



	return epoch;
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> L >> R;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> A[j][i];
		}
	}




	cout << MovePopulation() << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}