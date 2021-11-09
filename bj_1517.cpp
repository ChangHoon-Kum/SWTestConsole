#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
int N;
vector<long long int> vcNumber;
#define ARRAY_MAX 500001
long long int A[ARRAY_MAX];
long long int tree[4 * ARRAY_MAX];

long long int update(int start, int end, int idx, long long int val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] += val;

	int mid = (start + end) / 2;
	long long int lval = update(start, mid, idx, val, node * 2);
	long long int rval = update(mid + 1, end, idx, val, node * 2 + 1);
	return tree[node] = lval + rval;
}

long long int query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return 0;

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	long long int lval = query(start, mid, left, right, node * 2);
	long long int rval = query(mid + 1, end, left, right, node * 2 + 1);
	return lval + rval;
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	fill(A, A + ARRAY_MAX, LLONG_MIN);
	fill(tree, tree + 4 * ARRAY_MAX, 0);

	cin >> N;
	vcNumber.resize(N);
	for (int n = 0 ; n < N ; n++)
	{
		cin >> A[n];
		vcNumber[n] = A[n];
	}
	sort(vcNumber.begin(), vcNumber.end());
	vcNumber.erase(unique(vcNumber.begin(), vcNumber.end()), vcNumber.end());

	int kindOfNumbers = vcNumber.size();
	long long sum = 0;
	for (int n = 0 ; n < N ; n++)
	{
		int idx = lower_bound(vcNumber.begin(), vcNumber.end(), A[n]) - vcNumber.begin();
		sum += query(0, kindOfNumbers - 1, min(idx+1, kindOfNumbers), kindOfNumbers);

		update(0, kindOfNumbers - 1, idx, 1);
	}
	cout << sum;


	return 0;
}