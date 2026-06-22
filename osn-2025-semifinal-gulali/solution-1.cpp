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

  for (int i = 0; i < N; i++)
  {
    ULL a;
    cin >> a;
    if (a > hasil)
      hasil = a;
  }
  cout << hasil << endl;

  return 0;
}