#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int MAX_N = 256;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, X1, Y1, X2, Y2;	

	int K;
	string S;

	void InputFormat() {
		LINE(N, X1, Y1, X2, Y2);
	}
	
	void OutputFormat() {
		LINE(K);
		LINE(S);
	}

	void StyleConfig() {
		CustomScorer();
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}
	
	void Constraints() {
		CONS(valueOf(N).isBetween(2, MAX_N));
		CONS(isPowerOfTwo(N));
		CONS(valueOf(X1).isBetween(1, N));
		CONS(valueOf(Y1).isBetween(1, N));
		CONS(valueOf(X2).isBetween(1, N));
		CONS(valueOf(Y2).isBetween(1, N));
		CONS(abs(X1 - X2) + abs(Y1 - Y2) == 1);
	}

	void Subtask1() {
		Points(12);
		CONS(N == 2);
		CONS(X1 == 1);
		CONS(Y1 == 1);
	}
	
	void Subtask2() {
		Points(22);
		CONS(N <= 4);
	}
	
	void Subtask3() {
		Points(22);
		CONS(N <= 16);
		CONS(X1 == 1);
		CONS(Y1 == 1);
	}
	
	void Subtask4() {
		Points(22);
		CONS(N <= 16);
	}
	
	void Subtask5() {
		Points(22);
	}
	
private:
	bool isPowerOfTwo(int x) {
		while (x % 2 == 0) x /= 2;
		return (x == 1);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1, 2, 3, 4, 5});
		
		Input({
			"2 1 1 1 2"
		});
		Output({
			"3",
			"STU",
		});
	}
	
	void SampleTestCase2() {
		Subtasks({2, 4, 5});
		
		Input({
			"4 3 2 2 2"
		});
		/*
		Output({
			"19",
			"UUBSTTUTSSSBUBSBUUT",
		});
		*/
		Output({
			"15",
			"TTSBBBUUUTTTSBB",
		});
	}

	void TestGroup1() {
		Subtasks({1, 2, 3, 4, 5});
		
		CASE(N = 2, X1 = 1, Y1 = 1, X2 = 1, Y2 = 2);
		CASE(N = 2, X1 = 1, Y1 = 1, X2 = 2, Y2 = 1);
	}

	void TestGroup2() {
		Subtasks({2, 3, 4, 5});
		
		CASE(N = 4, X1 = 1, Y1 = 1, X2 = 1, Y2 = 2);
		CASE(N = 4, X1 = 1, Y1 = 1, X2 = 2, Y2 = 1);
	}
	
	void TestGroup3() {
		Subtasks({3, 4, 5});
		
		CASE(N = 8, X1 = 1, Y1 = 1, X2 = 1, Y2 = 2);
		CASE(N = 8, X1 = 1, Y1 = 1, X2 = 2, Y2 = 1);
		CASE(N = 16, X1 = 1, Y1 = 1, X2 = 1, Y2 = 2);
		CASE(N = 16, X1 = 1, Y1 = 1, X2 = 2, Y2 = 1);
	}
	
	void TestGroup4() {
		Subtasks({5});
		
		CASE(N = 32, X1 = 1, Y1 = 1, X2 = 1, Y2 = 2);
		CASE(N = 32, X1 = 1, Y1 = 1, X2 = 2, Y2 = 1);
		CASE(N = 64, X1 = 1, Y1 = 1, X2 = 1, Y2 = 2);
		CASE(N = 64, X1 = 1, Y1 = 1, X2 = 2, Y2 = 1);
		CASE(N = 128, X1 = 1, Y1 = 1, X2 = 1, Y2 = 2);
		CASE(N = 128, X1 = 1, Y1 = 1, X2 = 2, Y2 = 1);
		CASE(N = 256, X1 = 1, Y1 = 1, X2 = 1, Y2 = 2);
		CASE(N = 256, X1 = 1, Y1 = 1, X2 = 2, Y2 = 1);
	}
	
	void TestGroup5() {
		Subtasks({2, 4, 5});
		
		CASE(N = 2, X1 = 1, Y1 = 2, X2 = 1, Y2 = 1);
		CASE(N = 2, X1 = 1, Y1 = 2, X2 = 2, Y2 = 2);
		CASE(N = 2, X1 = 2, Y1 = 1, X2 = 1, Y2 = 1);
		CASE(N = 2, X1 = 2, Y1 = 1, X2 = 2, Y2 = 2);
		CASE(N = 2, X1 = 2, Y1 = 2, X2 = 2, Y2 = 1);
		CASE(N = 2, X1 = 2, Y1 = 2, X2 = 1, Y2 = 2);
	}

	void TestGroup6() {
		Subtasks({2, 4, 5});
		
		CASE(N = 4, X1 = 1, Y1 = 2, X2 = 1, Y2 = 1);
		CASE(N = 4, X1 = 2, Y1 = 1, X2 = 1, Y2 = 1);
		
		CASE(N = 4, X1 = 1, Y1 = N, X2 = 2, Y2 = N);
		CASE(N = 4, X1 = 1, Y1 = N, X2 = 1, Y2 = N - 1);
		CASE(N = 4, X1 = 2, Y1 = N, X2 = 1, Y2 = N);
		CASE(N = 4, X1 = 1, Y1 = N - 1, X2 = 1, Y2 = N);
		
		CASE(N = 4, X1 = N, Y1 = 1, X2 = N, Y2 = 2);
		CASE(N = 4, X1 = N, Y1 = 1, X2 = N - 1, Y2 = 1);
		CASE(N = 4, X1 = N, Y1 = 2, X2 = N, Y2 = 1);
		CASE(N = 4, X1 = N - 1, Y1 = 1, X2 = N, Y2 = 1);
		
		CASE(N = 4, X1 = N, Y1 = N, X2 = N, Y2 = N - 1);
		CASE(N = 4, X1 = N, Y1 = N, X2 = N - 1, Y2 = N);
		CASE(N = 4, X1 = N, Y1 = N - 1, X2 = N, Y2 = N);
		CASE(N = 4, X1 = N - 1, Y1 = N, X2 = N, Y2 = N);
		
		twoOnEdges(4);
		oneOnEdges(4);
		zeroOnEdges(4);
	}
	
	void TestGroup7() {
		Subtasks({4, 5});
		
		CASE(N = 16, X1 = 1, Y1 = 2, X2 = 1, Y2 = 1);
		CASE(N = 16, X1 = 2, Y1 = 1, X2 = 1, Y2 = 1);
		
		CASE(N = 16, X1 = 1, Y1 = N, X2 = 2, Y2 = N);
		CASE(N = 16, X1 = 1, Y1 = N, X2 = 1, Y2 = N - 1);
		CASE(N = 16, X1 = 2, Y1 = N, X2 = 1, Y2 = N);
		CASE(N = 16, X1 = 1, Y1 = N - 1, X2 = 1, Y2 = N);
		
		CASE(N = 16, X1 = N, Y1 = 1, X2 = N, Y2 = 2);
		CASE(N = 16, X1 = N, Y1 = 1, X2 = N - 1, Y2 = 1);
		CASE(N = 16, X1 = N, Y1 = 2, X2 = N, Y2 = 1);
		CASE(N = 16, X1 = N - 1, Y1 = 1, X2 = N, Y2 = 1);
		
		CASE(N = 16, X1 = N, Y1 = N, X2 = N, Y2 = N - 1);
		CASE(N = 16, X1 = N, Y1 = N, X2 = N - 1, Y2 = N);
		CASE(N = 16, X1 = N, Y1 = N - 1, X2 = N, Y2 = N);
		CASE(N = 16, X1 = N - 1, Y1 = N, X2 = N, Y2 = N);
		
		twoOnEdges(16);
		oneOnEdges(16);
		zeroOnEdges(16);
	}
	
	void TestGroup8() {
		Subtasks({5});
		
		CASE(N = MAX_N, X1 = 1, Y1 = 2, X2 = 1, Y2 = 1);
		CASE(N = MAX_N, X1 = 2, Y1 = 1, X2 = 1, Y2 = 1);
		
		CASE(N = MAX_N, X1 = 1, Y1 = N, X2 = 2, Y2 = N);
		CASE(N = MAX_N, X1 = 1, Y1 = N, X2 = 1, Y2 = N - 1);
		CASE(N = MAX_N, X1 = 2, Y1 = N, X2 = 1, Y2 = N);
		CASE(N = MAX_N, X1 = 1, Y1 = N - 1, X2 = 1, Y2 = N);
		
		CASE(N = MAX_N, X1 = N, Y1 = 1, X2 = N, Y2 = 2);
		CASE(N = MAX_N, X1 = N, Y1 = 1, X2 = N - 1, Y2 = 1);
		CASE(N = MAX_N, X1 = N, Y1 = 2, X2 = N, Y2 = 1);
		CASE(N = MAX_N, X1 = N - 1, Y1 = 1, X2 = N, Y2 = 1);
		
		CASE(N = MAX_N, X1 = N, Y1 = N, X2 = N, Y2 = N - 1);
		CASE(N = MAX_N, X1 = N, Y1 = N, X2 = N - 1, Y2 = N);
		CASE(N = MAX_N, X1 = N, Y1 = N - 1, X2 = N, Y2 = N);
		CASE(N = MAX_N, X1 = N - 1, Y1 = N, X2 = N, Y2 = N);
		
		twoOnEdges(MAX_N);
		oneOnEdges(MAX_N);
		zeroOnEdges(MAX_N);
	}

private:
	void twoOnEdges(int n) {
		CASE(N = n, X1 = 1, Y1 = rnd.nextInt(2, N - 2), X2 = 1, Y2 = Y1 + 1);
		CASE(N = n, X2 = 1, Y2 = rnd.nextInt(2, N - 2), X1 = 1, Y1 = Y2 + 1);
		CASE(N = n, X1 = N, Y1 = rnd.nextInt(2, N - 2), X2 = N, Y2 = Y1 + 1);
		CASE(N = n, X2 = N, Y2 = rnd.nextInt(2, N - 2), X1 = N, Y1 = Y2 + 1);
		
		CASE(N = n, X1 = rnd.nextInt(2, N - 2), Y1 = 1, X2 = X1 + 1, Y2 = 1);
		CASE(N = n, X2 = rnd.nextInt(2, N - 2), Y2 = 1, X1 = X2 + 1, Y1 = 1);
		CASE(N = n, X1 = rnd.nextInt(2, N - 2), Y1 = N, X2 = X1 + 1, Y2 = N);
		CASE(N = n, X2 = rnd.nextInt(2, N - 2), Y2 = N, X1 = X2 + 1, Y1 = N);
	}
	
	void oneOnEdges(int n) {
		CASE(N = n, X1 = 1, Y1 = rnd.nextInt(2, N - 1), X2 = 2, Y2 = Y1);
		CASE(N = n, X2 = 1, Y2 = rnd.nextInt(2, N - 1), X1 = 2, Y1 = Y2);
		CASE(N = n, X1 = N, Y1 = rnd.nextInt(2, N - 1), X2 = N - 1, Y2 = Y1);
		CASE(N = n, X2 = N, Y2 = rnd.nextInt(2, N - 1), X1 = N - 1, Y1 = Y2);
		
		CASE(N = n, X1 = rnd.nextInt(2, N - 1), Y1 = 1, X2 = X1, Y2 = 2);
		CASE(N = n, X2 = rnd.nextInt(2, N - 1), Y2 = 1, X1 = X2, Y1 = 2);
		CASE(N = n, X1 = rnd.nextInt(2, N - 1), Y1 = N, X2 = X1, Y2 = N - 1);
		CASE(N = n, X2 = rnd.nextInt(2, N - 1), Y2 = N, X1 = X2, Y1 = N - 1);
	}
	
	void zeroOnEdges(int n) {
		CASE(N = n, X1 = rnd.nextInt(2, N - 2), Y1 = rnd.nextInt(2, N - 1), X2 = X1 + 1, Y2 = Y1);
		CASE(N = n, X1 = rnd.nextInt(2, N - 1), Y1 = rnd.nextInt(2, N - 2), X2 = X1, Y2 = Y1 + 1);
		CASE(N = n, X1 = rnd.nextInt(3, N - 1), Y1 = rnd.nextInt(2, N - 1), X2 = X1 - 1, Y2 = Y1);
		CASE(N = n, X1 = rnd.nextInt(2, N - 1), Y1 = rnd.nextInt(3, N - 1), X2 = X1, Y2 = Y1 - 1);
	}
};

