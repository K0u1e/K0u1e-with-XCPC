#include <bits/stdc++.h>
using namespace std;
const int N = 5050;
typedef long long ll;
int w[N],b[N],n;
ll A,B,C,D,P,ans,tp;
bool check(int i,int j){
    return (A*(i+j)*(i+j)+B*(i-j)*(i-j)+C)%P>D;
}
int main(){
    scanf("%d",&n);
    scanf("%lld %lld %lld %lld %lld",&A,&B,&C,&P,&D);
    ans=n; ans=ans*(ans-1)*(ans-2)/3/2;
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            if(check(i,j)) b[i]++,b[j]++;
            else w[i]++,w[j]++;
        }
    }
    for(int i=1;i<=n;++i) tp+=w[i]*b[i];
    ans-=tp/2;
    printf("%lld\n",ans);
}