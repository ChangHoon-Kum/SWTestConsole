/**
 * 
 �� �ֺ�� ã��

�迭 A�� �־�����. Ex) [1, 2, 4, 2, 3, 3, 5]
�κ� ���� ���� ���� K�� �־�����. Ex) 5
�� ������ ��� �Ʒ� 3���� �κ� ������ ������ �ִ�.
[1, 2, 4, 2, 3] : �ֺ�� 2
[2, 4, 2, 3, 3] : �ֺ�� 3
[4, 2, 3, 3, 5] : �ֺ�� 3
�� �κ� ������ �ֺ���� 2, 3, 3�̸� �� �κ� ������ �ֺ�� �߿��� �ֺ���� �� ������ ����϶�
*�ֺ�� : �κ� �������� ���� ���� ���Ұ� �ֺ�� �̸�, �ֺ���� ������ ���ٸ� ������ ũ�Ⱑ ū ���� �ֺ���̴�.
�ش� ������ �ֺ���� 3�̸� 2�� �̹Ƿ� #1 3 2�� ��µȴ�.

�� �׽�Ʈ ���̽����� �迭�� �ֺ���� �� �ֺ���� ������ ����϶�

<�Է�>
ù°�ٿ� �׽�Ʈ ���̽��� ���� ��Ÿ���� .
�������� N(<=300,000)�� K(3<=K<=N)�� �־�����.
���� N���� ����A�� �־�����. ���� ���� (1<=A <= 1e9)

3
7 5
1 2 4 2 3 3 5
10 3
2 2 3 3 5 1 7 4 9 10
6 3
1 1000000000 100 100000 100 100000

<���>
#1 3 2
#2 7 2
#3 1000000000 2

<���ظ� ���� ���� ����° �׽�Ʈ ���̽� ����>
�κ� ����
[1 1000000000 100]                          :  �ֺ�� 1000000000
[1000000000 100 100000]                    : �ֺ�� 1000000000
[100 100000 100]                              : �ֺ�� 100
[100000 100 100000]                          : �ֺ�� 100000
 �κ� ������ �ֺ���� [1000000000, 1000000000, 100, 100000]�̸� ���� �ֺ���� 1000000000�̰� 2���̴�. ���� ����
#3 1000000000 2
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#define ARRAY_MAX 300001
using namespace std;

int A[ARRAY_MAX];
vector<int> vcVal;

typedef pair<int, int> PII; // first: �� ��, second: ���� ����
PII tree[4 * ARRAY_MAX];

int N, K;

PII update(int start, int end, int idx, int diff, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end)
	{
		tree[node].first += diff;
		tree[node].second = vcVal[idx];

		return tree[node];
	}

	int mid = (start + end) / 2;
	PII lval = update(start, mid, idx, diff, node * 2);
	PII rval = update(mid+1, end, idx, diff, node * 2 + 1);

	return tree[node] = max(lval, rval);
}

PII query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return make_pair(INT_MIN, INT_MIN);

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	PII lval = query(start, mid, left, right, node * 2);
	PII rval = query(mid + 1, end, left, right, node * 2 + 1);

	return max(lval, rval);
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase; cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		cin >> N >> K;
		vcVal.clear();
		vcVal.resize(N);
		fill(A, A + N, 0);
		fill(tree, tree + 4 * N, make_pair(0, 0));

		for (int n = 0 ; n < N ; n++)
		{
			cin >> A[n];
			vcVal[n] = A[n];
		}

		sort(vcVal.begin(), vcVal.end());
		vcVal.erase(unique(vcVal.begin(), vcVal.end()), vcVal.end());

		map<int, int> mapMaxFreqPart; // val , cnt
		for (int n = 0 ; n < N ; n++)
		{
			int idx = lower_bound(vcVal.begin(), vcVal.end(), A[n]) - vcVal.begin();
			update(0, N - 1, idx, 1);

			if (n >= K) // �����
			{
				int delidx = lower_bound(vcVal.begin(), vcVal.end(), A[n-K]) - vcVal.begin();
				update(0, N - 1, delidx, -1);
			}

			if (n >= K - 1) // �κ� �ֺ�
			{
				PII partMaxFreq = query(0, N - 1, 0, N - 1);

				mapMaxFreqPart[partMaxFreq.second]++;
			}
		}

		int maxFreqCnt = INT_MIN;
		int maxFreqVal = INT_MIN;
		for (auto it : mapMaxFreqPart)
		{
			if (it.second > maxFreqCnt)
			{
				maxFreqCnt = it.second;
				maxFreqVal = it.first;
			}
			else if(it.second == maxFreqCnt)
			{
				maxFreqVal = max(maxFreqVal, it.first);
			}
		}


		cout << "#" << t + 1 << " " << maxFreqVal << " " << maxFreqCnt << "\n";
	}

	return 0;
}