#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 6e5+100;
struct PAM{
    int next[N][26],fail[N],len[N];
    int txt[N],cnt[N];
    int tot,root0,root1,last,size;
    void init(){
        last=tot=size=0; txt[size]=-1; ans=0;
        root0=newnode(0); root1=newnode(-1);
        fail[root0]=1; fail[root1]=0;
    }
    int newnode(int l){
        len[tot]=l; cnt[tot]=0;
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
        last=next[now][c]; cnt[last]++;
    }
    void count(){
        for(int i=tot-1;~i;--i) cnt[fail[i]]+=cnt[i];
    }
}pam;