#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e18;

constexpr int BLOCK = 1 << 8;

int globalxor = 0;

struct Block {
  lint sum;
  vector<int> v; // with original index
  vector<lint> sumi; // sum(Ai * i), assuming i starts at 0
  
  Block(vector<int> ve) : v(move(ve)) {
    assert(globalxor == 0);

    sum = accumulate(v.begin(), v.end(), 0ll);

    assert(v.size() == BLOCK);

    sumi.resize(BLOCK);
    for (int x = 0; x < BLOCK; x++) {
      sumi[x] = 0;
      for (int i = 0; i < BLOCK; i++) {
        sumi[x] += i * get(i ^ x);
      }
    }
  }

  lint get(int i) {
    i ^= globalxor & (BLOCK - 1);
    return v[i];
  }

  lint getsum(int l) {
    lint ans = sumi[globalxor & (BLOCK - 1)];
    ans += 1ll * l * sum;
    return ans;
  }
};

vector<Block> blocks;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, q;
  cin >> n >> q;
  vector<int> a(BLOCK * BLOCK);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < BLOCK; i++) {
    vector<int> v;
    for (int j = 0; j < BLOCK; j++) {
      v.push_back(a[i * BLOCK + j]);
    }
    blocks.push_back(Block(move(v)));
  }

  auto query = [&](int r) -> pair<lint, lint> {
    if (r < 0) return {0, 0};
    lint sum = 0, sumi = 0;
    for (int i = 0; i < BLOCK; i++) {
      if ((i + 1) * BLOCK - 1 <= r) {
        // all is included
        sum += blocks[i].sum;
        sumi += blocks[i].getsum(i * BLOCK);
      } else if (i * BLOCK <= r && r < (i + 1) * BLOCK) {
        // partially included
        for (int j = 0; j <= r % BLOCK; j++) {
          sum += blocks[i].get(j);
          sumi += blocks[i].get(j) * (i * BLOCK + j);
        }
      }
    }
    return {sum, sumi};
  };

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int x;
      cin >> x;
      globalxor ^= x;
      x = x / BLOCK;

      for (int i = 0; i < BLOCK; i++) {
        if (i < (i ^ x)) {
          swap(blocks[i], blocks[i ^ x]);
        }
      }
    } else if (t == 2) {
      int l, r;
      cin >> l >> r;
      cout << query(r).first - query(l-1).first << '\n';
    } else if (t == 3) {
      int l, r;
      cin >> l >> r;

      auto ql = query(l-1);
      auto qr = query(r);

      lint ans = qr.second - ql.second; // A[l] * l + ... + A[r] * r
      ans -= (l - 1) * (qr.first - ql.first);

      cout << ans << '\n';
    }
  }
  return 0;
}
