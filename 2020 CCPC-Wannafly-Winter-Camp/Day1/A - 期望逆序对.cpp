#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 5e3+10;
const int MOD = 998244353;
struct node{
    ll l,r;
}a[N];
ll f[N],g[N],inv[N]; int n;
ll inv2;
bool cmp(node &a,node &b){
    return a.l+a.r<b.l+b.r;
}
ll fpow(ll x,int p){
    ll res=1;
    while(p){
        if(p&1) res=res*x%MOD;
        p>>=1; x=x*x%MOD;
    }
    return res;
}

ll work(node a,node b){
    ll rs=0;
    //printf("%lld %lld %lld %lld\n",a.l,a.r,b.l,b.r);
    if(a.l>b.r){
        return (a.r-a.l+1)*(b.r-b.l+1)%MOD;
    }
    if(a.r>b.r){
        rs+=(a.r-b.r)*(b.r-b.l+1)%MOD;
        a.r=b.r; rs%=MOD;
    }
    a.l=max(a.l,b.l); ll tp=a.l-b.l;
    if(a.l>a.r) return rs;
    rs+=(tp+tp+a.r-a.l)%MOD*(a.r-a.l+1)%MOD*inv2%MOD;
    rs%=MOD; return rs;
}

int main(){
    scanf("%d",&n); inv2=fpow(2,MOD-2);
    for(int i=1;i<=n;++i)
        scanf("%lld %lld",&a[i].l,&a[i].r);
    f[0]=0; g[0]=1; inv[0]=1;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;++i){
        g[i]=g[i-1]*(a[i].r-a[i].l+1)%MOD;
        f[i]=f[i-1]*(a[i].r-a[i].l+1)%MOD;
        inv[i]=fpow(a[i].r-a[i].l+1,MOD-2);
        for(int j=1;j<i;++j)
            f[i]=(f[i]+work(a[j],a[i])*g[i-1]%MOD*inv[j]%MOD)%MOD;
    }
    //printf("%lld\n",f[n]);
    printf("%lld\n",f[n]*fpow(g[n],MOD-2)%MOD);
}