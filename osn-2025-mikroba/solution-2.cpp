#include <bits/stdc++.h>
using namespace std;

int n, k;
int color, sz;
int a[57][57];

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

void ANSWER(int x, int y) {
	printf("ANSWER\n");
	printf("%d %d\n", x, y);
	fflush(stdout);
}

int main() {
	n = 6;
	k = 6;
	
	printf("%d\n", n);
	fflush(stdout);
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = i;
		}
	}
	QUERY();
	int x = color;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == color) {
				a[i][j] = j;
			} else {
				a[i][j] = 0;
			}
		}
	}
	QUERY();
	int y = color;
	
	ANSWER(x, y);
}
