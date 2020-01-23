#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 5e5+100;
const int D = 20;
int t1[N],t2[N],c[N];
struct suffix_array_on_tree{
    vector<int> g[N]; int n,dep;
    int str[N],rank[N],sa[N],fa[N][D];
    void init(int n){
        for(int i=0;i<=n;++i) g[i].clear();
        g[0].push_back(1); dep=0;
    }
    void dfs(int u,int f,int d){
        fa[u][0]=f; dep=max(dep,d);
        for(int i=1;i<D;++i)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(auto v:g[u]) dfs(v,u,d+1);
    }
    inline bool cmp(int *r,int a,int b,int l){
        return r[a]==r[b]&&r[fa[a][l]]==r[fa[b][l]];
    }
    void getsa(int n,int m){
        n++; int i,j,p,*x=t1,*y=t2;
        for(i=0;i<m;++i) c[i]=0;
        for(i=0;i<n;++i) c[x[i]=str[i]]++;
        for(i=1;i<m;++i) c[i]+=c[i-1];
        for(i=n-1;i>=0;--i) sa[--c[x[i]]]=i;
        
        for(j=0;(1<<j)<=dep;++j){
            for(i=0;i<m;++i) c[i]=0;
            for(i=0;i<n;++i) c[x[fa[i][j]]]++;
            for(i=1;i<m;++i) c[i]+=c[i-1];
            for(i=0;i<n;++i) y[--c[x[fa[i][j]]]]=i;
            for(i=0;i<m;++i) c[i]=0;
            for(i=0;i<n;++i) c[x[y[i]]]++;
            for(i=1;i<m;++i) c[i]+=c[i-1];
            for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
            swap(x,y); p=1; x[sa[0]]=0;
            for(i=1;i<n;++i) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
            if(p>=n) break; m=p;
        }
    }
}sa;

char s[N]; int n;
int main(){
    scanf("%d",&n); sa.init(n);
    for(int i=2,j;i<=n;++i){
        scanf("%d",&j);
        sa.g[j].push_back(i);
    }
    scanf("%s",s+1); sa.str[0]=0;
    for(int i=1;i<=n;++i) sa.str[i]=s[i]-'a'+1;
    sa.dfs(0,0,1); sa.getsa(n,27);
    for(int i=1;i<=n;++i) printf("%d ",sa.sa[i]);
}