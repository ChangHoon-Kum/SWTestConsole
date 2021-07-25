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
map<char, int> LUT;


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
	for (char ch = 'a' ; ch <= 'z' ; ch++)
	{
		LUT[ch] = (ch - 0x60);
	}

	for (char ch = 'A'; ch <= 'Z'; ch++)
	{
		LUT[ch] = (ch - 0x40);
	}
}


int main(int argc, char** argv)
{
	int n;
	string T;

	MakeLUT();

	freopen("input.txt", "r", stdin); // should be annotation
	cin >> T;

	int len = T.length();
	for (n = 0 ; n < len ; n++)
	{
		char ch = T.at(n);

		if (ch >= 0x41 && ch <= 0x5A)
		{
			cout << LUT[ch] << " ";
		}
		else if (ch >= 0x61 && ch <= 0x7A)
		{
			cout << LUT[ch] << " ";
		}
	}
	
	
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}