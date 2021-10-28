/**
 * 
■ 징검다리
A마을과 B마을 사이에 통나무로 이루어진 징검다리가 있다
각 징검다리에는 점수가 적혀있고, 이전 통나무에서 다음 통나무로 이동시 최대 K만큼 이동할수 있다
징검다리를 건넜을때 최대로 얻을 수 있는 점수를 구하라

< 제한조건>
1. N : 1 ~300, 000
2. K : 1 ~N
3. 점수 : 부호가있는 32bit 정수형
4. 첫나무와 끝나무는 무조건 밟아야 한다
5. 같은 나무를 2번 밟을 수 없다.

< 입력>
2                                // TC
7 2                            // N, K
- 6 - 4 - 6 4 - 4 - 2 9     // 통나무 점수
7 3
- 6 - 4 - 6 4 - 4 - 2 9

< 출력 >
#1 1
#2 7

예시
T1 : -6 -> - 4 -> 4 -> - 2 -> 9    합은 1
T2 : -6 -> 4-> 9  합은 7
*/
#include <iostream>
#include <algorithm>

using namespace std;

long long tree[4 * 300001];
int N, K;


long long update(int start, int end, int idx, long long val, int node = 1)
{
	if (idx < start || idx > end) return tree[node];

	if (start == end) return tree[node] = val;

	int mid = (start + end) / 2;
	return tree[node] = max(update(start, mid, idx, val, node * 2), update(mid + 1, end, idx, val, node * 2 + 1));
}

long long query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || left > end) return -INT_MAX;

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return max(query(start, mid, left, right, node * 2), query(mid + 1, end, left, right, node * 2 + 1));
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		cin >> N >> K;

		long long val;
		cin >> val;
		update(0, N - 1, 0, val);

		long long F;
		for (int i = 1 ; i < N ; i++)
		{
			cin >> val;

			long long F_prime = query(0, N - 1, max(0, i - K), i - 1);
			
			F = F_prime + val;
			update(0, N - 1, i, F);
		}

		cout << "#" << t + 1 << " " << F << "\n";
	}
}