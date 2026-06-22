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

int main() {
	srand(1412);
	
	n = 6;
	k = 4;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			inPlay[i][j] = true;
		}
	}
	
	printf("%d\n", n);
	fflush(stdout);
	
	for (int query = 1; query <= 3; query++) {
		int numInPlay = 0;
		vector<int> tmp;
		int tmpCtr = 0;
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (inPlay[i][j]) numInPlay++;
			}
		}
		
		for (int i = 0; i < numInPlay; i++) tmp.push_back(i % k + 1);
		random_shuffle(tmp.begin(), tmp.end());
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (inPlay[i][j]) {
					a[i][j] = tmp[tmpCtr++];
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
