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
int lpf[MAXM];
vector<ii> pos[MAXM];

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	iota(lpf, lpf + MAXM, 0);
	for (int i = 4; i < MAXM; i += 2)
		lpf[i] = 2;
	for (int i = 3; i < MAXM; i += 2) if (lpf[i] == i)
		for (ll j = 1ll*i*i; j < MAXM; j += i) if (lpf[j] == j) 
			lpf[j] = i;

	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		int k; cin >> k;

		int p = 0, fq = 0;
		for (; k > 1; k /= lpf[k])
		{
			if (p == lpf[k]) fq++;
			else
			{
				if (p) {
					pos[p].pb({i, fq});	
				} 
				p = lpf[k]; fq = 1;
			}
		}
		pos[p].pb({i, fq});
	}

	MintA Z = 1;
	for (int p = 2; p < MAXM; ++p) if (!pos[p].empty())
	{
		int prv = 0, prv_fq = 100;
		MintA val = 1, sum = 1;
		for (auto [i, fq] : pos[p])
		{
			if (i > prv + 1)
			{
				Z *= val;
				val = 0; sum = 1;
				prv_fq = fq; prv = i;
			}
			else
			{
	            if (prv_fq == fq) {
	                MintA tmp = sum;
	                sum += val * fq;
	                val = tmp; 
	            } else if (prv_fq < fq) {
	                sum += val * prv_fq;
	                val = 0;
	            } else {
	                sum = val * (fq+1);
	            }

	            prv_fq = fq; prv = i;
			}
		}

		if (auto [i, fq] = pos[p].back(); i == N)
		{
			Z *= fq * val + sum;
		}
		else
		{
			Z *= val;
		}
	}

	cout << Z << '\n';
	return 0;
}
