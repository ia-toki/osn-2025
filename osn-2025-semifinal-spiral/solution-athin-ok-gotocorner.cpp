#include <bits/stdc++.h>
using namespace std;

int N, X1, Y1, X2, Y2;
string S;

int main() {
	scanf("%d%d%d%d%d",&N, &X1, &Y1, &X2, &Y2);
	
	int x = X1;
	int y = Y1;
	
	while (x > 1) {
		S += 'U';
		x--;
	}
	while (y > 1) {
		S += 'B';
		y--;
	}
	
	S += 'T';
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N - 2; j++) {
			if (i % 2 == 1) S += 'T'; else S += 'B';
		}
		if (i != N) S += 'S';
	}
	
	S += 'B';
	
	for (int j = 1; j <= N - 1; j++) S += 'U';
	
	while (x < X2) {
		S += 'S';
		x++;
	}
	while (y < Y2) {
		S += 'T';
		y++;
	}
	
	cout << S.length() << endl;
	cout << S << endl;
}
