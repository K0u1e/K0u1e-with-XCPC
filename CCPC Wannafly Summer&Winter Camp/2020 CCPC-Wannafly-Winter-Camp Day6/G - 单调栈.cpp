#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int p[N],f[N],n,now;
vector<int> g[N];
int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i) scanf("%d",&f[i]);
        for(int i=1;i<=n;++i) g[i].clear();
        now=0;
        for(int i=1;i<=n;++i){
            if(f[i]==-1) f[i]=++now;
            else now=max(now,f[i]);
        }
        for(int i=n;i>=1;--i)
            g[f[i]].push_back(i);
        now=0;
        for(int i=1;i<=n;++i){
            for(auto j:g[i]) p[j]=++now;
        }
        for(int i=1;i<=n;++i)
            printf("%d%c",p[i],i==n?'\n':' ');
    }
}