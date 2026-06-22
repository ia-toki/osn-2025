#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
#include <tcrand/graph.hpp>

using namespace std;
using namespace tcframe;
using namespace tcrand;

#define mp make_pair
#define fr first
#define sc second

const int MXN = 100000;
const int MXM = 200000;
const int MXQ = 100000;
const int MXW = 10000;
const int MXT = 1000000000;

const int INF = MXT * 2;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M;
	vector<int> U, V, W, Z;
	int Q;
	vector<int> T;

	vector<int> ans;

	bool testcaseShuffle;

	void InputFormat() {
		LINE(N, M);
		LINES(U, V, W, Z) % SIZE(M);
		LINE(Q);
		LINES(T) % SIZE(Q);
	}

	void OutputFormat() {
		LINES(ans) % SIZE(Q);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}

	void Constraints() {
		CONS(2 <= N && N <= MXN);
		CONS(1 <= M && M <= MXM);
		CONS(eachElementOf(U).isBetween(1, N));
		CONS(eachElementOf(V).isBetween(1, N));
		CONS(eachElementOf(W).isBetween(1, MXW));
		CONS(eachElementOf(Z).isBetween(1, 2));
		CONS(edgeOrientation(U, V));
		CONS(1 <= Q && Q <= MXQ);
		CONS(eachElementOf(T).isBetween(1, MXT));
	}

	void Subtask1() {
		CONS(eachElementOf(Z).isBetween(2, 2));
		CONS(eachElementOf(W).isBetween(1, 1));
		Points(1);
	}

	void Subtask2() {
		CONS(eachElementOf(Z).isBetween(2, 2));
		Points(2);
	}

	void Subtask3() {
		CONS(eachElementOf(Z).isBetween(1, 1));
		Points(3);
	}

	void Subtask4() {
		CONS(N <= 2000);
		CONS(M <= 2000);
		CONS(Q <= 2000);
		Points(4);
	}

	void Subtask5() {
		CONS(specialEdgeCondition(N, U, V, Z));
		Points(5);
	}

	void Subtask6() {
		CONS(N <= 2000);
		CONS(M <= 2000);
		Points(6);
	}

	void Subtask7() {
		Points(7);
	}

private:
	bool edgeOrientation(vector<int> &u, vector<int> &v) {
		for (int i = 0; i < u.size(); i++) {
			if (u[i] >= v[i]) {
				return false;
			}
		}
		return true;
	}

	bool specialEdgeCondition(int n, vector<int> &u, vector<int> &v, vector<int> &z) {
		for (int i = 0; i < u.size(); i++) {
			if (z[i] == 2) {
				if (v[i] != n) {
					return false;
				}
			}
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({4, 6, 7});
		Input
		({
			"4 4",
			"1 3 20 1",
			"2 3 30 2",
			"2 3 20 1",
			"2 4 10 2",
			"3",
			"100",
			"20",
			"1"
		});
		Output
		({
			"50",
			"60",
			"-1"
		});
	}

	void BeforeTestCase() {
		U.clear();
		V.clear();
		W.clear();
		Z.clear();
		T.clear();
		testcaseShuffle = true;
	}

	void AfterTestCase() {
		rnd.shuffle(T.begin(), T.end());

		vector<int> midVertex;
		for (int i = 2; i < N; i++) {
			midVertex.push_back(i);
		}
		rnd.shuffle(midVertex.begin(), midVertex.end());
		for (int i = 0; i < U.size(); i++) {
			if (U[i] != 1 && U[i] != N) {
				U[i] = midVertex[U[i] - 2];
			}
			if (V[i] != 1 && V[i] != N) {
				V[i] = midVertex[V[i] - 2];
			}
			if (U[i] > V[i]) swap(U[i], V[i]);
		}

		if (testcaseShuffle) {
			for (int i = 0; i < U.size(); i++) {
				int p = rnd.nextInt(0, i);
				swap(U[i], U[p]);
				swap(V[i], V[p]);
				swap(W[i], W[p]);
				swap(Z[i], Z[p]);
			}
		}
	}

	void TestGroup1() {
		Subtasks({1, 2, 4, 5, 6, 7});

		CASE({
			N = 2;
			M = 1;
			U = {1};
			V = {2};
			W = {1};
			Z = {2};
			Q = 3;
			T = {1, 2, 3};
		});
	}

	void TestGroup2() {
		Subtasks({1, 2, 4, 6, 7});

		CASE({
			pureRandomGraph(75, rnd.nextInt(1990, 2000), 2, 2, 1, 1);
			pureRandomQuery(2000);
		});

		CASE({
			pureRandomGraph(75, rnd.nextInt(1990, 2000), 2, 2, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(500, 0, rnd.nextInt(1990, 2000), 0, 1, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1500, 0, rnd.nextInt(1990, 2000), 0, 1, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(500, 0, rnd.nextInt(1990, 2000), 0, 2, 1, 1); // disconnected
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1800, 0, rnd.nextInt(1990, 2000), 0, 2, 1, 1);  // disconnected
			queryBasedOnResult(2000);
		});

		CASE({
			triangleChains(666, 1, 1, 2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			lineGraph(2000, 2000, false, false, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(10, rnd.nextInt(1990, 2000), 2, 2, 1, 1);
			queryBasedOnResult(2000);
		});
	}

	void TestGroup3() {
		Subtasks({1, 2, 7});

		CASE({
			triangleChains(33333, 1, 1, 2, 2);
			queryBasedOnResult(100000);
		});

		CASE({
			ribbonGraphSpecial(2, 1);
			queryOneToQ(100000);
		});
	}

	void TestGroup4() {
		Subtasks({2, 4, 5, 6, 7});

		CASE({
			N = 2;
			M = 1;
			U = {1};
			V = {2};
			W = {5};
			Z = {2};
			Q = 5;
			T = {3, 4, 5, 6, 7};
		});
	}

	void TestGroup5() {
		Subtasks({2, 4, 6, 7});

		CASE({
			pureRandomGraph(10, rnd.nextInt(1990, 2000), 2, 2);
			pureRandomQuery(2000);
		});

		CASE({
			pureRandomGraph(75, rnd.nextInt(1990, 2000), 2, 2);
			pureRandomQuery(2000);
		});

		CASE({
			pureRandomGraph(75, rnd.nextInt(1990, 2000), 2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(500, 0, rnd.nextInt(1990, 2000), 0, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(500, 0, rnd.nextInt(1990, 2000), 0, 2); // disconnected
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1800, 0, rnd.nextInt(1990, 2000), 0, 2);  // disconnected
			queryBasedOnResult(2000);
		});

		CASE({
			triangleChains(666, 4999, 9997, 2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			triangleChains(666, 4999, 9999, 2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			triangleChains(666, 4999, 9998, 2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			lineGraph(2000, 2000, false, false);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(10, rnd.nextInt(1990, 2000), 2, 2);
			queryBasedOnResult(2000);
		});
	}

	void TestGroup6() {
		Subtasks({2, 7});

		CASE({
			denseSmallGraph(2);
			queryOneToQ(100000);
		});

		CASE({
			ribbonGraphSpecial(2);
			queryOneToQ(100000);
		});

		CASE({
			killBFS();
			queryOneToQ(100000);
		});
	}

	void TestGroup7() {
		Subtasks({3, 4, 5, 6, 7});

		CASE({
			N = 2;
			M = 1;
			U = {1};
			V = {2};
			W = {5};
			Z = {1};
			Q = 5;
			T = {3, 4, 5, 6, 7};
		});

		CASE({
			pureRandomGraph(10, rnd.nextInt(1990, 2000), 1, 1);
			pureRandomQuery(2000);
		});

		CASE({
			pureRandomGraph(75, rnd.nextInt(1990, 2000), 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(500, rnd.nextInt(1990, 2000), 0, 1, 0);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1250, rnd.nextInt(1990, 2000), 0, 1, 0);
			queryOneToQ(2000);
		});

		CASE({
			randomConnected(1500, rnd.nextInt(1990, 2000), 0, 1, 0);
			queryOneToQ(1500);
		});

		CASE({
			randomConnected(500, rnd.nextInt(1990, 2000), 0, 2, 0); // disconnected
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1800, rnd.nextInt(1990, 2000), 0, 2, 0);  // disconnected
			queryOneToQ(2000);
		});

		CASE({
			triangleChains(666, 4999, 9997, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			triangleChains(666, 4999, 9999, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			lineGraph(2000, 0, false, false);
			queryBasedOnResult(2000);
		});

		CASE({
			lineGraph(2000, 0, true, false);
			queryOneToQ(2000);
		});

		CASE({
			lineGraph(2000, 0, true, true);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(10, rnd.nextInt(1990, 2000), 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(20, rnd.nextInt(1990, 2000), 1, 1);
			queryOneToQ(2000);
		});
	}

	void TestGroup8() {
		Subtasks({3, 5, 7});

		CASE({
			denseSmallGraph(1);
			queryOneToQ(100000);
		});

		CASE({
			ribbonGraphSpecial(1);
			queryOneToQ(100000);
		});
	}

	void TestGroup9() {
		Subtasks({4, 5, 6, 7});

		CASE({
			pureRandomGraph(10, rnd.nextInt(1990, 2000) - 5, 1, 1);
			specialStarRandom(10, 5);
			pureRandomQuery(2000);
		});

		CASE({
			pureRandomGraph(75, rnd.nextInt(1990, 2000) - 75, 1, 1);
			specialStarAll(75);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(500, rnd.nextInt(1990, 2000) - 500, 0, 1, 0);
			specialStarBasedOnResult(500, 450);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1250, rnd.nextInt(1990, 2000) - 250, 0, 1, 0);
			specialStarRandom(1250, 250);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1500, rnd.nextInt(1990, 2000) - 350, 0, 1, 0);
			specialStarBasedOnResult(1500, 350);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(500, rnd.nextInt(1990, 2000) - 500, 0, 2, 0); // disconnected
			specialStarAll(500);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1800, rnd.nextInt(1990, 2000) - 150, 0, 2, 0);  // disconnected
			specialStarBasedOnResult(1800, 150);
			queryBasedOnResult(2000);
		});

		CASE({
			randomConnected(1900, rnd.nextInt(1990, 2000) - 5, 0, 2, 0);  // disconnected
			specialStarRandom(1900, 5);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(10, rnd.nextInt(1990, 2000) - 5, 1, 1);
			specialStarRandom(10, 5);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(20, rnd.nextInt(1990, 2000) - 5, 1, 1);
			specialStarBasedOnResult(20, 5);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(10, rnd.nextInt(1990, 2000) - 10, 1, 1);
			specialStarAll(10);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(20, rnd.nextInt(1990, 2000) - 20, 1, 1);
			specialStarBasedOnResult(20, 19);
			queryBasedOnResult(2000);
		});
	}

	void TestGroup10() {
		Subtasks({4, 6, 7});

		CASE({
			ribbonGraph(1000);
			queryBasedOnResult(2000);
		});

		CASE({
			layeredGraph(950, 3);
			queryBasedOnResult(2000);
		});

		CASE({
			pureRandomGraph(10, rnd.nextInt(1990, 2000), 1, 2);
			pureRandomQuery(2000);
		});

		CASE({
			pureRandomGraph(75, rnd.nextInt(1990, 2000), 1, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(600, 1400);
			randomConnected(500, M1, M - M1, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(800, M1, M - M1, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(200, M1, M - M1, 1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			int M2 = rnd.nextInt(100, 150);
			randomConnected(1250, rnd.nextInt(1990, 2000) - M2, 0, 1, 0);
			addRandomType(1250, M2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			int M2 = rnd.nextInt(500, 700);
			randomConnected(800, rnd.nextInt(1990, 2000) - M2, 0, 1, 0);
			addRandomType(800, M2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(800, M1, M - M1, 1, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			int M1 = rnd.nextInt(100, 150);
			randomConnected(1250, 0, rnd.nextInt(1990, 2000) - M1, 0, 1);
			addRandomType(1250, M1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			int M1 = rnd.nextInt(500, 700);
			randomConnected(800, 0, rnd.nextInt(1990, 2000) - M1, 0, 1);
			addRandomType(800, M1, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(800, M1, M - M1, 2, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(800, M1, M - M1, 2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			N = 2000;
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(700, 1300), M2 = M - M1;
			M = 0;
			addRandomType(2000, M1, 1);
			addRandomType(2000, M2, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			triangleChains(666, 2, 3, 2, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			triangleChains(666, 2, 4, 2, 1);
			queryBasedOnResult(2000);
		});

		CASE({
			triangleChains(666, 2, 5, 1, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			lineGraph(2000, 1000, false, false);
			queryBasedOnResult(2000);
		});

		CASE({
			lineGraph(2000, 1000, false, false);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(10, rnd.nextInt(1990, 2000), 1, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			specialMultiedge(20, rnd.nextInt(1990, 2000), 1, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			compositeLineGraph(1000);
			queryBasedOnResult(2000);
		});

		CASE({
			doubleTree(1000);
			queryBasedOnResult(2000);
		});

		CASE({
			doubleTreeDisconnected(1000, 1, 2);
			queryBasedOnResult(2000);
		});

		CASE({
			doubleTreeDisconnected(1000, 2, 1);
			queryBasedOnResult(2000);
		});
	}

	void TestGroup11() {
		Subtasks({5, 6, 7});
		CASE({
			specialMultiedge(10, rnd.nextInt(1990, 2000) - 10, 1, 1);
			specialStarBasedOnResult(10, 8);
			queryBasedOnResult(100000);
		});
	}

	void TestGroup12() {
		Subtasks({5, 7});

		CASE({
			pureRandomGraph(100000, rnd.nextInt(199000, 200000) - 50000, 1, 1);
			specialStarBasedOnResult(100000, 50000);
			queryBasedOnResult(100000);
		});
	}

	void TestGroup13() {
		Subtasks({6, 7});

		CASE({
			pureRandomGraph(75, rnd.nextInt(1990, 2000), 1, 2);
			queryOneToQ(100000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(800, M1, M - M1, 1, 1);
			queryOneToQ(100000);
		});

		CASE({
			int M2 = rnd.nextInt(100, 150);
			randomConnected(1250, rnd.nextInt(1990, 2000) - M2, 0, 1, 0);
			addRandomType(1250, M2, 2);
			queryOneToQ(100000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(800, M1, M - M1, 1, 2);
			queryOneToQ(100000);
		});

		CASE({
			int M1 = rnd.nextInt(500, 700);
			randomConnected(800, 0, rnd.nextInt(1990, 2000) - M1, 0, 1);
			addRandomType(800, M1, 1);
			queryOneToQ(100000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(800, M1, M - M1, 2, 1);
			queryOneToQ(100000);
		});

		CASE({
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(850, 1150);
			randomConnected(800, M1, M - M1, 2, 2);
			queryOneToQ(100000);
		});

		CASE({
			N = 2000;
			M = rnd.nextInt(1990, 2000);
			int M1 = rnd.nextInt(700, 1300), M2 = M - M1;
			M = 0;
			addRandomType(2000, M1, 1);
			addRandomType(2000, M2, 2);
			queryOneToQ(100000);
		});

		CASE({
			triangleChains(666, 4999, 9999, 2, 1);
			queryOneToQ(100000);
		});

		CASE({
			triangleChains(666, 4999, 9998, 2, 1);
			queryOneToQ(100000);
		});

		CASE({
			triangleChains(666, 4999, 9997, 1, 2);
			queryOneToQ(100000);
		});

		CASE({
			lineGraph(2000, 1000, false, false);
			queryBasedOnResult(100000);
		});

		CASE({
			compositeLineGraph(1000);
			queryBasedOnResult(100000);
		});

		CASE({
			doubleTree(1000);
			queryBasedOnResult(100000);
		});

		CASE({
			doubleTreeDisconnected(1000, 1, 2);
			queryBasedOnResult(100000);
		});

		CASE({
			ribbonGraph(1000);
			queryOneToQ(100000);
		});

		CASE({
			layeredGraph(950, 4);
			queryBasedOnResult(100000);
		});
	}

	void TestGroup14() {
		Subtasks({7});

		CASE({
			doubleTree(100000);
			queryBasedOnResult(100000);
		});

		CASE({
			int M2 = rnd.nextInt(50000, 70000);
			randomConnected(100000, rnd.nextInt(199000, 200000) - M2, 0, 1, 0);
			addRandomType(100000, M2, 2);
			queryOneToQ(100000);
		});

		CASE({
			triangleChains(33333, 4999, 9999, 1, 2);
			queryBasedOnResult(100000);
		});

		CASE({
			layeredGraph(100000, 400);
			queryBasedOnResult(100000);
		});
	}

private:
	vector<int> rndArray(int sz, int lf, int rg) {
		vector<int> r;
		for (int i = 0; i < sz; i++) {
			r.push_back(rnd.nextInt(lf, rg));
		}
		return r;
	}

	pair<vector<int>, vector<int> > createPurelyRandomGraph(int n, int m) {
		vector<int> u, v;
		for (int i = 0; i < m; i++) {
			int uu = rnd.nextInt(1, n);
			int vv = rnd.nextInt(1, n);
			while (uu == vv) {
				vv = rnd.nextInt(1, n);
			}
			if (uu > vv) swap(uu, vv);
			u.push_back(uu);
			v.push_back(vv);
		}
		return make_pair(u, v);
	}

	pair<vector<int>, vector<int> > createRandomConnectedGraph(int n, int m) {
		// return createPurelyRandomGraph(n, m);
		vector<int> u, v;
		GraphRandomizer graph_rand;
		tie(u, v) = graph_rand.node_count(n).edge_count(m).index_base(1).next().edges();
		for (int i = 0; i < m; i++) {
			if (u[i] > v[i]) swap(u[i], v[i]);
		}
		return make_pair(u, v);
	}

	pair<vector<int>, vector<int> > createRandomTwoCCGraph(int n, int m) {
		// Create graph with 2 components, guarantee vertex 1 and vertex n are in different components
		int n1 = n / 2 - 1, n2 = n - n1;
		int m1 = m / 2 + 1, m2 = m - m1;

		pair<vector<int>, vector<int> > edge1 = createRandomConnectedGraph(n1, m1);
		pair<vector<int>, vector<int> > edge2 = createRandomConnectedGraph(n2, m2);
		for (int i = 0; i < m2; i++) {
			edge2.first[i] += n1;
			edge2.second[i] += n1;
			edge1.first.push_back(edge2.first[i]);
			edge1.second.push_back(edge2.second[i]);
		}

		return edge1;
	}

	void addRandomType(int n, int m, int type) {
		M += m;
		for (int i = 0; i < m; i++) {
			int u = rnd.nextInt(1, n);
			int v = rnd.nextInt(1, n);
			while (u == v) {
				v = rnd.nextInt(1, n);
			}
			if (u > v) swap(u, v);
			U.push_back(u);
			V.push_back(v);
			W.push_back(rnd.nextInt(1, MXW));
			Z.push_back(type);
		}
	}

	void pureRandomGraph(int n, int m, int zl = 1, int zr = 2, int wl = 1, int wr = MXW) {
		pair<vector<int>, vector<int> > edges = createPurelyRandomGraph(n, m);
		U = edges.first;
		V = edges.second;
		W = rndArray(m, wl, wr);
		Z = rndArray(m, zl, zr);

		N = n;
		M = m;
	}

	void randomConnected(int n, int m1, int m2, int c1, int c2, int wl = 1, int wr = MXW) {
		pair<vector<int>, vector<int> > edges1, edges2;
		W = rndArray(m1 + m2, wl, wr);

		if (m1 > 0) {
			if (c1 == 0) {
			edges1 = createPurelyRandomGraph(n, m1);
			} else if (c1 == 1) {
				edges1 = createRandomConnectedGraph(n, m1);
			} else if (c1 == 2) {
				edges1 = createRandomTwoCCGraph(n, m1);
			}
		}
		if (m2 > 0) {
			if (c2 == 0) {
				edges2 = createPurelyRandomGraph(n, m2);
			} else if (c2 == 1) {
				edges2 = createRandomConnectedGraph(n, m2);
			} else if (c2 == 2) {
				edges2 = createRandomTwoCCGraph(n, m2);
			}
		}

		for (int i = 0; i < m1 + m2; i++) {
			if (i < m1) Z.push_back(1);
			else Z.push_back(2);
		}

		for (int i = 0; i < m1; i++) {
			U.push_back(edges1.first[i]);
			V.push_back(edges1.second[i]);
		}

		for (int i = 0; i < m2; i++) {
			U.push_back(edges2.first[i]);
			V.push_back(edges2.second[i]);
		}

		N = n;
		M = m1 + m2;
	}

	void triangleChains(int x, int wu = 2, int wb = 4, int zu = 2, int zb = 2) {
		N = 2 * x - 1;
		M = 3 * x - 3;
		for (int i = 1; i < x; i++) {
			int lf = 2 * i - 1, rg = 2 * i + 1;
			U.push_back(lf);
			V.push_back(rg);
			W.push_back(wb);
			Z.push_back(zb);
		}
		for (int i = 1; i < x; i++){
			int u = 2 * i;
			int lf = 2 * i - 1, rg = 2 * i + 1;
			U.push_back(lf); V.push_back(u); W.push_back(wu); Z.push_back(zu);
			U.push_back(u); V.push_back(rg); W.push_back(wu); Z.push_back(zu);
		}
	}

	void lineGraph(int n, int cntz2, bool zr = false, bool last_edge_z1 = false, int wl = 1, int wr = MXW) {
		N = n;
		M = n - 1;

		vector<int> g(n - 1, 0);
		for (int i = n-1 - 1; i > n-1 - cntz2; i--) g[i] = 1;
		if (zr) {
			rnd.shuffle(g.begin(), g.end());
			if (last_edge_z1) {
				g.assign(n - 1, 0);
				for (int i = n-2 - 1; i > n-2 - cntz2; i--) g[i] = 1;
				rnd.shuffle(g.begin(), g.begin() + n - 2);
			}
		}

		for (int i = 1; i < n; i++) {
			U.push_back(i); V.push_back(i + 1); W.push_back(rnd.nextInt(wl, wr)); Z.push_back(g[i - 1] + 1);
		}
	}

	void compositeLineGraph(int n, int wl = 1, int wr = MXW) {
		N = n;
		M = 2 * (n - 1);
		for (int i = 1; i < n; i++) {
			U.push_back(i); V.push_back(i + 1); W.push_back(rnd.nextInt(wl, wr)); Z.push_back(1);
			U.push_back(i); V.push_back(i + 1); W.push_back(rnd.nextInt(wl, wr)); Z.push_back(2);
		}
	}

	void specialMultiedge(int n, int m, int zl = 1, int zr = 2, int wl = 1, int wr = MXW) {
		// do this for m >= n * (n - 1) / 2
		N = n; M = m;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				U.push_back(i); V.push_back(j); W.push_back(rnd.nextInt(wl, wr)); Z.push_back(rnd.nextInt(zl, zr));
			}
		}
		m -= n * (n - 1) / 2;
		while (m > 0) {
			int u = rnd.nextInt(1, n);
			int v = rnd.nextInt(1, n);
			while (u == v) v = rnd.nextInt(1, n);
			if (u > v) swap(u, v);
			U.push_back(u); V.push_back(v); W.push_back(rnd.nextInt(wl, wr)); Z.push_back(rnd.nextInt(zl, zr));
			m--;
		}
	}

	void killBFS() {
		N = 100000;
		for (int i = 1; i + 3 <= N; i += 3) {
			U.push_back(i);
			V.push_back(i + 3);
			W.push_back(4);
			Z.push_back(2);

			U.push_back(i);
			V.push_back(i + 1);
			W.push_back(1);
			Z.push_back(2);

			U.push_back(i + 1);
			V.push_back(i + 2);
			W.push_back(1);
			Z.push_back(2);

			U.push_back(i + 2);
			V.push_back(i + 3);
			W.push_back(1);
			Z.push_back(2);
		}
		M = U.size();
	}

	void ribbonGraphSpecial(int zf = -1, int wt = -1) {
		for (int i = 2; i <= 5001; ++i) {
			U.push_back(1);
			V.push_back(i);
			W.push_back(wt == -1 ? i - 1 : 1);
			Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);

			U.push_back(i);
			V.push_back(10002);
			W.push_back(wt == -1 ? MXW - 2 * i + 3 : 1);
			Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);
		}
		for (int i = 5002; i <= 10001; ++i) {
			U.push_back(1);
			V.push_back(i);
			W.push_back(wt == -1 ? i - 5001 : 1);
			Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);

			U.push_back(i);
			V.push_back(10002);
			W.push_back(wt == -1 ? MXW - 2 * (i - 5000) + 4 : 1);
			Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);
		}
		int rest = (MXM - U.size()) / 2;
		N = min(10003 + rest, MXN);
		for (int i = 10003; i < N; i++) {
			U.push_back(10002);
			V.push_back(i);
			W.push_back(wt == -1 ? rnd.nextInt(1, MXW) : 1);
			Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);

			U.push_back(i);
			V.push_back(N);
			W.push_back(wt == -1 ? rnd.nextInt(1, MXW) : 1);
			Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);
		}
		M = U.size();
	}

	void layeredRibbonGraph(int _N, int zf = -1) {
		N = _N;
		int used = 0, start = 1, blocks = 0;

		auto addRibbonBlock = [&](int start, int end) {
			int L = end - start + 1;
			int mid = start + L / 2;
			for (int i = start + 2; i < mid; i++) {
				U.push_back(start);
				V.push_back(i);
				W.push_back(i % 4999);
				Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);

				U.push_back(i);
				V.push_back(mid);
				W.push_back(max(1, MXW - (i % 4999) * 2));
				Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);
			}
			for (int i = mid + 1; i < end; i++) {
				U.push_back(end);
				V.push_back(i);
				W.push_back(i % 4999);
				Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);

				U.push_back(i);
				V.push_back(mid);
				W.push_back(max(1, MXW - (i % 4999) * 2));
				Z.push_back(zf == -1 ? rnd.nextInt(1, 2) : zf);
			}
		};

		while (used < N) {
			int remaining = N - used;
			int sz = min(4999, remaining);
			int bStart = start, bEnd = start + sz - 1;
			addRibbonBlock(bStart, bEnd);
			if (blocks > 0) {
				int prevEnd = bStart - 1;
				U.push_back(prevEnd);
				V.push_back(bStart);
				W.push_back(1);
				Z.push_back(zf == 1 ? 1 : 2);
			}
			used += sz;
			start += sz;
			blocks++;
		}

		M = U.size();
	}

	void layeredGraph(int n, int X, int zf = -1) {
		N = n;
		vector<vector<int> > layers;
		int fi = 2, la = N - 1;
		int remaining = max(0, la - fi + 1);
		int L = (remaining == 0 ? 0 : ((remaining + X - 1) / X));
		int cur = fi;
		for (int i = 0; i < L; i++) {
			int take = min(X, la - cur + 1);
			vector<int> layer;
			for (int j = 0; j < take; j++) {
				layer.push_back(cur++);
			}
			layers.push_back(move(layer));
		}

		auto add_edge = [&](int x, int y, int layer_id) {
			if (x == y) return;
			if (x > y) swap(x, y);
			double p0 = 0.4, pL = 0.75;
			double p = (L == 0 ? pL : p0 + (pL - p0) * (double)layer_id / (double)L);
			int zt = 1;
			if (rnd.nextDouble(0.0, 1.0) < p) zt = 2;
			if (1 <= zf && zf <= 2) zt = zf;
			U.push_back(x);
			V.push_back(y);
			W.push_back(rnd.nextInt(1, MXW));
			Z.push_back(zt);
		};

		if (!layers.empty()) {
			for (int v : layers.front())
				add_edge(1, v, 0);
		}

		for (int k = 1; k < layers.size(); k++) {
			const auto &A = layers[k - 1];
			const auto &B = layers[k];
			int szA = A.size(), szB = B.size();
			for (int i = 0; i < szA; i++) {
				int u = A[i];
				if (szB == 1) {
					add_edge(u, B[0], k);
					add_edge(u, N, k);
				} else {
					add_edge(u, B[i % szB], k);
					add_edge(u, B[(i + 1) % szB], k);
				}
			}
		}

		if (!layers.empty()) {
			for (int v : layers.back())
				add_edge(v, N, L);
		}

		M = U.size();
	}

	void denseSmallGraph(int zf) {
		N = 3;
		M = MXM;
		testcaseShuffle = false;
		for (int i = MXW; i >= 1; i--) {
			U.push_back(1); V.push_back(2);
			W.push_back(i); Z.push_back(zf);
		}
		for (int i = 0; i < M - MXW; i++) {
			U.push_back(2); V.push_back(3);
			W.push_back(MXW); Z.push_back(zf);
		}
	}

	void ribbonGraph(int _N) {
		N = _N;
		int mid = N / 2;
		for (int i = 2; i < mid; ++i) {
			U.push_back(1);
			V.push_back(i);
			W.push_back(i);
			Z.push_back(rnd.nextInt(1, 2));

			U.push_back(i);
			V.push_back(mid);
			W.push_back(MXW - i*2);
			Z.push_back(rnd.nextInt(1, 2));
		}

		for (int i = mid + 1; i < N; ++i) {
			U.push_back(N);
			V.push_back(i);
			W.push_back(i);
			Z.push_back(rnd.nextInt(1, 2));

			U.push_back(i);
			V.push_back(mid);
			W.push_back(MXW - i*2);
			Z.push_back(rnd.nextInt(1, 2));
		}
		M = U.size();
	}

	void doubleTree(int n, int wl = 1, int wr = MXW) {
		N = n;
		M = 2 * n - 2;
		pair<vector<int>, vector<int> > edges1, edges2;
		edges1 = createRandomConnectedGraph(n, n - 1);
		edges2 = createRandomConnectedGraph(n, n - 1);

		for (int i = 0; i < n - 1; i++) {
			U.push_back(edges1.first[i]);
			V.push_back(edges1.second[i]);
			W.push_back(rnd.nextInt(wl, wr));
			Z.push_back(1);
		}

		for (int i = 0; i < n - 1; i++) {
			U.push_back(n + 1 - edges2.second[i]);
			V.push_back(n + 1 - edges2.first[i]);
			W.push_back(rnd.nextInt(wl, wr));
			Z.push_back(2);
		}
	}

	void doubleTreeDisconnected(int n, int cu = 1, int du = 2, int wl = 1, int wr = MXW) {
		N = n;
		M = 2 * n - 4;
		pair<vector<int>, vector<int> > edges1, edges2;
		edges1 = createRandomConnectedGraph(n - 1, n - 2);
		edges2 = createRandomConnectedGraph(n - 1, n - 2);

		for (int i = 0; i < n - 2; i++) { // 1 .. n-1
			U.push_back(edges1.first[i]);
			V.push_back(edges1.second[i]);
			W.push_back(rnd.nextInt(wl, wr));
			Z.push_back(cu);
		}

		for (int i = 0; i < n - 2; i++) { // 2 .. n
			U.push_back(1 + edges2.first[i]);
			V.push_back(1 + edges2.second[i]);
			W.push_back(rnd.nextInt(wl, wr));
			Z.push_back(du);
		}
	}

	void specialStarRandom(int n, int m) {
		M += m;
		for (int i = 0; i < m; i++) {
			int g = rnd.nextInt(1, n - 1);
			U.push_back(g);
			V.push_back(n);
			W.push_back(rnd.nextInt(1, MXW));
			Z.push_back(2);
		}
	}

	void specialStarAll(int n) {
		M += n - 1;
		for (int i = 1; i < n; i++) {
			U.push_back(i);
			V.push_back(n);
			W.push_back(rnd.nextInt(1, MXW));
			Z.push_back(2);
		}
	}

	void specialStarBasedOnResult(int n, int m) {
		M += m;
		vector<vector<pair<int, int> > > adj(n+1);
		vector<int> dist(n + 1, INF);
		for (int i = 1; i <= n; i++) { 
			adj[i].clear(); dist[i] = INF; 
		} 
		for (int i = 0; i < U.size(); i++) { 
			adj[U[i]].push_back(make_pair(V[i], W[i])); 
			adj[V[i]].push_back(make_pair(U[i], W[i])); 
		} 
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq; 
		dist[1] = 0; 
		pq.push(make_pair(0, 1)); 
		for (; !pq.empty(); pq.pop()) { 
			int dst = pq.top().first; 
			int nw = pq.top().second; 
			if (dst > dist[nw]) continue; 
			for (pair<int, int> e : adj[nw]) { 
				int nx = e.first; int wt = e.second; 
				if (dist[nx] > dist[nw] + wt) { 
					dist[nx] = dist[nw] + wt; 
					pq.push(make_pair(dist[nx], nx)); 
				} 
			} 
		} 
		vector<pair<int, int> > dtdt; 
		for (int i = 1; i < n; i++) 
			dtdt.push_back(make_pair(max(min(dist[i], MXT), 1), i)); 
		rnd.shuffle(dtdt.begin(), dtdt.end());
		vector<pair<int, int> > use;
		for (int i = 0; i < m; i++) use.push_back(dtdt[i]);
		sort(use.begin(), use.end());
		for (int i = 0; i < m; i++) {
			U.push_back(use[i].second);
			V.push_back(n);
			W.push_back(min(MXW, max(1, MXT - 2 * use[i].first)));
			Z.push_back(2);
		}
	}

	void pureRandomQuery(int q) {
		Q = q;
		for (int i = 0; i < q; i++) {
			T.push_back(rnd.nextInt(1, MXT));
		}
	}

	void queryOneToQ(int q) {
		Q = q;
		for (int i = 0; i < q; i++) {
			T.push_back(i + 1);
		}
	}

	void queryBasedOnResult(int q) {
		Q = q;
		int n = N;
		vector<vector<pair<int, int> > > adj(n+1);
		vector<int> dist(n + 1, INF);
		for (int i = 1; i <= n; i++) { 
			adj[i].clear(); dist[i] = INF; 
		} 
		for (int i = 0; i < U.size(); i++) { 
			adj[U[i]].push_back(make_pair(V[i], W[i])); 
			adj[V[i]].push_back(make_pair(U[i], W[i])); 
		} 
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq; 
		dist[1] = 0; 
		pq.push(make_pair(0, 1)); 
		for (; !pq.empty(); pq.pop()) { 
			int dst = pq.top().first; 
			int nw = pq.top().second; 
			if (dst > dist[nw]) continue; 
			for (pair<int, int> e : adj[nw]) { 
				int nx = e.first; int wt = e.second; 
				if (dist[nx] > dist[nw] + wt) { 
					dist[nx] = dist[nw] + wt; 
					pq.push(make_pair(dist[nx], nx)); 
				} 
			} 
		} 
		vector<int> dtdt; 
		for (int i = 1; i <= n; i++) 
			dtdt.push_back(max(min(dist[i], MXT), 1)); 
		sort(dtdt.begin(), dtdt.end());
		T = dtdt;
		if (T.size() < q) T.push_back(MXT);
		while (T.size() < q) {
			int gt = rnd.nextInt(1, n);
			T.push_back(max(min(dist[gt] + rnd.nextInt(-100, 100), MXT), 1));
		}
	}
};