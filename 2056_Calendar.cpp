#include<iostream>
//#include <cstdio> // should be annotation
//#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>

using namespace std;

int idx, val, Year, Month, Day;
vector<int> vcNumber;

int nMonthEnd[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
std::string Date;

void print(int t, std::string& result)
{
	cout << "#" << t << " " << result << endl;
}

void Init()
{
	idx = val = Year = Month = Day = 0;
	vcNumber.clear();
	Date = "-1";
}

void CheckDateType(int Number, std::string& strDate)
{

}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin); // should be annotation
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		Init();
		cin >> val;

		if ((int)(val / 100000000.) != 0)
		{
			Year = -1;
		}
		else
		{
			Year = val / 10000.;
			val -= Year * 10000;

			Month = val / 100.;
			val -= Month * 100;

			Day = val;

			if (Month < 1 || Month > 12)
			{
				Year = -1;
			}

			if (Day < 1 || Day > nMonthEnd[Month - 1])
			{
				Year = -1;
			}
		}

		char buffer[11];
		snprintf(buffer, 11, "%04d/%02d/%02d", Year, Month, Day);

		if (Year == -1)
		{
			cout << "#" << test_case << " " << -1 << endl;
		}
		else
		{
			cout << "#" << test_case << " " << string(buffer) << endl;
		}

	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}