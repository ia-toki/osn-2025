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

    ll cur = 0;
    for (int i = 0; i < N && i < zeroes; i++) {
        cur += S[i];
    }

    if (zeroes >= N) {
        cout << cur << endl;
        return 0;
    }

    ll res = cur;
    for (int j = zeroes; j < N; j++) {
        cur += S[j];
        cur -= S[j - zeroes];
        res = max(res, cur);
    }

    cout << res << endl;
}
