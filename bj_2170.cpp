#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void sweep(vector<pair<int, int>>& vcLine, int& _i, int& _j)
{
	/*if (vcLine.empty())
	{
		vcLine.emplace_back(_i, _j);
		return;
	}*/

	bool bCheck = false;
	for (auto& it : vcLine)
	{
		if (it.first <= _i && _j <= it.second) // ������ ����
		{
			bCheck = true;
			break;
		}
		else if (it.second < _i || _j < it.first) // ������ ������
		{
			continue;
		}
		else // �Ϻθ� ����, ����
		{
			bCheck = true;
			it.first = min(it.first, _i);
			it.second = max(it.second, _j);
			break;
		}
	}

	if (!bCheck)
	{
		vcLine.emplace_back(_i, _j);
	}
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	vector<pair<int, int>> vcLine;
	int N;
	cin >> N;
	for (int n = 0; n < N; n++)
	{
		int i, j;
		cin >> i >> j;
		if (i > j) swap(i, j);
		
		sweep(vcLine, i, j);
	}
	
	// skip sort -> O(NlogN) => O(N)
	// ������ ���� ���ɰ� ����.
	// sort�ؾ���.
	// Second sweep
	vector<pair<int, int>> vcLine2;
	for(auto it_line : vcLine)
	{
		sweep(vcLine2, it_line.first, it_line.second);
	}

	int sum = 0;
	for (auto it: vcLine2)
	{
		sum += (it.second - it.first);
	}

	cout << sum;

	return 0;
}