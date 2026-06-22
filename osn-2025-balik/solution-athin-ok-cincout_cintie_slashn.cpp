#include <bits/stdc++.h>
using namespace std;

int n;
long long a[500007];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = n - 1; i >= 0; i--) cout << a[i] << "\n";
}
