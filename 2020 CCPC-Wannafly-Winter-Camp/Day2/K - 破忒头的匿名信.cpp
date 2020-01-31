#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5+100;
const ll INF = 1e17;
struct AcTrie{
    int next[N][26],fail[N];
    int len[N],p[N],to[N];
    int root,tot; vector<int> g[N];
    int newnode(){
        for(int i=0;i<26;++i) next[tot][i]=-1;
        fail[tot]=0; len[tot]=p[tot]=to[tot]=-1; tot++;
        return tot-1;
    }
    void init(){
        tot=0; root=newnode();
    }
    int flx(char c){
        return c-'a';
    }
    void insert(char *buf,int c){
        int l=strlen(buf), now=root;
        for(int i=0;i<l;++i){
            if(next[now][flx(buf[i])]==-1)
                next[now][flx(buf[i])]=newnode();
            now=next[now][flx(buf[i])];    
        }
        len[now]=l; p[now]=p[now]==-1?c:min(p[now],c);
    }
    void build(){
        queue<int> Q; fail[root]=root;
        for(int i=0;i<26;++i){
            if(next[root][i]==-1) next[root][i]=root;
            else{
                fail[next[root][i]]=root;
                Q.push(next[root][i]);
            }
        }
        while(!Q.empty()){
            int now = Q.front(); Q.pop();
            for(int i=0;i<26;++i){
                if(next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else{
                    fail[next[now][i]]=next[fail[now]][i];
                    Q.push(next[now][i]);
                }
            }
        }
        for(int i=0;i<tot;++i) g[i].clear();
        for(int i=1;i<tot;++i) g[fail[i]].push_back(i);
    }
    void dfs(int u,int top){
        to[u]=top;
        for(auto v:g[u]) dfs(v,len[u]==-1?top:u);
    }
}ac;
char s[N]; int n,m;
ll dp[N];
int main(){
    scanf("%d",&n); ac.init();
    while(n--){
        scanf("%s %d",s,&m);
        ac.insert(s,m);
    }
    ac.build(); ac.dfs(ac.root,-1);
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;++i) dp[i]=INF; dp[0]=0;
    for(int now=ac.root,i=1;i<=n;++i){
        now=ac.next[now][s[i]-'a'];
        int tmp=ac.len[now]==-1?ac.to[now]:now;
        while(tmp!=-1){
            //printf("%d\n",tmp);
            dp[i]=min(dp[i-ac.len[tmp]]+ac.p[tmp],dp[i]);
            tmp=ac.to[tmp];
        }
    }
    printf("%lld\n",dp[n]==INF?-1:dp[n]);
}
