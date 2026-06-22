#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAX_N = 2e5;
const int MAX_K = 2e5;
int ar[MAX_N + 5];

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

vector<pii> v[2 * MAX_K + 5], v_before[2 * MAX_K + 5], lef[MAX_K + 5], rig[MAX_K + 5];

int main(){
    int n, k;
    scanf("%d%d", &n, &k);

    for(int i = 0;i < n; ++i){
        scanf("%d", &ar[i]);
        v[0].push_back(mp(ar[i], 1));
    }

    v_before[0] = v[0];

    // int cnt_loop = 0;
    int siz = 1;
    for(int i = 0;i < k; ++i/*, ++cnt_loop*/){
        for(int j = 0;j < siz; ++j){
            v_before[j] = v[j];
            vector<pii> cur_left;
            vector<pii> cur_right;
            int cur_sum = 0;
            for(pii& x: v[j]){
                if(cur_sum < n) {
                    int banyak = min(n - cur_sum, 2 * x.se);
                    int sisa = 2 * x.se - banyak;
                    cur_left.push_back(mp(x.fi, banyak));
                    if(sisa){
                        cur_right.push_back(mp(x.fi, sisa));
                    }
                }
                else{
                    cur_right.push_back(mp(x.fi, 2 * x.se));
                }

                cur_sum += 2 * x.se;
            }
            lef[j] = cur_left;
            rig[j] = cur_right;
        }

        int idx_v = 0;
        for(int j = 0;j < siz; ++j, ++idx_v){
            v[idx_v] = lef[j];
        }
        for(int j = 0;j < siz; ++j, ++idx_v){
            v[idx_v] = rig[j];
        }

        siz <<= 1;
        if(siz >= MAX_K) {
            bool same = true;
            for(int j = 0;j < MAX_K && same; ++j){
                if(v[j] != v_before[j]) same = false;
            }
            siz = min(siz, MAX_K);
            if(same) break;
        }
    } 

    for(int i = 0;i < siz; ++i){
        LL total = 0;
        for(pii &x: v[i]){
            total += 1LL * x.fi * x.se;
        }
        printf("%lld\n", total);
    }

    return 0;
}
