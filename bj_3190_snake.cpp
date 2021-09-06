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

int N, K, L;

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

enum DIRECTION { TOP = 0, RIGHT, BTM, LEFT, DIR_MAX };

//			TOP, RIGHT, BTM, LEFT
int dx[DIR_MAX] = { 0, 1, 0,-1 };
int dy[DIR_MAX] = { -1,0, 1, 0 };



vector<POINT> vcApple;
vector<std::pair<int, char>> vcCmd;

struct SNAKE
{
	DIRECTION dir;
	vector<POINT> vcPos;
	int time;

	SNAKE()
	{
		dir = RIGHT;
		vcPos.resize(1);
		vcPos.at(0) = POINT(0, 0);
		time = 0;
	}

	void Turn_CW()
	{
		dir = DIRECTION(dir + 1);
		if (dir >= DIR_MAX)
		{
			dir = DIRECTION(dir - DIR_MAX);
		}
	}

	void Turn_CCW()
	{
		dir = DIRECTION(dir - 1);
		if (dir < 0)
		{
			dir = DIRECTION(dir + DIR_MAX);
		}
	}

	// true: can move, false: exit game
	bool CheckBodyEat(const POINT _pt)
	{
		if (this->vcPos.size() < 4UL)
		{
			return true;
		}

		for (int idx = 3; idx < this->vcPos.size(); idx++)
		{
			if (vcPos.at(idx).x == _pt.x && vcPos.at(idx).y == _pt.y)
			{
				return false;
			}
		}

		return true;
	}

	// exist: valid index of apples, otherwise: -1
	int CheckApple(const POINT _pt)
	{
		for (int idx = 0; idx < vcApple.size(); idx++)
		{
			if (vcApple.at(idx).x == _pt.x && vcApple.at(idx).y == _pt.y)
			{
				return idx;
			}
		}

		return -1;
	}

	bool Move_Sub()
	{
		POINT nextPos(vcPos.at(0).x + dx[dir], vcPos.at(0).y + dy[dir]);

		if (!nextPos.isValidPoint())
		{
			return false;
		}

		if (!CheckBodyEat(nextPos))
		{
			return false;
		}

		int AppleIdx = CheckApple(nextPos);
		if (AppleIdx >= 0)
		{
			vcApple.erase(vcApple.begin() + AppleIdx);

			vcPos.insert(vcPos.begin(), nextPos);
		}
		else
		{
			vcPos.insert(vcPos.begin(), nextPos);
			vcPos.pop_back();
		}

		return true;
	}

	bool Move(std::vector<std::pair<int, char>>& _moveInfo)
	{
		if (time >= 10000)
		{
			return false;
		}

		if (_moveInfo.size() > 0UL)
		{
			if (time == _moveInfo.at(0).first)
			{
				if (_moveInfo.at(0).second == 'D')
				{
					Turn_CW();
				}
				else // if ('L')
				{
					Turn_CCW();
				}

				_moveInfo.erase(_moveInfo.begin());
			}
		}

		time++;
		return Move_Sub();
	}
};


int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> K;
	vcApple.resize(K);


	SNAKE snake;

	for (int idx = 0; idx < K; idx++)
	{
		cin >> vcApple.at(idx).y >> vcApple.at(idx).x;
		vcApple.at(idx).x--;
		vcApple.at(idx).y--;
	}

	cin >> L;
	vcCmd.resize(L);
	for (int idx = 0; idx < L; idx++)
	{
		cin >> vcCmd.at(idx).first >> vcCmd.at(idx).second;
	}

	while (snake.Move(vcCmd));

	cout << snake.time << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}