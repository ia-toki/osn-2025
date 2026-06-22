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

	int N;
	cin >> N;

	vector<int> A(N);
	for (int &x : A)
		cin >> x;

	int Z = 0;
	vector<int> v; 
	const auto rc = [&](const auto &self, int depth) -> void
	{
		if (depth == N+1)
		{
			bool ok = true;
			for (int i = 0; i < N; ++i) if (lcm(v[i], v[i+1]) != A[i])
			{
				ok = false;
				break;	
			}

			Z += ok;
			return;
		}
		
		for (int i = 1; i <= 12; ++i) {
			v.pb(i);
			self(self, depth + 1);
			v.pop_back();
		}
	};
	rc(rc, 0);

	cout << Z << '\n';
	return 0;
}