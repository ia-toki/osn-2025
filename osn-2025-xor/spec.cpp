#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int LOGN = 19;
const int MAXN = 1 << LOGN;
const int MAXQ = 200000;
const int MAXA = 1'000'000;

const int LOG_SMALLN = 10;
const int SMALLN = 1 << LOG_SMALLN;
const int SMALLQ = 1000;

const int LSQRTN = 16;
const int SQRTN = 1 << LSQRTN;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, Q;
  vector<int> A;
  vector<vector<int>> Ops;

  int query_count;
  vector<long long> Ans;

  void InputFormat() {
    LINE(N, Q);
    LINE(A % SIZE(N));
    LINES(Ops) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(Ans) % SIZE(query_count);
  }

  void BeforeOutputFormat() {
    query_count = 0;
    for (auto Op : Ops) {
      if (Op[0] == 2 || Op[0] == 3) {
        ++query_count;
      }
    }
  }

  void Constraints() {
    CONS(valueOf(N).isBetween(2, MAXN));
    CONS((N & -N) == N); // N is 2^k
    CONS(valueOf(Q).isBetween(1, MAXQ));
    CONS(eachElementOf(A).isBetween(1, MAXA));
    CONS(validOps(Ops));
  }

  void Subtask1() {
    Points(1);

    CONS(N <= SMALLN);
    CONS(Q <= SMALLQ);
  }

  void Subtask2() {
    Points(2);

    CONS(all_of(Ops.begin(), Ops.end(), [&](vector<int> op) {
      return op[0] != 1;
    }));
  }

  void Subtask3() {
    Points(3);

    CONS(updateBeforeQuery(Ops));
  }

  void Subtask4() {
    Points(4);

    CONS(all_of(Ops.begin(), Ops.end(), [&](vector<int> op) {
      return op[0] != 3;
    }));
  }

  void Subtask5() {
    Points(20);

    CONS(N <= SQRTN);
  }

  void Subtask6() {
    Points(30);

    CONS(all_of(Ops.begin(), Ops.end(), [&](vector<int> op) {
      return op[0] == 1 || (op[1] == 0 && op[2] == N - 1);
    }));
  }

  void Subtask7() {
    Points(40);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

private:

  bool validOps(vector<vector<int>> Ops) {
    for (auto op : Ops) {
      if (op.empty()) {
        return false;
      }

      if (op[0] == 1) {
        if (op.size() != 2) {
          return false;
        }

        if (!valueOf(op[1]).isBetween(0, N - 1)) {
          return false;
        }
      } else if (op[0] == 2 || op[0] == 3) {
        if (op.size() != 3) {
          return false;
        }

        int l = op[1], r = op[2];
        if (l < 0 || r < l || r >= N) {
          return false;
        }
      } else {
        return false;
      }
    }
    return true;
  }

  bool updateBeforeQuery(vector<vector<int>> Ops) {
    bool startQuery = false;
    for (auto op : Ops) {
      if (op[0] == 1) {
        if (startQuery) {
          return false;
        }
      } else {
        startQuery = true;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1, 5, 7});
    Input({
      "8 5",
      "1 2 3 4 5 6 7 8",
      "1 3",
      "2 1 6",
      "1 7",
      "2 0 7",
      "3 2 7",
    });
    Output({
      "27",
      "36",
      "73",
    });
  }

  void BeforeTestCase() {
    N = 0; Q = 0;
    A.clear();
    Ops.clear();
  }

  // Small N, Q
  void TestGroup1() {
    Subtasks({1, 5, 7});

    CASE(N = 4; Q = SMALLQ; A = randomA(N); Ops = randomOps(Q, N));
    CASE(N = 16; Q = SMALLQ; A = randomA(N); Ops = randomOps(Q, N));
    CASE(N = 256; Q = SMALLQ; A = randomA(N); Ops = randomOps(Q, N));
    CASE(N = 512; Q = SMALLQ; A = randomA(N); Ops = randomOps(Q, N));
    CASE(N = SMALLN; Q = SMALLQ; A = randomA(N); Ops = randomOps(Q, N));

    // all possible x = 1..500 when querying type 3
    CASE(N = SMALLN; Q = SMALLQ; A = increasingA(N); for (int i = 1; i <= SMALLQ/2; ++i) {
      Ops.push_back({1, (i - 1) ^ i});
      Ops.push_back({3, 1, N - 1});
    });
    CASE(N = SMALLN; Q = SMALLQ; A = randomA(N); for (int i = SMALLN - 1; i >= SMALLN - SMALLQ/2; --i) {
      Ops.push_back({1, ((i + 1) % SMALLN) ^ i});
      Ops.push_back({3, 0, N - 2});
    });
  }

  // No op 1; No op 3
  void TestGroup2() {
    Subtasks({2, 3, 4, 7});

    CASE(N = MAXN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 2));

    // Query all large range
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); for (int i = 0; i < Q; ++i) {
      Ops.push_back({2, rnd.nextInt(512), N - rnd.nextInt(512) - 1});
    });
  }

  // No op 1
  void TestGroup3() {
    Subtasks({2, 3, 7});
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 4));
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 6));
    CASE(N = MAXN / 2; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 6));

    CASE(N = MAXN; Q = MAXQ; A = vector<int>(N, MAXA); Ops = randomOps(Q, N, 6));
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); Ops = vector<vector<int>>(Q, {3, 1, N - 2}));

    // Query all large range
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); for (int i = 0; i < Q; ++i) {
      Ops.push_back({3, rnd.nextInt(512), N - rnd.nextInt(512) - 1});
    });
  }

  // Update before query
  void TestGroup4() {
    Subtasks({3, 7});

    // All possible X
    CASE(N = MAXN; Q = min(MAXN * 2 - 1, MAXQ); A = randomA(N); for (int i = 0; i < Q/2; ++i) {
      Ops.push_back({1, i ^ (i + 1)});
    }; for (int i = Q/2; i < Q; ++i) {
      int l = rnd.nextInt(N), r = rnd.nextInt(N);
      if (l > r) swap(l, r);
      Ops.push_back({rnd.nextInt(2, 3), l, r});
    });

    // All possible X; only query ops type 3
    CASE(N = MAXN; Q = min(MAXN * 2 - 1, MAXQ); A = randomA(N); for (int i = 0; i < Q/2; ++i) {
      Ops.push_back({1, i ^ (i + 1)});
    }; for (int i = Q/2; i < Q; ++i) {
      int l = rnd.nextInt(N), r = rnd.nextInt(N);
      if (l > r) swap(l, r);
      Ops.push_back({3, l, r});
    });

    // Lot of updates before query
    CASE(N = MAXN; Q = MAXQ; A = randomA(N);
         Ops = vector<vector<int>>(Q - 2, {1, rnd.nextInt(0, N - 1)}); Ops.push_back({1, 2}); Ops.push_back({3, 11, N - 11}));
  }

  // No op 3
  void TestGroup5() {
    Subtasks({4, 7});

    CASE(N = MAXN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 3));
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 3));
  }

  // Max range; small N
  void TestGroup6() {
    Subtasks({1, 5, 6, 7});

    // X = 1..500
    CASE(N = SMALLN; Q = SMALLQ; A = randomA(N); for (int i = 0; i < Q / 2; ++i) {
      Ops.push_back({1, i ^ (i + 1)});
      Ops.push_back({3, 0, N - 1});
    });

    // X = 501..
    CASE(N = SMALLN; Q = SMALLQ - 1; A = randomA(N); Ops.push_back({3, 0, N - 1}); Ops.push_back({2, 0, N - 1}); 
      Ops.push_back({1, 500});
      for (int i = 0; i < (Q - 3) / 2; ++i) {
        Ops.push_back({1, (500 + i) ^ (501 + i)});
        Ops.push_back({3, 0, N - 1});
      }
    );
  }
  
  // Max range; sqrt N
  void TestGroup7() {
    Subtasks({5, 6, 7});

    CASE(N = SQRTN; Q = min(N * 2 - 2, MAXQ); A = randomA(N); for (int i = 0; i < Q / 2; ++i) {
      Ops.push_back({1, i ^ (i + 1)});
      Ops.push_back({3, 0, N - 1});
    });
  }

  // sqrt N
  void TestGroup8() {
    Subtasks({5, 7});

    CASE(N = SQRTN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N));
    CASE(N = SQRTN / 2; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N));
    CASE(N = SQRTN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 5));
  }

  // Max range
  void TestGroup9() {
    Subtasks({6, 7});

    CASE(N = MAXN; Q = min(N * 2, MAXQ); A = randomA(N); for (int i = 0; i < Q / 2; ++i) {
      Ops.push_back({1, i ^ (i + 1)});
      Ops.push_back({3, 0, N - 1});
    });

    CASE(N = MAXN; Q = min(N * 2, MAXQ); A = randomA(N); for (int i = 0; i < Q / 2; ++i) {
      Ops.push_back({1, rnd.nextInt(1, N - 1)});
      Ops.push_back({3, 0, N - 1});
    });

    CASE(N = MAXN; Q = MAXQ; A = randomA(N);
      Ops.push_back({1, rnd.nextInt(1, N - 1)});
      for (int i = 1; i < Q - 1; ++i) Ops.push_back({3, 0, N - 1});
      Ops.push_back({1, rnd.nextInt(1, N - 1)});
    );
  }

  void TestGroup10() {
    Subtasks({7});
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 5));
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 7));
    CASE(N = MAXN / 2; Q = MAXQ; A = randomA(N); Ops = randomOps(Q, N, 7));
    CASE(N = MAXN; Q = MAXQ; A = vector<int>(N, MAXA); Ops = randomOps(Q, N, 5));
    // Large range
    CASE(N = MAXN; Q = MAXQ; A = randomA(N); for (int i = 0; i < Q / 2; ++i) {
      Ops.push_back({1, rnd.nextInt(1, N - 1)});
      Ops.push_back({3, rnd.nextInt(512), N - rnd.nextInt(512) - 1});
    });
  }

private:

  vector<int> randomA(int N, int lo=1, int hi=MAXA) {
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
      A[i] = rnd.nextInt(lo, hi);
    }
    return A;
  }

  vector<int> increasingA(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
      A[i] = i + 1;
    }
    return A;
  }

  vector<vector<int>> randomOps(int Q, int N, int opsTypeMask=7) {
    vector<int> types;
    if (opsTypeMask & 1) types.push_back(1);
    if (opsTypeMask & 2) types.push_back(2);
    if (opsTypeMask & 4) types.push_back(3);

    vector<vector<int>> Ops(Q);
    for (int i = 0; i < Q; ++i) {
      int t = types[rnd.nextInt(types.size())];
      if (t == 1) {
        int x = rnd.nextInt(1, N - 1);
        Ops[i] = {1, x};
      } else if (t == 2 || t == 3) {
        int l = rnd.nextInt(N), r = rnd.nextInt(N);
        if (l > r) {
          swap(l, r);
        }
        Ops[i] = {t, l, r};
      }
    }
    return Ops;
  }
};
