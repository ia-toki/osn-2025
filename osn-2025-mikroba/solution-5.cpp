#include <bits/stdc++.h>
using namespace std;

int n, k;
int color, sz;
int a[57][57];
bool inPlay[57][57];

void QUERY() {
	printf("QUERY\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	fflush(stdout);
	scanf("%d%d", &color, &sz);
}

int flag[57][57];
int cc;

void DFS1(int x, int y) {
	cc++;
	flag[x][y] = 1;
	if (flag[x - 1][y] == 2 && a[x - 1][y] == a[x][y]) DFS1(x - 1, y);
	if (flag[x + 1][y] == 2 && a[x + 1][y] == a[x][y]) DFS1(x + 1, y);
	if (flag[x][y - 1] == 2 && a[x][y - 1] == a[x][y]) DFS1(x, y - 1);
	if (flag[x][y + 1] == 2 && a[x][y + 1] == a[x][y]) DFS1(x, y + 1);
}

void DFS0(int x, int y) {
	inPlay[x][y] = false;
	flag[x][y] = 0;
	if (flag[x - 1][y] == 1 && a[x - 1][y] == a[x][y]) DFS0(x - 1, y);
	if (flag[x + 1][y] == 1 && a[x + 1][y] == a[x][y]) DFS0(x + 1, y);
	if (flag[x][y - 1] == 1 && a[x][y - 1] == a[x][y]) DFS0(x, y - 1);
	if (flag[x][y + 1] == 1 && a[x][y + 1] == a[x][y]) DFS0(x, y + 1);
}

void UPDATE() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (inPlay[i][j]) {
				flag[i][j] = 2;
			} else {
				flag[i][j] = 0;
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (flag[i][j] == 2) {
				cc = 0;
				DFS1(i, j);
				if (a[i][j] != color || cc != sz) {
					DFS0(i, j);
				}
			}
		}
	}
}

void ANSWER(int x, int y) {
	printf("ANSWER\n");
	printf("%d %d\n", x, y);
	fflush(stdout);
}

int pattern[57][57];
int rowP, colP, labelP;
bool doneTriColor;
int limit[57];

void initPattern() {
	rowP = 0;
	labelP = 0;
	
	doneTriColor = false;
	for (int i = 1; i <= k; i++) {
		limit[i] = n * n / k;
	}
}

void makePattern(vector<int> vec) {
	rowP++;
	colP = 0;
	
	for (int i = 0; i < vec.size(); i++) {
		labelP++;
		for (int j = 0; j < vec[i]; j++) {
			colP++;
			pattern[rowP][colP] = labelP;
		}
	}
}

void makeTriple(vector<int> vec) {
	makePattern(vec);
	makePattern(vec);
	makePattern(vec);
}

void triColor(int x = 1, int y = 1) {
	if (x > n) {
		doneTriColor = true;
		return;
	}
	
	if (y > n) {
		triColor(x + 1, 1);
		return;
	}

	for (int i = 1; i <= k && !doneTriColor; i++) {
		int toColor = ((i + x - 2) % 3) + 1;
		
		if (x > 1 && a[x - 1][y] == toColor) continue;
		if (y > 1 && pattern[x][y] == pattern[x][y - 1] && a[x][y - 1] != toColor) continue;
		if (y > 1 && pattern[x][y] != pattern[x][y - 1] && a[x][y - 1] == toColor) continue;
		if (limit[toColor] == 0) continue;
		
		a[x][y] = toColor;
		limit[toColor]--;
		triColor(x, y + 1);
		if (doneTriColor) break;
		limit[toColor]++;
		a[x][y] = 0;
	}
}

int main() {
	srand(1412);
	
	n = 9;
	k = 3;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			inPlay[i][j] = true;
		}
	}
	
	printf("%d\n", n);
	fflush(stdout);
	
	initPattern();
	makeTriple({9});
	makeTriple({3, 3, 3});
	makeTriple({1, 1, 1, 1, 1, 1, 1, 1, 1});
	triColor();
	
	QUERY();
	UPDATE();
	
	for (int query = 2; query <= 3; query++) {
		int tmp = 0;
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (inPlay[i][j]) {
					tmp = tmp % 3 + 1;
					a[i][j] = tmp;
				} else {
					a[i][j] = 0;
				}
			}
		}
		QUERY();
		UPDATE();
	}	
	
	int x, y;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (inPlay[i][j]) {
				x = i;
				y = j;
			}
		}
	}
	ANSWER(x, y);
}
