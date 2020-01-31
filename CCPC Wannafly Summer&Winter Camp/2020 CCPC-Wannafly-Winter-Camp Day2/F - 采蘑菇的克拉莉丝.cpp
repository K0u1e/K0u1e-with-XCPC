#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+10;
int n,m,dfs_clock;
struct Edge{
    int u,v,w;
}e[N];
int fa[N],siz[N];
int top[N],l[N],r[N],son[N];
ll w[N],f[N],bit[N];
vector<int> g[N];

ll sum(int x){
    ll rs=0;
    while(x){
        rs+=bit[x];
        x-=x&-x;
    }
    return rs;
}
void add(int x,int w){
    while(x<=n){
        bit[x]+=w;
        x+=x&-x;
    }
}

void dfs1(int u,int f){
    fa[u]=f; siz[u]=1; son[u]=-1;
    int maxson=-1,v;
    for(auto i:g[u]){
        v=e[i].u^e[i].v^u;
        if(v==f) continue; 
        dfs1(v,u); siz[u]+=siz[v]; w[v]=e[i].w;
        if(siz[v]>maxson) son[u]=v,maxson=siz[v];
    }
}
void dfs2(int u,int t){
    l[u]=++dfs_clock; top[u]=t;
    if(son[u]==-1){
        r[u]=dfs_clock;
        return ;
    }
    dfs2(son[u],t); int v;
    for(auto i:g[u]){
        v=e[i].u^e[i].v^u;
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v); 
    }
    r[u]=dfs_clock;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;++i){
        scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].w);
        g[e[i].u].push_back(i);
        g[e[i].v].push_back(i);
    }
    dfs1(1,1); dfs2(1,1);
    scanf("%d",&m);
    int op,v,x,u=1; ll ans;
    while(m--){
        scanf("%d",&op);
        if(op==1){
            scanf("%d %d",&v,&x);
            add(l[v],x); v=top[v];
            while(v!=fa[v]){
                f[fa[v]]+=w[v]*x;
                v=top[fa[v]];
            }
        }
        else scanf("%d",&u);
        ans=f[u];
        if(fa[u]!=u){
            ans+=sum(l[u]-1)*w[u];
            ans+=(sum(n)-sum(r[u]))*w[u];
        }
        if(~son[u])
            ans+=(sum(r[son[u]])-sum(l[son[u]]-1))*w[son[u]];
        printf("%lld\n",ans);
    }

}