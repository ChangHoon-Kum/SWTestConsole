#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>

using namespace std;

enum OPERATOR { ADD = 0, SUB, MUL, DIV, OPMAX = 4 };

int N;
vector<int> vcNumbers;
vector<OPERATOR> vcOp;
vector<int> vcResult;

int Calc_Sub(int _l, int _r, OPERATOR op)
{
	if (op == ADD)
	{
		return _l + _r;
	}
	else if (op == SUB)
	{
		return _l - _r;
	}
	else if (op == MUL)
	{
		return _l * _r;
	}
	else // DIV
	{
		if (_l > 0) // positive number
		{
			return (int)(_l / (double)_r);
		}
		else // negative number
		{
			return -1 * (int)((-1 * _l) / (double)_r);
		}
	}
}

void Calc(vector<OPERATOR>& setOp)
{
	int nOpSize = setOp.size();
	int nVal = vcNumbers.at(0);
	for (int idx = 0; idx < nOpSize; idx++)
	{
		nVal = Calc_Sub(nVal, vcNumbers.at(idx + 1), vcOp.at(idx));
	}

	vcResult.push_back(nVal);
}

// i, j: 서로 교환할 인덱스
void swap(vector<OPERATOR>& setOp, int i, int j)
{
	OPERATOR iVal = setOp.at(i);
	setOp.at(i) = setOp.at(j);
	setOp.at(j) = iVal;
}

// k: 현재까지 선택된 원소 수
void perm(vector<OPERATOR>& setOp, int k = 0)
{
	int nSize = setOp.size();
	if (k == nSize)
	{
		/*for (auto it : setOp)
		{
			cout << it << " ";
		}
		cout << endl;*/

		Calc(setOp);
		return;
	}
	else
	{
		for (int i = k; i < nSize; i++)
		{
			swap(setOp, k, i);
			perm(setOp, k + 1);
			swap(setOp, k, i);
		}
	}
}


int main(int argc, char** argv)
{
	//freopen("input.txt", "r", stdin);

	//Init
	{
		int idx;
		cin >> N;
		vcNumbers.resize(N);
		for (idx = 0; idx < N; idx++)
		{
			cin >> vcNumbers.at(idx);
		}

		int nPlus, nMinus, nMul, nDiv;
		cin >> nPlus >> nMinus >> nMul >> nDiv;
		for (idx = 0; idx < nPlus; idx++)
		{
			vcOp.push_back(ADD);
		}
		for (idx = 0; idx < nMinus; idx++)
		{
			vcOp.push_back(SUB);
		}
		for (idx = 0; idx < nMul; idx++)
		{
			vcOp.push_back(MUL);
		}
		for (idx = 0; idx < nDiv; idx++)
		{
			vcOp.push_back(DIV);
		}
	}

	perm(vcOp);

	int nMaxVal = *max_element(vcResult.begin(), vcResult.end());
	int nMinVal = *min_element(vcResult.begin(), vcResult.end());

	cout << nMaxVal << endl;
	cout << nMinVal << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}