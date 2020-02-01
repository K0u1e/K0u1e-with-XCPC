#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
const int MOD = 1e9+7;
int dp[N][N],tp[N],siz[N],n;
int f[N],g[N];
vector<int> G[N];
int fpow(int x,int p){
    int rs=1;
    while(p){
        if(p&1) rs=1LL*rs*x%MOD;
        x=1LL*x*x%MOD; p>>=1;
    }
    return rs;
}
int C(int n,int m){
    return 1LL*f[n]*g[m]%MOD*g[n-m]%MOD;
}
void dfs(int u,int fa){
    siz[u]=1; dp[u][1]=1;
    for(auto v:G[u]){
        if(v==fa) continue; dfs(v,u); 
        for(int i=1;i<=siz[u];++i) tp[i]=dp[u][i];
        siz[u]+=siz[v];
        for(int i=1;i<=siz[u];++i){
            dp[u][i]=0;
            for(int j=max(1,i-siz[v]);j<=i&&j<=siz[u]-siz[v];++j){
                dp[u][i]=(dp[u][i]+1LL*tp[j]*dp[v][i-j]%MOD*C(i-1,j-1))%MOD;
            }
        }
    }
    for(int i=siz[u]-1;i>=0;--i)
        dp[u][i]=(dp[u][i]+dp[u][i+1])%MOD;
}
int main(){
    scanf("%d",&n); f[0]=1;
    for(int i=1;i<=n;++i) f[i]=1LL*f[i-1]*i%MOD;
    g[n]=fpow(f[n],MOD-2);
    for(int i=n-1;i>=0;--i) g[i]=1LL*g[i+1]*(i+1)%MOD;
    for(int i=1,u,v;i<n;++i){
        scanf("%d %d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,1);
    printf("%d\n",dp[1][1]);
}