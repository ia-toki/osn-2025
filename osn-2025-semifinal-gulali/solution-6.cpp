#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using ULL = unsigned long long;

int main()
{

  int N;
  ULL K, hasil = 0;
  cin >> N >> K;
  priority_queue<ULL> data;

  for (int i = 0; i < N; i++)
  {
    ULL a;
    cin >> a;
    data.push(a);
  }

  while (K > 0 && !data.empty())
  {
    auto a = data.top();
    data.pop();
    if (a % 2 == 1)
    {
      hasil += a;
      K--;
    }
    else
    {
      data.push(a / 2);
      data.push(a / 2);
    }
  }

  cout << hasil << endl;
  return 0;
}