#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ULL = unsigned long long;

int main()
{

  int N;
  ULL K, hasil = 0;
  cin >> N >> K;

  vector<ULL> A;
  for (int i = 0; i < N; i++)
  {
    ULL a;
    cin >> a;
    A.push_back(a);
  }
  sort(A.begin(), A.end(), [](auto x, auto y)
       { return x > y; });

  for (int i = 0; i < min((ULL)N, K); i++)
    hasil += A[i];

  cout << hasil << endl;

  return 0;
}