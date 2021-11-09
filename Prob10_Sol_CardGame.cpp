#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
#define ARRAY_MAX 100001

long long tree[4 * ARRAY_MAX];
long long N, Q, K; // overflow 땜시 다 long long 으로 했음.
map<int, int> mapCards;//CardValue, CardCount
vector<int> vcCards;//CardValue;
//lower_bound, upper_bound 사용 위해 vector 사용

long long update(int start, int end, int idx, long long val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] = val; // val % K 로 했어야 했나?

	int mid = (start + end) / 2;
	long long lval = update(start, mid, idx, val, node * 2);
	long long rval = update(mid + 1, end, idx, val, node * 2 + 1);
	return tree[node] = (lval * rval) % K;
}

long long query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return 1; // 곱셈 연산이므로 return 1

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	long long lval = query(start, mid, left, right, node * 2);
	long long rval = query(mid + 1, end, left, right, node * 2 + 1);
	return (lval * rval) % K;
}

template<typename T>
void checkQuery(T& _l, T& _r) // left low, right high
{
	if (_r < _l)
	{
		T temp;
		temp = _l;
		_l = _r;
		_r = temp;
	}

	//min-max 추가 했어야 했나?, 범위 내에 있게 하기 위해?
	//_l = max(_l, vcCards.front());
	//_r = min(_r, vcCards.back());
}

long long getPowValue(long long CardVal, long long CardCnt, long long _k)
{
	if (_k == 0 || CardCnt == 0) return 1; // To avoid divide_zero

	CardVal = CardVal % _k;

	if (CardCnt > 2)
	{
		long long CardVal_Sub = getPowValue(CardVal, CardCnt / 2, _k);
		long long CardVal2 = (CardVal_Sub * CardVal_Sub) % _k;

		if (CardCnt % 2 == 1)
		{
			CardVal = (CardVal2 * CardVal) % _k;
		}
		else
		{
			CardVal = CardVal2;
		}
	}
	else if(CardCnt == 2)
	{
		CardVal = (CardVal * CardVal) % _k;
	}

	return CardVal;
}

void initValues()
{
	vcCards.clear();
	mapCards.clear(); // 했었나?

	fill(tree, tree + 4 * ARRAY_MAX, 1); // 곱셈 연산이기에 1로 초기화
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int testcase;
	cin >> testcase;

	for (int t = 0 ; t < testcase ; t++)
	{
		N = Q = K = 0;
		cin >> N >> Q >> K;

		initValues();

		int temp;
		for (int n = 0 ; n < N ; n++)
		{
			cin >> temp;

			if (mapCards.find(temp) != mapCards.end())
			{
				mapCards[temp]++;
			}
			else
			{
				mapCards[temp] = 1;
			}
		}

		int kindOfCards = mapCards.size();
		vcCards.resize(kindOfCards);
		int n = 0;
		for (auto it : mapCards)
		{
			vcCards[n] = it.first;
			n++;
		}

		// 좌표 압축 구현했다가 지움 map 사용으로 필요 없음.
		//sort(vcCards.begin(), vcCards.end());
		//vcCards.erase(unique(vcCards.begin(), vcCards.end()), vcCards.end());

		// seg tree
		for (int n = 0; n < kindOfCards ; n++)
		{
			int CardVal = vcCards[n];
			int CardCnt = mapCards[CardVal];

			// pow
			// 최악의 경우로 한계치의 카드 숫자면 pow 연산시 오버플로우 걱정
			// 무슨 이유에선지 pow 함수에서 컴파일 에러가 있기도 했음.
			// 처음엔 단순히 for문 돌면서 곱셈 연산
			// 카드 숫자 10만 개면 속도가 느리기에 재귀 dp 로 구현
			// 해당 부분 개선 후 테케 통과 수 3 -> 9로 늘어남
			long long  val = getPowValue(CardVal, CardCnt, K);
			update(0, N - 1, n, val); // N-1 이 아니라 kindOfCards로 바꿨어야 했다.
		}

		// 쿼리 이분 탐색 부분이 깔끔하지 못했음.
		// 막판 10초 정도 남기고 쿼리 제한 문 추가하니 테케 통과 수 가 9 -> 11로 늘어났다.
		long long sum = 0;
		int i, j;
		for (int q = 0 ; q < Q ; q++)
		{
			cin >> i >> j;
			checkQuery(i, j);

			auto left_it = upper_bound(vcCards.begin(), vcCards.end(), i - 1);
			if (left_it == vcCards.end() || *left_it < i)// 인덱싱이 이상하게 되서 값비교 구문을 넣었었는데 기억이 나지 않음.
			{
				left_it--;
			}

			auto right_it = lower_bound(vcCards.begin(), vcCards.end(), j);
			if (right_it == vcCards.end() || *right_it > j) // 여기도 값비교 구문을 넣었었음.
			{
				right_it--;
			}

			int leftIdx = left_it - vcCards.begin();
			int rightIdx = right_it - vcCards.begin();

			if (rightIdx < leftIdx) continue;

			if (i <= vcCards[leftIdx]) // 추가된 쿼리 제한문
				sum += query(0, N - 1, leftIdx, rightIdx); // N-1 이 아니라 kindOfCards로 바꿨어야 했다.
		}

		cout << "#" << t + 1 << " " << sum << "\n";
	}

	return 0;
}