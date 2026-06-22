#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int NUM_TC = 16;

class ProblemSpec : public BaseProblemSpec {
protected:
  int TC;

  void InputFormat() {
    LINE(TC);
  }

  void StyleConfig() {
    InteractiveEvaluator();
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(valueOf(TC).isBetween(0, NUM_TC - 1));
  }

  void Subtask1() {
    Points(100);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestGroup1() {
    Subtasks({1});
    for (int i = 0; i < NUM_TC; ++i) {
      CASE(TC = i);
    }
  }
};
