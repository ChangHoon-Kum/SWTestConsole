#include <iostream>
#include <cstdio> // should be annotation
#include <stdio.h> // should be annotation

#include <string.h> // for memset
// cannot use //#include <atlstr.h> // for cstring
#include <vector>
#include <algorithm>
#include <array>
#include <map>
#include <queue>
#include <list>

#include <bitset>

using namespace std;

#define ARRAY_SIZE 32

int main(int argc, char** argv)
{
	array<unsigned int, ARRAY_SIZE> opt;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		opt.at(i) = 1 << i;
		cout << std::bitset<ARRAY_SIZE>(opt.at(i)) << endl;
	}

	unsigned int items_flag = 0; // ����� 00000000 �� �ʱ�ȭ. ������ ���� ����.
	cout << "No item " << bitset<8>(items_flag) << endl; // 00000000 ���

	items_flag |= opt.at(0); // ������ 0 �� �����.
	cout << "item 0 obtained " << bitset<8>(items_flag) << endl; // 00000001 ���

	items_flag |= (opt.at(2) | opt.at(3)); // ������ 2�� 3 �� �����. (opt2 | opt3) -> 000001100
	cout << "item 2, 3 obtained " << bitset<8>(items_flag) << endl; // 00001101 ���

	items_flag &= ~opt.at(3); // ������ 3 �� �Ҿ���.
	cout << "item 3 losted " << bitset<8>(items_flag) << endl; // 0000**0**101 ���




	if (items_flag & opt.at(1)) //itmes_flag�� ������ 1 �ڸ��� 0 �̸� false�� ���� ������ ���� �ʴٰ� �Ǹ�
		cout << "Has item1" << endl;
	else
		cout << "Not have item1" << endl; // �̰� ��µ� ��.



	if ((items_flag & opt.at(2)) && !(items_flag & opt.at(1)))
	{
		items_flag ^= opt.at(1); // 000001**1**1
		items_flag ^= opt.at(2); // 00000**01**1
	}

	cout << bitset<8>(items_flag) << endl; // 00000011 ���
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}