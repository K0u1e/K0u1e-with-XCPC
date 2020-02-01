#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
int a[N],c[8],n,m,k,tp;

int main(){
    scanf("%d %d",&n,&k);
    for(int i=0;i<k;++i){
        scanf("%d",&m);
        while(m--){
            scanf("%d",&tp);
            a[tp]|=(1<<i);
        }
    }
    for(int i=1;i<=n;++i)
        c[a[i]]++;
    if(k==1) m=c[1];
    else if(k==2){
        m=c[3]+max(c[1],c[2]);
    }
    else{
        m=c[7];
        for(int i=0;i<k;++i){
            tp=min(c[((1<<k)-1)^(1<<i)],c[1<<i]);
            m+=tp;
            c[((1<<k)-1)^(1<<i)]-=tp;
            m+=c[((1<<k)-1)^(1<<i)];
            c[1<<i]-=tp;
        }
        tp=0;
        for(int i=0;i<k;++i) tp=max(tp,c[1<<i]);
        m+=tp;
    }
    printf("%d\n",m);
}