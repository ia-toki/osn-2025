#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

#define mp make_pair
#define fr first
#define sc second

const int MXN = 200000;
const int MXQ = 200000;
const int MXA = 1000000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	vector<int> A;
	int Q;
	vector<int> X, Y;

	vector<int> ans;

	void InputFormat() {
		LINE(N);
		LINE(A % SIZE(N));
		LINE(Q);
		LINES(X, Y) % SIZE(Q);
	}

	void OutputFormat() {
		LINES(ans) % SIZE(Q);
	}

	void GradingConfig() {
		TimeLimit(2);
		MemoryLimit(256);
	}

	void Constraints() {
		CONS(1 <= N && N <= MXN);
		CONS(eachElementOf(A).isBetween(1, MXA));
		CONS(1 <= Q && Q <= MXQ);
		CONS(eachElementOf(X).isBetween(1, N));
		CONS(eachElementOf(Y).isBetween(1, MXA));
	}

	void Subtask1() {
		CONS(N <= 5);
		CONS(Q <= 10);
		Points(1);
	}

	void Subtask2() {
		CONS(elementsAreInSet(A, 1, N));
		CONS(elementsAreInSet(Y, 1, N));
		Points(2);
	}

	void Subtask3() {
		CONS(N <= 100);
		CONS(Q <= 10);
		Points(3);
	}

	void Subtask4() {
		CONS(N <= 1000);
		CONS(Q <= 10);
		Points(4);
	}

	void Subtask5() {
		CONS(N <= 1000);
		CONS(Q <= 5000);
		Points(5);
	}

	void Subtask6() {
		CONS(numberOfDistinctValues(A, Y, 50));
		Points(6);
	}

	void Subtask7() {
		Points(7);
	}

private:
	bool elementsAreInSet(vector<int> &A, int t1, int t2) {
		vector<int> S;
		S.push_back(t1); S.push_back(t2);
		for (int i : A) {
			bool inSet = false;
			for (int j : S) {
				if (i == j) {
					inSet = true;
					break;
				}
			}
			if (!inSet) return false;
		}
		return true;
	}

	bool numberOfDistinctValues(vector<int> &A, vector<int> &Y, int K) {
		set<int> S;
		for (int i : A) S.insert(i);
		for (int i : Y) S.insert(i);
		return (S.size() <= K);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1, 3, 4, 5, 6, 7});
		Input
		({
			"4",
			"1 1 1 2",
			"5",
			"3 2",
			"1 4",
			"4 3",
			"3 4",
			"4 4",
		});
		Output
		({
			"2",
			"1",
			"0",
			"1",
			"0"
		});
	}

	void BeforeTestCase() {
		A.clear();
		X.clear();
		Y.clear();
		N = 0;
		Q = 0;
	}

	void AfterTestCase() {
		// vector<int> perm(N), revPerm(N);
		// iota(perm.begin(), perm.end(), 0);
		// vector<int> newA(N);
		// for (int i = 0; i < N; i++) {
		// 	newA[i] = A[perm[i]];
		// 	revPerm[perm[i]] = i;
		// }
		// A = newA;
		// for (int i = 0; i < Q; i++) {
		// 	X[i] = revPerm[X[i]];
		// }
	}

	void TestGroup1() {
		Subtasks({1, 2, 3, 4, 5, 6, 7});

		CASE({
			N = 3;
			A = {1, 1, 1};
			Q = 1;
			X = {3};
			Y = {3};
		});

		CASE({
			N = 1;
			A = {1};
			Q = 2;
			X = {1, 1};
			Y = {1, 1};
		});

		CASE({
			N = 2;
			A = {1, 2};
			Q = 3;
			X = {1, 2, 1};
			Y = {2, 1, 1};
		});

		CASE({
			N = 2;
			A = {2, 1};
			Q = 3;
			X = {1, 2, 1};
			Y = {1, 2, 2};
		});

		CASE({
			N = 5;
			A = {1, 1, 1, 1, 1};
			Q = 10;
			X = {1, 5, 4, 3, 2, 1, 4, 3, 4, 3};
			Y = {1, 5, 5, 5, 5, 5, 1, 1, 1, 5};
		});
	}

	void TestGroup2() {
		Subtasks({1, 3, 4, 5, 6, 7});

		CASE({
			N = 1;
			A = {1};
			Q = 4;
			X = {1, 1, 1, 1};
			Y = {2, 1, 3, 2};
		});

		CASE({
			N = 4;
			A = {5, 5, 5, 5};
			Q = 5;
			X = {2, 1, 3, 4, 2};
			Y = {7, 4, 6, 4, 1};
		});

		CASE({
			N = 5;
			A = {6, 6, 6, 3, 8};
			Q = 5;
			X = {5, 1, 4, 3, 2};
			Y = {6, 7, 4, 2, 1};
		});

		CASE({
			N = 5;
			A = {6, 5, 4, 2, 2};
			Q = 5;
			X = {2, 3, 4, 5, 1};
			Y = {6, 3, 1, 3, 5};
		});

		CASE({
			N = 5;
			A = {3, 3, 3, 5, 5};
			Q = 5;
			X = {4, 5, 4, 2, 1};
			Y = {3, 7, 6, 5, 2};
		});

		CASE({
			N = 5;
			A = {1, 2, 3, 4, 5};
			Q = 6;
			X = {1, 1, 1, 1, 1, 1};
			Y = {7, 6, 7, 6, 6, 6};
		});

		CASE({
			N = 5;
			A = {3, 3, 3, 3, 3};
			Q = 3;
			X = {5, 1, 2};
			Y = {5, 2, 7};
		});

		CASE({
			N = 5;
			A = {1, 1, 5, 5, 9};
			Q = 4;
			X = {3, 4, 5, 2};
			Y = {5, 1, 2, 9};
		});

		CASE({
			N = 3;
			A = {3, 3, 3};
			Q = 3;
			X = {2, 2, 1};
			Y = {MXA, 3, MXA};
		});
	}

	void TestGroup3() {
		Subtasks({2, 5, 6, 7}); // skipping 3 and 4 to reduce number of testgroups

		CASE({
			N = 1000; Q = 5000;
			for (int i = 0; i < N; i++) {
				A.push_back(rnd.nextInt(1, 2) == 1 ? 1 : N);
			}
			for (int i = 0; i < Q; i++) {
				X.push_back(rnd.nextInt(1, N));
				Y.push_back(rnd.nextInt(1, 2) == 1 ? 1 : N);
			}
		});

		CASE({
			N = 1000; Q = 5000;
			for (int i = 0; i < N; i++) {
				A.push_back(rnd.nextInt(1, 2) == 1 ? 1 : N);
			}
			for (int i = 0; i < Q; i++) {
				X.push_back(rnd.nextInt(1, N));
				Y.push_back(rnd.nextInt(1, 2) == 1 ? 1 : N);
			}
		});

		CASE({
			N = 1000; Q = 5000;
			for (int i = 0; i < N; i++) {
				A.push_back(1);
			}
			for (int i = 0; i < 5 * N; i++) {
				X.push_back(i % N + 1);
				Y.push_back((i / N == 0 || i / N == 3) ? 1 : N);
			}
		});
	}

	void TestGroup4() {
		Subtasks({2, 6, 7});

		CASE({
			N = 50000; Q = 200000;
			for (int i = 0; i < N; i++) {
				A.push_back(1);
			}
			for (int i = 0; i < 4 * N; i++) {
				X.push_back(i % N + 1);
				Y.push_back((i / N == 0 || i / N == 3) ? 1 : N);
			}
		});
	}

	void TestGroup5() {
		Subtasks({3, 4, 5, 6, 7});

		CASE(createSubtask6(100, 10, 0, 0));
		CASE(createSubtask6(100, 10, 1, 0));
		CASE(createSubtask6(100, 10, 4, rnd.nextInt(2, 5)));
		CASE(createSubtask6(100, 10, 7, rnd.nextInt(4, 10)));
		CASE(createSubtask6(100, 10, 11, rnd.nextInt(7, 15)));
		CASE(createSubtask6(100, 10, 15, rnd.nextInt(10, 20)));
		CASE(createSubtask6(100, 10, 23, rnd.nextInt(15, 25)));
		CASE(createSubtask6(100, 10, 25, rnd.nextInt(20, 35)));
		CASE(createSubtask6(100, 10, 29, rnd.nextInt(30, 50)));
	}

	void TestGroup6() {
		Subtasks({3, 4, 5, 7});

		CASE(pureRandom(100, 10, 0));
	}

	void TestGroup7() {
		Subtasks({4, 5, 6, 7});

		CASE(createSubtask6(1000, 10, 0, 0));
		CASE(createSubtask6(1000, 10, 4, 15));
		CASE(createSubtask6(1000, 10, 9, rnd.nextInt(31, 62)));
		CASE(createSubtask6(1000, 10, 15, rnd.nextInt(62, 125)));
		CASE(createSubtask6(1000, 10, 23, rnd.nextInt(125, 250)));
		CASE(createSubtask6(1000, 10, 29, rnd.nextInt(250, 500)));
	}

	void TestGroup8() {
		Subtasks({4, 5, 7});

		for (int i = 0; i < 10; i++)
			CASE(pureRandom(1000, 10, 1));
		for (int i = 0; i < 7; i++)
			CASE(pureRandom(1000, 10, 0));
	}

	void TestGroup9() {
		Subtasks({5, 6, 7});

		CASE(createSubtask6(1000, 5000, 0, 0));
		CASE(createSubtask6(1000, 5000, 4, 10));
		CASE(createSubtask6(1000, 5000, 9, 20));
		CASE(createSubtask6(1000, 5000, 15, 40));
		CASE(createSubtask6(1000, 5000, 23, 80));
		CASE(createSubtask6(1000, 5000, 28, 160));
	}

	void TestGroup10() {
		Subtasks({5, 7});

		for (int i = 0; i < 10; i++)
			CASE(createMeaningfulQuery(1000, 5000, i * N / 10));
		CASE(pureRandom(1000, 5000, 1));
		CASE(pureRandom(1000, 5000, 0));
	}

	void TestGroup11() {
		Subtasks({6, 7});

		CASE(createSubtask6(MXN, MXQ, 0, 0));
		CASE(createSubtask6(MXN, MXQ, 7, MXN / rnd.nextInt(500, 1000)));
		CASE(createSubtask6(MXN, MXQ, 15, MXN / rnd.nextInt(125, 500)));
		CASE(createSubtask6(MXN, MXQ, 22, MXN / rnd.nextInt(30, 125)));
		CASE(createSubtask6(MXN, MXQ, 30, MXN / rnd.nextInt(4, 20)));
	}

	void TestGroup12() {
		Subtasks({7});

		for (int i = 0; i < 4; i ++)
			CASE(pureRandom(MXN, MXQ, 1));
		for (int i = 0; i < 3; i++)
			CASE(pureRandom(MXN, MXQ, 0));
	}

private:
	void pureRandom(int n, int q, int inBound) {
		N = n; Q = q;
		for (int i = 0; i < N; i++) {
			if (inBound) A.push_back(rnd.nextInt(1, N));
			else {
				if (rnd.nextDouble(0, 1) < 0.15) A.push_back(N + 1);
				else A.push_back(rnd.nextInt(1, N));
			}
		}

		for (int i = 0; i < Q; i++) {
			X.push_back(rnd.nextInt(1, N));
			int id = X.back() - 1;
			if (A[id] == N + 1) {
				Y.push_back(rnd.nextInt(1, N));
				A[id] = Y.back();
			} else {
				if (A[id] >= N / 2 && rnd.nextDouble(0, 1) < 0.2) {
					Y.push_back(N + 1);
					A[id] = Y.back();
				} else {
					Y.push_back(rnd.nextInt(1, N));
					A[id] = Y.back();
				}
			}
		}
	}

	void createSubtask6(int n, int q, int wantOOB, int useO) {
		N = n; Q = q;
		vector<int> inVal, outVal;
		vector<int> anchor;
		for (int i = 0; i < 20; i++) {
			int pw = (1 << i);
			if (pw <= N)
				anchor.push_back(pw);
		}
		anchor.push_back(1);
		anchor.push_back(N);
		sort(anchor.begin(), anchor.end());
		anchor.erase(unique(anchor.begin(), anchor.end()), anchor.end());
		anchor.erase(remove_if(anchor.begin(), anchor.end(), [&](int x){ return x < 1 || x > N; }), anchor.end());

		int maxOOB = min(wantOOB, max(0, 50 - (int)anchor.size()));
		int maxIN = 50 - maxOOB;

		inVal = anchor;

		vector<int> candidate;
		for (int v = 1; v <= N; v++) {
			if (!binary_search(inVal.begin(), inVal.end(), v))
				candidate.push_back(v);
		}

		rnd.shuffle(candidate.begin(), candidate.end());
		while ((int)inVal.size() < min(maxIN, N) && !candidate.empty()) {
			inVal.push_back(candidate.back());
			candidate.pop_back();
		}

		sort(inVal.begin(), inVal.end());

		for (int i = 1; i <= wantOOB; i++) outVal.push_back(N + i * i);

		A.assign(N, 1);

		vector<int> idx(N); iota(idx.begin(), idx.end(), 0);
		rnd.shuffle(idx.begin(), idx.end());
		unordered_set<int> oPos;
		for (int i = 0; i < useO; i++) {
			oPos.insert(idx[i]);
		}

		for (int i = 0; i < N; i++) {
			if (oPos.count(i) && !outVal.empty()) {
				A[i] = outVal[rnd.nextInt(0, (int)outVal.size() - 1)];
			} else {
				A[i] = inVal[rnd.nextInt(0, (int)inVal.size() - 1)];
			}
		}

		auto pick_target = [&](int cur) -> int {
			int ret = cur;
			while (ret == cur) {
				double r = rnd.nextDouble(0, 1);
				int x = cur;
				if (r < 0.35) {
					x = anchor[(int)anchor.size() - 1 - rnd.nextInt(0, 2)];
				} else if (r < 0.60 && !outVal.empty()) {
					x = outVal[rnd.nextInt(0, (int)outVal.size() - 1)];
				} else if (r < 0.80) {
					x = anchor[rnd.nextInt(0, 2)];
				} else {
					vector<int> top;
					for (auto i : inVal) if (i > 4) top.push_back(i);
					const vector<int>& pool = top.empty() ? inVal : top;
					x = pool[rnd.nextInt(0, (int)pool.size() - 1)];
				}
				ret = x;	
			}
			return ret;
		};

		int hotCount = min(max(5, Q / 10), N);
		vector<int> hotIdx(N); iota(hotIdx.begin(), hotIdx.end(), 0);
		rnd.shuffle(hotIdx.begin(), hotIdx.end());
		hotIdx.resize(hotCount);

		vector<int> saveA = A;

		for (int t = 0; t < Q; t++) {
			int p = (rnd.nextDouble(0, 1) < 0.7 && hotCount > 0) ? hotIdx[rnd.nextInt(0, hotCount - 1)] : rnd.nextInt(0, N-1);
			int newY = A[p];
			for (int tries = 0; tries < 12 && newY == A[p]; tries++) newY = pick_target(A[p]);
			if (newY == A[p]) {
				if (A[p] != N) newY = N;
				else newY = 1;
			}
			X.push_back(p + 1);
			Y.push_back(newY);
			A[p] = newY;
		}

		A = saveA;
	}

	
	void createMeaningfulQuery(int n, int q, int initial) {
		N = n;
		vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
		rnd.shuffle(idx.begin(), idx.end());
		
		vector<int> itv(N, 1);
		for (int i = 0; i < initial; i++) itv[idx[i]] = 0;

		if (initial == N) {
			for (int i = 0; i < N; i++) A.push_back(N + rnd.nextInt(1, N));
		} else {
			int last = N;
			while (itv[last - 1] == 0) last--;
			int idx = last - 1;
			A.push_back(last);
			idx--;
			while (idx >= 0) {
				if (itv[idx] == 1) {
					if (rnd.nextDouble(0, 1) < 0.1) {
						A.push_back(idx + 1);
						last = idx + 1;
					} else {
						A.push_back(last);
					}
					idx--;
				} else {
					idx--;
					while (idx >= 0 && itv[idx] == 0) idx--;
					if (idx >= 0) {
						last = idx + 1;
						A.push_back(last);
						last--;
					}
				}
			}

			vector<int> ones;
			for (int i = 0; i < N; i++) {
				if (itv[i] == 1) ones.push_back(i + 1);
			}
			rnd.shuffle(ones.begin(), ones.end());
			while (A.size() < N) {
				A.push_back(ones[rnd.nextInt(0, (int)ones.size() - 1)]);
			}
		}

		vector<int> copyOfA = A;

		vector<int> su(N + 1, 0);
		int extra = 0;
		for (int i = 0; i < N; i++) {
			if (A[i] > N) extra++;
			else su[A[i]]++;
		}

		auto L_of = [&](int i, int s) {
			return max(1, i - s + 1);
		};

		vector<int> diff(N + 2, 0);
		for (int i = 1; i <= N; i++) if (su[i] > 0) {
			int L = L_of(i, su[i]);
			int R = i;
			if (1 <= L && L <= N) diff[L]++;
			if (R + 1 <= N) diff[R + 1]--;
		}
		vector<int> C(N + 2, 0);
		for (int t = 1; t <= N; t++) C[t] = C[t - 1] + diff[t];

		auto zerosCount = [&]() {
			int z = 0;
			for (int t = 1; t <= N; t++)
				if (C[t] == 0) z++;
			return z;
		};

		vector<queue<int> > pos(N + 1);
		queue<int> posExtra;
		for (int p = 0; p < N; p++) {
			if (A[p] > N) posExtra.push(p);
			else pos[A[p]].push(p);
		}

		auto can_remove_safe = [&](int i) -> bool {
			if (i < 1 || i > N || su[i] <= 0) return false;
			int Lold = L_of(i, su[i]);
			if (Lold < 1 || Lold > N) return true;
			return (C[Lold] >= 2);
		};
		auto can_remove_mkzero = [&](int i) -> bool {
			if (i < 1 || i > N || su[i] <= 0) return false;
			int Lold = L_of(i, su[i]);
			if (Lold < 1 || Lold > N) return false;
			return (C[Lold] == 1);
		};
		auto can_add_rmzero = [&](int i) -> bool {
			if (i < 1 || i > N) return false;
			int Lnew = L_of(i, su[i] + 1);
			if (Lnew < 1 || Lnew > N) return false;
			return (C[Lnew] == 0);
		};
		auto can_add_safe = [&](int i) -> bool {
			if (i < 1 || i > N) return false;
			int Lnew = L_of(i, su[i] + 1);
			if (Lnew < 1 || Lnew > N) return true;
			return (C[Lnew] >= 1);
		};
		
		auto dec_bucket_apply = [&](int i) {
			int Lold = L_of(i, su[i]);
			if (1 <= Lold && Lold <= N) C[Lold]--;
			su[i]--;
		};
		auto inc_bucket_apply = [&](int i) {
			su[i]++;
			int Lnew = L_of(i, su[i]);
			if (1 <= Lnew && Lnew <= N) C[Lnew]++;
		};

		auto grab_index_with_value = [&](int v) -> int {
			if (v > N) {
				if (posExtra.empty()) return -1;
				int p = posExtra.front(); posExtra.pop();
				return p;
			} else {
				if (v < 1 || v > N) return -1;
				if (pos[v].empty()) return -1;
				int p = pos[v].front(); pos[v].pop();
				return p;
			}
		};
		auto put_index_with_value = [&](int v, int p) {
			if (v > N) posExtra.push(p);
			else pos[v].push(p);
		};
		Q = q;

		for (int i = 0; i < Q; i++) {
			int z = zerosCount();
			int target;
			double r = rnd.nextDouble(0, 1);
			if (z < N / 5) {
				target = (r < 0.2 ? 0 : (r < 0.8 ? +1 : -1));
			} else if (z > 4 * N / 5) {
				target = (r < 0.2 ? 0 : (r < 0.8 ? -1 : +1));
			} else {
				target = (r < 0.1 ? 0 : (r < 0.1 + 0.45 + 0.45 * ((double)(z - N / 2) / (double)N) ? +1 : -1));
			}

			bool done = false;
			for (int attempt = 0; attempt < 80 && !done; attempt++) {
				if (target == +1) {
					vector<int> candRem;
					for (int i = 1; i <= N; i++) if (can_remove_mkzero(i)) candRem.push_back(i);
					if (!candRem.empty()) {
						int i0 = candRem[rnd.nextInt(0, (int)candRem.size() - 1)];
						int p = grab_index_with_value(i0);
						if (p == -1) continue;
						dec_bucket_apply(i0);
						int newVal = MXA - rnd.nextInt(0, N);
						extra++;
						int oldVal = A[p];
						A[p] = newVal;
						put_index_with_value(newVal, p);
						done = true;
						X.push_back(p + 1);
						Y.push_back(newVal);
					}
				} else if (target == -1) {
					vector<int> candAdd;
					for (int i = 1; i <= N; i++) if (can_add_rmzero(i)) candAdd.push_back(i);
					if (!candAdd.empty()) {
						int i1 = candAdd[rnd.nextInt(0, (int)candAdd.size() - 1)];
						int p = grab_index_with_value(N + 1);
						if (p == -1) {
							vector<int> candRem;
							for (int i = 1; i <= N; i++) if (can_remove_safe(i)) candRem.push_back(i);
							if (candRem.empty()) continue;
							int i0 = candRem[rnd.nextInt(0, (int)candRem.size() - 1)];
							int p = grab_index_with_value(i0);
							if (p == -1) continue;
							dec_bucket_apply(i0);
						} else {
							extra--;
						}
						inc_bucket_apply(i1);
						int newVal = i1;
						A[p] = newVal;
						put_index_with_value(newVal, p);
						done = true;
						X.push_back(p + 1);
						Y.push_back(newVal);
					}
				} else {
					vector<int> candRem, candAdd;
					for (int i = 1; i <= N; i++) if (can_add_safe(i)) candAdd.push_back(i);
					for (int i = 1; i <= N; i++) if (can_remove_safe(i)) candRem.push_back(i);
					if (!candRem.empty() && !candAdd.empty()) {
						int i0 = candRem[rnd.nextInt(0, (int)candRem.size() - 1)];
						int i1 = candAdd[rnd.nextInt(0, (int)candAdd.size() - 1)];
						int p = grab_index_with_value(i0);
						if (p == -1) continue;
						dec_bucket_apply(i0);
						inc_bucket_apply(i1);
						int newVal = i1;
						A[p] = newVal;
						put_index_with_value(newVal, p);
						done = true;
						X.push_back(p + 1);
						Y.push_back(newVal);
					}
				}
			}

			if (!done) {
				int p = -1;
				if (!posExtra.empty()) {
					p = grab_index_with_value(N + 1);
					extra--;
				} else {
					int i0 = -1;
					for (int i = 1; i <= N; i++) if (!pos[i].empty()) {
						i0 = i; break;
					}
					if (i0 != -1) {
						p = grab_index_with_value(i0);
						dec_bucket_apply(i0);
					} else {
						p = 0;
					}
				}

				int i1 = (int)(rnd.nextInt(0, N - 1)) + 1;
				inc_bucket_apply(i1);
				int newVal = i1;
				A[p] = newVal;
				put_index_with_value(newVal, p);
				X.push_back(p + 1);
				Y.push_back(newVal);
			}

			if (X.back() < 1 || X.back() > N) {
				X.back() = rnd.nextInt(1, N);
			}
		}

		A = copyOfA;
	}
};