#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;
ll n,l,r,ans,tp; int t;
int fpow(int x,int p){
    int rs=1;
    while(p){
        if(p&1) rs=1LL*rs*x%MOD;
        x=1LL*x*x%MOD; p>>=1;
    }
    return rs;
}
int main(){
    scanf("%d",&t); ll inv2=fpow(2,MOD-2);
    while(t--){
        scanf("%lld %lld %lld",&n,&l,&r); ans=0;
        for(ll i=l,j;i<=r;i=j+1){
            j=min(n/(n/i),r);
            tp=(n*(j-i+1)%MOD-n/i*(i+j)%MOD*(j-i+1)%MOD*inv2%MOD+MOD)%MOD;
            ans+=tp*(1+n/i)%MOD*(n-n/i-1)%MOD;
            tp=((n/i+1)*(i+j)%MOD*(j-i+1)%MOD*inv2%MOD-n*(j-i+1)%MOD+MOD)%MOD;
            ans+=tp*(n/i)%MOD*(n-n/i)%MOD;
            ans%=MOD;
        }
        ans=ans*inv2%MOD;
        printf("%lld\n",ans);
    }
}
