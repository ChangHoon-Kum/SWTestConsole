#include<iostream>
//#include <cstdio> // should be annotation
//#include <stdio.h> // should be annotation

//#include <string.h> // for memset
#include <vector>
#include <algorithm>

using namespace std;

int val;
vector<int> vcNumber;

void print(int result)
{
	cout << result << endl;
}

void Init()
{
	val = 0;
	vcNumber.clear();
}


int main(int argc, char** argv)
{
	int num_idx;
	int N;
	Init();

	//freopen("input.txt", "r", stdin); // should be annotation
	cin >> N;

	if (N < 1 || N > 9999)
		return 0;

	vcNumber.resize(4);

	vcNumber[3] = N / 1000.;
	N -= vcNumber[3] * 1000;

	vcNumber[2] = N / 100.;
	N -= vcNumber[2] * 100;

	vcNumber[1] = N / 10.;
	N -= vcNumber[1] * 10;

	vcNumber[0] = N;

	for (auto it : vcNumber)
	{
		val += it;
	}

	print(val);

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}