#include <bits/stdc++.h>
using namespace std;

ifstream tc_in, tc_out;
FILE* con_out;

const int MAX_K = 200000;
const char CHAR_UP = 'U';
const char CHAR_DOWN = 'S';
const char CHAR_LEFT = 'B';
const char CHAR_RIGHT = 'T';

int N, X1, Y1, X2, Y2;
bool flag[307][307];
int apple, x, y;

// ======================================
// ===== RETURN & SCORING FUNCTIONS =====
// ======================================

int AC() {
	cout << "AC" << endl;
	return 0;
}

int OK(double percentage) {
	cout << "OK" << endl;
	cout << fixed << setprecision(2) << percentage << "%" << endl;
	return 0;
}

int WA() {
	cout << "WA" << endl;
	return 0;
}

double log2(double x) {
	return log(x) / log(2);
}

int getFinalVerdict(int K) {
	if (K <= N * N) return AC();
	return OK((0.20 + pow(0.75, log2(K - N * N + 2))) * 100);
}

// ============================
// ===== HELPER FUNCTIONS =====
// ============================

void initMap() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			flag[i][j] = true;
		}
	}
	
	flag[X1][Y1] = false;
	flag[X2][Y2] = false;
	
	apple = N * N - 2;
	x = X1;
	y = Y1;
}

// ==========================
// ===== MAIN FUNCTIONS =====
// ==========================

void readInput(char* argv) {
	ifstream tc_in(argv);
	
	tc_in >> N >> X1 >> Y1 >> X2 >> Y2;
}

void readOutput(char* argv) {
	ifstream tc_out(argv);
	
	// no need
}

void readContestant(char* argv) {
	con_out = fopen(argv, "r");
}

int doGrading() {
	int K;
	if (fscanf(con_out, "%d", &K) != 1) return WA();
	if (K < 1 || K > MAX_K) return WA();
	
	char S[300007];
	if (fscanf(con_out, "%299999s", S) != 1) return WA();
	if (strlen(S) != K) return WA();
	
	char excess[101];
	if (fscanf(con_out, "%99s", excess) == 1) return WA();
	
	initMap();
	for (int i = 0; i < K; i++) {
		if (S[i] == CHAR_UP) x--;
		else if (S[i] == CHAR_DOWN) x++;
		else if (S[i] == CHAR_LEFT) y--;
		else if (S[i] == CHAR_RIGHT) y++;
		else return WA();
		
		if (x < 1 || x > N || y < 1 || y > N) return WA();
		
		if (flag[x][y]) {
			flag[x][y] = false;
			apple--;
		}
	}
	
	if (apple != 0) return WA();
	if (x != X2 || y != Y2) return WA();
	return getFinalVerdict(K);
}

int main(int argc, char* argv[]) {
	readInput(argv[1]);
	readOutput(argv[2]);
	readContestant(argv[3]);
	return doGrading();
}