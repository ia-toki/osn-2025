#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

#define pb push_back

using ll = long long;

constexpr int MAXN = 1e5;
constexpr int MAXA = 1e6;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, Z;
  vector<int> A;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(Z);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(eachElementBetween(A, 1, MAXA));
  }

  void Subtask1() {
    Points(1);

    CONS(N <= 5);
    CONS(eachElementBetween(A, 1, 12));
  }

  void Subtask2() {
    Points(1);

    CONS(N == 1);
  }

  void Subtask3() {
    Points(1);

    CONS(N <= 100);
    CONS(eachElementBetween(A, 1, 100));
  }


  void Subtask4() {
    Points(1);

    CONS(N <= 100);
    CONS(eachElementBetween(A, 1, 5000));
  }

  
  void Subtask5() {
    Points(1);

    CONS(eachElementPowerOfTwo(A));
  }

  void Subtask6() {
    Points(1);

    CONS(eachElementBetween(A, 1, 5000));
  }

  void Subtask7() {
    Points(1);
  }

private:
  bool eachElementBetween(const vector<int> &v, int lo, int hi) {
    for (int x : v) if (!(lo <= x && x <= hi)) {
      return false;
    }
    return true;
  }

  bool eachElementPowerOfTwo(const vector<int> &v) {
    for (int x : v) if (x != (x & -x)) {
      return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({ 1, 3, 4, 6, 7 }); 
    Input({
      "4",
      "3 12 12 4",
    });
    Output({
      "15",
    });
  }
  
  void SampleTestCase2() {
    Subtasks({ 2, 3, 4, 5, 6, 7 });
    Input({
      "1",
      "16",
    });
    Output({
      "9",
    });
  }

  void SampleTestCase3() {
    Subtasks({ 3, 4, 5, 6, 7 });
    Input({
      "24",
      "8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8",
    });
    Output({
      "674257757",
    });
  }

  void BeforeTestCase() {
    if (primes.empty()) {
      static bitset<MAXA + 1> prime;
      
      prime[2] = true;
      for (int i = 3; i <= MAXA; i += 2) prime[i] = true;
      for (int i = 3; i <= MAXA; i += 2) if (prime[i]) {
        for (ll j = 1ll*i*i; j <= MAXA; j += i) 
          prime[j] = false;
      }
      
      primes100.pb(2);
      primes5000.pb(2);
      primes.pb(2);
      for (int i = 3; i <= MAXA; i += 2) if (prime[i]) {
        if (i <= 100) primes100.pb(i);
        if (i <= 5000) primes5000.pb(i);
        primes.pb(i);
      }
    }
  }

  void TestGroup1() {
    Subtasks({1, 2, 3, 4, 5, 6, 7});

    CASE(N = 1, A = { 1 });
    CASE(N = 1, A = { 2 });
    CASE(N = 1, A = { 4 });
    CASE(N = 1, A = { 8 });
  }

  void TestGroup2() {
    Subtasks({ 1, 3, 4, 5, 6, 7});

    CASE(N = 2, A = {1, 2});
    CASE(N = 3, A = {1, 2, 4});
    CASE(N = 3, A = {1, 1, 1});
  }

  void TestGroup3() {
    Subtasks({ 1, 3, 4, 6, 7 });
    
    CASE(N = 5, A = vector<int>(N, 12));
    CASE(N = 5, A = {8, 8, 6, 12, 12});
    CASE(N = 5, A = {1, 2, 3, 4, 5});
    CASE(N = 4, A = {11, 11, 11, 7});
    CASE(N = 4, A = {6, 9, 9, 10});
  }

  void TestGroup4() {
    Subtasks({2, 4, 6, 7});
    CASE(N = 1, A = { 3456 });
    CASE(N = 1, A = { 2310 });
  }

  void TestGroup5() {
    Subtasks({ 2, 5, 7 });
    
    CASE(N = 1, A = { 65536 });
    CASE(N = 1, A = { 262144 });
  }

  void TestGroup6() {
    Subtasks({ 2, 7 });

    CASE(N = 1, A = { kMaxFactor });
    CASE(N = 1, A = { 999979  }); // second-largest prime under 1 mil
    CASE(N = 1, A = { 911 * 991 }); // two primes
  }

  void TestGroup7() {
    Subtasks({ 3, 4, 5, 6, 7 });

    CASE(N = 100, A = vector<int>(N, 64));
    CASE(N = 100, A = GenerateHalfHalf(N, 64, 32));
    CASE(N = rnd.nextInt(91, 100), A = GeneratePowerOfTwo(N, 0, 2, 6, 9));
    CASE(N = rnd.nextInt(91, 100), A = GeneratePowerOfTwo(N, 0, 6, 6, 9));
  }
  
  void TestGroup8() {
    Subtasks({ 3, 4, 6, 7 });
  
    CASE(N = 100, A = vector<int>(N, kMaxFactor100));
    CASE(N = 100, A = GenerateHalfHalf(N, 64, 96));
    CASE(N = rnd.nextInt(91, 100), A = GenerateTwoStep(N,    {2}, 4, 4, 7, 100, 3));
    CASE(N = rnd.nextInt(91, 100), A = GenerateTwoStep(N, {3, 5}, 3, 7, 11, 100, 2));
    CASE(N = rnd.nextInt(91, 100), A = GenerateTwoStep(N, {3, 5, 7, 9, 11, 13}, 2, 6, 9, 100, 2, 13, 31));
    CASE(N = rnd.nextInt(91, 100), A = GenerateTwoStep(N, primes100, 1, 2, 3, 100, 2, 13, 31));
    CASE(N = rnd.nextInt(91, 100), A = GenerateRandom(N, 2, 100, 1, 2)); // answer is most-likely 0
    CASE(N = rnd.nextInt(91, 100), A = GenerateRandom(N, 2, 100, 13, 31));
  }

  void TestGroup9() {

    Subtasks({ 4, 5, 6, 7 });

    CASE(N = 100, A = vector<int>(N, 4096));
    CASE(N = 100, A = GenerateHalfHalf(N, 4096, 2048));
    CASE(N = rnd.nextInt(91, 100), A = GeneratePowerOfTwo(N, 0, 12, 6, 9));
  }

  void TestGroup10() {
    Subtasks({ 4, 6, 7 });
    
    CASE(N = 100, A = vector<int>(N, kMaxFactor5000));
    CASE(N = 100, A = GenerateHalfHalf(N, 4680, 4320));
    CASE(N = 100, A = GenerateHalfHalf(N, 3456, 2592));
    CASE(N = rnd.nextInt(91, 100), A = GenerateTwoStep(N,    {2}, 12, 4, 7, 5000, 3));
    CASE(N = rnd.nextInt(91, 100), A = GenerateTwoStep(N, {3, 5}, 8, 7, 11, 5000, 2));
    CASE(N = rnd.nextInt(91, 100), A = GenerateTwoStep(N, {3, 5, 7, 9, 11, 269, 4999}, 4, 6, 9, 5000, 2, 13, 31));
    CASE(N = rnd.nextInt(91, 100), A = GenerateTwoStep(N, primes5000, 1, 2, 3, 5000, 2, 13, 31));
    CASE(N = rnd.nextInt(91, 100), A = GenerateRandom(N, 2, 5000, 13, 31));
  }

  void TestGroup11() {

    Subtasks({ 5, 6, 7 });

    CASE(N = MAXN, A = vector<int>(N, 4096));
    CASE(N = MAXN, A = GenerateHalfHalf(N, 4096, 2048));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GeneratePowerOfTwo(N, 0, 12, 6, 9));
  }

  void TestGroup12() {
    Subtasks({ 5, 7 });

    CASE(N = MAXN, A = GeneratePowerOfTwo(N, kMaxTwoExp, kMaxTwoExp, N, N));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GeneratePowerOfTwo(N, 0, kMaxTwoExp, 1, N));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GeneratePowerOfTwo(N, 0, kMaxTwoExp, 1, 31));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GeneratePowerOfTwo(N, 17, kMaxTwoExp, 209, 369));
  }

  void TestGroup13() {
    Subtasks({ 6, 7 });
    
    CASE(N = MAXN, A = vector<int>(N, kMaxFactor5000));
    CASE(N = MAXN, A = GenerateHalfHalf(N, 4680, 4320));
    CASE(N = MAXN, A = GenerateHalfHalf(N, 4320, 3456));
    CASE(N = MAXN, A = GenerateHalfHalf(N, 3456, 2592));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateTwoStep(N,    {2}, 12, 137, 237, 5000, 3));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateTwoStep(N, {3, 5}, 8, 224, 301, 5000, 2));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateTwoStep(N, {3, 5, 7, 9, 11, 269, 4999}, 6, 69, 96, 5000, 2, 13, 31));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateTwoStep(N, primes5000, 1, 2, 5, 5000, 2, 13, 31));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateRandom(N, 2, 5000, 265, 373));
  }

  void TestGroup14() {
    Subtasks({ 7 });
    
    CASE(N = MAXN, A = vector<int>(N, kMaxFactor));
    CASE(N = MAXN, A = GenerateHalfHalf(N, 967860, 997920));
    CASE(N = MAXN, A = GenerateHalfHalf(N, 997920, 746496));
    CASE(N = MAXN, A = GenerateHalfHalf(N, 524288, 531441));
    CASE(N = MAXN, A = GenerateHalfHalf(N, 1000000, 750000));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateTwoStep(N,    {2}, 16, 137, 237, MAXA, 3));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateTwoStep(N, {3, 5, 7}, 12, 224, 301, MAXA, 2));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateTwoStep(N, {3, 5, 7, 9, 11, 31, 67, 101, 216901, 250499, 802357}, 10, 69, 96, MAXA, 2, 13, 31));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateTwoStep(N, primes, 1, 2, 5, MAXA, 2, 13, 31));
    CASE(N = rnd.nextInt(MAXN-10, MAXN), A = GenerateRandom(N, 2, MAXA, 458, 2221));
  }

private:
  static constexpr int kMaxTwoExp = 19;
  static constexpr int kMaxFactor100 = 96;    //  12 factors
  static constexpr int kMaxFactor5000 = 4680; //  48 factors 
  static constexpr int kMaxFactor = 997920;   // 240 factors
  
  vector<int> primes100, primes5000, primes;

  vector<int> GenerateHalfHalf(int N, int p_l, int p_r) {
    vector<int> Z;
    Z.reserve(N);

    int rep_l = rnd.nextInt(N/3, 2*N/3);
    for (int i = 0; i < rep_l; ++i) {
      Z.push_back(p_l);
    }
    for (int i = rep_l; i < N; ++i) {
      Z.push_back(p_r);
    }
    return Z;
  }

  vector<int> GeneratePowerOfTwo(int N, int exp_l, int exp_r, int gap_l, int gap_r) {
    vector<int> exp = GenerateExponent(N, exp_l, exp_r, gap_l, gap_r);
    
    vector<int> Z;
    Z.reserve(N);
    for (int y : exp) {
      Z.push_back(1 << y);
    }
    return Z;
  }       

  vector<int> GenerateExponent(int N, int exp_l, int exp_r, int gap_l, int gap_r) {
    vector<int> Z;
    Z.reserve(N);
    
    for (int prv = -1; Z.size() < N;) {
      int y = rnd.nextInt(exp_l, exp_r);
      
      int l = gap_l, r = min(gap_r, N - static_cast<int>(Z.size()));
      if (!Z.empty() && Z.back() < y) l = max(l, 2); // need to increase to prevent answer=0, can ignore for index 0 or N-1
      int rep = rnd.nextInt(min(l, r), r);
      
      for (int j = 0; j < rep; ++j) {
        Z.push_back(y);
      }
    }
    return Z;
  }
  
  /**
   * At some index i, for up to `base_rep` times, do
   * - select a number b from bases
   * - multiply Z[i .. i+k] with b where k is sampled from [base_l, base_r]
   * - if multiply exceeds cap, then abort
   * Second step is to maximize multiplying them with p
   */
  vector<int> GenerateTwoStep(int N, const vector<int>& bases, int base_rep, int base_l, int base_r, int cap = MAXA, int p = 2, int p_l = 2, int p_r = 5) {
    vector<int> Z(N, 1);
    
    for (int i = 0; i < N; ) {
      int rem = N - i;
      int k = rnd.nextInt(min(rem, base_l), min(rem, base_r));

      int brep = rnd.nextInt(1, base_rep);
      for (int rep = 0; rep < brep; ++rep) {
        int b = bases[rnd.nextInt(0, static_cast<int>(bases.size()) - 1)];

        bool ok = true;
        for (int j = i; j < i+k; ++j) if (1ll * Z[j] * b > cap) {
          ok = false;
          break;
        }
        if (!ok) {
          break;
        }

        for (int j = i; j < i+k; ++j) {
          Z[j] *= b;
        }
      }

      i += k;
    }
  
    for (int i = 0; i < N; ) {
      int rem = N - i;
      int k = rnd.nextInt(min(rem, p_l), min(rem, p_r));
     
      int mn_pwr = 100;
      for (int j = i; j < i+k; ++j) {
        int ctr = 0;
        for (int x = Z[j]; x*p <= cap;) {
          x *= p;
          ++ctr;
        }
        mn_pwr = min(mn_pwr, ctr);
      }

      int p_pwr = 1;
      for (int j = 0; j < mn_pwr; ++j) {
        p_pwr *= p;
      }

      for (int j = i; j < i+k; ++j) {
        Z[j] *= p_pwr;
      }
      i += k;
    }
    return Z;
  }

  vector<int> GenerateRandom(int N, int A_l, int A_r, int gap_l, int gap_r) {
    vector<int> Z;
    Z.reserve(N);

    while (Z.size() < N) {
      int rem = N - static_cast<int>(Z.size());

      int x = rnd.nextInt(A_l, A_r);
      int rep = rnd.nextInt(min(rem, gap_l), min(rem, gap_r));
      for (int j = 0; j < rep; ++j) {
        Z.push_back(x);
      }
    }
    return Z;
  }

  int fpow(int x, int y) {
    int Z = 1;
    for (; y > 0; y >>= 1, x *= x) {
      if (y & 1)
        Z *= x;
    }
    return Z;
  }
};

