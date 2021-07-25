#include<iostream>
//#include <cstdio> // should be annotation
//#include <stdio.h> // should be annotation

//#include <string.h> // for memset
//#include <vector>

using namespace std;

int idx, val, sum;
double dAvg;

void print(int t, int result)
{
	cout << "#" << t << " " << result << endl;
}

void Init()
{
	idx = val = sum = 0;
	dAvg = 0.;
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
		for (idx = 0; idx < 10; idx++)
		{
			cin >> val;
			if (val < 0)
			{
				val = 0;
			}
			else if (val > 10000)
			{
				val = 10000;
			}

			sum += val;
		}
		dAvg = sum / (double)10;

		print(test_case, int(dAvg + 0.5));
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}