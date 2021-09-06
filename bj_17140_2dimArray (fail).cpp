#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <array>
#include <map>

using namespace std;

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

	bool isValidPoint(int _size)
	{
		return this->x >= 0 && this->y >= 0 && this->x < _size&& this->y < _size;
	}
};

#define abs(n) (n>0?n:-n)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
int N;
int r, c, k;
int s[100][100] = { 0, };
int r_max = 3, c_max = 3;


void initArr(int* pRg)
{
	for (int i = 0; i < 100; i++)
	{
		if (pRg[i] == 0)
		{
			break;
		}
		pRg[i] = 0;
	}
}

bool pred(const pair<int, int>& _lval, const pair<int, int>& _rval)
{
	if (_lval.second == _rval.second)
	{
		return _lval.first < _rval.first;
	}
	else
	{
		return _lval.second < _rval.second;
	}
}

void op_R()
{
	c_max = 0;
	for (int j = 0; j < 100; j++)
	{
		if (s[j][0] == 0)
		{
			break;
		}

		map<int, int> buf;
		for (int i = 0; i < 100; i++)
		{
			if (s[j][i] == 0)
			{
				continue;
			}

			if (buf.find(s[j][i]) == buf.end())
			{
				buf[s[j][i]] = 1;
			}
			else
			{
				buf[s[j][i]]++;
			}

			s[j][i] = 0;
		}

		vector<pair<int, int>> vcBuf(buf.begin(), buf.end());
		sort(vcBuf.begin(), vcBuf.end(), pred);
		int nSz = vcBuf.size() * 2;
		c_max = max(c_max, nSz);
		int idx = 0;
		for (auto it : vcBuf)
		{

			if (it.first == 0 || it.second == 0)
			{
				c_max -= 2;
				continue;
			}

			s[j][idx] = it.first;
			s[j][idx + 1] = it.second;
			idx += 2;
		}
	}
}

void op_C()
{
	r_max = 0;
	for (int i = 0; i < 100; i++)
	{
		if (s[0][i] == 0)
		{
			break;
		}

		map<int, int> buf;
		for (int j = 0; j < 100; j++)
		{
			if (s[j][i] == 0)
			{
				continue;
			}

			if (buf.find(s[j][i]) == buf.end())
			{
				buf[s[j][i]] = 1;
			}
			else
			{
				buf[s[j][i]]++;
			}

			s[j][i] = 0;
		}

		vector<pair<int, int>> vcBuf(buf.begin(), buf.end());
		sort(vcBuf.begin(), vcBuf.end(), pred);
		int nSz = vcBuf.size() * 2;
		r_max = max(r_max, nSz);

		int idx = 0;
		for (auto it : vcBuf)
		{
			if (it.first == 0 || it.second == 0)
			{
				r_max -= 2;
				continue;
			}

			s[idx][i] = it.first;
			s[idx + 1][i] = it.second;
			idx += 2;
		}
	}
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> r >> c >> k;
	r--;
	c--;

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			cin >> s[j][i];
		}
	}

	int time = 0;

	while (s[r][c] != k && time <= 100)
	{
		if (r_max < c_max)
		{
			op_C();
		}
		else
		{
			op_R();
		}


		time++;
	}

	if (time >= 100) time = -1;

	cout << time << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}