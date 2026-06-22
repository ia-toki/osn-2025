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

  ULL hasil = 0;
  ULL ambil = 0;
  int idx = 0;
  while (ambil < K && idx < A.size())
  {

    ULL rest = K - ambil;
    ULL ada = A[idx].second;
    ULL cur;

    if (rest >= ada)
      cur = ada;
    else
      cur = rest;

    hasil += cur * A[idx].first;
    ambil += cur;
    idx++;
  }

  cout << hasil << endl;
}