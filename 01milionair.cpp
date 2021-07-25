/////////////////////////////////////////////////////////////////////////////////////////////
// �⺻ �����ڵ�� ���� �����ص� ���� �����ϴ�. ��, ����� ���� ����
// �Ʒ� ǥ�� ����� ���� �ʿ�� �����ϼ���.
// ǥ�� �Է� ����
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int ���� 1�� �Է¹޴� ����
// cin >> b >> c;                       // float ���� 2�� �Է¹޴� ���� 
// cin >> d >> e >> f;                  // double ���� 3�� �Է¹޴� ����
// cin >> g;                            // char ���� 1�� �Է¹޴� ����
// cin >> var;                          // ���ڿ� 1�� �Է¹޴� ����
// cin >> AB;                           // long long ���� 1�� �Է¹޴� ����
/////////////////////////////////////////////////////////////////////////////////////////////
// ǥ�� ��� ����
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int ���� 1�� ����ϴ� ����
// cout << b << " " << c;               // float ���� 2�� ����ϴ� ����
// cout << d << " " << e << " " << f;   // double ���� 3�� ����ϴ� ����
// cout << g;                           // char ���� 1�� ����ϴ� ����
// cout << var;                         // ���ڿ� 1�� ����ϴ� ����
// cout << AB;                          // long long ���� 1�� ����ϴ� ����
/////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
//#include <vector>
//#include <algorithm>

using namespace std;

#define DAY_LIMIT 1000002

int nDays;
int day;

long GetMaxProfit(long* vcPrice, int nDays, int buyingDate = 0L)
{
	int nRet = 0;
	int nMaxProfit = 0;
	if ((nDays <= 1) || (buyingDate >= nDays - 1))
	{
		return 0;
	}
	else
	{
		nMaxProfit = 0;
		for (day = buyingDate + 1; day < nDays; day++)
		{
			if ((vcPrice[day] - vcPrice[buyingDate]) > nMaxProfit)
				nMaxProfit = (vcPrice[day] - vcPrice[buyingDate]);
		}

		nRet = nMaxProfit + GetMaxProfit(vcPrice, nDays, buyingDate + 1);
	}

	return nRet;
}

long priceList[DAY_LIMIT];

int main(int argc, char** argv)
{
	int test_case;
	int T;
	long profit = 0;
	bool bErrPrice = false;
	/*
	   �Ʒ��� freopen �Լ��� input.txt �� read only �������� �� ��,
	   ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   //�������� �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��,
	   freopen �Լ��� �̿��ϸ� ���� cin �� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�.
	   ���� �׽�Ʈ�� ������ ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �����ϴ�.
	   freopen �Լ��� ����ϱ� ���ؼ��� #include <cstdio>, Ȥ�� #include <stdio.h> �� �ʿ��մϴ�.
	   ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�.
	*/
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		for (day = 0; day < nDays; day++)
		{
			priceList[day] = 0;
		}

		nDays = 0;
		cin >> nDays;

		profit = 0;
		if (nDays >= 2 && nDays <= 1000000)
		{
			bErrPrice = false;
			for (day = 0; day < nDays; day++)
			{
				cin >> priceList[day];
			}
			if (!bErrPrice)
				profit = GetMaxProfit(priceList, nDays);
		}

		cout << "#" << test_case << " " << profit << endl;
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}