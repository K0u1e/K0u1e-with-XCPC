#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N][N],d[N],h[N],n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j) scanf("%d",&a[i][j]);
    d[2]=a[3][2]-a[3][1]; h[1]=(a[1][2]-d[2])/2;
    for(int i=3;i<=n;++i) d[i]=a[2][i]-a[2][1];
    for(int i=2;i<=n;++i) h[i]=d[i]+h[1];
    for(int i=1;i<=n;++i) printf("%d ",h[i]);
}