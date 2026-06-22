#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int N;
int H[MAXN], P[MAXN];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
        res = max(res, H[i] - P[i]);
    }

    cout << res << endl;
}
