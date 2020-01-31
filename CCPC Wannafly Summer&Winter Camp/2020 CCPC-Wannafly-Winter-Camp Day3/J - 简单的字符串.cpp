#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
const int D = 18;
int t1[N],t2[N],c[N],lg2[N];
struct suffix_array{
    int str[N],sa[N],rank[N],height[N];
    int rmq[D][N];
    bool cmp(int *r,int a,int b,int l){
        return r[a]==r[b]&&r[a+l]==r[b+l];
    }
    void da(int n,int m){
        n++; int i, j, p, *x = t1, *y = t2;
        for(i=0;i<m;++i) c[i]=0;
        for(i=0;i<n;++i) c[x[i]=str[i]]++;
        for(i=1;i<m;++i) c[i]+=c[i-1];
        for(i=n-1;i>=0;--i) sa[--c[x[i]]]=i;

        for(j=1;j<n;j<<=1){
            p=0;
            for(i=n-j;i<n;++i) y[p++]=i;
            for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;

            for(i=0;i<m;++i) c[i]=0;
            for(i=0;i<n;++i) c[x[y[i]]]++;
            for(i=1;i<m;++i) c[i]+=c[i-1];
            for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];

            swap(x,y); p=1; x[sa[0]]=0;
            for(i=1;i<n;++i) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
            if(p>=n) break; m=p;
        }
        int k=0; n--;
        for(i=0;i<=n;++i) rank[sa[i]]=i;
        for(i=0;i<n;++i){
            if(k) k--;
            j=sa[rank[i]-1];
            while(str[i+k]==str[j+k]) ++k;
            height[rank[i]]=k;
        }
    }
    void initlcp(int n){
        for(int i=1;i<=n;++i)
            rmq[0][i]=height[i];
        for(int k=1;k<=lg2[n];++k)
            for(int i=1;i+(1<<k)-1<=n;++i)
                rmq[k][i]=min(rmq[k-1][i],rmq[k-1][i+(1<<(k-1))]);
    }
    int lcp(int a,int b){
        a=rank[a]; b=rank[b];
        if(a>b) swap(a,b); a+=1;
        int d=lg2[b-a+1];
        return min(rmq[d][a],rmq[d][b-(1<<d)+1]);
    }
}sa;
char s[N]; int nex[N],n,q,l,k;
stack<int> st;
int main(){
    scanf("%s %d",s,&q); n=strlen(s); lg2[0]=-1;
    for(int i=1;i<=n;++i) lg2[i]=(i&(i-1))?lg2[i-1]:lg2[i-1]+1;
    for(int i=0;i<n;++i) sa.str[i]=s[i]-'a'+1; sa.str[n]=0;
    sa.da(n,27); sa.initlcp(n); st.push(n);
    for(int i=n-1;i>=0;--i){
        while(sa.rank[st.top()]>sa.rank[i]) st.pop();
        nex[i]=st.top(); st.push(i);
    }
    while(q--){
        scanf("%d %d",&l,&k); l--;
        if(k==1||nex[l]==n) printf("%d %d\n",l+1,n);
        else{
            int r=nex[l]; int lcp=sa.lcp(l,r),d=r-l;
            if(lcp==0) printf("%d %d\n",l+1,r);
            else{
                r+=lcp/d*d;
                if(r==n){
                    d=(((r-l)/d-1)/k+1)*d;
                    printf("%d %d\n",l+1,l+d);
                }
                else{
                    int d1=(((r-l)/d-1)/k+1)*d;
                    int d2=((r-l)/d/k)*d;
                    if(d1==d2) printf("%d %d\n",r-d1+1,n);
                    else printf("%d %d\n",l+1,l+d1);
                }
            }
        }
    }
}