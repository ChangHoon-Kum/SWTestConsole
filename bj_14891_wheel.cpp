#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>

using namespace std;

enum DIRECTION { LEFT = 0, BOTTOM, RIGHT, TOP, DIRMAX = 4 };

int wheel[4][8];
vector<pair<int/*idx*/, int/*dir*/>> vcOp;

// dir: 1 = cw, -1 = ccw
void shift(int* arr, int dir)
{
	int temp;
	if (dir == 1)
	{
		temp = arr[7];
		for (int i = 7; i > 0; i--)
		{
			arr[i] = arr[i - 1];
		}
		arr[0] = temp;
	}
	else
	{
		temp = arr[0];
		for (int i = 0; i < 7; i++)
		{
			arr[i] = arr[i + 1];
		}
		arr[7] = temp;
	}
}

void turn_wheel(int sel_wheel, int dir, bool bCheckLeft, bool bCheckRight)
{
	const int left_wheel = sel_wheel - 1;
	const int right_wheel = sel_wheel + 1;

	bool bLeft = false, bRight = false;

	// Left
	if (bCheckLeft && left_wheel >= 0)
	{
		if (wheel[left_wheel][2] != wheel[sel_wheel][6])
		{
			bLeft = true;
		}
	}

	// Right
	if (bCheckRight && right_wheel < 4)
	{
		if (wheel[sel_wheel][2] != wheel[right_wheel][6])
		{
			bRight = true;
		}
	}

	shift(wheel[sel_wheel], dir);
	if (bLeft) turn_wheel(left_wheel, dir * -1, true, false);
	if (bRight) turn_wheel(right_wheel, dir * -1, false, true);
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	//Init
	{
		int temp = 0;
		string line;
		for (int idx = 0; idx < 4; idx++)
		{
			cin >> line;
			for (int idx_sub = 0; idx_sub < 8; idx_sub++)
			{
				temp = line[idx_sub] - '0';
				wheel[idx][idx_sub] = temp;
			}
		}
	}

	int K = 0;
	{
		cin >> K;
		int wheel_idx, wheel_dir;

		for (int idx = 0; idx < K; idx++)
		{
			cin >> wheel_idx >> wheel_dir;
			wheel_idx--; // zero based
			vcOp.push_back(make_pair(wheel_idx, wheel_dir));
		}
	}

	//const int left_cn = 6;
	//const int right_cn = 2;
	for (int idx = 0; idx < K; idx++)
	{
		//cout << idx+1 << "trial" << endl;
		//cout << vcOp.at(idx).first << "," << vcOp.at(idx).second << endl;
		const int sel_wheel = vcOp.at(idx).first;

		turn_wheel(sel_wheel, vcOp.at(idx).second, true, true);

		/*for (int j = 0 ; j < 4 ; j++)
		{
			for (int i = 0 ;  i < 8 ; i++)
			{
				cout << wheel[j][i];
			}
			cout << endl;
		}
		cout << endl;*/
	}


	// Cal Score
	int nVal = 0;
	int nUnit = 1;
	for (int idx = 0; idx < 4; idx++)
	{
		if (wheel[idx][0] == 1) // S
		{
			nVal += nUnit;
		}
		nUnit *= 2;
	}
	cout << nVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}