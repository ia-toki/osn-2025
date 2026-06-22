#include <tcframe/spec.hpp>
using namespace tcframe;

const int MAXN = 100000;
const int MAXA = 100000;

const int SMALLN = 1000;
const int SMALLA = 1000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector<int> A;

  long long res;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(res);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(valueOf(N).isBetween(2, MAXN));
    CONS(eachElementOf(A).isBetween(1, MAXA));
  }

  void Subtask1() {
    Points(10);
    CONS(N <= SMALLN);
  }

  void Subtask2() {
    Points(20);
    CONS(eachElementOf(A).isBetween(1, SMALLA));
  }

  void Subtask3() {
    Points(30);
    CONS(eachElementOf(A).satisfies([&](int a) {
      return (a & -a) == a;
    }));
  }

  void Subtask4() {
    Points(40);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1, 2, 4});
    Input({
      "4",
      "3 12 12 4",
    });
    Output({
      "2"
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  // Small N, small A
  void TestGroup1() {
    Subtasks({1, 2, 4});
    CASE(N = 8, A = {5, 5, 5, 5, 4, 6, 12, 15});

    CASE(N = rnd.nextInt(9 * SMALLN / 10, SMALLN); A = randomElements(N, 1, SMALLA));
    CASE(N = SMALLN; A = randomElements(N, 1, SMALLA));
    CASE(N = SMALLN; A = sortedNumbers(N, 1));
    CASE(N = SMALLN; A = vector<int>(N, SMALLA));
  }

  // Small N
  void TestGroup2() {
    Subtasks({1, 4});

    CASE(N = SMALLN; A = randomElements(N, 1, MAXA));
    CASE(N = SMALLN; A = sortedNumbers(N, MAXA / 2));
    CASE(N = SMALLN; A = sortedNumbers(N, MAXA - N));

    // Highly composite numbers
    CASE(N = SMALLN; for (int i = 0; i < N; ++i) {
      vector<int> nums = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, 45360, 50400, 55440, 83160};
      A.push_back(nums[rnd.nextInt(nums.size())]);
    });
  }

  // Small A
  void TestGroup3() {
    Subtasks({2, 4});

    CASE(N = MAXN; A = randomElements(N, 1, SMALLA));
    CASE(N = MAXN; A = randomElements(N, 1, SMALLA));
    CASE(N = MAXN; A = randomElements(N, 1, 4));
    // Highly composite numbers
    CASE(N = MAXN; for (int i = 0; i < N; ++i) {
      vector<int> nums = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840};
      A.push_back(nums[rnd.nextInt(nums.size())]);
    });

    //CASE 2 angka aja
    CASE(N = MAXN, A = duaAngka(N, 4, 6));
  }

  // A = 2^k; small A
  void TestGroup4() {
    Subtasks({2, 3, 4});
    CASE(N = MAXN; A = vector<int>(N, 1));
    CASE(N = MAXN; A = randomElements(N, 1, 2));
  }

  // A = 2^k
  void TestGroup5() {
    Subtasks({3, 4});
    CASE(N = MAXN; A = vector<int>(N, 1 << 16));
    CASE(N = MAXN; for (int i = 0; i < N; ++i) {
      A.push_back(1 << rnd.nextInt(17));
    });
  }

  void TestGroup6() {
    Subtasks({4});

    //CASE SORTED NUMBERS
    CASE(N = MAXN, A = sortedNumbers(N, 1));
    
    //note: 2 angka fibo terbesar
    CASE(N = MAXN, A = duaAngka(N, 46368, 75025));
    
    //CASE: semua angka sama
    CASE(N = MAXN, A = vector<int>(N, MAXN));
    CASE(N = MAXN, A = vector<int>(N, 99991));
    CASE(N = MAXN, A = vector<int>(N, 92927));
    //note: angka yang punya jumlah faktor terbanyak
    CASE(N = MAXN, A = vector<int>(N, 83160));
    
    //CASE: ANGKA FIBONACCI
    CASE(N = 10000, A = fiboNumbers(N));
    CASE(N = MAXN, A = fiboNumbers(N));
    
    
    //CASE RANDOM
    CASE(N = 10000, A = randomElements(N, 1, MAXN));
    CASE(N = MAXN, A = randomElements(N, 1, MAXN));

    // Highly composite numbers
    CASE(N = MAXN; for (int i = 0; i < N; ++i) {
      vector<int> nums = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, 45360, 50400, 55440, 83160};
      A.push_back(nums[rnd.nextInt(nums.size())]);
    });
  }

private:
  vector<int> randomElements(int amount, int minRange, int maxRange) {
    vector<int> A;
    for (int i = 0; i < amount; i++) {
      A.push_back(rnd.nextInt(minRange, maxRange));
    }
    return A;
  }
  
  vector<int> fiboNumbers(int amount){
    vector<int> fibo;
    fibo.push_back(1);
    fibo.push_back(2);
    while (fibo.back() + fibo[fibo.size() - 2] <= MAXN){
      fibo.push_back(fibo.back() + fibo[fibo.size() - 2]);
    }
    int minNum = amount / fibo.size();
    int addNum = amount % fibo.size();

    vector<int> A;
    for (auto &num : fibo){
      for (int i = 0; i < minNum; i++){
        A.push_back(num);
      }
      if (addNum){
        addNum--;
        A.push_back(num);
      }
    }
    rnd.shuffle(A.begin(), A.end());
    return A;
  }
  
  vector<int> sortedNumbers(int amount, int start){
    vector<int> A;
    for (int i = start; i < amount + start; i++){
      A.push_back(i);
    }
    return A;
  }
  
  vector<int> duaAngka(int amount, int x, int y){
    vector<int> A;
    int half = amount / 2;
    for (int i = 0; i < half; i++){
      A.push_back(x);
    }
    for (int i = 0; i < amount - half; i++){
      A.push_back(y);
    }
    return A;
  }
};
