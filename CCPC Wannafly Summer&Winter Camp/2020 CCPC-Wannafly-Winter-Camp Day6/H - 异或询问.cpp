#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5+10;
const int D = 30;
const int MOD = 998244353;
struct Trie{
    int root,tot,sum;
    int nex[N*D][2],w[N*D],v[N*D];
    int newnode(){
        nex[tot][0]=nex[tot][1]=-1;
        w[tot]=v[tot]=0; tot++;
        return tot-1;
    }
    void init(){
        tot=sum=0;
        root=newnode();
    }
    void insert(int x){
        int now=root;
        for(int i=D-1;i>=0;--i){
            if(nex[now][(x>>i)&1]==-1)
                nex[now][(x>>i)&1]=newnode(); 
            now=nex[now][(x>>i)&1];
        }
        w[now]++;
    }
    void dfs(int u,int d){
        if(nex[u][0]==-1&&nex[u][1]==-1){
            sum+=w[u]; w[u]=1LL*sum*sum%MOD;
            return ;
        }
        for(int i=0;i<2;++i){
            if(~nex[u][i]){
                dfs(nex[u][i],d-1);
                w[u]+=w[nex[u][i]];
            }
            else{
                v[u]=1LL*sum*sum%MOD;
                w[u]+=(1LL<<d)*v[u]%MOD;
            }
        }
        if(w[u]>=MOD) w[u]-=MOD;
    }
    int query(int r,int x){
        r++;
        if(r==(1<<D)) return w[root];
        int rs=0;
        for(int i=D-1,now=root;i>=0&&r>0;--i){
            int p=(x>>i)&1;
            if((1<<i)<=r){
                if(~nex[now][p]) rs+=w[nex[now][p]];
                else rs+=1LL*v[now]*(1<<i)%MOD;
                if(rs>=MOD) rs-=MOD;
                r-=1<<i;
                if(~nex[now][p^1]) now=nex[now][p^1];
                else{
                    rs+=1LL*v[now]*r%MOD; r=0;
                    if(rs>=MOD) rs-=MOD;
                }
            }else{
                if(~nex[now][p]) now=nex[now][p];
                else{
                    rs+=1LL*v[now]*r%MOD; r=0;
                    if(rs>=MOD) rs-=MOD;
                }
            }
        }
        return rs;
    }
    int ask(int l,int r,int x){
        return (query(r,x)-query(l-1,x)+MOD)%MOD;
    }
}t;
int n,q,l,r,x;
int main(){
    scanf("%d %d",&n,&q); t.init();
    while(n--){
        scanf("%d",&x); t.insert(x);
    }
    t.dfs(t.root,D-1);
    while(q--){
        scanf("%d %d %d",&l,&r,&x);
        printf("%d\n",t.ask(l,r,x));
    }
}