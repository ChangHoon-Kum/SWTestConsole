/**
 * 
 수열이 N(1~100개)개가 주어진다. 숫자의 범위는 (1~1000)이다..
각 수열에서 숫자 구간이 주어질때 그 숫자 구간에서의 최대 빈도수와 그 숫자를 출력하라
Query 는 M개 주어지며, 구간a~b 가 입력으로 주어진다.
예를 들어 1, 2, 3, 4, 4, 5, 5 가 주어졌을때
숫자 범위 3~5안에 있는 최빈수는? 그 빈도수와 해당 숫자를 출력하라
  -> 해당 숫자 범위에 있는 숫자는 3 4 4 5 5 이고, 4가 2개, 5가 2개 이기때문에 이 문제에서는 5
세그트리로만 구현...
input
20 3
1 3 4 3 2 5 6 7 8 7 5 5 2 4 8 3 4 7 5 9
1 10
3 5
7 9
출력
5 4
5 4
7 3
추가.. 이 문제에서 N은 10000, 이고 숫자 범위가 1~1e9라면???
=> 위 문제에서 좌표 압축기법만 적용하면 풀이 가능... try~

 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define ARRAY_MAX 10000

vector<int> vcVal;
int tree[4 * ARRAY_MAX];
int A[ARRAY_MAX];

int update(int start, int end, int idx, int diff, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] += diff;

	int mid = (start + end) / 2;
	int lval = update(start, mid, idx, diff, node * 2);
	int rval = update(mid+1, end, idx, diff, node * 2 + 1);
	return max(lval, rval);
}

int query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return INT_MIN;

	if (left <= start && end >= right) return tree[node];

	int mid = (start + end) / 2;
	int lval = query(start, mid, left, right, node * 2);
	int rval = query(mid + 1, end, left, right, node * 2 + 1);
	return max(lval, rval);
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int N, K; // 입력 숫자 수, 쿼리 수
	cin >> N >> K;
	
	for (int n = 0 ; n < N ; n++)
	{
		cin >> A[n];
		update(0, N - 1, A[n], 1);
	}


	return 0;
}