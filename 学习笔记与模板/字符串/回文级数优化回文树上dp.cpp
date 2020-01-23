//codeforces 932G
//给一段字符串，问切割成若干个长度为偶数的回文串的方案数。
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 1e6+100;
const int MOD = 1e9+7;
struct PAM{
    int next[N][26],fail[N],len[N];
    int txt[N],diff[N],link[N];
    int tot,root0,root1,last,size;
    void init(){
        last=tot=size=0; txt[size]=-1;
        root0=newnode(0); root1=newnode(-1);
        fail[root0]=1; fail[root1]=0;
    }
    int newnode(int l){
        len[tot]=l; diff[tot]=0;
        memset(next[tot],0,sizeof(next[tot]));
        tot++; return tot-1;
    }
    int getfail(int x){
        while(txt[size-len[x]-1]!=txt[size]) x=fail[x];
        return x;
    }
    void extend(int c){
        txt[++size]=c; int now=getfail(last);
        if(!next[now][c]){
            int tmp=newnode(len[now]+2);
            fail[tmp]=next[getfail(fail[now])][c];
            next[now][c]=tmp;
        }
        last=next[now][c];
        diff[last]=len[last]-len[fail[last]];
        if(diff[last]==diff[fail[last]]) link[last]=link[fail[last]];
        else link[last]=fail[last];
    }
}pam;
char s[N],t[N];
int f[N],g[N],n;

int main(){
    scanf("%s",t+1); n=strlen(t+1);
    if(n&1){
        printf("0\n");
        return 0;
    }
    pam.init(); f[0]=1;
    for(int i=1;i<=n;++i)
        s[i]=i&1?t[(i+1)>>1]:t[n+1-(i>>1)];
    for(int i=1;i<=n;++i){
        pam.extend(s[i]-'a');
        for(int j=pam.last;j;j=pam.link[j]){
            g[j]=f[i-pam.diff[j]-pam.len[pam.link[j]]];
            if(pam.link[j]!=pam.fail[j])
                g[j]=(g[j]+g[pam.fail[j]])%MOD;
            if((i&1)==0) f[i]=(f[i]+g[j])%MOD;
        }
    }
    printf("%d\n",f[n]);
}