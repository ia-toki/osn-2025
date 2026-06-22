#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ULL = unsigned long long;

pair<ULL, ULL> faktor2(ULL m)
{
  ULL c = 1;
  while (m % 2 == 0)
  {
    c *= 2;
    m /= 2;
  }

  return make_pair(m, c);
}

int main()
{

  int N;
  ULL K;
  cin >> N >> K;
  vector<pair<ULL, ULL>> A;
  for (int i = 0; i < N; i++)
  {
    ULL a;
    cin >> a;
    A.emplace_back(faktor2(a));
  }

  sort(A.begin(), A.end(), [](auto x, auto y)
       { return x.first > y.first; });

  cout << A[0].first << endl;
  return 0;
}