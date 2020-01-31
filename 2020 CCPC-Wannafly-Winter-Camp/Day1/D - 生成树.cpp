#include <bits/stdc++.h>
using namespace std;
const int N = 410;
const int MOD = 998244353;
int fpow(int x,int p){
    int rs=1;
    while(p){
        if(p&1) rs=1LL*rs*x%MOD;
        x=1LL*x*x%MOD; p>>=1;
    }
    return rs;
}
int a[N][N<<1],b[N][N],n,m;
char G1[N][N],G2[N][N];

int Gauss(){  //消B获取逆矩阵
    int rs=1,inv,i,j,k;
    for(i=0;i<n;++i){
        for(j=0;j<n;++j){
            a[i][j]=(a[i][j]+MOD)%MOD;
            a[i][j+n]=i==j?1:0;
        }
    }
    for(i=0;i<n;++i){
        for(j=i;j<n;++j) if(a[j][i]) break;
        if(j!=i){
            rs=MOD-rs;
            for(k=i;k<m;++k) swap(a[i][k],a[j][k]);
        }
        inv=fpow(a[i][i],MOD-2); rs=1LL*rs*a[i][i]%MOD;
        for(k=i;k<m;++k) a[i][k]=1LL*a[i][k]*inv%MOD;
        for(j=0;j<n;++j){
            if(i==j||!a[j][i]) continue;
            for(k=i+1;k<m;++k)
                a[j][k]=(a[j][k]-1LL*a[j][i]*a[i][k]%MOD+MOD)%MOD;
            a[j][i]=0;
        }
    }
    return rs;
}

int main(){
    scanf("%d",&n); int ans=0,tp;
    for(int i=0;i<n;++i) scanf("%s",G1[i]);
    for(int i=0;i<n;++i) scanf("%s",G2[i]);
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            if(G1[i][j]=='1'){
                a[i][j]--; a[j][i]--;
                a[i][i]++; a[j][j]++;
                if(G2[i][j]=='1'){
                    b[i][j]--; b[j][i]--;
                    b[i][i]++; b[j][j]++;
                }
            }
        }
    }
    n--; m=n<<1; tp=Gauss();
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            ans=(ans+1LL*a[i][j+n]*b[i][j]%MOD+MOD)%MOD;
    ans=1LL*ans*tp%MOD;
    printf("%d\n",ans);
}