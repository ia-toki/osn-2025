#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAX_K = 200000;

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

        vector<vector<int>> ans_before = ans;
        
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

        // after some time, the array will always be the same when duplicating again if already exceeds MAX_K. If that happens, terminate.
        // it will happen after log(N) * 2 times, but just checking if already the same to be sure

        if(ans_before.size() >= MAX_K) {
            bool same = true;
            for(int j = 0;j < MAX_K && same; ++j){
                if(ans[j] != ans_before[j]) same = false;
            }
            if(same) break;
            ans.resize(MAX_K);
        }
    }

    if(ans.size() > MAX_K) ans.resize(MAX_K);

    for(vector<int>&v: ans){
        LL res = 0;
        for(int& x: v){
            res += x;
        }
        printf("%lld\n", res);
    }
    return 0;
}
