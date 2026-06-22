#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int MAX_N = 500000;
const int MAX_N_SMALL = 5000;
const long long MAX_A = 1000000000000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	vector<long long> A;
	vector<long long> B;

	void InputFormat() {
		LINE(N);
		LINES(A) % SIZE(N);
	}
	
	void OutputFormat() {
		LINES(B) % SIZE(N);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}
	
	void Constraints() {
		CONS(valueOf(N).isBetween(1, MAX_N));
		CONS(eachElementOf(A).isBetween(1, MAX_A));
	}
	
	void Subtask1() {
		CONS(N <= MAX_N_SMALL);
		Points(50);
	}
	
	void Subtask2() {
		Points(50);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1, 2});
		Input({
			"5",
			"100",
			"200",
			"75",
			"100",
			"325",
		});
		Output({
			"325",
			"100",
			"75",
			"200",
			"100",
		});
	}
	
	void SampleTestCase2() {
		Subtasks({1, 2});
		Input({
			"1",
			"1000000000000000000",
		});
		Output({
			"1000000000000000000",
		});
	}

	void TestGroup1() {
		Subtasks({1, 2});
		CASE(N = 1; A = {1});
		CASE(N = 2; A = {MAX_A, 1});
		
		for (int i = 3; i <= 5; i++) {
			CASE(N = MAX_N_SMALL; generateRandomA());
		}
	}
	
	void TestGroup2() {
		Subtasks({2});

		for (int i = 1; i <= 3; i++) {
			CASE(N = MAX_N; generateRandomA());
		}
	}
	
private:
	void generateRandomA() {
		A.clear();
		for (int i = 0; i < N; i++) {
			A.push_back(rnd.nextLongLong(1, MAX_A));
		}
	}
};
