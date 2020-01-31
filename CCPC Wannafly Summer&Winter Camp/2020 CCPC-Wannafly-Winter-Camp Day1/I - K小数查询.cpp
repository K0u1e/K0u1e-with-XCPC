#include <bits/stdc++.h>
using namespace std;
const int N = 8e4+10;
const int M = N*400;
int rt[N<<2],tag[N<<2],a[N],n,q;
int c[M],lson[M],rson[M],tot;

void upd(int p,int v,int &k,int l,int r){
    if(k==-1){
        k=tot++;
        lson[k]=rson[k]=-1; c[k]=0;
    }
    c[k]+=v; if(l==r) return; 
    int mid=(l+r)>>1;
    if(p<=mid) upd(p,v,lson[k],l,mid);
    else upd(p,v,rson[k],mid+1,r);
}

int dfs1(int t,int x,int k,int l,int r){
    if(l==r){
        if(c[k]){
            for(int i=t>>1;i;i>>=1)
                upd(l,-c[k],rt[i],1,n);
        }
        int rs=c[k]; c[k]=0; return rs;
    }
    int mid=(l+r)>>1,rs=0;
    if(~lson[k]&&c[lson[k]]&&x<mid) rs+=dfs1(t,x,lson[k],l,mid);
    if(~rson[k]&&c[rson[k]]) rs+=dfs1(t,x,rson[k],mid+1,r);
    c[k]-=rs; return rs;
}

int dfs2(int x,int k,int l,int r){
    if(l==r){
        int rs=c[k]; c[k]=0;
        return rs;
    }
    int mid=(l+r)>>1,rs=0;
    if(~lson[k]&&c[lson[k]]&&x<mid) rs+=dfs2(x,lson[k],l,mid);
    if(~rson[k]&&c[rson[k]]) rs+=dfs2(x,rson[k],mid+1,r);
    c[k]-=rs; return rs;
}

void update(int a,int b,int x,int k,int l,int r){
    if(a>r||b<l) return ;
    if(a<=l&&r<=b){
        if(~tag[k]&&tag[k]<=x) return ;
        int c=dfs1(k,x,rt[k],1,n);
        if(c){
            for(int i=k;i;i>>=1)
                upd(x,c,rt[i],1,n);
        }
        tag[k]=x; return;
    }
    int mid=(l+r)>>1,lk=(k<<1),rk=(k<<1)|1;
    if(~tag[k]){
        if(tag[lk]==-1||tag[lk]>tag[k]){
            int c=dfs2(tag[k],rt[lk],1,n);
            if(c) upd(tag[k],c,rt[lk],1,n);
            tag[lk]=tag[k];
        }
        if(tag[rk]==-1||tag[rk]>tag[k]){
            int c=dfs2(tag[k],rt[rk],1,n);
            if(c) upd(tag[k],c,rt[rk],1,n);
            tag[rk]=tag[k];
        }
        tag[k]=-1;
    }
    update(a,b,x,lk,l,mid); update(a,b,x,rk,mid+1,r);
}

int tt[30],cnt;
void que(int a,int b,int k,int l,int r){
    if(a>r||b<l) return;
    if(a<=l&&r<=b){
        tt[cnt++]=rt[k];
        return;
    }
    int mid=(l+r)>>1,lk=(k<<1),rk=(k<<1)|1;
    if(~tag[k]){
        if(tag[lk]==-1||tag[lk]>tag[k]){
            upd(tag[k],dfs2(tag[k],rt[lk],1,n),rt[lk],1,n);
            tag[lk]=tag[k];
        }
        if(tag[rk]==-1||tag[rk]>tag[k]){
            upd(tag[k],dfs2(tag[k],rt[rk],1,n),rt[rk],1,n);
            tag[rk]=tag[k];
        }
        tag[k]=-1;
    }
    que(a,b,lk,l,mid); que(a,b,rk,mid+1,r);
}
int query(int a,int b,int k){
    cnt=0; que(a,b,1,1,n);
    int l=1,r=n,mid,s;
    while(l!=r){
        s=0,mid=(l+r)>>1;
        for(int i=0;i<cnt;++i)
            if(~tt[i]&&~lson[tt[i]]) s+=c[lson[tt[i]]];
        if(k>s){
            k-=s;
            for(int i=0;i<cnt;++i)
                if(~tt[i]) tt[i]=rson[tt[i]];
            l=mid+1;
        }
        else{
            for(int i=0;i<cnt;++i)
                if(~tt[i]) tt[i]=lson[tt[i]];
            r=mid;
        }
    }
    return l;
}

void build(int k,int l,int r){
    rt[k]=tag[k]=-1;
    for(int i=l;i<=r;++i) upd(a[i],1,rt[k],1,n);
    if(l==r) return;
    int mid=(l+r)>>1,lk=(k<<1),rk=(k<<1)|1;
    build(lk,l,mid); build(rk,mid+1,r);
}

int op,l,r,x;
int main(){
    scanf("%d %d",&n,&q); tot=0;
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    build(1,1,n);
    while(q--){
        scanf("%d %d %d %d",&op,&l,&r,&x);
        if(op==1){
            if(x>=n) continue;
            update(l,r,x,1,1,n);
        }
        else printf("%d\n",query(l,r,x));
    }
}