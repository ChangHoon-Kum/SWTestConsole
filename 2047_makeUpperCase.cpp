#include<iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int idx, val, Year, Month, Day;
vector<int> vcNumber;
map<char, char> LUT;


void print(int t, std::string& result)
{
	cout << "#" << t << " " << result << endl;
}

void Init()
{
	idx = val = Year = Month = Day = 0;
	vcNumber.clear();
}

void CheckDateType(int Number, std::string& strDate)
{

}

void MakeLUT()
{
	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		LUT[ch] = (char)(ch - 0x20);
	}
}


int main(int argc, char** argv)
{
	int n;
	string T;

	MakeLUT();

	//freopen("input.txt", "r", stdin); // should be annotation
	cin >> T;

	int len = T.length();
	for (n = 0; n < len; n++)
	{
		char ch = T.at(n);

		if (ch >= 'a' && ch <= 'z')
		{
			cout << LUT[ch];
		}
		else
		{
			cout << ch;
		}
	}


	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}