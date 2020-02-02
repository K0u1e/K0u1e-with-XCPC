#include <bits/stdc++.h>
using namespace std;
const int N = 1<<20;
const int M = 20;
typedef long long ll;
vector<int> que[N];
int e[M],n,m,q,s,lq,lp;
int nex[N],c1[N][M],c2[N][M];
int vis[N],c[M]; int x; ll k;

ll solve(int x,ll k){
    ll rs=0;
    if(c1[lq][x]>=k){
        int l=-1,r=lq,mid;
        while(l+1<r){
            mid=(l+r)>>1;
            if(c1[mid][x]>=k) r=mid;
            else l=mid;
        }
        rs+=r;
    }
    else{
        rs+=lq; k-=c1[lq][x];
        if(c2[lp][x]==0) return -1;
        rs+=(k/c2[lp][x]-(k%c2[lp][x]==0))*lp;
        k-=(k/c2[lp][x]-(k%c2[lp][x]==0))*c2[lp][x];
        int l=0,r=lp,mid;
        while(l+1<r){
            mid=(l+r)>>1;
            if(c2[mid][x]>=k) r=mid;
            else l=mid;
        }
        rs+=r;
    }
    return rs;
}

int main(){
    scanf("%d %d %d",&n,&m,&q);
    for(int i=0,j;i<n;++i){
        scanf("%d",&j);
        if(j) s|=(1<<i);
    }
    while(m--){
        int x,y; scanf("%d %d",&x,&y);
        x--; y--; e[x]|=(1<<y);
    }
    for(int i=0;i<(1<<n);++i)
        for(int j=0;j<n;++j) if((i>>j)&1) nex[i]^=e[j];
    memset(vis,-1,sizeof(vis));
    int pre=s,now=s;
    while(vis[now]==-1){
        vis[now]=vis[pre]+1;
        for(int i=0;i<n;++i) if((now>>i)&1) c[i]++;
        memcpy(c1[vis[now]],c,sizeof(c));
        pre=now; now=nex[now];
    }
    for(int i=0;i<n;++i) if((now>>i)&1) c[i]++;
    memcpy(c1[vis[pre]+1],c,sizeof(c));
    lq=vis[now]; lp=vis[pre]+1-vis[now];
    for(int i=lq;i<=lq+lp;++i){
        for(int j=0;j<n;++j) c2[i-lq][j]=c1[i][j]-c1[lq][j];
    }
    while(q--){
        scanf("%d %lld",&x,&k); x--;
        printf("%lld\n",solve(x,k));
    }
}