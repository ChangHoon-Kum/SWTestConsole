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

// 좌, 하, 우, 상
int dx[4] = { -1,0,1, 0 };
int dy[4] = { 0,1,0,-1 };

vector<vector<int>> vcA; // 인구
vector<vector<int>> vcMap; // 선거구 나눈 버퍼



bool isCorrectPos(int j, int i, int N, int M)
{
	return j >= 0 && i >= 0 && j < N&& i < M;
}

bool isCorrectPos(POINT& _pt, int N)
{
	return isCorrectPos(_pt.y, _pt.x, N, N);
}

void mapClear(int _N)
{
	for (int j = 0; j < _N; j++)
	{
		for (int i = 0; i < _N; i++)
		{
			vcMap.at(j).at(i) = 0;
		}
	}
}


int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init Map
	int idx = 0, idx_sub = 0;
	int j, i, d1, d2, j_sub, i_sub;
	int N = 0;
	cin >> N;
	vcA.resize(N);
	vcMap.resize(N);
	for (int j = 0; j < N; j++)
	{
		vcA.resize(N);
		vcMap.resize(N);
		for (int i = 0; i < N; i++)
		{
			vcA.at(j).resize(N);
			vcMap.at(j).resize(N);

			cin >> vcA.at(j).at(i);
			vcMap.at(j).at(i) = 0;
		}
	}

	POINT Border[4];
	int dir;
	vector<int> vcDiff;
	for (j = 1; j < N - 1; j++)
	{
		for (i = 0; i < N - 2; i++)
		{
			for (d1 = 1; j - d1 >= 0; d1++)
			{
				for (d2 = 1; j + d2 < N && i + d1 + d2 < N; d2++)
				{
					Border[0] = POINT(i, j);
					Border[1] = POINT(i + d1, j - d1);
					Border[2] = POINT(i + d2, j + d2);
					Border[3] = POINT(i + d1 + d2, j - d1 + d2);

					if (isCorrectPos(Border[0], N) && isCorrectPos(Border[1], N) && isCorrectPos(Border[2], N) && isCorrectPos(Border[3], N))
					{
						mapClear(N);

						// fill Border
						vcMap.at(Border[0].y).at(Border[0].x) = 5;
						vcMap.at(Border[1].y).at(Border[1].x) = 5;
						vcMap.at(Border[2].y).at(Border[2].x) = 5;
						vcMap.at(Border[3].y).at(Border[3].x) = 5;
						POINT TmpPt;
						for (idx_sub = 1; idx_sub < d1; idx_sub++)
						{
							TmpPt.x = Border[0].x + idx_sub;
							TmpPt.y = Border[0].y - idx_sub;
							vcMap.at(TmpPt.y).at(TmpPt.x) = 5;
						}
						for (idx_sub = 1; idx_sub < d2; idx_sub++)
						{
							TmpPt.x = Border[0].x + idx_sub;
							TmpPt.y = Border[0].y + idx_sub;
							vcMap.at(TmpPt.y).at(TmpPt.x) = 5;
						}
						for (idx_sub = 1; idx_sub < d2; idx_sub++)
						{
							TmpPt.x = Border[1].x + idx_sub;
							TmpPt.y = Border[1].y + idx_sub;
							vcMap.at(TmpPt.y).at(TmpPt.x) = 5;
						}
						for (idx_sub = 1; idx_sub < d1; idx_sub++)
						{
							TmpPt.x = Border[2].x + idx_sub;
							TmpPt.y = Border[2].y - idx_sub;
							vcMap.at(TmpPt.y).at(TmpPt.x) = 5;
						}

						//fill Area1
						vcMap.at(0).at(0) = 1;
						vector<POINT> spread1;
						spread1.push_back(POINT(0, 0));
						while (spread1.size() > 0UL)
						{
							POINT ptSeed = spread1.at(0);
							spread1.erase(spread1.begin());

							for (dir = 0; dir < 4; dir++)
							{
								POINT ptSeedTmp = ptSeed;
								ptSeedTmp.x += dx[dir];
								ptSeedTmp.y += dy[dir];

								if (!isCorrectPos(ptSeedTmp, N))
								{
									continue;
								}

								if (vcMap.at(ptSeedTmp.y).at(ptSeedTmp.x) == 0 && ptSeedTmp.y < j && ptSeedTmp.x <= i + d1)
								{
									vcMap.at(ptSeedTmp.y).at(ptSeedTmp.x) = 1;
									spread1.push_back(ptSeedTmp);
								}
							}
						}

						//fill Area2
						vcMap.at(0).at(N - 1) = 2;
						vector<POINT> spread2;
						spread2.push_back(POINT(N - 1, 0));
						while (spread2.size() > 0UL)
						{
							POINT ptSeed = spread2.at(0);
							spread2.erase(spread2.begin());

							for (dir = 0; dir < 4; dir++)
							{
								POINT ptSeedTmp = ptSeed;
								ptSeedTmp.x += dx[dir];
								ptSeedTmp.y += dy[dir];

								if (!isCorrectPos(ptSeedTmp, N))
								{
									continue;
								}

								if (vcMap.at(ptSeedTmp.y).at(ptSeedTmp.x) == 0 && ptSeedTmp.y <= Border[3].y && ptSeedTmp.x > i + d1)
								{
									vcMap.at(ptSeedTmp.y).at(ptSeedTmp.x) = 2;
									spread2.push_back(ptSeedTmp);
								}
							}
						}

						//fill Area3
						vcMap.at(N - 1).at(0) = 3;
						vector<POINT> spread3;
						spread3.push_back(POINT(0, N - 1));
						while (spread3.size() > 0UL)
						{
							POINT ptSeed = spread3.at(0);
							spread3.erase(spread3.begin());

							for (dir = 0; dir < 4; dir++)
							{
								POINT ptSeedTmp = ptSeed;
								ptSeedTmp.x += dx[dir];
								ptSeedTmp.y += dy[dir];

								if (!isCorrectPos(ptSeedTmp, N))
								{
									continue;
								}

								if (vcMap.at(ptSeedTmp.y).at(ptSeedTmp.x) == 0 && ptSeedTmp.y >= j && ptSeedTmp.x < i + d2)
								{
									vcMap.at(ptSeedTmp.y).at(ptSeedTmp.x) = 3;
									spread3.push_back(ptSeedTmp);
								}
							}
						}

						//fill Area4
						vcMap.at(N - 1).at(N - 1) = 4;
						vector<POINT> spread4;
						spread4.push_back(POINT(N - 1, N - 1));
						while (spread4.size() > 0UL)
						{
							POINT ptSeed = spread4.at(0);
							spread4.erase(spread4.begin());

							for (dir = 0; dir < 4; dir++)
							{
								POINT ptSeedTmp = ptSeed;
								ptSeedTmp.x += dx[dir];
								ptSeedTmp.y += dy[dir];

								if (!isCorrectPos(ptSeedTmp, N))
								{
									continue;
								}

								if (vcMap.at(ptSeedTmp.y).at(ptSeedTmp.x) == 0 && ptSeedTmp.y > Border[3].y && ptSeedTmp.x >= i + d2)
								{
									vcMap.at(ptSeedTmp.y).at(ptSeedTmp.x) = 4;
									spread4.push_back(ptSeedTmp);
								}
							}
						}

						//fill Area5
						for (j_sub = 0; j_sub < N; j_sub++)
						{
							for (i_sub = 0; i_sub < N; i_sub++)
							{
								if (vcMap.at(j_sub).at(i_sub) == 0)
								{
									vcMap.at(j_sub).at(i_sub) = 5;
								}
							}
						}

						//cout << vcMap.at(0).at(0) << vcMap.at(0).at(1) << vcMap.at(0).at(2) << vcMap.at(0).at(3) << vcMap.at(0).at(4) << vcMap.at(0).at(5) << endl;
						//cout << vcMap.at(1).at(0) << vcMap.at(1).at(1) << vcMap.at(1).at(2) << vcMap.at(1).at(3) << vcMap.at(1).at(4) << vcMap.at(1).at(5) << endl;
						//cout << vcMap.at(2).at(0) << vcMap.at(2).at(1) << vcMap.at(2).at(2) << vcMap.at(2).at(3) << vcMap.at(2).at(4) << vcMap.at(2).at(5) << endl;
						//cout << vcMap.at(3).at(0) << vcMap.at(3).at(1) << vcMap.at(3).at(2) << vcMap.at(3).at(3) << vcMap.at(3).at(4) << vcMap.at(3).at(5) << endl;
						//cout << vcMap.at(4).at(0) << vcMap.at(4).at(1) << vcMap.at(4).at(2) << vcMap.at(4).at(3) << vcMap.at(4).at(4) << vcMap.at(4).at(5) << endl;
						//cout << vcMap.at(5).at(0) << vcMap.at(5).at(1) << vcMap.at(5).at(2) << vcMap.at(5).at(3) << vcMap.at(5).at(4) << vcMap.at(5).at(5) << endl;
						//cout << endl;

						// cal sum Area
						vector<int> nSum;
						nSum.resize(6);
						nSum.at(0) = 0;
						nSum.at(1) = 0;
						nSum.at(2) = 0;
						nSum.at(3) = 0;
						nSum.at(4) = 0;
						nSum.at(5) = 0;
						for (j_sub = 0; j_sub < N; j_sub++)
						{
							for (i_sub = 0; i_sub < N; i_sub++)
							{
								int nFlag = vcMap.at(j_sub).at(i_sub);
								nSum.at(nFlag) += vcA.at(j_sub).at(i_sub);
							}
						}

						int nMax = *max_element(nSum.begin() + 1, nSum.end());
						int nMin = *min_element(nSum.begin() + 1, nSum.end());

						vcDiff.push_back(nMax - nMin);
					}
				}
			}
		}
	}


	int nMinVal = *min_element(vcDiff.begin(), vcDiff.end());

	cout << nMinVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}