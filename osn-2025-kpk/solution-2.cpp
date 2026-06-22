#include <bits/stdc++.h>
using namespace std;

#define pb push_back

using ll = long long;

ll lcm(ll a, ll b)
{
	return a * b / gcd(a, b);
}

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	int N, A;
	cin >> N >> A;

	vector<int> factor;
	for (int i = 1; i*i <= A; ++i) if (A % i == 0)
	{
		factor.pb(i);
		if (i*i < A) factor.pb(A/i);
	}

	int Z = 0;
	for (int x : factor) for (int y : factor) if (lcm(x, y) == A) {
		Z++;
	}

	cout << Z << '\n';
	return 0;
}