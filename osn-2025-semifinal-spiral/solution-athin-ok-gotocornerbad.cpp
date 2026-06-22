#include <bits/stdc++.h>
using namespace std;

int N, X1, Y1, X2, Y2;
string s;

int main() {
	scanf("%d%d%d%d%d",&N, &X1, &Y1, &X2, &Y2);
	
	int x = X1;
	int y = Y1;
	
	while (x > 1) {
		s += 'U';
		x--;
	}
	while (y > 1) {
		s += 'B';
		y--;
	}
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N - 1; j++) {
			if (i % 2 == 1) s += 'T'; else s += 'B';
		}
		if (i != N) s += 'S';
	}
	
	for (int j = 1; j <= N - 1; j++) s += 'U';
	
	while (x < X2) {
		s += 'S';
		x++;
	}
	while (y < Y2) {
		s += 'T';
		y++;
	}
	
	cout << s.length() << endl;
	cout << s << endl;
}
