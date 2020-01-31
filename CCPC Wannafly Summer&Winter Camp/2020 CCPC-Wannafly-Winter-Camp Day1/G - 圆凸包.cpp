#include <bits/stdc++.h>
using namespace std;
const int N = 110;
const double eps = 1e-8;
const double PI = acos(-1.0);
struct Point{
    double x,y;
    Point(){ x=0,y=0; }
    Point(double _x,double _y){ x=_x,y=_y; }
};
struct Circle{
    Point c; double r;
    Circle(){ c=Point(0,0),r=0; };
    Circle(Point _c,double _r){ c=_c,r=_r; }
    Point point(double a){ return Point(c.x+r*cos(a),c.y+r*sin(a)); }
};
int sgn(double x) { if(fabs(x)<eps) return 0; else return x<0?-1:1; }
Point operator + (Point a, Point b) { return Point(a.x+b.x,a.y+b.y); }
Point operator - (Point a, Point b) { return Point(a.x-b.x,a.y-b.y); }
Point operator * (Point a, double p) { return Point(a.x*p,a.y*p); }
Point operator / (Point a, double p) { return Point(a.x/p,a.y/p); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x-b.x)?sgn(a.x-b.x)<0:sgn(a.y-b.y)<0; }
bool operator == (const Point &a, const Point &b) { return sgn(a.x-b.x)==0&&sgn(a.y-b.y)==0; }
double Dot(Point a, Point b) { return a.x*b.x+a.y*b.y; }
double Length(Point a) { return sqrt(Dot(a,a)); }
double Angle(Point a, Point b) { return acos(Dot(a,b)/Length(a)/Length(b)); }
double Cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }

Point p[N*N*4],cvx[N*N*4]; int n,m;
Circle cr[N]; bool ok[N];

bool chk(Point p){
    for(int i=0;i<n;++i){
        if(!ok[i]) continue;
        if(sgn((p.x-cr[i].c.x)*(p.x-cr[i].c.x)+(p.y-cr[i].c.y)*(p.y-cr[i].c.y)-cr[i].r*cr[i].r)<0)
            return false;
    }
    return true;
}

void getTangents(Circle a,Circle b){
    if(a.r<b.r) swap(a,b);
    double d2=(a.c.x-b.c.x)*(a.c.x-b.c.x)+(a.c.y-b.c.y)*(a.c.y-b.c.y);
    //double rdiff=a.r-b.r;
    //if(sgn(d2-rdiff*rdiff)<=0) return ;
    double base=atan2(b.c.y-a.c.y,b.c.x-a.c.x);
    double ang=acos((a.r-b.r)/(sqrt(d2)));
    p[m++]=a.point(base+ang); if(!chk(p[m-1])) m--;
    p[m++]=b.point(base+ang); if(!chk(p[m-1])) m--;
    p[m++]=a.point(base-ang); if(!chk(p[m-1])) m--;
    p[m++]=b.point(base-ang); if(!chk(p[m-1])) m--;
}

void pre(Circle a,Circle b,int i,int j){
    if(sgn(a.r-b.r)<0) swap(a,b),swap(i,j);
    double d2=(a.c.x-b.c.x)*(a.c.x-b.c.x)+(a.c.y-b.c.y)*(a.c.y-b.c.y);
    double rdiff=a.r-b.r;
    if(sgn(d2-rdiff*rdiff)<=0)  ok[j]=false;
}

int getConvex(Point *p,int n,Point *cvx){
    int m=0; sort(p,p+n);
    //for(int i=0;i<n;++i) printf("p %lf %lf\n",p[i].x,p[i].y);
    n=unique(p,p+n)-p;
    //printf("nnn%d\n",n);
    for(int i=0;i<n;++i){
        while(m>1&&sgn(Cross(cvx[m-1]-cvx[m-2],p[i]-cvx[m-2]))<=0) m--;
        cvx[m++]=p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;--i){
        while(m>k&&sgn(Cross(cvx[m-1]-cvx[m-2],p[i]-cvx[m-2]))<=0) m--;
        cvx[m++]=p[i];
    }
    if(cvx[m-1]==cvx[0]) return m-1;
    else return m;
}

int check(Point a,Point b){
    for(int i=0;i<n;++i){
        if(!ok[i]) continue;
        if(sgn((a.x-cr[i].c.x)*(a.x-cr[i].c.x)+(a.y-cr[i].c.y)*(a.y-cr[i].c.y)-cr[i].r*cr[i].r)) continue;
        if(sgn((b.x-cr[i].c.x)*(b.x-cr[i].c.x)+(b.y-cr[i].c.y)*(b.y-cr[i].c.y)-cr[i].r*cr[i].r)) continue;
        return i;
    }
    return -1;
}

int main(){
    //freopen("D:\\data\\1.in","r",stdin);
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d",&n); double x,y,r;
        for(int i=0;i<n;++i){
            scanf("%lf %lf %lf",&x,&y,&r);
            cr[i]=Circle(Point(x,y),r); ok[i]=true;
        }
        for(int i=0;i<n;++i)
            for(int j=i+1;j<n;++j) pre(cr[i],cr[j],i,j);
        m=0; r=0;
        for(int i=0;i<n;++i) if(ok[i]) m++,r=cr[i].r;
        if(m==1){
            printf("%.11lf\n",2*r*PI);
            continue;
        }
        m=0;
        for(int i=0;i<n;++i){
            if(!ok[i]) continue;
            for(int j=i+1;j<n;++j){
                if(!ok[j]) continue;
                getTangents(cr[i],cr[j]);
            }
        }
        m=getConvex(p,m,cvx);
        //for(int i=0;i<m;++i) printf("%lf %lf\n",cvx[i].x,cvx[i].y);
        //cvx[m]=cvx[0];
        double ans=0;
        for(int i=0;i<m;++i){
            int o=check(cvx[i],cvx[i+1]);
            if(~o){
                int op=sgn(Cross(cvx[i+1]-cr[o].c,cvx[i]-cr[o].c));
                //printf("op %d\n",o);
                if(op<=0) ans+=Angle(cvx[i+1]-cr[o].c,cvx[i]-cr[o].c)*cr[o].r;
                else ans+=(2*PI-Angle(cvx[i+1]-cr[o].c,cvx[i]-cr[o].c))*cr[o].r;
            }
            else ans+=Length(cvx[i+1]-cvx[i]);
            //printf("%lf\n",ans);
        }
        printf("%.11lf\n",ans);
    }
}