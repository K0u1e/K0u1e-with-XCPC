#include <bits/stdc++.h>
using namespace std;
const int e = 116195171;
const int P = 998244353, G=3, Gi=332748118;
const int N = 1<<21;
int fpow(int x,int p){
    int rs=1;
    while(p){
        if(p&1) rs=1LL*rs*x%P;
        x=1LL*x*x%P; p>>=1;
    }
    return rs;
}
int l=18,r[N];
void NTT(int *A,int limit,int opt){
    for(int i=0;i<limit;i++)
        if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1;i<limit;i<<=1){
        int wn=fpow((opt==1)?G:Gi,(P-1)/(i<<1));
        for(int p=i<<1,j=0;j<limit;j+=p){
            int w=1;
            for(int k=0;k<i;k++,w=1LL*w*wn%P){
                int x=A[j+k],y=1LL*w*A[j+i+k]%P;
                A[j+k]=(x+y)%P; A[j+i+k]=(x-y+P)%P;
            }
        }
    }
}
int a[N],b[N],n,m;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&m);
        a[m]=(a[m]+fpow(e,P-1-(1LL*m*m%(P-1))))%P;
    }
    n=1<<18;
    for(int i=0;i<n;++i)
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    NTT(a,n,1);
    for(int i=0;i<n;++i) a[i]=1LL*a[i]*a[i]%P;
    NTT(a,n,-1); int o=fpow(n,P-2);
    for(int i=0;i<n;++i) a[i]=1LL*a[i]*o%P;
    int ans=0;
    for(int i=0;i<n;++i)
        ans=(ans+1LL*a[i]*fpow(e,1LL*i*i%(P-1)))%P;
    printf("%d\n",ans);
}