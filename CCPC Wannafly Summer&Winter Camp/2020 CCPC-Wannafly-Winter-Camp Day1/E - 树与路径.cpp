#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 3e5+10;
const int D = 20;
int fa[N][D],deg[N],n,m;
ll ans[N],a[N],d[N];
ll tp,dp,w;
vector<int> g[N];
int u[N],v[N],an[N];
void dfs1(int u,int f){
    deg[u]=deg[f]+1; fa[u][0]=f;
    for(int i=1;i<D;++i)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(auto v:g[u]){
        if(v==f) continue;
        dfs1(v,u);
    }
}
int lca(int u,int v){
    if(deg[u]>deg[v]) swap(u,v);
    int hu=deg[u], hv=deg[v];
    int tu=u, tv=v;
    for(int det=hv-hu,i=0;det;det>>=1,i++){
        if(det&1) tv=fa[tv][i];
    }
    if(tu==tv) return tu;
    for(int i=D-1;i>=0;i--){
        if(fa[tu][i]==fa[tv][i]) continue;
        tu=fa[tu][i]; tv=fa[tv][i];
    }
    return fa[tu][0];
}
void pre(int u,int v,int an){
    int hu=deg[u]-deg[an],hv=deg[v]-deg[an];
    d[an]-=4; d[u]+=2; d[v]+=2;
    a[an]+=2*(-hu-hv+1)+4*(hu+hv);
    a[u]+=hu+hv-1-2*(hu+hv); a[v]+=hu+hv-1-2*(hu+hv);
    w+=1LL*hu*hv;
}
void pre2(int u,int v,int an){
    int hu=deg[u]-deg[an],hv=deg[v]-deg[an];
    d[an]-=hu*2+hv*2;
}
void dfs2(int u,int f){
    for(auto v:g[u]){
        if(v==f) continue;
        dfs2(v,u);
        d[u]+=d[v]; a[u]+=a[v];
    }
}
void dfs3(int u,int f){
    for(auto v:g[u]){
        if(v==f) continue;
        dfs3(v,u);
        d[u]+=d[v];
    }
}
void dfs4(int u,int f){
    w+=a[u]+d[u];
    ans[u]=w;
    for(auto v:g[u]){
        if(v==f) continue;   
        dfs4(v,u);
    }
    w-=a[u]+d[u];
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i=1,u,v;i<n;++i){
        scanf("%d %d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1,1);
    for(int i=0;i<m;++i){
        scanf("%d %d",&u[i],&v[i]);
        an[i]=lca(u[i],v[i]);
        pre(u[i],v[i],an[i]);
    }
    dfs2(1,1);
    for(int i=0;i<m;++i) pre2(u[i],v[i],an[i]);
    dfs3(1,1); dfs4(1,1);
    
    for(int i=1;i<=n;++i)
        printf("%lld\n",ans[i]);
}

/*
5 2
1 2
1 3
3 4
3 5
2 5
4 5

3
1
3
2
0

*/