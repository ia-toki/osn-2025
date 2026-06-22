#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

using ll = long long;

const int MAXN = 100000;
const int MAXV = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> H, P;

    ll ans;

    void InputFormat() {
        LINE(N);
        LINE(H % SIZE(N));
        LINE(P % SIZE(N));
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(valueOf(N).isBetween(1, MAXN));
        CONS(eachElementOf(H).isBetween(1, MAXV));
        CONS(eachElementOf(P).isBetween(0, MAXV));
        CONS(atLeastOneZeroInP());
    }

    void Subtask1() {
        Points(25);
        CONS(exactlyOneZeroInP());
    }

    void Subtask2() {
        Points(25);
        CONS(N <= 2000);
    }

    void Subtask3() {
        Points(25);
        CONS(eachElementofPIsLessThanOrEqualToCorrespondingH());
    }

    void Subtask4() {
        Points(25);
    }

private:
    bool atLeastOneZeroInP() {
        for (int p : P) {
            if (p == 0) {
                return true;
            }
        }
        return false;
    }

    bool exactlyOneZeroInP() {
        int cnt = 0;
        for (int p : P) {
            if (p == 0) {
                cnt++;
            }
        }
        return cnt == 1;
    }

    bool eachElementofPIsLessThanOrEqualToCorrespondingH() {
        for (int i = 0; i < N; i++) {
            if (P[i] > H[i]) {
                return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({2, 4});
        Input({
            "10",
            "7 4 10 9 2 3 6 6 6 4",
            "0 3 0 0 5 1 0 0 0 7"
        });
        Output({"30"});
    }

    void SampleTestCase2() {
        Subtasks({2, 4});
        Input({
            "5",
            "10 20 50 20 10",
            "0 50 15 50 0",
        });
        Output({"35"});
    }

    void SampleTestCase3() {
        Subtasks({1, 2, 3, 4});
        Input({
            "4",
            "10 20 30 40",
            "10 10 10 0",
        });
        Output({"40"});
    }

    void TestGroup1() {
        Subtasks({1, 2, 4});

        CASE(N = 2, H = {10, 5}, P = {0, 10});

        CASE(N = 2000, randomH(), randomP(), randomZeroesInP(1));
        CASE(N = 2000, randomH(), randomP(), randomZeroesInP(1));
    }

    void TestGroup2() {
        Subtasks({1, 2, 3, 4});

        CASE(N = 1, H = {1}, P = {0});
        CASE(N = 2, H = {40, 20}, P = {10, 0});
        CASE(N = 2, H = {20, 40}, P = {10, 0});
    }

    void TestGroup3() {
        Subtasks({1, 4});

        CASE(N = MAXN, randomH(), randomP(), randomZeroesInP(1));
    }

    void TestGroup4() {
        Subtasks({2, 4});

        CASE(
            N = 14,
            H = {1, 1, 10, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1},
            P = {1, 2,  1, 2, 1, 2,  1, 2, 0, 0, 0, 0, 0, 0}
        );

        CASE(
            N = 6;
            H = {5, 2, 5, 1, 1, 1};
            P = {1, 4, 1, 0, 0, 0};
        );

        CASE(N = 100, randomH(100), randomP(100), randomZeroesInP(10));
        CASE(N = 100, randomH(100), randomP(150), randomZeroesInP(10));
        CASE(N = 100, randomH(100), randomP(200), randomZeroesInP(10));

        CASE(N = 2000, randomH(100), randomP(100), randomZeroesInP(5));
        CASE(N = 2000, randomH(100), randomP(200), randomZeroesInP(1000));
    }

    void TestGroup5() {
        Subtasks({2, 3, 4});

        CASE(N = 100, randomHGreaterThanOrEqualToP(), randomZeroesInP(10));
        CASE(N = 2000, randomHGreaterThanOrEqualToP(), randomZeroesInP(100));
    }

    void TestGroup6() {
        Subtasks({3, 4});

        CASE(N = MAXN, randomHGreaterThanOrEqualToP(100), randomZeroesInP(10));
        CASE(N = MAXN, randomHGreaterThanOrEqualToP(1000), randomZeroesInP(10000));
        CASE(N = MAXN, randomHGreaterThanOrEqualToP(), randomZeroesInP(MAXN));
    }

    void TestGroup7() {
        Subtasks({4});

        CASE(N = MAXN, randomH(100), randomP(200), randomZeroesInP(1000));
        CASE(N = MAXN, randomH(1000), randomP(1000), randomZeroesInP(MAXN-100));
        CASE(N = MAXN, randomH(), randomP(), randomZeroesInP(MAXN/2));
        CASE(N = MAXN, randomH(), randomP(), randomZeroesInP(MAXN/2));
    }

private:
    void randomH(int maks = MAXV) {
        H.resize(N);
        for (int i = 0; i < N; i++) {
            H[i] = rnd.nextInt(1, maks);
        }
    }

    void randomP(int maks = MAXV) {
        P.resize(N);
        for (int i = 0; i < N; i++) {
            P[i] = rnd.nextInt(0, maks);
        }
    }

    void randomHGreaterThanOrEqualToP(int maks = MAXV) {
        H.resize(N);
        P.resize(N);
        for (int i = 0; i < N; i++) {
            H[i] = rnd.nextInt(1, maks);
            P[i] = rnd.nextInt(0, H[i]);
        }
    }

    void randomZeroesInP(int zeroes) {
        for (int i = 0; i < zeroes; i++) {
            P[rnd.nextInt(0, N - 1)] = 0;
        }
    }
};
