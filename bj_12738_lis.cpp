#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int res[1000000];

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	cin >> N;

	int size = 0;
	for (int n = 0; n < N ; n++)
	{
		int val;
		cin >> val;

		int lo = lower_bound(res, res + size, val) - res;

		res[lo] = val;

		if (lo == size) size++;
	}

	cout << size;

	return 0;
}