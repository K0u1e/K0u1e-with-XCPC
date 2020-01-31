#include <bits/stdc++.h>
using namespace std;
const int N = 55, D = 30;
const int MOD = 1e9+7;
int m[N],n,k,f[N][N],ans;
int fpow(int x,int p){
    int rs=1; x%=MOD;
    while(p){
        if(p&1) rs=1LL*rs*x%MOD;
        x=1LL*x*x%MOD; p>>=1;
    }
    return rs;
}
int solve(int d){
    if(d==-1) return 1;
    int rs=0,c=0;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n;++j) f[i][j]=0;
    f[0][0]=1;
    for(int i=1;i<=n;++i){
        if((m[i]>>d)&1) c++;
        if((m[i]>>d)&1) f[i][0]=1LL*f[i-1][0]*(1<<d)%MOD;
        else f[i][0]=1LL*f[i-1][0]*(m[i]+1)%MOD;
        for(int j=1;j<=c;++j){
            if((m[i]>>d)&1){
                f[i][j]=1LL*f[i-1][j]*(1<<d)%MOD;
                f[i][j]=(f[i][j]+1LL*f[i-1][j-1]*(m[i]-(1<<d)+1))%MOD;
            }
            else f[i][j]=1LL*f[i-1][j]*(m[i]+1)%MOD;
        }
    }
    for(int i=(k>>d)&1;i<=c;i+=2){
        if(i!=c) rs=(rs+f[n][i])%MOD;
        else{
            for(int i=1;i<=n;++i) m[i]&=(1<<d)-1;
            rs=(1LL*rs*fpow(1<<d,MOD-2)+solve(d-1))%MOD;
            return rs;
        }
    }
    rs=1LL*rs*fpow(1<<d,MOD-2)%MOD;
    return rs;
}
int main(){
    while(scanf("%d %d",&n,&k)!=EOF){
        for(int i=1;i<=n;++i) scanf("%d",&m[i]);
        printf("%d\n",solve(D));
    }
}