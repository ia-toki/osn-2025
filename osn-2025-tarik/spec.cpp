#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

typedef long long LL;

const int K_SUBTASK_1 = 3;
const int K_SMALL = 20;
const int MAX_K = 200000;
const int MAX_LINES = 200000;
const int MAX_N = 200000;
const int MAX_N_POWER_OF_TWO = 1 << 17;
const int MIN_VAL = 0;
const int MAX_VAL = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, K;
  vector<int> V;
  vector<LL> ans;
  int query_count;

  void InputFormat() {
    LINE(N, K);
    LINE(V % SIZE(N));
  }

  void OutputFormat() {
    LINES(ans) % SIZE(query_count);
  }

  void BeforeOutputFormat() {
    query_count = K <= 17 ? 1 << K : MAX_LINES;
  }

  void Constraints() {
    CONS(valueOf(N).isBetween(1, MAX_N));
    CONS(valueOf(K).isBetween(1, MAX_K));
    CONS(eachElementOf(V).isBetween(0, MAX_VAL));
  }

  void Subtask1() {
    Points(10);
    CONS(K <= 3);
  }

  void Subtask2() {
    Points(10);
    CONS(K <= 20);
    CONS(isFirstElementIsOneAndOtherElementIsZero(V));
  }

  void Subtask3() {
    Points(15);
    CONS(K <= 20);
    CONS((N & -N) == N); // N = 2^x
  }

  void Subtask4() {
    Points(15);
    CONS(K <= 20);
  }

  void Subtask5() {
    Points(20);
    CONS(N == 3);
  }

  void Subtask6() {
    Points(30);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

private:
  bool isFirstElementIsOneAndOtherElementIsZero(vector<int>& ve){
    if(ve[0] != 1) return false;
    for(int i = 1;i < N; ++i){
      if(ve[i] != 0) return false;
    }
    return true;
  }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1, 4, 6});
    Input({
      "5 2",
      "1 2 3 4 5"
    });
    Output({
      "6",
      "18",
      "12",
      "24"
    });
  }
  void SampleTestCase2(){
    Subtasks({3, 4, 6});
    Input({
      "1 20",
      "0"
    });
    Output(vector<string>(200000, "0"));
  }


  void BeforeTestCase() {
    V.clear();
    ans.clear();
  }

  void TestGroup1() {
    Subtasks({1, 2, 3, 4, 6});
    CASE(N = MAX_N_POWER_OF_TWO; K = 3; firstElementIsOneAndOtherElementIsZero());
  }

  void TestGroup2() {
    Subtasks({1, 2, 4, 5, 6});
    CASE(N = 3; K = 3; firstElementIsOneAndOtherElementIsZero());
  }


  void TestGroup3() {
    Subtasks({1, 2, 4, 6});
    CASE(N = MAX_N - 1; K = 3; firstElementIsOneAndOtherElementIsZero());
    CASE(N = MAX_N; K = 3; firstElementIsOneAndOtherElementIsZero());
  }


  void TestGroup4() {
    Subtasks({1, 3, 4, 6});
    CASE(N = 1 << 10; K = 3; randomElement());
    CASE(N = 1 << 10; K = 3; permutationElement());
    CASE(N = 1 << 10; K = 3; duplicateElement());

    CASE(N = MAX_N_POWER_OF_TWO; K = 3; randomElement());
    CASE(N = MAX_N_POWER_OF_TWO; K = 3; maxElement());
  }

  void TestGroup5() {
    Subtasks({1, 4, 6});
    CASE(N = MAX_N; K = 3; permutationElement());

    CASE(N = MAX_N - 1; K = 3; randomElement());

    CASE(N = MAX_N_POWER_OF_TWO - 1; K = 3; randomElement());
  }

  void TestGroup6(){
    Subtasks({1, 4, 5, 6});
    CASE(N = 3; K = 3; randomElement());
    CASE(N = 3; K = 3; maxElement());
    CASE(N = 3; K = 3; duplicateElement());
    CASE(N = 3; K = 3; permutationElement());
  }

  void TestGroup7(){
    Subtasks({2, 3, 4, 6});
    CASE(N = 1; K = 10; firstElementIsOneAndOtherElementIsZero());
    CASE(N = MAX_N_POWER_OF_TWO; K = 10; firstElementIsOneAndOtherElementIsZero());
    for(int i = 0; i < 1; ++i){
      CASE(N = 1 << rnd.nextInt(4, 16); K = 20; firstElementIsOneAndOtherElementIsZero());
    }
  }

  void TestGroup8(){
    Subtasks({2, 4, 5, 6});    
    CASE(N = 3; K = 4; firstElementIsOneAndOtherElementIsZero());
    CASE(N = 3; K = 20; firstElementIsOneAndOtherElementIsZero());
  }

  void TestGroup9(){
    Subtasks({2, 4, 6});    
    CASE(N = MAX_N; K = 20; firstElementIsOneAndOtherElementIsZero());
    CASE(N = MAX_N - 1; K = 20; firstElementIsOneAndOtherElementIsZero());
  }
  
  void TestGroup10(){
    Subtasks({3, 4, 6});    
    CASE(N = MAX_N_POWER_OF_TWO; K = 20; randomElement());
    for(int i = 0; i < 1; ++i){
      CASE(N = 1 << rnd.nextInt(4, 16); K = rnd.nextInt(17, 20); permutationElement());
    }
  }
  
  void TestGroup11(){
    Subtasks({4, 5, 6});    
    CASE(N = 3; K = 4; randomElement());
    CASE(N = 3; K = 20; randomElement());
  }

  void TestGroup12(){
    Subtasks({4, 6});    
    CASE(N = MAX_N - 1; K = 20; randomElement());
    CASE(N = MAX_N; K = 20; randomElement());
    CASE(N = MAX_N_POWER_OF_TWO + 1; K = 20; permutationElement());
  }

  void TestGroup13(){
    Subtasks({5, 6});
    CASE(N = 3; K = 23; permutationElement());

    CASE(N = 3; K = 34; permutationElement());
    CASE(N = 3; K = 35; permutationElement());
    CASE(N = 3; K = 36; permutationElement());
    CASE(N = 3; K = MAX_K; permutationElement());
  }

  void TestGroup14(){
    Subtasks({6});
    CASE(N = 1; K = MAX_K; randomElement());

    CASE(N = MAX_N; K = 34; randomElement());
    CASE(N = MAX_N; K = 35; randomElement());
    CASE(N = MAX_N; K = 36; randomElement());
    CASE(N = MAX_N; K = MAX_K; randomElement());

    CASE(N = MAX_N - 1; K = 23; randomElement());
    CASE(N = MAX_N - 1; K = 33; duplicateElement());
    CASE(N = MAX_N - 1; K = 34; randomElement());
    CASE(N = MAX_N - 1; K = 35; randomElement());
    CASE(N = MAX_N - 1; K = 36; randomElement());

    CASE(N = MAX_N - 1; K = MAX_K; permutationElement());
  }

private:
  void randomElement(int mins = MIN_VAL, int maks = MAX_VAL){
    V.resize(N);
    for(int i = 0; i < N; ++i){
      int next_elem = rnd.nextInt(mins, maks);
      V[i] = next_elem;
    }
  }

  void minElement(){
    randomElement(MIN_VAL, MIN_VAL);
  }

  void maxElement(){
    randomElement(MAX_VAL, MAX_VAL);
  }

  void permutationElement(){
    int start = rnd.nextInt(0, MAX_VAL - N + 1);
    V.resize(N);
    for(int i = 0; i < N; ++i){
      int next_elem = start + i;
      V[i] = next_elem;
    }
    rnd.shuffle(V.begin(), V.end());
  }

  void duplicateElement(){
    int start = rnd.nextInt(0, MAX_VAL - N + 1);
    int finish = start + rnd.nextInt(0, N - 1);
    V.resize(N);
    for(int i = 0; i < N; ++i){
      int next_elem = rnd.nextInt(start, finish);
      V[i] = next_elem;
    }
    rnd.shuffle(V.begin(), V.end());
  }

  void firstElementIsOneAndOtherElementIsZero(){
    V.resize(N);
    V[0] = 1;
    for(int i = 1;i < N; ++i) V[i] = 0;
  }

};
