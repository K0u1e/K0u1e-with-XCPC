#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5+1;
struct Edge{
    int to,w;
}edge[N<<1];
vector<int> g[N],t[N];
bool vis[N]; int siz[N],n,k,p;
ll d[N],d1[N],d2[N],tp;
void dfs(int u,int fa,int w){
    d[u]=d[fa]+w;
    if(vis[u]) siz[u]=1,tp+=d[u]*2;
    for(auto i:g[u]){
        Edge &e=edge[i]; if(e.to==fa) continue;
        dfs(e.to,u,e.w);
        if(siz[e.to]){
            t[u].push_back(i);
            t[e.to].push_back(i^1);
            siz[u]+=siz[e.to];
        }
    }
    if(siz[u]) tp-=1LL*w*(siz[u]-1)*2;
}
void dfs1(int u,int fa){
    for(auto i:t[u]){
        Edge &e=edge[i]; if(e.to==fa) continue;
        d1[e.to]=d1[u]+e.w; dfs1(e.to,u);
    }
}
void dfs2(int u,int fa){
    for(auto i:t[u]){
        Edge &e=edge[i]; if(e.to==fa) continue;
        d2[e.to]=d2[u]+e.w; dfs2(e.to,u);
    }
}
void dfs3(int u,int fa){
    for(auto i:g[u]){
        Edge &e=edge[i];
        if(e.to==fa||siz[e.to]) continue;
        d[e.to]=d[u]+e.w; dfs3(e.to,u);
    }
}

int main(){
    scanf("%d %d",&n,&k);
    for(int i=0,u,v,w;i<n-1;++i){
        scanf("%d %d %d",&u,&v,&w);
        edge[i<<1].to=v; edge[i<<1].w=w;
        edge[(i<<1)|1].to=u; edge[(i<<1)|1].w=w;
        g[u].push_back(i<<1);
        g[v].push_back((i<<1)|1);
    }
    while(k--){
        scanf("%d",&p);
        vis[p]=true;
    }
    dfs(p,p,0);
    for(int i=1;i<=n;++i){
        if(!vis[i]) continue;
        if(d[i]>d[p]) p=i;
    }
    dfs1(p,p);
    for(int i=1;i<=n;++i){
        if(!vis[i]) continue;
        if(d1[i]>d1[p]) p=i;
    }
    dfs2(p,p);
    for(int i=1;i<=n;++i){
        if(!siz[i]) continue;
        d[i]=tp-max(d1[i],d2[i]);
    }
    for(int i=1;i<=n;++i)
        if(siz[i]) dfs3(i,i);
    for(int i=1;i<=n;++i)
        printf("%lld\n",d[i]);
}