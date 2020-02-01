#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 55;
const int MOD = 998244353;
vector<int> a[N];
int dp[N],tmp[N],n,m,t;
int f[N],g[N],w[N][N][N]; ll k;
int fpow(int x,int p){
    int rs=1;
    while(p){
        if(p&1) rs=1LL*rs*x%MOD;
        x=1LL*x*x%MOD; p>>=1;
    }
    return rs;
}
int C(int n,int m){
    return 1LL*f[n]*g[n-m]%MOD*g[m]%MOD;
}
int main(){
    scanf("%d",&t); f[0]=g[0]=1;
    for(int i=1;i<N;++i){
        f[i]=1LL*f[i-1]*i%MOD;
        g[i]=fpow(f[i],MOD-2);
    }
    for(int i=1;i<N;++i){
        for(int j=i;j<N;++j){
            w[i][j][1]=C(j,i);
            for(int k=2;k*i<=j;++k)
                w[i][j][k]=1LL*C(j,i)*w[i][j-i][k-1]%MOD;
        }
    }
    while(t--){
        scanf("%d %lld",&n,&k);
        memset(dp,0,sizeof(dp)); dp[0]=1;
        for(int i=1;i<=n;++i){
            if(k%i) continue;
            memcpy(tmp,dp,sizeof(dp));
            for(int j=0;j<=n;++j){
                for(int k=1,c=f[i-1];j+k*i<=n;++k,c=1LL*c*f[i-1]%MOD){
                    dp[j+k*i]=(dp[j+k*i]+1LL*tmp[j]*w[i][n-j][k]%MOD*c%MOD*g[k])%MOD;
                }
            }
        }
        printf("%d\n",dp[n]);
    }
}
