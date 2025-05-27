const int TRIE_01_DATA_SIZE=200010*31;

struct TRIE_01{
    int child[TRIE_01_DATA_SIZE][2],maxval[TRIE_01_DATA_SIZE],tot,maxdep,root;
    void build(int len){
        root=tot=0;
        maxdep=len;
        return;
    }
    int getNode(){
        ++tot;
        child[tot][0]=child[tot][1]=maxval[tot]=0;
        return tot;
    }
    void pushup(int p){return maxval[p]=std::max(maxval[child[p][0]],maxval[child[p][1]]),void();}
    void insert(int &p,int x,int dep,int val){
        if(!p) p=getNode();
        if(dep==-1) return maxval[p]=std::max(maxval[p],val),void();
        insert(child[p][(x>>dep)&1],x,dep-1,val);
        return pushup(p);
    }
    void insert(int x,int val){return insert(root,x,maxdep,val);}
    int getMax(int p,int x,int dep){
        if(!p) return 0;
        if(dep==-1) return maxval[p];
        if(child[p][((x>>dep)&1)^1]) return getMax(child[p][((x>>dep)&1)^1],x,dep-1);
        else return getMax(child[p][(x>>dep)&1],x,dep-1);
    }
    int getPos(int p,int x,int y,int dep){
        if(!p) return 0;
        if(dep==-1) return 0;
        if(((x^y)>>dep)&1) return getPos(child[p][(y>>dep)&1],x,y,dep-1);
        else return std::max(maxval[child[p][((y>>dep)&1)^1]],getPos(child[p][(y>>dep)&1],x,y,dep-1));
    }
    int getMax(int x){return getMax(root,x,maxdep);}
    int getPos(int x,int y){return getPos(root,x,y,maxdep);}
    void add(int p){
        if(!p) return;
        std::swap(child[p][0],child[p][1]);
        add(child[p][0]);
        return pushup(p);
    }
}trie;