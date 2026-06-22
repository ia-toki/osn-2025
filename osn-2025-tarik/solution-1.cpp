#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    vector<vector<int>>ans(1);
    for(int i = 0;i < n; ++i){
        int x;
        scanf("%d", &x);
        ans[0].push_back(x);
    }

    for(int i = 0;i < k; ++i){
        vector<vector<int>> ans_left;
        vector<vector<int>> ans_right;
        
        for(vector<int>&v: ans){
            vector<int> lef;
            vector<int> rig;
            int cnt = 0;
            for(int j = 0;j < n; ++j){
                if(cnt < n) lef.push_back(v[j]);
                else rig.push_back(v[j]);
                cnt++;
                if(cnt < n) lef.push_back(v[j]);
                else rig.push_back(v[j]);
                cnt++;
            }
            ans_left.push_back(lef);
            ans_right.push_back(rig);
        }

        ans = ans_left;
        ans.insert(ans.end(), ans_right.begin(), ans_right.end());
    }

    for(vector<int>&v: ans){
        LL res = 0;
        for(int& x: v){
            res += x;
        }
        printf("%lld\n", res);
    }
    return 0;
}
