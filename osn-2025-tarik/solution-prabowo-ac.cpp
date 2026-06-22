#include <bits/stdc++.h>

using namespace std;

const int MAX = 200000;

int main() {
  int N, K;
  scanf("%d %d", &N, &K);

  vector<pair<int, int>> A[MAX];
  A[0].resize(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[0][i].first);
    A[0][i].second = 1;
  }
  int sz = 1;

  K = min(40, K);
  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < sz; ++j) {
      int lsum = 0;
      vector<pair<int, int>> lft, rgt;
      for (auto [elem, cnt] : A[j]) {
        cnt *= 2;
        if (lsum < N) {
          int add = min(N - lsum, cnt);
          lft.emplace_back(elem, add);
          cnt -= add;
          lsum += add;
        }
        if (cnt > 0) {
          rgt.emplace_back(elem, cnt);
        }
      }

      A[j] = lft;
      if (sz + j < MAX) {
        A[sz + j] = rgt;
      }
    }

    sz = min(sz * 2, MAX);
  }

  for (int j = 0; j < sz; ++j) {
    long long sum = 0;
    for (auto [elem, cnt] : A[j]) {
      sum += 1LL * elem * cnt;
    }
    printf("%lld\n", sum);
  }
  return 0;
}
