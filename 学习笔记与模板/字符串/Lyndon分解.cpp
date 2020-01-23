#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pr;
const int N = 1e6+100;
vector<pr> ldn;
void Duval(char *s){
    int n=strlen(s),i=0,j,k;
    while(i<n){
        j=i+1,k=i;
        while(j<n&&s[k]<=s[j]){
            if(s[k]<s[j]) k=i;
            else k++;
            j++;
        }
        while(i<=k){
            ldn.push_back(make_pair(i,i+j-k-1));
            i+=j-k;
        }
    }
}
char s[N];
int main(){
    scanf("%s",s); Duval(s);
    for(auto p:ldn) printf("%d ",p.second+1);
}