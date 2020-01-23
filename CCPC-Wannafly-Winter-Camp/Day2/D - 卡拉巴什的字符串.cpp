#include <bits/stdc++.h>
using namespace std;
const int N = 2e6+100;
struct SAM{
    int next[N][26],fa[N],len[N];
    int root,tot,last,up,down; int son[N];
    int newnode(int l){
        fa[tot]=-1; son[tot]=0;
        for(int i=0;i<26;++i)  next[tot][i]=-1;
        len[tot++]=l; return tot-1;
    }
    void init(){
        tot=up=0; down=N;
        last=root=newnode(0);
    }
    void extend(int x){
        int p=last; int cur=newnode(len[p]+1);
        while(p!=-1&&next[p][x]==-1){
            next[p][x]=cur; p=fa[p];
        }
        if(p==-1) fa[cur]=root,son[root]++;
        else{
            int q=next[p][x];
            if(len[q]==len[p]+1){
                fa[cur]=q;
                if(!son[q]) up=max(up,len[q]);
                if(!son[q]) down=min(down,len[q]); son[q]++;
            }
            else{
                int tmp = newnode(len[p]+1);
                memcpy(next[tmp],next[q],sizeof(next[q]));
                up=max(len[tmp],up); down=min(len[tmp],down);
                fa[tmp]=fa[q]; fa[q]=fa[cur]=tmp; son[tmp]+=2;
                while(p!=-1&&next[p][x]==q){
                    next[p][x]=tmp; p=fa[p];
                }
            }
        }
        last=cur;
    }
}sam;
int t,n; char s[N];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%s",s); n=strlen(s); sam.init();
        for(int i=0;i<n;++i){
            sam.extend(s[i]-'a');
            if(i==0) printf("0");
            else if(sam.son[0]>=2) printf("%d",sam.up+1);
            else printf("%d",0);
            printf("%c",i==n-1?'\n':' ');
        }
    }
}