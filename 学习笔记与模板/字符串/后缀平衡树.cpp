#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull INF = (1ULL<<63)-1;
const double alpha = 0.75;
const int N = 8e5+10, M = 3e6+10;
struct SBT{
    int son[N][2],siz[N],fa[N],v[N],val[N],id[N];
    int pre[N]; char s[N],t[M];
    int root,tot,cnt,last; ull rk[N]={0,};
    void init(){ pre[root=tot=last=0]=0; s[0]='\0'; }
    void pushup(int k){
        siz[k]=siz[son[k][0]]+siz[son[k][1]]+1;
        val[k]=val[son[k][0]]+val[son[k][1]]+v[k];
        fa[son[k][0]]=fa[son[k][1]]=k;
    }
    void dfs(int k){
        if(k){ dfs(son[k][0]); id[++cnt]=k; dfs(son[k][1]); } 
    }
    int build(int l,int r,ull tl,ull tr){
        if(l>r) return 0;
        int mid=(l+r)>>1; int k=id[mid]; rk[k]=(tl+tr)>>1;
        son[k][0]=build(l,mid-1,tl,(tl+tr)>>1);
        son[k][1]=build(mid+1,r,(tl+tr)>>1,tr);
        pushup(k); return k;
    }
    int rebuild(int k,ull tl,ull tr){
        cnt=0; dfs(k); return build(1,cnt,tl,tr);
    }
    bool cmp(int a,int b){
        return s[a]==s[b]?rk[pre[a]]>rk[pre[b]]:s[a]>s[b];
    }
    void ins(int &k,int p,ull tl,ull tr){
        if(!k){
            k=++tot; son[k][0]=son[k][1]=0; siz[k]=val[k]=v[k]=1; 
            rk[k]=(tl+tr)>>1; return ;
        }
        if(cmp(k,p)) ins(son[k][0],p,tl,(tl+tr)>>1);
        else ins(son[k][1],p,(tl+tr)>>1,tr);
        pushup(k);
        if(alpha*siz[k]+5<max(siz[son[k][0]],siz[son[k][1]])) k=rebuild(k,tl,tr);
    }
    void del(int x){
        v[x]=0; while(x){ val[x]--; x=fa[x]; }
    }
    bool check(int j,int l){
        for(int i=0;i<l;++i,j=pre[j])
            if(s[j]!=t[i]) return s[j]<t[i];
        return false;
    }
    int que(int k,int l){
        if(!k) return 0; int d=check(k,l);
        return que(son[k][d],l)+(d?val[son[k][0]]+v[k]:0);
    }
    void insert(char *buf){
        int l=strlen(buf); strcpy(t,buf);
        for(int i=0;i<l;++i){
            pre[tot+1]=last; s[tot+1]=t[i];
            ins(root,tot+1,0,INF); last=tot;
        }
        fa[root]=0;
    }
    void erase(int l){ while(l&&last){ del(last); last=pre[last]; l--; } }
    int query(char *buf){
        int l=strlen(buf); strcpy(t,buf); reverse(t,t+l); t[l]='~';
        return que(root,l+1)-que(root,l);
    }
}sbt;
char s[M]; int q,k,mask,ans;
void decode(int mask){
    int l=strlen(s);
    for(int i=0;i<l;++i){
        mask=(mask*131+i)%l;
        swap(s[i],s[mask]);
    }
}
int main(){
    //freopen("D:\\in.txt","r",stdin);
    scanf("%d",&q); sbt.init();
    scanf("%s",s); sbt.insert(s);
    while(q--){
        scanf("%s",s);
        if(s[0]=='Q'){
            scanf("%s",s); decode(mask);
            printf("%d\n",ans=sbt.query(s)); mask^=ans;
        }
        else if(s[0]=='A'){
            scanf("%s",s); decode(mask);
            sbt.insert(s);
        }
        else{
            scanf("%d",&k); sbt.erase(k);
        }
    }
}