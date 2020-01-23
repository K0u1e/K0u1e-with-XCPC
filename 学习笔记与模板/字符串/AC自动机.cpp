#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cctype>
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
const int maxn = 1e6+100;
const ll mod = 1e9+7;

int depth[maxn];
vector<int> pos[maxn];

struct AcTrie{
    int next[maxn][26],fail[maxn];
    ll end[maxn];
    int root,tot;
    int newnode(){
        for(int i=0;i<26;++i) next[tot][i]=-1;
        end[tot++]=0; return tot-1;
    }
    void init(){
        tot=0; root=newnode();
    }
    int flx(char c){
        return c-'a';
    }
    void insert(char *buf,int id){
        int len=strlen(buf), now=root;
        for(int i=0;i<len;++i){
            if(next[now][flx(buf[i])]==-1){
                next[now][flx(buf[i])]=newnode();
                end[next[now][flx(buf[i])]]=(end[now]*26+flx(buf[i]))%mod;
            }
            now=next[now][flx(buf[i])];
            pos[id].push_back(now);
        }
    }
    
    void build(){
        queue<int> Q; fail[root]=root;
        for(int i=0;i<26;++i){
            if(next[root][i]==-1) next[root][i]=root;
            else{
                fail[next[root][i]]=root;
                Q.push(next[root][i]); depth[next[root][i]]=1;
            }
        }
        while(!Q.empty()){
            int now = Q.front(); Q.pop();
            for(int i=0;i<26;++i){
                if(next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else{
                    fail[next[now][i]]=next[fail[now]][i];
                    depth[next[now][i]]=depth[fail[next[now][i]]]+1;
                    //end[next[now][i]]+=end[fail[next[now][i]]];
                    Q.push(next[now][i]);
                }
            }
        }
    }
    /*void query(char *buf){
        int len=strlen(buf), now=root, res=0;
        for(int i=0;i<len;++i){
            now = next[now][flx(buf[i])];
            int tmp = now;
            while(tmp!=root){
                if(end[tmp]!=0) ++cnt[end[tmp]];
                tmp = fail[tmp];
            }
        }
    }*/
    /*void debug(){
        for(int i=0;i<tot;++i){
            printf("%d %d\n[",end[i],fail[i]);
            for(int j=0;j<10;++j) printf("%d ",next[i][j]);
            printf("]\n");
        }
    }*/
};

AcTrie ac;
char s[maxn];
int fa[maxn][21];

void pre(){
    for(int i=1;i<ac.tot;++i) fa[i][0]=ac.fail[i];
    for(int k=1;k<21;++k){
        for(int i=0;i<ac.tot;++i)
            fa[i][k]=fa[fa[i][k-1]][k-1];
    }
}

int lca(int u,int v){
    int du=depth[u], dv=depth[v];
    if(du<dv) swap(du,dv),swap(u,v);
    int tu=u,tv=v;
    for(int i=du-dv,j=0;i;i>>=1,j++)
        if(i&1) tu=fa[tu][j];
    if(tu==tv) return tu;
    for(int k=20;k>=0;--k){
        if(fa[tu][k]!=fa[tv][k])
            tu=fa[tu][k],tv=fa[tv][k];
    }
    return fa[tu][0];
}

int n,m,a,b,c,d;

int main(){
    scanf("%d",&n); ac.init();
    for(int i=1;i<=n;++i){
        scanf("%s",s); ac.insert(s,i);
    }
    ac.build(); pre();
    scanf("%d",&m);
    while(m--){
        scanf("%d %d %d %d",&a,&b,&c,&d);
        printf("%lld\n",ac.end[lca(pos[a][b-1],pos[c][d-1])]);
    }
}