#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305;
int a[N],b[5],n,ans;
int f[N][N]; bool q[5];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=n-1;i>=0;--i){
        for(int j=1;j<=n;++j){
            f[i][j]=f[i+1][j];
        }
        f[i][a[i+1]]++;
    }
    for(int i=1;i<=4;++i) scanf("%d",&b[i]);
    for(int i=1;i<=4;++i){
        for(int j=1;j<i;++j)
            if(b[i]==b[j]) q[i]=true;
    }
    int op=1; while(b[4]!=b[op]) op++;
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            if((a[i]==a[j])!=(b[1]==b[2])) continue;
            for(int k=j+1;k<=n;++k){
                if((a[i]==a[k])!=(b[1]==b[3])) continue;
                if((a[j]==a[k])!=(b[2]==b[3])) continue;
                if(op==1) ans+=f[k][a[i]];
                else if(op==2) ans+=f[k][a[j]];
                else if(op==3) ans+=f[k][a[k]];
                else{
                    ans+=n-k;
                    if(!q[1]) ans-=f[k][a[i]];
                    if(!q[2]) ans-=f[k][a[j]];
                    if(!q[3]) ans-=f[k][a[k]];
                }
            }
        }
    }
    printf("%d\n",ans);
}