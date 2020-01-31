#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
    scanf("%d",&n); printf("%d\n",n);
    printf("%d %d\n",-1,-n);
    for(int i=1;i<n;++i)
        printf("%d %d\n",-i,i+1);
}