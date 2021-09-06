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

enum DIRECTION { LEFT = 0, BOTTOM, RIGHT, TOP, DIRMAX = 4 };

// 좌, 하, 우, 상
int dx[4] = { -1,0,1, 0 };
int dy[4] = { 0,1,0,-1 };

vector<vector<int>> vcMap_Init;
vector<vector<int>> vcMap;
vector<int> vcMaxBlock;

bool isCorrectPos(int j, int i, int N, int M)
{
	return j >= 0 && i >= 0 && j < N&& i < M;
}

bool isCorrectPos(POINT& _pt, int Row, int Col)
{
	return isCorrectPos(_pt.y, _pt.x, Row, Col);
}

void Simul_Sub(DIRECTION _dir)
{
	int Rows = vcMap.size();
	int Cols = vcMap.at(0).size();

	vector<int> tmpBlocks;
	bool bMerge;
	if (_dir == LEFT)
	{
		for (int j = 0; j < Rows; j++)
		{
			tmpBlocks.clear();
			for (int i = 0; i < Cols; i++)
			{
				if (i == Cols - 1)
				{
					if (vcMap.at(j).at(i) > 0)
						tmpBlocks.push_back(vcMap.at(j).at(i));
					break;
				}

				if (vcMap.at(j).at(i) == 0)
				{
					continue;
				}

				bMerge = false;
				for (int i_Sub = i + 1; i_Sub < Cols; i_Sub++)
				{
					if (vcMap.at(j).at(i_Sub) > 0)
					{
						if (vcMap.at(j).at(i) == vcMap.at(j).at(i_Sub))
						{
							tmpBlocks.push_back(2 * vcMap.at(j).at(i));
							i = i_Sub;
							bMerge = true;
							break;
						}
					}
				}

				if (!bMerge)
				{
					tmpBlocks.push_back(vcMap.at(j).at(i));
				}
			}

			for (int i = 0; i < Cols; i++)
			{
				vcMap.at(j).at(i) = 0;
			}

			for (int i = 0; i < tmpBlocks.size(); i++)
			{
				vcMap.at(j).at(i) = tmpBlocks.at(i);
			}
		}
	}
	else if (_dir == RIGHT)
	{
		for (int j = 0; j < Rows; j++)
		{
			tmpBlocks.clear();
			for (int i = Cols - 1; i >= 0; i--)
			{
				if (i == 0)
				{
					if (vcMap.at(j).at(i) > 0)
						tmpBlocks.insert(tmpBlocks.begin(), vcMap.at(j).at(i));
					break;
				}

				if (vcMap.at(j).at(i) == 0)
				{
					continue;
				}

				bMerge = false;
				for (int i_Sub = i - 1; i_Sub >= 0; i_Sub--)
				{
					if (vcMap.at(j).at(i_Sub) > 0)
					{
						if (vcMap.at(j).at(i) == vcMap.at(j).at(i_Sub))
						{
							tmpBlocks.insert(tmpBlocks.begin(), 2 * vcMap.at(j).at(i));
							i = i_Sub;
							bMerge = true;
							break;
						}
					}
				}

				if (!bMerge)
				{
					tmpBlocks.insert(tmpBlocks.begin(), vcMap.at(j).at(i));
				}
			}

			for (int i = 0; i < Cols; i++)
			{
				vcMap.at(j).at(i) = 0;
			}

			for (int i = 0; i < tmpBlocks.size(); i++)
			{
				vcMap.at(j).at(i) = tmpBlocks.at(i);
			}
		}
	}
	else if (_dir == TOP)
	{
		for (int i = 0; i < Cols; i++)
		{
			tmpBlocks.clear();
			for (int j = 0; j < Rows; j++)
			{
				if (j == Rows - 1)
				{
					if (vcMap.at(j).at(i) > 0)
						tmpBlocks.push_back(vcMap.at(j).at(i));
					break;
				}

				if (vcMap.at(j).at(i) == 0)
				{
					continue;
				}

				bMerge = false;
				for (int j_Sub = 0; j_Sub < Rows; j_Sub++)
				{
					if (vcMap.at(j_Sub).at(i) > 0)
					{
						if (vcMap.at(j).at(i) == vcMap.at(j_Sub).at(i))
						{
							tmpBlocks.push_back(2 * vcMap.at(j).at(i));
							j = j_Sub;
							bMerge = true;
							break;
						}
					}
				}

				if (!bMerge)
				{
					tmpBlocks.push_back(vcMap.at(j).at(i));
				}
			}

			for (int j = 0; j < Rows; j++)
			{
				vcMap.at(j).at(i) = 0;
			}

			for (int j = 0; j < tmpBlocks.size(); j++)
			{
				vcMap.at(j).at(i) = tmpBlocks.at(j);
			}
		}
	}
	else if (_dir == BOTTOM)
	{
		for (int i = 0; i < Cols; i++)
		{
			tmpBlocks.clear();
			for (int j = Cols - 1; j >= 0; j--)
			{
				if (j == 0)
				{
					if (vcMap.at(j).at(i) > 0)
						tmpBlocks.insert(tmpBlocks.begin(), vcMap.at(j).at(i));
					break;
				}

				if (vcMap.at(j).at(i) == 0)
				{
					continue;
				}

				bMerge = false;
				for (int j_Sub = j - 1; j_Sub >= 0; j_Sub--)
				{
					if (vcMap.at(j_Sub).at(i) > 0)
					{
						if (vcMap.at(j).at(i) == vcMap.at(j_Sub).at(i))
						{
							tmpBlocks.insert(tmpBlocks.begin(), 2 * vcMap.at(j).at(i));
							j = j_Sub;
							bMerge = true;
							break;
						}
					}
				}

				if (!bMerge)
				{
					tmpBlocks.insert(tmpBlocks.begin(), vcMap.at(j).at(i));
				}
			}

			for (int j = 0; j < Rows; j++)
			{
				vcMap.at(j).at(i) = 0;
			}

			for (int j = 0; j < tmpBlocks.size(); j++)
			{
				vcMap.at(j).at(i) = tmpBlocks.at(j);
			}
		}
	}
	else
	{
		cout << "Error Dir" << endl;
	}
}

void Simul(vector<DIRECTION>& vcDir)
{
	vcMap = vcMap_Init;
	const int szDir = vcDir.size();
	for (int idx = 0; idx < szDir; idx++)
	{
		Simul_Sub(vcDir.at(idx));
	}
}

void SelDir(vector<DIRECTION>& vcDir)
{
	if (vcDir.size() >= 5)
	{
		Simul(vcDir);

		int Rows = vcMap.size();
		int Cols = vcMap.at(0).size();

		int nMaxVal = 0;
		for (int j = 0; j < Rows; j++)
		{
			for (int i = 0; i < Cols; i++)
			{
				if (nMaxVal < vcMap.at(j).at(i))
				{
					nMaxVal = vcMap.at(j).at(i);
				}
			}
		}

		vcMaxBlock.push_back(nMaxVal);
	}
	else
	{
		for (int dir = 0; dir < DIRMAX; dir++)
		{
			vcDir.push_back((DIRECTION)dir);
			SelDir(vcDir);
			vcDir.pop_back();
		}
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init Map
	int idx = 0, idx_sub = 0;
	int j, i;
	int N = 0;

	cin >> N;
	vcMap_Init.resize(N);
	for (j = 0; j < N; j++)
	{
		vcMap_Init.at(j).resize(N);
		for (i = 0; i < N; i++)
		{
			cin >> vcMap_Init.at(j).at(i);
		}
	}

	vector<DIRECTION> vcDir;
	SelDir(vcDir);

	int nMaxVal = *max_element(vcMaxBlock.begin(), vcMaxBlock.end());
	cout << nMaxVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}