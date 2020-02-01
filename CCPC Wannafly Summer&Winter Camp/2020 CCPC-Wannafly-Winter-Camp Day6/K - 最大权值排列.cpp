#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i+=2)
        printf("%d ",i);
    for(int i=n/2*2;i>=1;i-=2)
        printf("%d ",i);
    printf("\n");
}