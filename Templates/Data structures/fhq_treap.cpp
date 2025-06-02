const int FHQ_DATA_SIZE=2000010;

std::mt19937 mt;

template<typename T=int>
struct FHQTreap{
    struct FHQNODE{
        int lChild,rChild,size,rnd;
        T val;
    };
    FHQNODE tree[FHQ_DATA_SIZE];
    int mem[FHQ_DATA_SIZE],top,root;

    void build(int n){
        mt=std::mt19937(time(0));
        register int i;
        for(i=0;i<=n;++i) mem[i]=i;
        top=n;
        root=0;
        return;
    }

    int getMem(){return mem[top--];}
    void rMem(int pos){return (void)(mem[++top]=pos);}
    int getNode(T data){
        int pos=getMem();
        tree[pos].lChild=tree[pos].rChild=0;
        tree[pos].size=1;
        tree[pos].val=data;
        tree[pos].rnd=rand();
        return pos;
    }
    void rTree(int p){
        if(!p) return;
        rTree(tree[p].lChild);
        rTree(tree[p].rChild);
        return rMem(p);
    }

    void pushup(int p){return (void)(tree[p].size=tree[tree[p].lChild].size+tree[tree[p].rChild].size+1);}

    void split(int p,int &x,int &y,T val){
        if(!p){return (void)(x=y=0);}
        if(tree[p].val<=val) x=p,split(tree[p].rChild,tree[p].rChild,y,val);
        else y=p,split(tree[p].lChild,x,tree[p].lChild,val);
        pushup(p);
        return;
    }
    void split_rank(int p,int &x,int &y,int rank){
        if(!rank){return (void)(x=0,y=p);}
        if(tree[tree[p].lChild].size<rank) x=p,split_rank(tree[p].rChild,tree[p].rChild,y,rank-tree[tree[p].lChild].size-1);
        else y=p,split_rank(tree[p].lChild,x,tree[p].lChild,rank);
        pushup(p);
        return;
    }

    int merge(int u,int v){
        if((!u)||(!v)) return u|v;
        if(tree[u].rnd<tree[v].rnd){
            tree[u].rChild=merge(tree[u].rChild,v);
            pushup(u);
            return u;
        }
        tree[v].lChild=merge(u,tree[v].lChild);
        pushup(v);
        return v;
    }

    int insert_rank(T data,int rk){
        int pos=getNode(data),x,y;
        split_rank(root,x,y,rk);
        root=merge(merge(x,pos),y);
        return pos;
    }
    void insert_rank_n(T *data,int cnt,int rk){
        register int i;
        int x,y=0,z;
        split_rank(root,x,z,rk);
        for(i=0;i<cnt;++i) y=merge(y,getNode(data[i]));
        root=merge(merge(x,y),z);
    }
    int insert(T data){
        int pos=getNode(data),x,y;
        split(root,x,y,data);
        root=merge(merge(x,pos),y);
        return pos;
    }

    void erase_rank(int rk){
        int x,y,z;
        split_rank(root,x,z,rk);
        split_rank(x,x,y,rk-1);
        root=merge(x,z);
        return rMem(y);
    }
    void erase_rank_range(int l,int r){
        int x,y,z;
        split_rank(root,x,z,r);
        split_rank(x,x,y,l-1);
        root=merge(x,z);
        return rTree(y);
    }
    void erase(T data){
        int x,y,z;
        split(root,x,y,data-1);
        split(y,y,z,data);
        root=merge(merge(x,tree[y].lChild),merge(tree[y].rChild,z));
        rMem(y);
    }

    int findRank(T data){
        int x,y,res;
        split(root,x,y,data-1);
        res=tree[x].size+1;
        root=merge(x,y);
        return res;
    }
    T findKthNum(int &p,int k){
        int x,y,z;
        split_rank(p,x,z,k);
        split_rank(x,x,y,k-1);
        T res=tree[y].val;
        p=merge(merge(x,y),z);
        return res;
    }
    T findPre(T data){
        int x,y;
        split(root,x,y,data-1);
        T res=findKthNum(x,tree[x].size);
        root=merge(x,y);
        return res;
    }
    T findNxt(T data){
        int x,y;
        split(root,x,y,data);
        T res=findKthNum(y,1);
        root=merge(x,y);
        return res;
    }
};