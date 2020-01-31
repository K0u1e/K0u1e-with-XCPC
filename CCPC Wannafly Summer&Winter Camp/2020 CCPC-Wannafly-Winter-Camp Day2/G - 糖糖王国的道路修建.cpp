#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3010;
struct Point{
    ll x,y;
    Point(ll _x=0.0,ll _y=0.0){
        x=_x; y=_y;
    };
};
Point operator + (Point a, Point b) { return Point(a.x+b.x,a.y+b.y); }
Point operator - (Point a, Point b) { return Point(a.x-b.x,a.y-b.y); }
bool operator < (const Point &a, const Point &b) { return a.x<b.x||(a.x==b.x&&a.y<b.y); }
bool operator == (const Point &a, const Point &b) { return (a.x-b.x)==0&&(a.y-b.y)==0; }
ll Cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }

Point pt[N]; int nl,nr,n,m;

struct Triangle{
    int a,b,c;
    Triangle(int _a=0,int _b=0,int _c=0){
        a=_a; b=_b; c=_c;
        if(Cross(pt[b]-pt[a],pt[c]-pt[a])<0) swap(b,c);
    }
    bool InTriangle(int p){
        if(Cross(pt[p]-pt[a],pt[b]-pt[a])>=0) return false;
        if(Cross(pt[p]-pt[b],pt[c]-pt[b])>=0) return false;
        if(Cross(pt[p]-pt[c],pt[a]-pt[c])>=0) return false;
        return true;
    }
};
bool cmp(int x,int y) { return pt[x]<pt[y]; }
int getConvex(int *p,int n,int *cvx){
    int m=0; sort(p,p+n,cmp);
    for(int i=0;i<n;++i){
        while(m>1&&Cross(pt[cvx[m-1]]-pt[cvx[m-2]],pt[p[i]]-pt[cvx[m-2]])<=0) m--;
        cvx[m++]=p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;--i){
        while(m>k&&Cross(pt[cvx[m-1]]-pt[cvx[m-2]],pt[p[i]]-pt[cvx[m-2]])<=0) m--;
        cvx[m++]=p[i];
    }
    return m-1;
}

vector<pair<int,int> > ans;
int px[N],cvx[N],col[N];
vector<int> pl,pr;

int check(){
    for(int i=1;i<=n;++i) px[i]=i;
    m=getConvex(px+1,n,cvx);
    //for(int i=0;i<m;++i) printf("%d ",cvx[i]); printf("cvx\n");
    int f=0;
    for(int i=0;i<m;++i) f|=col[cvx[i]];
    if(f==3){
        int now=0,aim=3-col[cvx[0]];
        while(now<m&&col[cvx[now]]!=aim) now++;
        while(now<m&&col[cvx[now]]==aim){
            if(aim==1) pl.push_back(cvx[now]);
            else pr.push_back(cvx[now]);
            now++;
        }
        aim=3-aim;
        while(now<m&&col[cvx[now]]==aim){
            if(aim==1) pl.push_back(cvx[now]);
            else pr.push_back(cvx[now]);
            now++;
        }
        if(now!=m) return 0;
        now=0;
        while(now<m&&col[cvx[now]]==aim){
            if(aim==1) pl.push_back(cvx[now]);
            else pr.push_back(cvx[now]);
            now++;
        }
        if(pl.size()+pr.size()<m) return 0;
        return 2;
    }
    return 1;
}
void solve(Triangle t,vector<int> p){
    if(p.size()==0) return ;
    int f=-1;
    for(auto v:p){
        if(col[v]==col[t.a]){
            f=v; break;
        }
    }
    if(f==-1){
        for(auto v:p) ans.push_back(make_pair(v,t.b));
        return ;
    }
    else{
        ans.push_back(make_pair(f,t.a));
        Triangle tt(f,t.b,t.c); vector<int> pp;
        for(auto v:p) if(tt.InTriangle(v)) pp.push_back(v);
        solve(tt,pp);
        tt=Triangle(t.b,t.a,f); pp.clear();
        for(auto v:p) if(tt.InTriangle(v)) pp.push_back(v);
        solve(tt,pp);
        tt=Triangle(t.c,t.a,f); pp.clear();
        for(auto v:p) if(tt.InTriangle(v)) pp.push_back(v);
        solve(tt,pp);
    }
}

int main(){
    scanf("%d %d",&nl,&nr); n=nl+nr;
    for(int i=1;i<=nl;++i){
        scanf("%lld %lld",&pt[i].x,&pt[i].y);
        col[i]=1;
    }
    for(int i=nl+1;i<=nl+nr;++i){
        scanf("%lld %lld",&pt[i].x,&pt[i].y);
        col[i]=2;
    }
    int f=check();
    if(!f){
        printf("Poor Quailty\n");
        return 0;
    }
    if(f==1){
        for(int i=0;i<m-1;++i) ans.push_back(make_pair(cvx[i],cvx[i+1]));
        int aim=col[cvx[0]]; int f=aim==1?nl+1:1;
        cvx[m]=cvx[0];
        Triangle t; vector<int> p;
        for(int i=0;i<m;++i){
            t=Triangle(f,cvx[i],cvx[i+1]); p.clear();
            for(int i=1;i<=n;++i)
                if(t.InTriangle(i)) p.push_back(i);
            solve(t,p);
        }
    }
    else{
        for(int i=0;i<pl.size()-1;++i)
            ans.push_back(make_pair(pl[i],pl[i+1]));
        for(int i=0;i<pr.size()-1;++i)
            ans.push_back(make_pair(pr[i],pr[i+1]));
        Triangle t; vector<int> p;
        for(int i=0;i<pl.size()-1;++i){
            t=Triangle(pr[0],pl[i],pl[i+1]); p.clear();
            for(int i=1;i<=n;++i)
                if(t.InTriangle(i)) p.push_back(i);
            solve(t,p);
        }
        for(int i=0;i<pr.size()-1;++i){
            t=Triangle(pl[0],pr[i],pr[i+1]); p.clear();
            for(int i=1;i<=n;++i)
                if(t.InTriangle(i)) p.push_back(i);
            solve(t,p);
        }
    }
    sort(ans.begin(),ans.end());
    for(auto p:ans){
        if(col[p.first]==2) printf("%d %d\n",p.first-=nl,p.second-=nl);
        else printf("%d %d\n",p.first,p.second);
    }
}