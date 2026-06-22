#include <bits/stdc++.h>
using namespace std;

int n;
long long a[500007];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
	for (int i = n - 1; i >= 0; i--) printf("%lld\n", a[i]);
}
