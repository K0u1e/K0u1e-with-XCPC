#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+100;
char s[N]; int n;
double f[N];

bool check(char c){
    if(c=='a') return true;
    if(c=='e') return true;
    if(c=='i') return true;
    if(c=='o') return true;
    if(c=='u') return true;
    if(c=='y') return true;
    return false;
}

int main(){
    scanf("%s",s); n=strlen(s); f[0]=0;
    for(int i=1;i<=n;++i) f[i]=1.0/i+f[i-1];
    for(int i=1;i<=n;++i) f[i]+=f[i-1];
    double ans=0;
    for(int i=0;i<n;++i){
        if(!check(s[i])) continue;
        ans+=f[n]-f[n-i-1]-f[i];
    }
    ans/=n*(n+1)/2;
    printf("%.9lf\n",ans);
}