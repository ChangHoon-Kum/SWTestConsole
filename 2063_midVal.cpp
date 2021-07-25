#include<iostream>
//#include <cstdio> // should be annotation
//#include <stdio.h> // should be annotation

//#include <string.h> // for memset
#include <vector>
#include <algorithm>

using namespace std;

int idx, val, midIdx;
vector<int> vcNumber;

void print(int result)
{
	cout << result << endl;
}

void Init()
{
	idx = val = midIdx = 0;
	vcNumber.clear();
}


int main(int argc, char** argv)
{
	int num_idx;
	int N;
	Init();

	//freopen("input.txt", "r", stdin); // should be annotation
	cin >> N;

	if (N < 9 || N > 199 || N % 2 == 0)
		return 0;

	for (num_idx = 0; num_idx < N; num_idx++)
	{
		cin >> val;

		vcNumber.push_back(val);
	}

	std::sort(vcNumber.begin(), vcNumber.end());
	midIdx = int(N / (double)2);

	print(vcNumber.at(midIdx));

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}