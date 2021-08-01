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

enum DIRECTION { TOP = 0, TOPLEFT, LEFT, BOTTOMLEFT, BOTTOM, BOTTOMRIGHT, RIGHT, TOPRIGHT, DIRMAX = 8 };

//      TOP = 0, TOPLEFT, LEFT, BOTTOMLEFT, BOTTOM, BOTTOMRIGHT, RIGHT, TOPRIGHT
int dx[8] = { 0,  -1,      -1,      -1,       0,         1,        1,       1 };
int dy[8] = { -1, -1,       0,       1,       1,         1,        0,      -1 };

#define RC_MAX 4

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

bool isCorrectPos(POINT& val)
{
	return val.x >= 0 && val.y >= 0 && val.x < RC_MAX&& val.y < RC_MAX;
}

struct BASIC
{
	POINT pos;
	DIRECTION dir;
};

struct FISH : BASIC
{
	int fishnum;

	FISH() {};

	FISH(int _num, int _dir, POINT pt)
	{
		this->fishnum = _num;
		this->dir = (DIRECTION)_dir;
		this->pos = pt;
	}
};

struct SHARK : BASIC
{
	int maxfish = 0;
	int space[RC_MAX][RC_MAX] = { 0, }; // noted fishnum, 0 means EMPTY
	map<int/*fishnum*/, FISH> mapFish;

	SHARK()
	{
		pos = POINT(0, 0);
		maxfish = 0;
	}

	void eatFish(POINT ptFish)
	{
		FISH tmpFish = mapFish[space[ptFish.y][ptFish.x]];

		this->pos = tmpFish.pos;
		this->dir = tmpFish.dir;
		this->maxfish += tmpFish.fishnum;
		this->space[tmpFish.pos.y][tmpFish.pos.x] = 0;
		this->mapFish.erase(tmpFish.fishnum);
	}

	void eatFish(FISH _fish)
	{
		this->pos = _fish.pos;
		this->dir = _fish.dir;
		this->maxfish += _fish.fishnum;
		this->space[_fish.pos.y][_fish.pos.x] = 0;
		this->mapFish.erase(_fish.fishnum);
	}

	vector<POINT> getNextCoordinate()
	{
		vector<POINT> vcCoordinate;

		POINT pt(this->pos.x + dx[this->dir], this->pos.y + dy[this->dir]);
		while (isCorrectPos(pt))
		{
			if (space[pt.y][pt.x] > 0)
				vcCoordinate.push_back(pt);

			pt.x += dx[this->dir];
			pt.y += dy[this->dir];
		}

		return vcCoordinate;
	}

	vector<SHARK> getNextStep()
	{
		vector<POINT> vcCoordinate = getNextCoordinate();
		vector<SHARK> vcSharkCandidate;

		for (int idx = 0; idx < vcCoordinate.size(); idx++)
		{
			SHARK tmpShark = *this;
			tmpShark.pos = vcCoordinate.at(idx);
			FISH ateFISH = tmpShark.mapFish[space[tmpShark.pos.y][tmpShark.pos.x]];
			tmpShark.eatFish(ateFISH);

			vcSharkCandidate.push_back(tmpShark);
		}

		return vcSharkCandidate;
	}

	void moveFish(int _fishnum)
	{
		if (this->mapFish.find(_fishnum) == mapFish.end())
		{
			return;
		}

		FISH curfish = this->mapFish[_fishnum];

		for (int dir_idx = 0; dir_idx < DIRMAX; dir_idx++)
		{
			int cur_dir = curfish.dir + dir_idx;
			cur_dir = cur_dir % DIRMAX;
			POINT nxtPos(curfish.pos.x + dx[cur_dir], curfish.pos.y + dy[cur_dir]);

			if (isCorrectPos(nxtPos) && (nxtPos != this->pos))
			{
				//Can Move
				if (this->space[nxtPos.y][nxtPos.x] <= 0) //Empty space
				{
					this->space[curfish.pos.y][curfish.pos.x] = 0;
					this->space[nxtPos.y][nxtPos.x] = curfish.fishnum;
					curfish.pos = nxtPos;
					curfish.dir = (DIRECTION)cur_dir;
					this->mapFish[curfish.fishnum] = curfish;
				}
				else if (this->space[nxtPos.y][nxtPos.x] > 0 && this->space[nxtPos.y][nxtPos.x] <= 16 && this->space[nxtPos.y][nxtPos.x] != curfish.fishnum)//swap with other fish
				{
					FISH nxtFISH;
					if (this->mapFish.find(space[nxtPos.y][nxtPos.x]) != mapFish.end())
					{
						nxtFISH = this->mapFish[space[nxtPos.y][nxtPos.x]];
					}

					this->space[nxtPos.y][nxtPos.x] = curfish.fishnum;
					this->space[curfish.pos.y][curfish.pos.x] = nxtFISH.fishnum;
					nxtFISH.pos = curfish.pos;
					curfish.pos = nxtPos;
					curfish.dir = (DIRECTION)cur_dir;
					this->mapFish[curfish.fishnum] = curfish;
					this->mapFish[nxtFISH.fishnum] = nxtFISH;
				}

				break;
			}
		}
	}

	void moveFishALL()
	{
		for (int idx = 1; idx <= 16; idx++)
		{
			moveFish(idx);
		}
	}

	void CheckAbnormal()
	{
		for (auto it : this->mapFish)
		{
			if (it.first < 0)
			{
				cout << "map abnormal" << endl;
			}
		}

		for (int j = 0; j < RC_MAX; j++)
		{
			for (int i = 0; i < RC_MAX; i++)
			{
				if (this->space[j][i] < 0)
				{
					cout << "map abnormal" << endl;
				}
			}
		}
	}
};

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init Fish, Shark info
	vector<SHARK> vcShark;
	vector<SHARK> vcSharkFinal;
	vector<int> vcMaxFishVal;
	{
		SHARK InitShark;
		InitShark.pos.x = 0;
		InitShark.pos.y = 0;

		int fnum = 0;
		int fdir = 0;
		FISH tempFish;
		for (int j = 0; j < RC_MAX; j++)
		{
			for (int i = 0; i < RC_MAX; i++)
			{
				cin >> fnum;
				cin >> fdir;
				tempFish.fishnum = fnum;
				tempFish.dir = (DIRECTION)(fdir - 1);
				tempFish.pos.x = i;
				tempFish.pos.y = j;
				InitShark.space[j][i] = fnum;
				InitShark.mapFish[fnum] = tempFish;
			}
		}

		InitShark.eatFish(POINT(0, 0));

		vcShark.push_back(InitShark);
	}

	while (vcShark.size() > 0)
	{
		SHARK curShark = vcShark.at(vcShark.size() - 1);
		vcShark.pop_back();

		curShark.moveFishALL();
		vector<SHARK> vcCand = curShark.getNextStep();
		curShark.CheckAbnormal();

		if (vcCand.size() == 0UL)
		{
			vcMaxFishVal.push_back(curShark.maxfish);
			vcSharkFinal.push_back(curShark);
		}
		else
		{
			vcShark.insert(vcShark.end(), vcCand.begin(), vcCand.end());
		}
	}

	int nMaxVal = *max_element(vcMaxFishVal.begin(), vcMaxFishVal.end());


	cout << nMaxVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}