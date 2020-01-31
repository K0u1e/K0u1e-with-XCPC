#include <bits/stdc++.h>
using namespace std;
const int N = 17;
int dp[1<<N],mps[N][N],n,m;
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0,u,v;i<m;++i){
        scanf("%d %d",&u,&v);
        u--; v--;
        mps[u][v]=mps[v][u]=1;
    }
    for(int i=0;i<(1<<n);++i){
        bool flag=true;
        for(int j=0;j<n;++j){
            for(int k=0;k<n;++k){
                if(j==k) continue;
                if(mps[j][k]&((i>>j)&1)&((i>>k)&1))
                    flag=false;
                if(!flag) break;
            }
            if(!flag) break;
        }
        dp[i]=flag?1:N;
    }
    for(int s=0;s<(1<<n);++s){
        for(int s1=s,s2;s1;s1=(s1-1)&s){
            s2=s^s1;
            dp[s]=min(dp[s],dp[s1]+dp[s2]);
        }
    }
    printf("%d\n",dp[(1<<n)-1]-1);
}

