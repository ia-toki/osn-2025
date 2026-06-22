#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, q; cin >> n;
	vector<int> a(n); int cntn = 0, cnt1 = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] == n) cntn++;
		else cnt1++;
	}

	cin >> q;
	for (int x, y, i = 0; i < q; i++) {
		cin >> x >> y;
		x--;
		if (a[x] == n) cntn--;
		else cnt1--;
		a[x] = y;
		if (a[x] == n) cntn++;
		else cnt1++;

		cout << n - cntn - (cnt1 > 0 ? 1 : 0) << endl;
	}
}