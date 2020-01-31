#include <bits/stdc++.h>
using namespace std;
const int N = 550;
int a[N][N],n,m,b[N],ans;

int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m); ans=0;
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j) scanf("%1d",&a[i][j]);
        }
        for(int i=0;i<m;++i) b[i]=0;
        for(int i=n-1;i>=0;--i){
            for(int j=m-1,k=0;j>=0;--j){
                if(a[i][j]^k^b[j]){
                    ans++; k^=1;
                }
                b[j]^=k;
            }
        }
        if(ans&1) printf("call\n");
        else printf("aoligei\n");
    }
}