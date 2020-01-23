#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+10;
ll a[N],p,q;
int b[65],n;
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%lld",&a[i]); p^=a[i];
        q=a[i]; int c=-1;
        while(q){
            c++;
            if(q%2==1) b[c]++;
            q>>=1;
        }
        q=p; c=-1;
        while(q){
            c++; q>>=1;
        }
        if(c==-1) printf("0\n");
        else printf("%d\n",b[c]);
    }
}