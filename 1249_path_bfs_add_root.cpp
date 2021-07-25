#include <iostream>
//#include <cstdio> // should be annotation
//#include <stdio.h> // should be annotation

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
vector<vector<pair<int, vector<POINT>>>> vcMapDst;
queue<pair<int, int>> q;

// 상, 하, 좌, 우
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

void Init()
{
	vcMap.clear();
	vcMapDst.clear();

	while (q.size())
	{
		q.pop();
	}
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
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Init();

		cin >> N;
		vcMap.resize(N);
		vcMapDst.resize(N);
		for (int idx = 0; idx < N; idx++)
		{
			vcMap.at(idx).resize(N);
			vcMapDst.at(idx).resize(N);
		}

		int temp = 0;
		string line;
		for (int j = 0; j < N; j++)
		{
			cin >> line;
			for (int i = 0; i < N; i++)
			{
				temp = line[i] - '0';
				vcMap.at(j).at(i) = temp;
				vcMapDst.at(j).at(i).first = 10000;
			}
		}

		vcMapDst.at(0).at(0).first = vcMap.at(0).at(0);
		//vcMapDst.at(0).at(0).second.push_back(POINT(0, 0));
		q.push(make_pair(0, 0));

		int idx_x = 0;
		int idx_y = 0;

		while (q.size())
		{
			idx_x = q.front().first;
			idx_y = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++)
			{
				int next_x = idx_x + dx[i];
				int next_y = idx_y + dy[i];

				if (next_x < 0 || next_y < 0 || next_x >= N || next_y >= N)
				{
					continue;
				}

				if (vcMapDst.at(next_y).at(next_x).first > vcMapDst.at(idx_y).at(idx_x).first + vcMap.at(next_y).at(next_x))
				{
					vcMapDst.at(next_y).at(next_x).first = vcMapDst.at(idx_y).at(idx_x).first + vcMap.at(next_y).at(next_x);
					vcMapDst.at(next_y).at(next_x).second.assign(vcMapDst.at(idx_y).at(idx_x).second.begin(), vcMapDst.at(idx_y).at(idx_x).second.end());
					vcMapDst.at(next_y).at(next_x).second.push_back(POINT(idx_x, idx_y));
					q.push(make_pair(next_x, next_y));
				}
			}
		}

		cout << "#" << test_case << " " << vcMapDst.at(N - 1).at(N - 1).first << endl;
		for (auto it : vcMapDst.at(N - 1).at(N - 1).second)
		{
			cout << it.GetString();
		}
		cout << endl;
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}