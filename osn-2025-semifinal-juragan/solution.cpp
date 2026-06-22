#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 200005;

int N;
ll H[MAXN], P[MAXN];
ll S[MAXN];
int zeroes;

priority_queue<pair<ll, int>> pq;

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> H[i];
    }

    for (int i = 1; i <= N; i++) {
        cin >> P[i];
        if (P[i] == 0) {
            zeroes++;
        }

        S[i] = S[i - 1] + H[i] - P[i];
    }

    pq.push({0, 0});

    ll res = 0;
    for (int i = 1; i <= N; i++) {
        while (!pq.empty() && i - pq.top().second > zeroes) {
            pq.pop();
        }

        if (!pq.empty()) {
            res = max(res, S[i] + pq.top().first);
        }
        pq.push({-S[i], i});
    }

    cout << res << endl;
}
