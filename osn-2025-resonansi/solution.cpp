#include <bits/stdc++.h>
using namespace std;

const int MX = 200005;
int n, q, a[MX], freq[MX];

struct node {
	int min;
	int count;
} st[MX * 4];

void upd(int nd, int cl, int cr, int ps, int val) {
	if (ps < cl || cr < ps) return;
	if (ps == cl && ps == cr) {
		st[nd].min += val;
		st[nd].count = 1;
		return;
	}

	int cm = (cl + cr) / 2;
	upd(nd * 2, cl, cm, ps, val);
	upd(nd * 2 + 1, cm + 1, cr, ps, val);

	if (st[nd * 2].min == st[nd * 2 + 1].min) {
		st[nd].min = st[nd * 2].min;
		st[nd].count = st[nd * 2].count + st[nd * 2 + 1].count;
	} else if (st[nd * 2].min < st[nd * 2 + 1].min) {
		st[nd] = st[nd * 2];
	} else {
		st[nd] = st[nd * 2 + 1];
	}
	return;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		freq[min(a[i], n + 1)]++;
	}

	vector<int> pref(n + 2, 0);
	for (int i = 1; i <= n; i++) if (freq[i] > 0) {
		int lf = max(i - freq[i] + 1, 1), rg = i;
		pref[lf]++; pref[rg + 1]--;
	}
	for (int i = 1; i <= n + 1; i++) {
		pref[i] += pref[i - 1];
		upd(1, 1, n, i, pref[i]);
	}

	cin >> q;
	for (int x, y; q--;) {
		cin >> x >> y; x--;
		int old = min(a[x], n + 1), left = max(old - freq[old] + 1, 0);
		if (old <= n && left >= 1)
			upd(1, 1, n, left, -1);
		freq[old]--;
		int nw = min(y, n + 1);
		freq[nw]++; left = max(nw - freq[nw] + 1, 0);
		if (nw <= n && left >= 1)
			upd(1, 1, n, left, 1);
		a[x] = nw;

		int mn = st[1].min, count = st[1].count;
		if (mn > 0) cout << 0 << endl;
		else cout << count << endl;
	}

	return 0;
}