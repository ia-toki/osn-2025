#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAX_N = 2e5;
const int MAX_K = 2e5;
LL ar[MAX_N + 5];

typedef pair<LL,int> pli;
#define fi first
#define se second
#define mp make_pair

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    vector<vector<pli> > v;

    vector<pli> now;
    for(int i = 0;i < n; ++i){
        scanf("%lld", &ar[i]);
        now.push_back(mp(ar[i], 1));
    }

    v.push_back(now);

    for(int i = 0;i < k; ++i){
        vector<vector<pli> > lef;
        vector<vector<pli> > rig;
        for(vector<pli>& ve: v){
            vector<pli> cur_left;
            vector<pli> cur_right;
            int cur_sum = 0;
            for(pli& x: ve){
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
            lef.push_back(cur_left);
            rig.push_back(cur_right);
        }

        v = lef;
        v.insert(v.end(), rig.begin(), rig.end());
    } 

    if(v.size() > MAX_K) v.resize(MAX_K);
    for(vector<pli>& ve: v){
        LL total = 0;
        for(pli &x: ve){
            total += x.fi * x.se;
        }
        printf("%lld\n", total);
    }

    return 0;
}
