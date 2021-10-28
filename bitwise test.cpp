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

	unsigned int items_flag = 0; // 현재는 00000000 로 초기화. 아이템 없는 상태.
	cout << "No item " << bitset<8>(items_flag) << endl; // 00000000 출력

	items_flag |= opt.at(0); // 아이템 0 을 얻었다.
	cout << "item 0 obtained " << bitset<8>(items_flag) << endl; // 00000001 출력

	items_flag |= (opt.at(2) | opt.at(3)); // 아이템 2와 3 을 얻었다. (opt2 | opt3) -> 000001100
	cout << "item 2, 3 obtained " << bitset<8>(items_flag) << endl; // 00001101 출력

	items_flag &= ~opt.at(3); // 아이템 3 을 잃었다.
	cout << "item 3 losted " << bitset<8>(items_flag) << endl; // 0000**0**101 출력




	if (items_flag & opt.at(1)) //itmes_flag의 아이템 1 자리가 0 이면 false가 나와 가지고 있지 않다고 판명
		cout << "Has item1" << endl;
	else
		cout << "Not have item1" << endl; // 이게 출력될 것.



	if ((items_flag & opt.at(2)) && !(items_flag & opt.at(1)))
	{
		items_flag ^= opt.at(1); // 000001**1**1
		items_flag ^= opt.at(2); // 00000**01**1
	}

	cout << bitset<8>(items_flag) << endl; // 00000011 출력
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}