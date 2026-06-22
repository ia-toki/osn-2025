#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

ifstream tc_in;

const int MIN_N = 6;
const int MAX_N = 50;
const int MAX_K = 36;

const int QUERY_LIMIT = 3;
const string QUERY = "QUERY";
const string ANSWER = "ANSWER";

int N, K, TC;
vector<PII> SM;
int A[57][57];
bool inPlay[57][57];

// ======================================
// ===== RETURN & SCORING FUNCTIONS =====
// ======================================

int AC() {
	cerr << "AC" << endl;
	return 0;
}

int OK(double score, int N, int K) {
	cerr << "OK" << endl;
	cerr << score << " N = " << N << ", K = " << K << endl;
	return 0;
}

int WA(string errorMsg) {
	cerr << "WA" << endl;
	cerr << errorMsg << endl;
	return 0;
}

int INCORRECT_ANSWER() {
	cerr << "WA" << endl;
	cerr << "INCORRECT ANSWER: N = " << N << ", K = " << K << ", (S, M) = {";
	for (int i = 0; i < SM.size(); i++) {
		if (i > 0) {
			cerr << ", ";
		}
		cerr << "(" << SM[i].first << ", " << SM[i].second << ")";
	}
	cerr << "}" << endl;
	return 0;
}

int getFinalVerdict(int N, int K) {	
	if (6 < K && K <= 36) return 				OK(4, N, K);
	if (4 < K && K <= 6) return 				OK(9, N, K);
	if (K == 4) return 							OK(16, N, K);
	
	if (K <= 3 && 6 <= N && N < 9) return 		OK(26 + 3.0 * (N - 6), N, K);
	if (K <= 3 && 9 <= N && N < 18) return 		OK(41 + 2.0 * (N - 9), N, K);
	if (K <= 3 && 18 <= N && N < 30) return 	OK(63 + 1.5 * (N - 18), N, K);
	if (K <= 3 && 30 <= N && N <= 36) return	OK(84 + 2.5 * (N - 30), N, K);
	
	/* if (K <= 3 && N > 36) */ return 			AC();
}

// ============================
// ===== HELPER FUNCTIONS =====
// ============================

int randInt(int x, int y) {
	return x + (rand() % (y - x + 1));
}

// =================================
// ===== (ADAPTIVE) STRATEGIES =====
// =================================

/*
	 0		: Sample (X = 4, Y = 2)
	 1 - 24	: Whenever exists, get a region with this size
	25 - 35 : Always pick a response resulting most inPlay
	36 - 38 : Suboptimal play on Turn 1: RANDOM PICK
	39 - 40 : Suboptimal play on Turn 2: RANDOM PICK
	41		: X = 1, Y = 1
	42		: (X, Y) at the corner -- except (1, 1)
	43		: (X, Y) at the side -- except corners
	44 - 50 : (X, Y) at random point -- except sides
*/

int ANS_X = -1;
int ANS_Y = -1;
int PICK_REGION = -1;

bool OPTIMAL_TURN_1 = true;
bool OPTIMAL_TURN_2 = true;

PII gridRes[57][57];
map<PII, int> countRes;

void initStrategy(int TC) {
	// Seed is based on N for a consistent behavior by the grader
	srand(N);
	
	if (TC == 0) {
		ANS_X = 4;
		ANS_Y = 2;
		
	} else if (1 <= TC && TC <= 24) {
		PICK_REGION = TC;
	
	} else if (25 <= TC && TC <= 35) {
		// This is how we adapt optimally
		
	} else if (36 <= TC && TC <= 38) {
		OPTIMAL_TURN_1 = false;
		
	} else if (39 <= TC && TC <= 40) {
		OPTIMAL_TURN_2 = false;
		
	} else if (TC == 41) {
		ANS_X = 1;
		ANS_Y = 1;
		
	} else if (TC == 42) {
		int tmp = randInt(1, 3);
		if (tmp == 1) {
			ANS_X = 1;
			ANS_Y = N;
		} else if (tmp == 2) {
			ANS_X = N;
			ANS_Y = 1;
		} else {
			ANS_X = N;
			ANS_Y = N;
		}
		
	} else if (TC == 43) {
		int tmp = randInt(1, 4);
		if (tmp == 1) {
			ANS_X = 1;
			ANS_Y = randInt(2, N - 1);
		} else if (tmp == 2) {
			ANS_X = randInt(2, N - 1);
			ANS_Y = 1;
		} else if (tmp == 3) {
			ANS_X = N;
			ANS_Y = randInt(2, N - 1);
		} else {
			ANS_X = randInt(2, N - 1);
			ANS_Y = N;
		}
		
	} else {
		ANS_X = randInt(2, N - 1);
		ANS_Y = randInt(2, N - 1);
	}
}

bool checkAnswer(int X, int Y) {
	if (ANS_X != -1) {
		return (X == ANS_X && Y == ANS_Y);
		
	} else {
		int countInPlay = 0;
		
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (inPlay[i][j]) countInPlay++;
			}
		}
		
		return (countInPlay == 1);
	}
}

bool checkValidQueryInPlay() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (inPlay[i][j]) {
				if (A[i][j] < 1 || A[i][j] > MAX_K) return false;
				K = max(K, A[i][j]);
			}
		}
	}
	return true;
}

bool checkValidQueryNotInPlay() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!inPlay[i][j]) {
				if (A[i][j] != 0) return false;
			}
		}
	}
	return true;
}

void populateRes() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			gridRes[i][j] = PII(-1, -1);
		}
	}
	
	// This is just a DFS (Flood Fill)
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (inPlay[i][j] && gridRes[i][j].first == -1) {
				int color = A[i][j];
				gridRes[i][j].first = color;
				
				stack<PII> cc, st;
				cc.push(PII(i, j));
				st.push(PII(i, j));
				
				while (!st.empty()) {
					int x = st.top().first;
					int y = st.top().second;
					st.pop();
					
					if (inPlay[x - 1][y] && A[x - 1][y] == color && gridRes[x - 1][y].first == -1) {
						gridRes[x - 1][y].first = color;
						cc.push(PII(x - 1, y));
						st.push(PII(x - 1, y));
					}
					if (inPlay[x + 1][y] && A[x + 1][y] == color && gridRes[x + 1][y].first == -1) {
						gridRes[x + 1][y].first = color;
						cc.push(PII(x + 1, y));
						st.push(PII(x + 1, y));
					}
					if (inPlay[x][y - 1] && A[x][y - 1] == color && gridRes[x][y - 1].first == -1) {
						gridRes[x][y - 1].first = color;
						cc.push(PII(x, y - 1));
						st.push(PII(x, y - 1));
					}
					if (inPlay[x][y + 1] && A[x][y + 1] == color && gridRes[x][y + 1].first == -1) {
						gridRes[x][y + 1].first = color;
						cc.push(PII(x, y + 1));
						st.push(PII(x, y + 1));
					}
				}
				
				int sz = cc.size();
				while (!cc.empty()) {
					int x = cc.top().first;
					int y = cc.top().second;
					cc.pop();
					gridRes[x][y].second = sz;
				}
			}
		}
	}
	
	countRes.clear();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (inPlay[i][j]) {
				int color = gridRes[i][j].first;
				int sz = gridRes[i][j].second;
				countRes[PII(color, sz)]++;
			}
		}
	}
}

void updateInPlay(PII res) {
	SM.push_back(res);
	populateRes();
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int color = gridRes[i][j].first;
			int sz = gridRes[i][j].second;
			if (color != res.first || sz != res.second) {
				inPlay[i][j] = false;
			}
		}
	}
}

PII getResponse(int numQuery) {
	populateRes();
	
	// If (X, Y) is fixed
	if (ANS_X != -1) return gridRes[ANS_X][ANS_Y];

	// Find a region with a fixed size
	if (PICK_REGION != -1) {
		vector<PII> toPick;
		int most = -1;
		
		for (int color = 1; color <= K; color++) {
			if (countRes[PII(color, PICK_REGION)] > most) {
				most = countRes[PII(color, PICK_REGION)];
				toPick.clear();
				toPick.push_back(PII(color, PICK_REGION));
				
			} else if (countRes[PII(color, PICK_REGION)] == most) {
				toPick.push_back(PII(color, PICK_REGION));
			}
		}
		
		// If no such region
		if (most == 0) {
			toPick.clear();
			most = -1;
			
			for (auto const& [res, cnt] : countRes) {
				if (cnt > most) {
					most = cnt;
					toPick.clear();
					toPick.push_back(res);
					
				} else if (cnt == most) {
					toPick.push_back(res);
				}
			}
		}
		
		return toPick[randInt(0, toPick.size() - 1)];
	}
	
	// Playing optimally
	if ((numQuery == 1 && OPTIMAL_TURN_1) || (numQuery == 2 && OPTIMAL_TURN_2) || (numQuery == 3)) {
		vector<PII> toPick;
		int most = -1;
		
		for (auto const& [res, cnt] : countRes) {
			if (cnt > most) {
				most = cnt;
				toPick.clear();
				toPick.push_back(res);
				
			} else if (cnt == most) {
				toPick.push_back(res);
			}
		}
		
		return toPick[randInt(0, toPick.size() - 1)];
		
	// Playing NOT optimally
	} else {
		vector<PII> toPick;
		
		for (auto const& [res, cnt] : countRes) {
			if (cnt > 0) {
				toPick.push_back(res);
			}
		}
		
		return toPick[randInt(0, toPick.size() - 1)];
	}
}

// ==========================
// ===== MAIN FUNCTIONS =====
// ==========================

void readInput(char* argv) {
	ifstream tc_in(argv);
	tc_in >> TC;
}

void initInteraction() {
	// This time, the grader is not the one who initate the interaction
}

int doInteraction() {
	if (scanf("%d", &N) != 1) return WA("Tidak dapat membaca N");
	if (N < MIN_N || N > MAX_N) return WA("N harus di antara 6 dan 50");
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			inPlay[i][j] = true;
		}
	}
	
	initStrategy(TC);
	
	int numQuery = 0;
	K = 0;
	
	while (true) {
		char op[101];
		if (scanf("%99s", op) != 1) return WA("Tidak dapat membaca 'QUERY' atau 'ANSWER'");
		
		if (op == ANSWER) {
			int X, Y;
			if (scanf("%d", &X) != 1) return WA("Tidak dapat membaca X");
			if (X < 1 || X > N) return WA("X harus di antara 1 dan N");
			if (scanf("%d", &Y) != 1) return WA("Tidak dapat membaca Y");
			if (Y < 1 || Y > N) return WA("Y harus di antara 1 dan N");
			
			if (checkAnswer(X, Y) == false) {	
				return INCORRECT_ANSWER();
				
			} else {
				char excess[101];
				if (scanf("%99s", excess) == 1) return WA("Program harus berhenti setelah melakukan 'ANSWER'");
				
				return getFinalVerdict(N, K);
			}
			
		} else if (op == QUERY) {
			numQuery++;
			if (numQuery > QUERY_LIMIT) return WA("Hanya boleh melakukan maksimal 3x 'QUERY'");
			
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (scanf("%d", &A[i][j]) != 1) return WA("Tidak dapat membaca papan A secara utuh");
				}
			}
			
			if (checkValidQueryInPlay() == false) {
				return WA("Petak TIDAK STERIL harus berisi angka di antara 1 dan 36");
			
			} else if (checkValidQueryNotInPlay() == false) {
				return WA("Petak STERIL harus berisi angka 0");
			
			} else {
				PII res = getResponse(numQuery);
				printf("%d %d\n", res.first, res.second);
				fflush(stdout);	
				updateInPlay(res);
			}
			
		} else {
			return WA("Tidak dapat membaca 'QUERY' atau 'ANSWER'");
		}
	}
}

int main(int argc, char* argv[]) {
	readInput(argv[1]);
	initInteraction();
	return doInteraction();
}
