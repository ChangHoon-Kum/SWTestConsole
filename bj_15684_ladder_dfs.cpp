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

using namespace std;


#define abs(n) (n>0?n:-n)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

#define N_MAX 10 + 5 
#define H_MAX 30 + 5

int N, M, H;
int ladder_map[H_MAX][N_MAX] = { 0 };

struct POINT
{
	int x;
	int y;

	POINT()
	{
		x = y = -1;
	}

	POINT(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
	}

	string GetString()
	{
		char buffer[100];
		snprintf(buffer, 100, "(%d, %d) ", x, y);
		return string(buffer);
	}

	bool isValidPoint()
	{
		return x >= 0 && y >= 0 && x < N&& y < N;
	}

	bool operator==(const POINT& _r)
	{
		return this->x == _r.x && this->y == _r.y;
	}
};

enum DIRECTION { TOP = 0, TOPLEFT, LEFT, BOTTOMLEFT, BOTTOM, BOTTOMRIGHT, RIGHT, TOPRIGHT, DIRMAX = 8 };

//      TOP = 0, TOPLEFT, LEFT, BOTTOMLEFT, BOTTOM, BOTTOMRIGHT, RIGHT, TOPRIGHT
int dx[8] = { 0,  -1,      -1,      -1,       0,         1,        1,       1 };
int dy[8] = { -1, -1,       0,       1,       1,         1,        0,      -1 };

// 정답이 되는지 출력
int is_answer() {
	for (int col = 1; col <= N; col++) {
		int now_col = col;
		for (int row = 1; row <= H; row++) {
			int left = ladder_map[row][now_col - 1];
			int right = ladder_map[row][now_col];

			if (left)  now_col--;
			if (right) now_col++;
		}
		if (now_col != col) return 0;
	}
	return 1;
}

// 사다리를 놓는다. dfs 방식으로 설치하고 완료되면 종료
int make_ladder(int _end_depth, int _now_depth, int _row, int _col) {
	if (_now_depth == _end_depth) {
		if (is_answer()) {
			cout << _now_depth << endl;
			exit(0);
		}
		return 0;
	}
	int row = _col + 1 > H ? _row + 1 : _row;
	int col = _col + 1 > H ? 0 : _col + 1;
	for (; row <= H; row++) {
		for (; col <= N; col++) {
			if (ladder_map[row][col - 1] || ladder_map[row][col] || ladder_map[row][col + 1]) continue;
			ladder_map[row][col] = 1;
			make_ladder(_end_depth, _now_depth + 1, row, col);
			ladder_map[row][col] = 0;
		}
		col = 1;
	}
	return 0;
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);

	cin >> N >> M >> H;

	for (int m_idx = 0; m_idx < M; m_idx++) {
		int a, b;
		cin >> a >> b;
		ladder_map[a][b] = 1;
	}

	if (is_answer()) {
		cout << 0 << endl;
		return 0;
	}

	for (int plus = 1; plus <= 3; plus++) {
		for (int row = 1; row <= H; row++) {
			for (int col = 1; col <= N; col++) {
				if (ladder_map[row][col - 1] || ladder_map[row][col] || ladder_map[row][col + 1]) continue;
				ladder_map[row][col] = 1;
				make_ladder(plus, 1, row, col);
				ladder_map[row][col] = 0;
			}
		}
	}

	cout << -1 << endl;

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}