#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
#define ARRAY_MAX 100001

long long tree[4 * ARRAY_MAX];
long long N, Q, K; // overflow ���� �� long long ���� ����.
map<int, int> mapCards;//CardValue, CardCount
vector<int> vcCards;//CardValue;
//lower_bound, upper_bound ��� ���� vector ���

long long update(int start, int end, int idx, long long val, int node = 1)
{
	if (idx < start || end < idx) return tree[node];

	if (start == end) return tree[node] = val; // val % K �� �߾�� �߳�?

	int mid = (start + end) / 2;
	long long lval = update(start, mid, idx, val, node * 2);
	long long rval = update(mid + 1, end, idx, val, node * 2 + 1);
	return tree[node] = (lval * rval) % K;
}

long long query(int start, int end, int left, int right, int node = 1)
{
	if (right < start || end < left) return 1; // ���� �����̹Ƿ� return 1

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

	//min-max �߰� �߾�� �߳�?, ���� ���� �ְ� �ϱ� ����?
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
	mapCards.clear(); // �߾���?

	fill(tree, tree + 4 * ARRAY_MAX, 1); // ���� �����̱⿡ 1�� �ʱ�ȭ
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

		// ��ǥ ���� �����ߴٰ� ���� map ������� �ʿ� ����.
		//sort(vcCards.begin(), vcCards.end());
		//vcCards.erase(unique(vcCards.begin(), vcCards.end()), vcCards.end());

		// seg tree
		for (int n = 0; n < kindOfCards ; n++)
		{
			int CardVal = vcCards[n];
			int CardCnt = mapCards[CardVal];

			// pow
			// �־��� ���� �Ѱ�ġ�� ī�� ���ڸ� pow ����� �����÷ο� ����
			// ���� ���������� pow �Լ����� ������ ������ �ֱ⵵ ����.
			// ó���� �ܼ��� for�� ���鼭 ���� ����
			// ī�� ���� 10�� ���� �ӵ��� �����⿡ ��� dp �� ����
			// �ش� �κ� ���� �� ���� ��� �� 3 -> 9�� �þ
			long long  val = getPowValue(CardVal, CardCnt, K);
			update(0, N - 1, n, val); // N-1 �� �ƴ϶� kindOfCards�� �ٲ��� �ߴ�.
		}

		// ���� �̺� Ž�� �κ��� ������� ������.
		// ���� 10�� ���� ����� ���� ���� �� �߰��ϴ� ���� ��� �� �� 9 -> 11�� �þ��.
		long long sum = 0;
		int i, j;
		for (int q = 0 ; q < Q ; q++)
		{
			cin >> i >> j;
			checkQuery(i, j);

			auto left_it = upper_bound(vcCards.begin(), vcCards.end(), i - 1);
			if (left_it == vcCards.end() || *left_it < i)// �ε����� �̻��ϰ� �Ǽ� ���� ������ �־����µ� ����� ���� ����.
			{
				left_it--;
			}

			auto right_it = lower_bound(vcCards.begin(), vcCards.end(), j);
			if (right_it == vcCards.end() || *right_it > j) // ���⵵ ���� ������ �־�����.
			{
				right_it--;
			}

			int leftIdx = left_it - vcCards.begin();
			int rightIdx = right_it - vcCards.begin();

			if (rightIdx < leftIdx) continue;

			if (i <= vcCards[leftIdx]) // �߰��� ���� ���ѹ�
				sum += query(0, N - 1, leftIdx, rightIdx); // N-1 �� �ƴ϶� kindOfCards�� �ٲ��� �ߴ�.
		}

		cout << "#" << t + 1 << " " << sum << "\n";
	}

	return 0;
}