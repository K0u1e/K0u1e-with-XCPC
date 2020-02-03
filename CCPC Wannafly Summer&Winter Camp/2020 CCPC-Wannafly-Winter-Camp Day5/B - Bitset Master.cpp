#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+10;
int u[N],v[N],f[N],g[N],p[N],n,m;

int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<n;++i) scanf("%d %d",&u[i],&v[i]);
    for(int i=1;i<=n;++i) f[i]=1;
    for(int i=0;i<m;++i) scanf("%d",&p[i]);
    while(m--){
        int pu=u[p[m]],pv=v[p[m]];
        g[p[m]]=f[pu]=f[pv]=f[pu]+f[pv]-g[p[m]];
    }
    for(int i=1;i<=n;++i) printf("%d%c",f[i],i==n?'\n':' ');
}