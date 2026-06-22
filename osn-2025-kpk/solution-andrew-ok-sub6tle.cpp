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

const int MAXN = 1e5 + 1;
const int MAXM = 1e6 + 1;
const int LG = 20;

bitset<MAXM> prime, used;

int N, A[MAXN], P[MAXN];
MintA dp[2][LG];

int main()
{
    ios :: sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    // for (int i = 2; i < MAXM; ++i)
    //     prime[i] = true;
    // for (int i = 2; i*i < MAXM; ++i) if (prime[i]) {
    //     for (int j = i*i; j < MAXM; j += i) 
    //         prime[j] = false;
    // }

    for (int i = 0; i < N; ++i) {
        cin >> A[i];

        int x = A[i];
        for (int p = 2; p*p <= x; ++p) while (x % p == 0) {
            used[p] = true;
            x /= p;
        }
        if (x > 1) used[x] = true;
    }

    MintA Z = 1;
    for (int p = 2; p < MAXM; ++p) if (used[p])
    {
        memset(P, 0, sizeof(P));

        int l = N, r = 0, max_pwr = 0;

        for (int i = 0; i < N; ++i) {
            while (A[i] % p == 0) {
                P[i]++;
                A[i] /= p;
            }

            if (P[i]) {
                max_pwr = max(max_pwr, P[i]);
                l = min(l, i);
                r = max(r, i);
            }
        }

        if (l == 0) {
            fill(dp[0], dp[0] + max_pwr+1, 1);
        } else {
            fill(dp[l&1], dp[l&1] + max_pwr+1, 0);
            dp[l&1][0] = 1;
        }

        for (int i = l; i <= r; ++i)
        {
            fill(dp[~i&1], dp[~i&1] + max_pwr+1, 0);
            for (int x = 0; x < P[i]; ++x) {
                dp[~i&1][P[i]] += dp[i&1][x];
            }
            for (int y = 0; y <= P[i]; ++y) {
                dp[~i&1][y] += dp[i&1][P[i]];
            }
        }

        if (r == N-1) {
            Z *= accumulate(dp[N&1], dp[N&1] + max_pwr+1, MintA(0));
        } else {
            Z *= dp[~r&1][0];
        }
    }


    cout << Z << '\n';;
    return 0;
}
