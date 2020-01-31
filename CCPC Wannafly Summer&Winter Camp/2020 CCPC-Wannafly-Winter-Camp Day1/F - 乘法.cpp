#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e5+10;
const ll INF = 1e12+10;
vector<ll> a,b,c,d,e,f;
int n,m; ll q,k;

bool check(ll x){
    ll rs=0;
    if(x>0){
        for(int i=0,j=d.size()-1;i<a.size();++i){
            while(j>=0&&d[j]*a[i]<x) j--;
            rs+=j+1;
        }
        //printf("%lld %lld\n",x,rs);
        for(int i=c.size()-1,j=0;i>=0;--i){
            while(j<f.size()&&f[j]*c[i]<x) j++;
            rs+=f.size()-j;
        }
        //printf("%lld %lld\n",x,rs);
    }
    else if(x==0){
        rs+=1LL*a.size()*d.size();
        rs+=1LL*c.size()*f.size();
        rs+=1LL*e.size()*(a.size()+c.size());
        rs+=1LL*b.size()*(d.size()+f.size());
        rs+=1LL*e.size()*b.size();
    }
    else{
        rs+=1LL*a.size()*d.size();
        rs+=1LL*c.size()*f.size();
        rs+=1LL*e.size()*(a.size()+c.size());
        rs+=1LL*b.size()*(d.size()+f.size());
        rs+=1LL*e.size()*b.size();
        for(int i=0,j=0;i<a.size();++i){
            while(j<f.size()&&a[i]*f[j]>=x) j++;
            rs+=j;
        }
        for(int i=0,j=0;i<d.size();++i){
            while(j<c.size()&&d[i]*c[j]>=x) j++;
            rs+=j;
        }
    }
    return rs>=k;
}

int main(){
    scanf("%d %d %lld",&n,&m,&k);
    for(int i=0;i<n;++i){
        scanf("%lld",&q);
        if(q<0) a.push_back(q);
        else if(q==0) b.push_back(q);
        else c.push_back(q);
    }
    for(int i=0;i<m;++i){
        scanf("%lld",&q);
        if(q<0) d.push_back(q);
        else if(q==0) e.push_back(q);
        else f.push_back(q);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    sort(d.begin(),d.end());
    sort(e.begin(),e.end());
    sort(f.begin(),f.end());
    ll l=-INF,r=INF;
    while(l+1<r){
        ll mid=(l+r)>>1;
        if(check(mid)) l=mid;
        else r=mid;
    }
    printf("%lld\n",l);
}