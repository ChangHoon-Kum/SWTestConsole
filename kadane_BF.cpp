#include <algorithm>
#include <iostream>

int A[10] = { -3, 3, 5, -3, -7, 9, -2, 10, -5, -2 };
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int sum_max = A[0];
	for (int i = 0; i < 10; i++)
	{
		int cursum = 0;

		for (int j = i ; j < 10 ; j++)
		{
			cursum += A[i];
			sum_max = max(cursum, sum_max);
		}
	}


	return 0;
}