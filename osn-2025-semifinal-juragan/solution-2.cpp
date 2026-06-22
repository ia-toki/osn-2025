#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N;
ll H[MAXN], P[MAXN];
ll S[MAXN];
int zeroes;

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> P[i];
        if (P[i] == 0) {
            zeroes++;
        }

        S[i] = H[i] - P[i];
    }

    ll res = 0;

    for (int i = 0; i < N; i++) {
        ll cur = 0;
        for (int j = 0; j < zeroes && i+j < N; j++) {
            cur += S[i+j];
            res = max(res, cur);
        }
    }

    cout << res << endl;
}
