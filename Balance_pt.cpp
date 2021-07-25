#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <map>
//#include <format>

using namespace std;

std::vector<std::pair<int/*coor*/, int/*weight*/>> vcPoints;

int main(int argc, char** argv)
{
	int T;
	int test_case;

	freopen("input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1 ; test_case <= T ; ++test_case)
	{
		int ptCount;
		cin >> ptCount;

		vcPoints.resize(ptCount);
		for (int idx = 0 ; idx < ptCount; idx++)
		{
			int val;
			cin >> val;
			vcPoints.at(idx).first = val;
		}

		for (int idx = 0; idx < ptCount; idx++)
		{
			int val;
			cin >> val;
			vcPoints.at(idx).second = val;
		}

		cout << "#" << test_case << " ";

		for (int idx = 0 ; idx < ptCount -1 ; idx++)
		{
			int m1 = 0, d1 = 0; 
			for (int idx_l = 0 ; idx_l <= idx ; idx_l++)
			{
				m1 += vcPoints.at(idx_l).second;
				//d1 += vcPoints.at(idx_l).first;
			}
			
			int m2 = 0, d2 = 0;
			for (int idx_r = idx+1; idx_r < ptCount; idx_r++)
			{
				m2 += vcPoints.at(idx_r).second;
				//d2 += vcPoints.at(idx_r).first;
			}

			double dVal = sqrt(m2) / (double)sqrt(m1);
			double dBias = abs(vcPoints.at(0).first - vcPoints.at(ptCount-1).first) 
				/ (double)(1 + dVal);
			
			char buffer[100];
			snprintf(buffer, 100, "%.10lf ", vcPoints.at(idx).first + dBias);

			cout << string(buffer);
		}

		cout << endl;
	}
	

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}