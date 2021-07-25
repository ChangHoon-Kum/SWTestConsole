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

	string GetString()
	{
		char buffer[100];
		snprintf(buffer, 100, "(%d, %d) ", x, y);
		return string(buffer);
	}
};
vector<vector<int>> vcMap;


// 좌, 하, 우, 상
int dx[4] = { -1,0,1, };
int dy[4] = { 0,1,0,-1 };

double dProbKernel[4][5][5] =
{
	{
		{0., 0.,  0.02, 0., 0.},
		{0., 0.1, 0.07, 0.01, 0.},
		{0.05, -1.,  0., 0., 0.},
		{0., 0.1, 0.07, 0.01, 0.},
		{0., 0.,  0.02, 0., 0.}
	},
	{
		{0., 0., 0., 0., 0.},
		{0., 0.01, 0., 0.01, 0.},
		{0.02, 0.07,  0., 0.07, 0.02},
		{0., 0.1, -1., 0.1, 0.},
		{0., 0., 0.05, 0., 0.}
	},
	{
		{0., 0., 0.02, 0., 0.},
		{0., 0.01, 0.07, 0.1, 0.},
		{0., 0,  0., -1., 0.05},
		{0., 0.01, 0.07, 0.1, 0.},
		{0., 0., 0.02, 0., 0.}
	},
	{
		{0., 0., 0.05, 0., 0.},
		{0., 0.1, -1., 0.1, 0.},
		{0.02, 0.07,  0., 0.07, 0.02},
		{0., 0.01, 0., 0.01, 0.},
		{0., 0., 0., 0., 0.}
	}
};

int step;
int stribe;
int stribe_sub;
int dir;

int sand_out;

void Init()
{
	vcMap.clear();
	//vcMapDst.clear();

	step = 0;
	stribe = 1;
	stribe_sub = 0;
	dir = 0;
	sand_out = 0;
}


void solve(int num)
{
	
}


int main(int argc, char** argv)
{
	int test_case;
	int T;
	int N; // map size
	
	//freopen("input.txt", "r", stdin);

	Init();
	cin >> N;

	vcMap.resize(N);
	for (int idx = 0; idx < N; idx++)
	{
		vcMap.at(idx).resize(N);
	}

	int temp = 0;
	string line;
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> temp;
			vcMap.at(j).at(i) = temp;
		}
	}

	//0 based index
	POINT pt(floor(N / 2.), floor(N / 2.));

	bool bFinish = false;
	while (!bFinish)
	{
		POINT ptMoved(pt.x + dx[dir], pt.y + dy[dir]);

		int val = vcMap.at(ptMoved.y).at(ptMoved.x);
		int val_remain = val;

		POINT ptAlpha;
		for (int j = 0 ; j < 5 ; j++)
		{
			for (int i = 0 ; i < 5 ; i++)
			{
				double dProb = dProbKernel[dir][j][i];
				int target_x = ptMoved.x + i - 2;
				int target_y = ptMoved.y + j - 2;
				
				if (dProb < 0.)
				{
					ptAlpha.x = target_x;
					ptAlpha.y = target_y;
					continue;
				}

				int SpreadVal = floor(val * dProb);

				if (target_x < 0 || target_y < 0 || target_x >= N || target_y >= N)
				{
					sand_out += SpreadVal;
				}
				else
				{
					vcMap.at(target_y).at(target_x) += SpreadVal;
				}

				val_remain -= SpreadVal;
			}
		}

		if (ptAlpha.x < 0 || ptAlpha.y < 0 || ptAlpha.x >= N || ptAlpha.y >= N)
		{
			sand_out += val_remain;
		}
		else
		{
			vcMap.at(ptAlpha.y).at(ptAlpha.x) += val_remain;
		}

		if (ptMoved.x == 0 && ptMoved.y == 0)
		{
			bFinish = true;
		}
		else
		{
			stribe_sub++;
			if (stribe_sub >= stribe)
			{
				stribe_sub = 0;
				step++;
				dir++;
				dir = dir % 4;

				if (step % 2 == 0)
				{
					stribe++;
				}
			}

			pt = ptMoved;
		}
	}
	
	cout << sand_out << endl;
	
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}