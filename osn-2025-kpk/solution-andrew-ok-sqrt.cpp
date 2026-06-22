#include <bits/stdc++.h>
using namespace std;

#define f1 first
#define s2 second
#define pb push_back

using ii = pair<int, int>;
using ll = long long;

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

const int MAX = 1 << 17;
const int MAXM = 1 << 20;

int N;
vector<ii> pos[MAXM];

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		int k; cin >> k;

		for (int p = 2; p*p <= k; ++p) if (k % p == 0)
		{
			int fq = 0;
			while (k % p == 0)
				fq++, k /= p;

			pos[p].pb({i, fq});
		}

		if (k > 1) pos[k].pb({i, 1});
	}

	MintA Z = 1;
	for (int p = 2; p < MAXM; ++p) if (!pos[p].empty())
	{
		int max_pwr = 0;
		for (ll cur = p; cur <= MAXM; cur *= p)
			max_pwr++;

		vector<MintA> dp(max_pwr+1, 1), nxt(max_pwr+1);

		int prv = 0;
		for (auto [i, fq] : pos[p])
		{
			if (i > prv + 1)
			{
				Z *= dp[0];
				fill(dp.begin(), dp.end(), 0);
				dp[fq] = 1; prv = i;
			}
			else
			{
				fill(nxt.begin(), nxt.end(), 0);
				for (int x = 0; x < fq; ++x) if (dp[x] != 0)
				{
					nxt[fq] += dp[x];
				}
				if (dp[fq] != 0)
				{
					for (int y = 0; y <= fq; ++y)
						nxt[y] += dp[fq];
				}

				dp = nxt; prv = i;
			}
		}

		if (auto [i, fq] = pos[p].back(); i == N)
		{
			MintA sum = 0;
			for (int x = 0; x <= fq; ++x)
				sum += dp[x];
			Z *= sum;
		}
		else
		{
			Z *= dp[0];
		}
	}

	cout << Z << '\n';
	return 0;
}
