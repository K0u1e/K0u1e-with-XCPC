#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+100;
ll tr[N<<2];
int mx[N<<2],mn[N<<2],lz[N<<2];
void pushup(int k){
    int lk=k<<1,rk=k<<1|1;
    tr[k]=tr[lk]+tr[rk];
    mx[k]=max(mx[lk],mx[rk]);
    mn[k]=min(mn[lk],mn[rk]);
}
void build(int k,int l,int r){
    lz[k]=-1;
    if(l==r){    
        tr[k]=mn[k]=mx[k]=l-1;
        return;
    }
    int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
    build(lk,l,mid); build(rk,mid+1,r);
    pushup(k);
}
void pushdown(int k,int l,int r){
    if(~lz[k]){
        int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
        lz[lk]=lz[k]; lz[rk]=lz[k];
        mx[lk]=mn[lk]=mx[rk]=mn[rk]=lz[k];
        tr[lk]=1LL*(mid-l+1)*lz[k];
        tr[rk]=1LL*(r-mid)*lz[k];
        lz[k]=-1;
    }
}
void update(int a,int b,int x,int k,int l,int r){
    if(a>r||b<l) return ;
    if(a<=l&&r<=b){
        if(mn[k]>=x) return ;
        if(mx[k]<x){
            tr[k]=1LL*(r-l+1)*x;
            mn[k]=mx[k]=x;
            lz[k]=max(lz[k],x);
            return ;
        }
    }
    int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
    pushdown(k,l,r);
    update(a,b,x,lk,l,mid);
    update(a,b,x,rk,mid+1,r);
    pushup(k);
}
int p[N],n,m=2e5,t;
ll ans=0,tp;
int a,b,c,d;
int main(){
    scanf("%d",&t);
    while(t--){
        memset(p,0,sizeof(p));
        scanf("%d",&n); ans=0;
        for(int i=1;i<=n;++i){
            scanf("%d",&a); p[a]=i;
        }
        build(1,1,n);
        for(int i=m;i>=1;--i){
            a=N,b=N,c=-N,d=-N;
            for(int j=i;j<=m;j+=i){
                if(!p[j]) continue;
                if(a>p[j]) b=a,a=p[j];
                else if(b>p[j]) b=p[j];
                if(d<p[j]) c=d,d=p[j];
                else if(c<p[j]) c=p[j];
            }
            if(b==N) continue;
            tp=tr[1];
            if(b<n) update(b+1,n,n,1,1,n);
            update(a+1,b,d-1,1,1,n);
            update(1,a,c-1,1,1,n); 
            ans+=(tr[1]-tp)*i;
        }
        printf("%lld\n",ans);
    }
}
