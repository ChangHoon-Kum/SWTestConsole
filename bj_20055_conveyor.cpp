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

struct CONVEYOR
{
	int pos;
	int durability;
	bool isLoaded;

	CONVEYOR()
	{
		pos = durability = -1;
		isLoaded = false;
	}

	CONVEYOR(int _pos, int _durability, bool _isLoaded)
	{
		this->pos = _pos;
		this->durability = _durability;
		this->isLoaded = _isLoaded;
	}

	bool IsCanLoad()
	{
		return this->durability > 0 && this->isLoaded == false;
	}

	void Load()
	{
		this->durability--;
		this->isLoaded = true;
	}

	void Unload()
	{
		this->isLoaded = false;
	}
};

vector<CONVEYOR> vcConveyor;
//vector<int/*pos*/> vcRobot;

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init Map
	int idx = 0, idx_sub = 0;
	int N = 0, K = 0;
	cin >> N >> K;
	vcConveyor.resize(2 * N);
	const int posLoad = 0;
	const int posUnload = N - 1;
	{
		int nVal = 0;
		for (idx = 0; idx < 2 * N; idx++)
		{
			cin >> nVal;
			vcConveyor.at(idx) = CONVEYOR(idx, nVal, false);
		}
	}

	int nIter = 0;
	int nUnvalid = 0;
	do
	{
		nIter++;

		// 1. Conveyor Rotation
		{
			CONVEYOR last_elem = vcConveyor.at(2 * N - 1);
			for (idx = 2 * N - 1; idx > 0; idx--)
			{
				vcConveyor.at(idx) = vcConveyor.at(idx - 1);

				//if (vcConveyor.at(idx).pos == posUnload)
				{

				}
			}
			vcConveyor.at(0UL) = last_elem;
		}

		if (vcConveyor.at(posUnload).isLoaded)
		{
			/*for (idx_sub = vcRobot.size() - 1; idx_sub >= 0; idx_sub--)
			{
				if (vcRobot.at(idx_sub) == vcConveyor.at(posUnload).pos)
				{
					vcRobot.erase(vcRobot.begin() + idx_sub);
					break;
				}
			}*/
			vcConveyor.at(posUnload).Unload();
		}

		// 2. Robot Rotation
		/*for (idx = 0 ; idx < vcRobot.size(); idx++)
		{
			int pos_robot = vcRobot.at(idx);
			int pos_next = pos_robot + 1;
			if (pos_next >= 2*N)
			{
				pos_next -= 2 * N;
			}

			// Find index in vcConveyor
			int index_cur = -1, index_next = -1;
			for (idx_sub = 0 ; idx_sub < 2 * N ; idx_sub++)
			{
				if (index_cur < 0)
				{
					if (vcConveyor.at(idx_sub).pos == pos_robot)
					{
						index_cur = idx_sub;
					}
				}

				if (index_next < 0)
				{
					if (vcConveyor.at(idx_sub).pos == pos_next)
					{
						index_next = idx_sub;
					}
				}

				if (index_cur>=0 && index_next>=0)
				{
					break;
				}
			}

			// Check can move
			CONVEYOR cur = vcConveyor.at(index_cur);
			CONVEYOR nxt = vcConveyor.at(index_next);
			if (vcConveyor.at(index_next).IsCanLoad())
			{
				cur.Unload();
				nxt.Load();

				if (index_next == posUnload)
				{
					nxt.Unload();
					vcRobot.erase(vcRobot.begin() + idx);
				}
				else
				{
					vcRobot.at(idx) = nxt.pos;
				}

				vcConveyor.at(index_cur) = cur;
				vcConveyor.at(index_next) = nxt;
			}
		}*/
		for (idx = 2 * N - 1; idx >= 0; idx--)
		{
			idx_sub = idx - 1;
			if (idx_sub < 0) idx_sub += 2 * N;

			if (vcConveyor.at(idx_sub).isLoaded)
			{
				CONVEYOR cur = vcConveyor.at(idx_sub);
				CONVEYOR nxt = vcConveyor.at(idx);

				if (vcConveyor.at(idx).IsCanLoad())
				{
					cur.Unload();
					nxt.Load();

					if (idx == posUnload)
					{
						nxt.Unload();
					}

					vcConveyor.at(idx_sub) = cur;
					vcConveyor.at(idx) = nxt;
				}
			}
		}


		// 3. Robot Loading
		if (vcConveyor.at(posLoad).IsCanLoad())
		{
			//vcRobot.push_back(vcConveyor.at(posLoad).pos);
			vcConveyor.at(posLoad).Load();
		}


		// 4. Check availability
		int nUnvalid_Sub = 0;
		for (idx = 0; idx < 2 * N; idx++)
		{
			if (vcConveyor.at(idx).durability <= 0)
			{
				nUnvalid_Sub++;
			}
		}
		nUnvalid = nUnvalid_Sub;
	} while (nUnvalid < K);


	cout << nIter << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}