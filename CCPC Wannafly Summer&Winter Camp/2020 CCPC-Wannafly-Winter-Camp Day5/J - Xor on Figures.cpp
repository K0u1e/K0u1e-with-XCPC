#include <bits/stdc++.h>
using namespace std;
const int N = 32;
const int MOD = 1e9+7;
int n,m,a[1024],mps[N][N];
bitset<1024> b[1024];
int Gauss(){
    int i,j,k; //cout<<n<<endl;
    for(i=0,k=0;i<n&&k<n;++i,++k){
        for(j=i;j<n;++j) if(b[j][k]) break;
        if(j<n) swap(b[i],b[j]);
        else{
            i--; continue;
        }
        //printf("%d %d %d\n",i,j,k);
        for(j=0;j<n;++j)
            if(i!=j&&b[j][k]) b[j]^=b[i];
    }
    //printf("qq\n");
    int rs=0;
    for(i=0;i<n;++i) if(b[i].count()>0) rs++;
    //printf("rs%d\n",rs);
    return rs;
}
int fpow(int x,int p){
    int rs=1;
    while(p){
        if(p&1) rs=1LL*rs*x%MOD;
        x=1LL*x*x%MOD; p>>=1;
    }
    return rs;
}
inline void init(int id,int x,int y){
    if(x>=n) x-=n; if(y>=n) y-=n;
    b[id][x*n+y]=1;
}
int main(){
    scanf("%d",&n); n=1<<n;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            scanf("%1d",&mps[i][j]);
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            for(int x=0;x<n;++x){
                for(int y=0;y<n;++y){
                    if(!mps[x][y]) continue;
                    init(i*n+j,x+i,y+j);
                }
            }
        }
    }
    n*=n;
    printf("%d\n",fpow(2,Gauss()));
}
