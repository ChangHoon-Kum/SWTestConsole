#include<iostream>
//#include <cstdio> // should be annotation
//#include <stdio.h> // should be annotation

//#include <string.h> // for memset
//#include <vector>

using namespace std;

int idx, val1, val2;
string oper;

void print(int t, int val1, int val2)
{
	if (val1 < val2)
	{
		oper = "<";
	}
	else if (val1 > val2)
	{
		oper = ">";
	}
	else // ==
	{
		oper = "=";
	}

	cout << "#" << t << " " << oper << endl;
}

void Init()
{
	idx = val1 = val2 = 0;
	oper = " ";
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
		cin >> val1;
		cin >> val2;


		print(test_case, val1, val2);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}