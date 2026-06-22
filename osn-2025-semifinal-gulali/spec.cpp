#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
using ULL = unsigned long long;

const int MAXN = 1e5;
const ULL MAXA = 1e12, MAXK = 1e12;

class ProblemSpec : public BaseProblemSpec
{
protected:
  int N;
  ULL K;
  vector<ULL> A;
  ULL ans;

  void InputFormat()
  {
    LINE(N, K);
    LINE(A % SIZE(N));
  }

  void OutputFormat()
  {
    LINE(ans);
  }

  void GradingConfig()
  {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints()
  {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= K && K <= MAXK);
    CONS(A.size() == N);
    CONS(eachElementBetween(A, 1ULL, MAXA));
  }

  void Subtask1()
  {
    Points(7);
    CONS(K == 1);
    CONS(allElementsOdd(A));
  }
  void Subtask2()
  {
    Points(7);
    CONS(K == N);
    CONS(allElementsOdd(A));
  }

  void Subtask3()
  {
    Points(12);
    CONS(allElementsOdd(A));
  }

  void Subtask4()
  {
    Points(13);
    CONS(allElementsPowersOfTwo(A));
  }

  void Subtask5()
  {
    Points(15);
    CONS(N == 1);
    CONS(K == 1);
  }

  void Subtask6()
  {
    Points(21);
    CONS(N <= 500);
    CONS(eachElementBetween(A, 1ULL, 500ULL));
  }

  void Subtask7()
  {
    Points(25);
  }

private:
  template <typename T>
  bool eachElementBetween(const vector<T> &curV, T db, T ub)
  {
    for (int i = 0; i < curV.size(); i++)
    {
      if (!(db <= curV[i] && curV[i] <= ub))
      {
        return 0;
      }
    }
    return 1;
  }

  template <typename T>
  bool allElementsOdd(const vector<T> &A)
  {
    for (auto a : A)
    {
      if (a % 2 == 0)
        return 0;
    }
    return 1;
  }

  template <typename T>
  bool isPowerOfTwo(T a)
  {
    while (a % 2 == 0)
      a /= 2;

    return a == 1;
  }

  template <typename T>
  bool allElementsPowersOfTwo(const vector<T> &A)
  {
    for (auto a : A)
    {
      if (!isPowerOfTwo(a))
        return 0;
    }
    return 1;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
  void SampleTestCase1()
  {
    Subtasks({6, 7});
    Input({"5 3",
           "8 15 12 6 20"});
    Output({
        "25",
    });
  }

  void SampleTestCase2()
  {
    Subtasks({4, 6, 7});
    Input({
        "2 3",
        "4 8",
    });
    Output({
        "3",
    });
  }

  void BeforeTestCase()
  {
    A.clear();
  }

  void TestGroup1()
  {
    Subtasks({1, 2, 3, 4, 5, 6, 7});
    CASE(N = 1, K = 1, A = {1});
  }

  void TestGroup2()
  {
    Subtasks({1, 2, 3, 5, 6, 7});
    CASE(N = 1, K = 1, A = {499});
  }

  void TestGroup3()
  {
    Subtasks({1, 2, 3, 5, 7});
    CASE(N = 1, K = 1, A = {999999999999});
  }

  void TestGroup4()
  {
    Subtasks({1, 3, 6, 7});
    CASE(N = 10, K = 1, A = {137, 5, 25, 3, 185, 457, 99, 1, 299, 499});
    CASE(N = 500, K = 1, A = antiInsertionSortArray(N, 1, 500, true));
  }

  void TestGroup5()
  {
    Subtasks({1, 3, 7});
    CASE(N = MAXN / 2, K = 1, A = antiInsertionSortArray(N, 1, MAXA - 1, true));
    CASE(N = MAXN, K = 1, A = antiInsertionSortArray(N, 1, MAXA - 1, true));
  }

  void TestGroup6()
  {
    Subtasks({2, 3, 6, 7});
    CASE(N = 400, K = N, A = antiInsertionSortArray(N, 1, 500, true));
	CASE(N = 475, K = N, A = antiInsertionSortArray(N, 1, 500, true));
    CASE(N = 500, K = N, A = antiInsertionSortArray(N, 1, 500, true));
  }

  void TestGroup7()
  {
    Subtasks({2, 3, 7});
    CASE(N = MAXN / 2, K = N, A = antiInsertionSortArray(N, 1, MAXA - 1, true));
    CASE(N = MAXN, K = N, A = antiInsertionSortArray(N, 1, MAXA - 1, true));
  }

  void TestGroup8()
  {
    Subtasks({3, 7});
    CASE(N = 5000, K = 4750, A = antiInsertionSortArray(N, 1, MAXA - 1, true));
    CASE(N = MAXN, K = MAXK, A = antiInsertionSortArray(N, 1, MAXA - 1, true));
  }

  void TestGroup9()
  {
    Subtasks({4, 5, 6, 7});
    CASE(N = 1, K = 1, A = {256});
  }

  void TestGroup10()
  {
    Subtasks({4, 5, 7});
    CASE(N = 1, K = 1, A = {powerOfTwo(38)});
  }

  void TestGroup11()
  {
    Subtasks({4, 6, 7});
    CASE(N = 8, K = 30, A = {8, 256, 16, 128, 64, 2, 4, 32});
	CASE(N = 8, K = 30, A = {8, 256, 16, 128, 64, 1, 4, 32});
	CASE(N = 8, K = 10000, A = {8, 256, 16, 128, 64, 1, 4, 32});
    CASE(N = 8, K = 10000, A = {8, 256, 16, 128, 64, 2, 4, 32});
  }

  void TestGroup12()
  {
    Subtasks({4, 7});
    CASE(N = 10000, K = 20000, A = randPowersOfTwo(N, 1, 39));
    CASE(N = MAXN, K = MAXK, A = randPowersOfTwo(N, 1, 39));
  }

  void TestGroup13()
  {
    Subtasks({5, 7});
    CASE(N = 1, K = 1, A = {powerOfTwo(20) * 77777});
    CASE(N = 1, K = 1, A = {powerOfTwo(22) * 253 * 185});
    CASE(N = 1, K = 1, A = {powerOfTwo(25) * 137});
  }

  void TestGroup14()
  {
    Subtasks({6, 7});
    CASE(N = 500, K = 1000, A = antiInsertionSortArray(N, 1, 500));
    CASE(N = 500, K = MAXK, A = antiInsertionSortArray(N, 1, 500));
  }

  void TestGroup15()
  {
    Subtasks({7});
    CASE(N = MAXN, K = 200000, A = antiInsertionSortArray(N, 1, MAXA));
    CASE(N = MAXN, K = 200000, A = antiInsertionSortArray(N, 1, MAXA));
    CASE(N = MAXN, K = MAXK, A = antiInsertionSortArray(N, 1, MAXA));
    CASE(N = MAXN, K = MAXK, A = antiInsertionSortArray(N, 1, MAXA));
  }

private:
  vector<ULL> randArray(int sz, ULL lb, ULL ub, bool isOdd = false)
  {
    vector<ULL> res;

    for (int i = 0; i < sz; i++)
    {
      ULL a = rnd.nextLongLong(lb, ub);
      if (isOdd)
      {
        if (a % 2 == 0)
          a++;
        if (a > ub)
          a -= 2;
      }
      res.push_back(a);
    }
    return res;
  }

  vector<ULL> antiInsertionSortArray(int sz, ULL db, ULL ub, bool isOdd = false)
  {
    vector<ULL> tmp, res;
    tmp = randArray(sz, db, ub, isOdd);

    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < sz; i++)
    {
      if (i % 2 == 0)
      {
        res.push_back(tmp[i / 2]);
      }
      else
      {
        res.push_back(tmp[sz - 1 - i / 2]);
      }
    }
    return res;
  }

  ULL powerOfTwo(int pow)
  {
    ULL res = 1LL;
    return res << pow;
  }

  vector<ULL> randPowersOfTwo(int sz, int lp, int up)
  {
    vector<ULL> res;
    for (int i = 0; i < sz; i++)
    {
      int p = rnd.nextInt(lp, up);
      res.push_back(powerOfTwo(p));
    }

    return res;
  }
};
