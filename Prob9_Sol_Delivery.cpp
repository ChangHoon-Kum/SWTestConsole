/**
 * 
 ■ 배달

음식점은 주어진 거리 D보다 작은 거리의 집에 배달 서비스를 제공한다. 배달 가능한 집의 개수와 배달 건수를 출력한다.
	1)     음식점에서 일정 거리(D)아네 위치한 집은 배달 가능하다.
	2)     Distance(음식점, 집) : abs(음식점 x – 집 x) + abs(y)
	3)     음식점과 집의 좌표는 중복되지 않는다.
	4)     X y좌표 범위 : -1e9 ~ 1e9

음식점 수(N), 집의 수 (M), 배달가능 거리 (D)가 주어진다.  음식점 1곳이상 배달을 시킬수 있는 집의 개수와 배달 주문이 가능한 모든 건수를 출력하라
N <= 10,000
M <= 100,000,000
D <= 1,000,000,000

<입력>
1           // test case
4 3 3       // 음식점 수 (N), 집개수(M), 거리 (D)
-4 4 0 1 // 음식점 위치, y는 0
0 2         // 집1
-3 -2      // 집2
3 -3       // 집3

<출력>
#1 2 3



<예시>
집 2의 경우 음식점1과 거리가 x축 1, y축 2가 떨어져있으므로  3이내 이다. 그리고, 집1 은 음식점 3, 4에서 주문을 할수 있다. 집 3은 주문할수 있는 음식점은 없다. 따라서 음식배달이 가능한 집은 2개이며, 가능한 주문은 3개이다.
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int N, M, D; // N: 음식점, M: 집, D: 거리제한


int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		cin >> N >> M >> D;

		vector<int> vcShop;
		vcShop.resize(N);

		for (int n = 0 ; n < N ; n++)
		{
			cin >> vcShop[n];
		}
		sort(vcShop.begin(), vcShop.end());

		//priority_queue<int/*abs(y)*/, int/*x*/> pqHouse;
		priority_queue<pair<int,int>> pqHouse;
		{
			int x, y;
			for (int m = 0 ; m < M ; m++)
			{
				cin >> x >> y;

				pqHouse.push(make_pair(-abs(y), x));
			}
		}

		int CntValidBill = 0;
		int CntValidHouse = 0;
		while (!pqHouse.empty())
		{
			auto itHouse = pqHouse.top();
			pqHouse.pop();

			itHouse.first = -itHouse.first;

			if (itHouse.first > D)
			{
				break;
			}

			int left_x = itHouse.second - (D - itHouse.first) -1;
			int right_x = itHouse.second + (D - itHouse.first);

			auto it_left = upper_bound(vcShop.begin(), vcShop.end(), left_x);
			if (it_left == vcShop.end())
			{
				continue;
			}

			auto it_right = lower_bound(vcShop.begin(), vcShop.end(), right_x);
			if (it_right == vcShop.end())
			{
				it_right--;
			}
			else if (right_x  < *it_right)
			{
				it_right--;
			}

			int leftIdx = it_left - vcShop.begin();
			int rightIdx = it_right - vcShop.begin();

			if (rightIdx < leftIdx)
			{
				continue;
			}

			int CntShop = rightIdx - leftIdx + 1;
			CntValidBill += CntShop;
			if (CntShop > 0)
			{
				CntValidHouse++;
			}
		}


		cout << "#" << t + 1 << " " << CntValidHouse << " " << CntValidBill << "\n";
	}



	return 0;
}