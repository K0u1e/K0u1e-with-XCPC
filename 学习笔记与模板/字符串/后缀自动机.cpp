struct SAM{
    int next[N][26],fa[N],len[N],endpos[N];
    int root,tot,last; vector<int> son[N];
    int newnode(int l){
        fa[tot]=-1; endpos[tot]=-1;
        for(int i=0;i<26;++i)  next[tot][i]=-1;
        len[tot++]=l; return tot-1;
    }
    void init(){
        tot=0;
        last=root=newnode(0,0);
    }
    void extend(int x,int ep){
        int p=last; int cur=newnode(len[p]+1);
        endpos[cur]=ep;
        while(p!=-1&&next[p][x]==-1){
            next[p][x]=cur; p=fa[p];
        }
        if(p==-1) fa[cur]=root;
        else{
            int q=next[p][x];
            if(len[q]==len[p]+1) fa[cur]=q;
            else{
                int tmp = newnode(len[p]+1,0);
                memcpy(next[tmp],next[q],sizeof(next[q]));
                fa[tmp]=fa[q]; fa[q]=fa[cur]=tmp;
                while(p!=-1&&next[p][x]==q){
                    next[p][x]=tmp; p=fa[p];
                }
            }
        }
        last=cur;
    }
    void build(){
        for(int i=0;i<tot;++i) son[i].clear();
        for(int i=1;i<tot;++i) son[fa[i]].push_back(i);
    }
}sam;