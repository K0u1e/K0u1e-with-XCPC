#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+1;
int n,MOD,phi[N];
map<int,int> mps;
void phi_table(int n){
    phi[1]=1;
    for(int i=2;i<=n;++i) if(!phi[i]){
        for(int j=i;j<=n;j+=i){
            if(!phi[j]) phi[j]=j;
            phi[j]=phi[j]/i*(i-1);
        }
    }
    for(int i=1;i<=n;++i)
        phi[i]=(phi[i]+phi[i-1])%MOD;
}
int phi_sum(int n){
    if(n<N) return phi[n];
    if(mps.count(n)) return mps[n];
    int rs=1LL*n*(n+1)/2%MOD;
    for(int i=2,j;i<=n;i=j+1){
        j=n/(n/i);
        rs-=1LL*(j-i+1)*phi_sum(n/i)%MOD;
        if(rs<0) rs+=MOD;
    }
    mps[n]=rs; return rs;
}
int sum(int k){
    int a=k,b=k+1,c=2*k+1;
    if(a%3==0) a/=3;
    else if(b%3==0) b/=3;
    else c/=3;
    if(a%2==0) a/=2;
    else if(b%2==0) b/=2;
    else c/=2;
    k=1LL*a*b%MOD*c%MOD;
    return k;
}
int main(){
    scanf("%d %d",&n,&MOD);
    phi_table(N-1); int ans=0;
    for(int i=1,j;i<=n;i=j+1){
        j=n/(n/i);
        ans+=1LL*(sum(j)-sum(i-1)+MOD)%MOD*phi_sum(n/i)%MOD;
        if(ans>=MOD) ans-=MOD;
    }
    printf("%d\n",ans);
}