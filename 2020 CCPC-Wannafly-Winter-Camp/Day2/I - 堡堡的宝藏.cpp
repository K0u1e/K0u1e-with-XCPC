#include <bits/stdc++.h>
using namespace std;
const int N = 751;
const int INF = 0x3f3f3f3f;
int w[N][N],lx[N],ly[N];
int linker[N],slack[N],pre[N];
int n,m,nl,nr;
bool vis[N];
int idx[N<<1];
void bfs(int x){
    int y=0,nex=0,d;
    memset(pre,0,sizeof(pre));
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;++i) slack[i]=INF;
    linker[y]=x;
    while(true){
        x=linker[y]; d=INF; vis[y]=true;
        for(int i=1;i<=n;++i){
            if(!vis[i]){
                if(slack[i]>lx[x]+ly[i]-w[x][i]){
                    slack[i]=lx[x]+ly[i]-w[x][i];
                    pre[i]=y;
                }
                if(slack[i]<d){
                    d=slack[i]; nex=i;
                }
            }
        }
        for(int i=0;i<=n;++i){
            if(vis[i]){
                lx[linker[i]]-=d; ly[i]+=d;
            }
            else slack[i]-=d;
        }
        y=nex; if(linker[y]==-1) break;
    }
    while(y){
        linker[y]=linker[pre[y]]; y=pre[y];
    }
}
long long KM(){
    long long rs=0;
    memset(lx,0,sizeof(lx)); memset(ly,0,sizeof(ly));
    memset(linker,-1,sizeof(linker));
    for(int i=1;i<=n;++i) bfs(i);
    for(int i=1;i<=n;++i) rs+=lx[i],rs+=ly[i];
    return rs;
}

int main(){
    scanf("%d %d",&n,&m); nl=nr=0;
    for(int i=0;i<n*m;++i){
        if((i/m+i%m)&1) idx[i]=++nl;
        else idx[i]=++nr;
    }
    scanf("%d",&n); int x1,y1,x2,y2,v;
    while(n--){
        scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2,&v);
        x1--; y1--; x2--; y2--;
        if((x2+y2)&1) swap(x1,x2),swap(y1,y2);
        x1=idx[x1*m+y1]; x2=idx[x2*m+y2];
        w[x1][x2]=max(w[x1][x2],v);
    }
    n=max(nl,nr); printf("%lld\n",KM());
}