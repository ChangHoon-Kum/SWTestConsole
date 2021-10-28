// 수열이 주어진다. 해당 수열에서 연속되는 구간의 min-max차이가 K가 되는 최소구간의 길이와 갯수를 구하고자 한다.
// 예를 들어 아래와 같은 10개의 수열에서 min max차이가 10이 되는 구간을 찾아 보자
// 1, 7, 9, 11, 3, 15, 13, 14, 5, 2
// [1, 7, 9, 11] 과[15, 13, 14, 5]는 구간 길이가 4이고 min max차이가 10이다.따라서 답은 구간길이4 갯수 2이다

//○입력
//첫줄에 testcase의 숫자가 주어진다(1 < T < 45)
//둘째줄에 수열의 갯수N과(2 < N < 100000)와 차이값K(1, 000, 000, 000)가 주어진다.입력되는 수열 A의 범위는 1 < A < 1, 000, 000, 000이며 중복되는 숫자는 존재하지않는다
//○출력
//각 테스트케이스마다 구간의 길이 및 갯수를 출력한다. 단 정답이 존재하지 않을 경우 '-1'을 출력한다

//○풀이
//Two Pointer 기법으로 순차 검색
//시간 복잡도: O(N) 예상

#include <stdio.h>
#include <iostream>

using namespace std;
#define ARRAY_MAX 10000

int A[ARRAY_MAX];

int main(void)
{
	freopen("input.txt", "r", stdin);

	int testcase, N, K;
	cin >> testcase >> N >> K;

	for (int t = 0 ; t < testcase ; t++)
	{
		// 0. Initialize
		memset(A, 0, sizeof(int) * ARRAY_MAX);

		for (size_t i = 0; i < N; i++)
		{
			cin >> A[i];
		}

		int min_length = INT_MAX;
		int min_count = 0;

		// 1. Two point
		int s = 0;
		int e = s;

		while (true)
		{
			if (A[s] <= A[e])
			{
				if ((A[e] - A[s]) == K)
				{
					int cur_length = (e - s) + 1;
					if (cur_length < min_length)
					{
						min_length = cur_length;
						min_count = 1;
					}
					else if (cur_length == min_length)
					{
						min_count++;
					}

					s = e + 1;
					e = s;
				} 
				else if((A[e] - A[s]) < K)
				{
					e++;
				}
				else
				{
					s = e;
				}
			}
			else
			{
				s = e;
			}

			if (s >= N || e >= N)
			{
				break;
			}
		}
		
		// 2. Output
		if (min_count > 0)
		{
			printf("%d, %d\n", min_length, min_count);
		}
		else
		{
			printf("-1\n");
		}
	}

	return 0;
}