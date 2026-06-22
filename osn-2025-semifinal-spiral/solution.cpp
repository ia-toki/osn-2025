#include <bits/stdc++.h>
using namespace std;

int N, X1, Y1, X2, Y2;
int sta, fin;
bool noflag[307][307];
bool flag[70007];
vector<int> edge[70007];
string S;

int conv(int x, int y) {
	return (x - 1) * N + (y - 1);
}

void DFS1(int x, int y) {
	// atas
	if (noflag[x - 1][y]) {
		edge[conv(x, y)].push_back(conv(x - 1, y));
		edge[conv(x - 1, y)].push_back(conv(x, y));
		noflag[x - 1][y] = false;
		DFS1(x - 1, y);
	}
	
	// kanan
	if (noflag[x][y + 1]) {
		edge[conv(x, y)].push_back(conv(x, y + 1));
		edge[conv(x, y + 1)].push_back(conv(x, y));
		noflag[x][y + 1] = false;
		DFS1(x, y + 1);
	}
	
	// kiri
	if (noflag[x][y - 1]) {
		edge[conv(x, y)].push_back(conv(x, y - 1));
		edge[conv(x, y - 1)].push_back(conv(x, y));
		noflag[x][y - 1] = false;
		DFS1(x, y - 1);
	}
	
	// bawah
	if (noflag[x + 1][y]) {
		edge[conv(x, y)].push_back(conv(x + 1, y));
		edge[conv(x + 1, y)].push_back(conv(x, y));
		noflag[x + 1][y] = false;
		DFS1(x + 1, y);
	}
}

void DFS2(int x, int y) {
	// kanan
	if (noflag[x][y + 1]) {
		edge[conv(x, y)].push_back(conv(x, y + 1));
		edge[conv(x, y + 1)].push_back(conv(x, y));
		noflag[x][y + 1] = false;
		DFS2(x, y + 1);
	}
	
	// bawah
	if (noflag[x + 1][y]) {
		edge[conv(x, y)].push_back(conv(x + 1, y));
		edge[conv(x + 1, y)].push_back(conv(x, y));
		noflag[x + 1][y] = false;
		DFS2(x + 1, y);
	}
	
	// atas
	if (noflag[x - 1][y]) {
		edge[conv(x, y)].push_back(conv(x - 1, y));
		edge[conv(x - 1, y)].push_back(conv(x, y));
		noflag[x - 1][y] = false;
		DFS2(x - 1, y);
	}
	
	// kiri
	if (noflag[x][y - 1]) {
		edge[conv(x, y)].push_back(conv(x, y - 1));
		edge[conv(x, y - 1)].push_back(conv(x, y));
		noflag[x][y - 1] = false;
		DFS2(x, y - 1);
	}	
}

void DFS3(int x, int y) {
	// bawah
	if (noflag[x + 1][y]) {
		edge[conv(x, y)].push_back(conv(x + 1, y));
		edge[conv(x + 1, y)].push_back(conv(x, y));
		noflag[x + 1][y] = false;
		DFS3(x + 1, y);
	}
	
	// kiri
	if (noflag[x][y - 1]) {
		edge[conv(x, y)].push_back(conv(x, y - 1));
		edge[conv(x, y - 1)].push_back(conv(x, y));
		noflag[x][y - 1] = false;
		DFS3(x, y - 1);
	}
	
	// kanan
	if (noflag[x][y + 1]) {
		edge[conv(x, y)].push_back(conv(x, y + 1));
		edge[conv(x, y + 1)].push_back(conv(x, y));
		noflag[x][y + 1] = false;
		DFS3(x, y + 1);
	}
	
	// atas
	if (noflag[x - 1][y]) {
		edge[conv(x, y)].push_back(conv(x - 1, y));
		edge[conv(x - 1, y)].push_back(conv(x, y));
		noflag[x - 1][y] = false;
		DFS3(x - 1, y);
	}
}

void DFS4(int x, int y) {
	// kiri
	if (noflag[x][y - 1]) {
		edge[conv(x, y)].push_back(conv(x, y - 1));
		edge[conv(x, y - 1)].push_back(conv(x, y));
		noflag[x][y - 1] = false;
		DFS4(x, y - 1);
	}
	
	// atas
	if (noflag[x - 1][y]) {
		edge[conv(x, y)].push_back(conv(x - 1, y));
		edge[conv(x - 1, y)].push_back(conv(x, y));
		noflag[x - 1][y] = false;
		DFS4(x - 1, y);
	}
	
	// bawah
	if (noflag[x + 1][y]) {
		edge[conv(x, y)].push_back(conv(x + 1, y));
		edge[conv(x + 1, y)].push_back(conv(x, y));
		noflag[x + 1][y] = false;
		DFS4(x + 1, y);
	}
	
	// kanan
	if (noflag[x][y + 1]) {
		edge[conv(x, y)].push_back(conv(x, y + 1));
		edge[conv(x, y + 1)].push_back(conv(x, y));
		noflag[x][y + 1] = false;
		DFS4(x, y + 1);
	}
}

void DFSANS(int idx) {
	flag[idx] = true;
	for (int i = 0; i < edge[idx].size(); i++) {
		if (idx == sta && edge[idx][i] == fin) continue;
		if (!flag[edge[idx][i]]) {
			if (edge[idx][i] == idx - 1) S += 'B';
			if (edge[idx][i] == idx + 1) S += 'T';
			if (edge[idx][i] == idx - N) S += 'U';
			if (edge[idx][i] == idx + N) S += 'S';
			DFSANS(edge[idx][i]);
		}
	}
}

int main() {
	scanf("%d%d%d%d%d",&N, &X1, &Y1, &X2, &Y2);
	sta = conv(X1, Y1);
	fin = conv(X2, Y2);
	
	// pattern 1:
	//  4  5  6  7
	//  3 10  9  8
	//  2 11 12 13
	//  1 16 15 14
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			noflag[i][j] = true;
			edge[conv(i, j)].clear();
		}
	}
	
	// noflag[N][1] = false <-- intentionally commented
	DFS1(N, 1);
	
	if (edge[sta][0] == fin || edge[sta][1] == fin) {
		DFSANS(sta);
		cout << S.length() << endl;
		cout << S << endl;
		return 0;
	}
	
	// pattern 2:
	//  1  2  3  4
	// 16 11 10  5
	// 15 12  9  6
	// 14 13  8  7
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			noflag[i][j] = true;
			edge[conv(i, j)].clear();
		}
	}
	
	// noflag[N][1] = false <-- intentionally commented
	DFS2(1, 1);
	
	if (edge[sta][0] == fin || edge[sta][1] == fin) {
		DFSANS(sta);
		cout << S.length() << endl;
		cout << S << endl;
		return 0;
	}
	
	// pattern 3:
	// 10 11 16  1
	//  9 12 15  2
	//  8 13 14  3
	//  7  6  5  4
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			noflag[i][j] = true;
			edge[conv(i, j)].clear();
		}
	}
	
	// noflag[N][1] = false <-- intentionally commented
	DFS3(1, N);
	
	if (edge[sta][0] == fin || edge[sta][1] == fin) {
		DFSANS(sta);
		cout << S.length() << endl;
		cout << S << endl;
		return 0;
	}
	
	// pattern 4:
	// 7  8  13 14
	// 6  9  12 15
	// 5 10  11 16
	// 4  3   2  1
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			noflag[i][j] = true;
			edge[conv(i, j)].clear();
		}
	}
	
	// noflag[N][1] = false <-- intentionally commented
	DFS4(N, N);
	
	if (edge[sta][0] == fin || edge[sta][1] == fin) {
		DFSANS(sta);
		cout << S.length() << endl;
		cout << S << endl;
		return 0;
	}
}
