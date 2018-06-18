#include <bits/stdc++.h>

using namespace std;

map<vector<int>, int> dp;

int ask(vector<int> t) {
    if(dp.find(t)!=dp.end()) return dp[t];
    
    for(auto i:t) {
        cout<<i<<" ";
    }
    cout<<"\n";
    cout.flush();
    
    int ans;
    cin>>ans;
    
    return dp[t]=ans;
}

int main() {
    int n;
    cin>>n;
    
    map<int,int> cnt, akt;
    vector<int> t(n);
    for(int i=0;i<n;++i) {
        cin>>t[i];
        cnt[t[i]]++;
        akt[t[i]]=1;
    }
    
    sort(t.begin(), t.end());
    
    int last=ask(t);
    vector<int> ans(n);
    
    vector<pair<int,int>> lst;
    
    for(int i=1;i<=n;++i) {
        rotate(t.begin(), t.begin()+1, t.end());
        int curr=ask(t);
        
        int pos=(last-curr+n-cnt[t.back()])/2+cnt[t.back()]-akt[t.back()];
        lst.push_back({pos, t.back()});        
        //cerr<<last-curr<<"\n";
        cerr<<pos<<"\n";
        last=curr;
        akt[t.back()]++;
    }
    
    sort(lst.begin(), lst.end());
    for(auto i:lst) cout<<i.second<<" ";
    
    cout.flush();
    int rep;
    cin>>rep;
    
    assert(rep==0);
    
    return 0;
}
