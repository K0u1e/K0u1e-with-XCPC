#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e3+100;
char s[N][105];
int len[N],n,m,a[N],b[N];
char get(char a,char b){
    int x=a>'Z'?a-'a':a-'A'+26;
    int y=b>'Z'?b-'a':b-'A'+26;
    x=(y-x+52)%52;
    if(x>=26) return 'A'+x-26;
    else return 'a'+x;
}
void change(int i,int j){
    for(int o=0;o<len[j];++o)
        s[j][o]=get(s[i][o%len[i]],s[j][o]);
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;++i)
        scanf("%d %d",&a[i],&b[i]);
    for(int i=1;i<=n;++i){
        scanf("%s",s[i]);
        len[i]=strlen(s[i]);
    }
    
    while(m--) change(a[m],b[m]);
    for(int i=1;i<=n;++i)
        printf("%s\n",s[i]);
}