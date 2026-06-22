#include <bits/stdc++.h>
using namespace std;

#define pb push_back

using ll = long long;

ll lcm(ll a, ll b)
{
	return a * b / gcd(a, b);
}

template<int MOD>
class Mint 
{
public:
    int v;
    Mint() : v(0) {}
    Mint(int64_t _v) {
        v = int((-MOD < _v && _v < MOD) ? (_v) : (_v % MOD));
        if (v < 0) v += MOD;
    }
 
    friend bool operator==(const Mint &a, const Mint &b) {return a.v == b.v;}
    friend bool operator!=(const Mint &a, const Mint &b) {return a.v != b.v;}
    friend bool operator< (const Mint &a, const Mint &b) {return a.v <  b.v;}
    friend bool operator<=(const Mint &a, const Mint &b) {return a.v <= b.v;}
    friend bool operator> (const Mint &a, const Mint &b) {return a.v >  b.v;}
    friend bool operator>=(const Mint &a, const Mint &b) {return a.v >= b.v;}
 
    Mint &operator+=(const Mint &a) {if ((v += a.v) >= MOD) v -= MOD; return *this;}
    Mint &operator-=(const Mint &a) {if ((v -= a.v) < 0) v += MOD; return *this;}
    Mint &operator*=(const Mint &a) {v = int(1ll * v * a.v % MOD); return *this;}
    Mint &operator/=(const Mint &a) {return (*this) *= inverse(a);}
 
    friend Mint fpow(Mint a, long long x) {
        Mint res = 1;
        for (; x; x /= 2, a *= a) if (x & 1) res *= a;
        return res;
    }
    friend Mint inverse(Mint a) {return fpow(a, MOD - 2);}
 
    Mint operator+ () const {return Mint( v);}
    Mint operator- () const {return Mint(-v);}
    Mint operator++() const {return *this += 1;}
    Mint operator--() const {return *this -= 1;}
 
    friend Mint operator+(Mint a, const Mint &b) {return a += b;}
    friend Mint operator-(Mint a, const Mint &b) {return a -= b;}
    friend Mint operator*(Mint a, const Mint &b) {return a *= b;}
    friend Mint operator/(Mint a, const Mint &b) {return a /= b;}
 
    friend istream &operator>>(istream &is, Mint &v) {return is >> v.v;}
    friend ostream &operator<<(ostream &os, const Mint &v) {return os << v.v;}
};
const int ModA = 1e9 + 7;
using MintA    = Mint<ModA>;

const int MAXN = 100001;
const int MAXM = 5001;

int N, A[MAXN];
MintA dp[2][MAXM];

vector<int> get_factors(int k) {
  vector<int> Z;
  for (int i = 1; i*i <= k; ++i) if (k % i == 0) {
    Z.pb(i);
    if (i*i < k) Z.pb(k / i);
  }
  return Z;
}

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }

  fill(dp[0], dp[0] + MAXM, 1);
  vector<int> prv = get_factors(A[0]);
  for (int i = 0; i < N; ++i)
	{
		fill(dp[~i&1], dp[~i&1] + MAXM, 0);
    
    vector<int> cur = get_factors(gcd(A[i], A[i+1]));
		for (int x : prv) for (int y : cur) if (lcm(x, y) == A[i])	
		{
			dp[~i&1][y] += dp[i&1][x];
		}
    prv = cur;
	}

	cout << accumulate(dp[N&1], dp[N&1] + MAXM, MintA(0)) << '\n';;
	return 0;
}
