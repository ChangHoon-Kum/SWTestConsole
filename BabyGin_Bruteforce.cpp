#include <iostream>
//#include <cstdio> // should be annotation
//#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool bLeft, bRight;

// i, j: 서로 교환할 인덱스
void swap(vector<int>& setCard, int i, int j)
{
	int iVal = setCard.at(i);
	setCard.at(i) = setCard.at(j);
	setCard.at(j) = iVal;
}

bool checkRun(vector<int>& vc)
{
	bool bRet = true;
	for (int idx = 0 ; idx < vc.size()-1 ; idx++)
	{
		if(vc.at(idx+1) == vc.at(idx)+1)
		{ }
		else
		{
			bRet = false;
		}
	}
	return bRet;
}

bool checkTriple(vector<int>& vc)
{
	bool bRet = true;
	for (int idx = 0; idx < vc.size() - 1; idx++)
	{
		if (vc.at(idx + 1) == vc.at(idx))
		{
		}
		else
		{
			bRet = false;
		}
	}
	return bRet;
}

bool CheckBabyGin(vector<int> setCard)
{
	int nSize = setCard.size();
	int nSplitVol = nSize / 2.;

	vector<int> vcLeft, vcRight;
	vcLeft.assign(setCard.begin(), setCard.begin() + nSplitVol);
	vcRight.assign(setCard.begin() + nSplitVol, setCard.end());

	std::sort(vcLeft.begin(), vcLeft.end());
	std::sort(vcRight.begin(), vcRight.end());

	if (checkRun(vcLeft))
	{
		cout << "Run(";
		for (auto it : vcLeft)
		{
			cout << it << " ";
		}
		cout << ")" << endl;
		bLeft = true;
	}

	if (checkRun(vcRight))
	{
		cout << "Run(";
		for (auto it : vcRight)
		{
			cout << it << " ";
		}
		cout << ")" << endl;
		bRight = true;
	}

	if (checkTriple(vcLeft))
	{
		cout << "Triple(";
		for (auto it : vcLeft)
		{
			cout << it << " ";
		}
		cout << ")" << endl;
		bLeft = true;
	}

	if (checkTriple(vcRight))
	{
		cout << "Triple(";
		for (auto it : vcRight)
		{
			cout << it << " ";
		}
		cout << ")" << endl;
		bRight = true;
	}

	if ((bLeft==true) && (bRight==true))
	{
		return true;
	}
	else
	{
		bLeft = bRight = false;
		return false;
	}
}

// k: 현재까지 선택된 원소 수
void perm(vector<int>& setCard, int k = 0)
{
	int nSize = setCard.size();
	if (k == nSize)
	{
		for (auto it: setCard)
		{
			cout << it << " ";
		}
		cout << endl;

		CheckBabyGin(setCard);
		return;
	}
	else
	{
		for (int i = k ; i < nSize; i++)
		{
			swap(setCard, k, i);
			perm(setCard, k + 1);
			if ((bLeft == true) && (bRight == true))
			{
				return;
			}
			swap(setCard, k, i);
		}
	}
}

// vcArr: 데이터 전체 집합(, n: 전체 갯수)
// r: 선택할 원소수
// vcBag: 선택된 원소가 저장되는 공간, resize로 반드시 용량 설정 먼저
vector<int> vcArr;
vector<int> vcBag;
void comb(int n, int r)
{
	if (r == 0)
	{
		// vcBag 선택완료
	}
	else if (n < r)
	{
		return;
	}
	else
	{
		vcBag.at(r - 1) = vcArr.at(n - 1);
		comb(n - 1, r - 1);
		comb(n - 1, r);
	}
}

int main(int argc, char** argv)
{
	bLeft = bRight = false;
	vector<int> setCard;
	for (int cardIdx = 0; cardIdx < 6 ; cardIdx++)
	{
		int card;
		cin >> card;

		setCard.push_back(card);
	}

	perm(setCard);

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}