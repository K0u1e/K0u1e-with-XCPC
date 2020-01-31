#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
vector<int> g[N];
int siz[N],son[N],ans[N],n;
struct Data{
    set<int> st;
    long long val;
    void clear(){
        st.clear(); val=0;
    }
    void insert(int x){
        set<int>::iterator l,r;
        r=st.lower_bound(x);
        if(r!=st.begin()){
            l=r; l--; val+=1LL*(x-*l)*(x-*l);
        }
        if(r!=st.end()){
            val+=1LL*(*r-x)*(*r-x);
        }
        if(r!=st.begin()&&r!=st.end()){
            val-=1LL*(*r-*l)*(*r-*l);
        }
        st.insert(x);
    }
}da;

void dfs1(int u){
    son[u]=-1; siz[u]=1;
    for(auto v:g[u]){
        dfs1(v); siz[u]+=siz[v];
        if(son[u]==-1||siz[v]>siz[son[u]]) son[u]=v;
    }
}

void dfs2(int u){
    da.insert(u);
    for(auto v:g[u]) dfs2(v);
}

void dfs3(int u,int cl){
    for(auto v:g[u]){
        if(v==son[u]) continue;
        dfs3(v,1);
    }
    if(~son[u]) dfs3(son[u],0);
    for(auto v:g[u])
        if(v!=son[u]) dfs2(v);
    da.insert(u); ans[u]=da.val;
    if(cl) da.clear();
}

int main(){
    scanf("%d",&n);
    for(int i=2,j;i<=n;++i){
        scanf("%d",&j);
        g[j].push_back(i);
    }
    dfs1(1); dfs3(1,1);
    for(int i=1;i<=n;++i) printf("%d\n",ans[i]);
}