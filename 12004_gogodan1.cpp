#include <iostream>
//#include <cstdio> // should be annotation
//#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int idx, val;
bool bResult;

vector<int> vcNumber;
map<char, char> LUT;


void Init()
{
	idx = val = 0;
	bResult = false;

	vcNumber.clear();
}


void solve(int num)
{
	bResult = false;
	for (int i = 1; i < 10; i++)
	{
		if (num % i == 0)
		{
			int val1 = num / i;
			if (val1 > 0 && val1 < 10)
			{
				bResult = true;
			}
		}
	}
}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Init();

		cin >> val;

		solve(val);

		if (bResult)
		{
			cout << "#" << test_case << " Yes" << endl;
		}
		else
		{
			cout << "#" << test_case << " No" << endl;
		}
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}