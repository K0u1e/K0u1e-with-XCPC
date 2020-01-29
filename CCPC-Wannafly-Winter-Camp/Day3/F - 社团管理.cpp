#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+100;
const ll INF = 1e18;
int a[N],n,k;
ll f[N],g[N];
struct DATA{
    int c[N]={0,},l=1,r=0; ll val=0;
    void get(int L,int R){
        while(l<L){
            c[a[l]]--;
            val-=c[a[l]]; l++;
        }
        while(l>L){
            l--; val+=c[a[l]];
            c[a[l]]++;
        }
        while(r<R){
            r++; val+=c[a[r]];
            c[a[r]]++;
        }
        while(r>R){
            c[a[r]]--;
            val-=c[a[r]]; r--;
        }
    }
}da;
void solve(int l,int r,int L,int R){
    int mid=(l+r)>>1; int lim=min(mid,R),p=0;
    f[mid]=INF;
    for(int i=L;i<=lim;++i){
        da.get(i,mid);
        if(f[mid]>g[i-1]+da.val){
            f[mid]=g[i-1]+da.val; p=i;
        }
    }
    if(l<mid) solve(l,mid-1,L,p);
    if(mid<r) solve(mid+1,r,p,R);
}
int main(){
    scanf("%d %d",&n,&k); k--;
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i){
        da.get(1,i); f[i]=da.val;
    }
    while(k--){
        for(int i=1;i<=n;++i) g[i]=f[i];
        solve(1,n,1,n);
    }
    printf("%lld\n",f[n]);
}