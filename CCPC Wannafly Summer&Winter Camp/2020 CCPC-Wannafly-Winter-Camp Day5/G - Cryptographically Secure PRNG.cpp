#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+100;
int f[N],p,n;
vector<pair<int,int> >ans;
int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%d",&p); ans.clear();
        int mn=p; f[1]=1;
        for(int i=2;i<p;++i){
            f[i]=1LL*(p-p/i)*f[p%i]%p;
            mn=min(mn,f[i]);
            if(mn==f[i]){
                if(i>f[i]) break;
                if(i!=f[i]) ans.push_back(make_pair(i,f[i]));
                ans.push_back(make_pair(f[i],i));
            }
        }
        sort(ans.begin(),ans.end());
        printf("%d\n",ans.size());
        for(auto q:ans)
            printf("%d %d\n",q.first,q.second);
    }
}