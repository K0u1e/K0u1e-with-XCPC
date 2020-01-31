#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2010;
int g[N][N],cur[N];
int ans[N*N*2],cnt;
ll n,m;
void solve(){
    int x=1; cnt=0;
    while(x<=m){
        ans[cnt++]=x;
        while(cur[x]<=m&&g[x][cur[x]]==0) cur[x]++;
        //if(cur[x]>m) break;
        g[x][cur[x]]--; g[cur[x]][x]--;
        x=cur[x];
    }
}
int main(){
    scanf("%lld",&n);
    ll l=0,r=2e9,mid,tp;
    while(l+1<r){
        mid=(l+r)>>1;
        if(mid%2==1) tp=mid*(mid-1)/2+1;
        else tp=mid*(mid-1)/2+mid/2;
        if(tp<=n) l=mid;
        else r=mid;
    }
    m=l; printf("%lld\n",m);
    if(n>2000000) return 0;
    for(int i=1;i<=m;++i)
        for(int j=1;j<=m;++j) g[i][j]=i==j?0:1;
    if(m%2&&m>1) g[1][m]--,g[m][1]--;
    else{
        for(int i=3;i<=m;i+=2){
            g[i][i-1]++; g[i-1][i]++;
        }
    }
    for(int i=1;i<=m;++i) cur[i]=1;
    solve(); while(cnt<n) ans[cnt++]=1;
    for(int i=0;i<cnt;++i)
        printf("%d%c",ans[i],i==cnt-1?'\n':' ');
}