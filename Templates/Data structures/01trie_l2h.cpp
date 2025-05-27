
#define TRIE_01_DATA_TYPE int
const int TRIE_01_DATA_SIZE=100010<<7;

struct TRIE_01{
    int child[TRIE_01_DATA_SIZE][2],cnt[TRIE_01_DATA_SIZE],root[TRIE_01_DATA_SIZE],tot,maxdep;
    TRIE_01_DATA_TYPE xorv[TRIE_01_DATA_SIZE];

    void build(int len,int n){
        for(register int i=0;i<=n;++i) root[i]=0;
        maxdep=len;
        tot=cnt[0]=xorv[0]=0;
        return;
    }
    int getNode(){
        ++tot;
        child[tot][0]=child[tot][1]=cnt[tot]=xorv[tot]=0;
        return tot;
    }
    void pushup(int p){return (void)(cnt[p]=cnt[child[p][0]]^cnt[child[p][1]],xorv[p]=((xorv[child[p][0]]<<1)^(xorv[child[p][1]]<<1))|cnt[child[p][1]]);}
    void insert(int &p,int x,int dep){
        if(!p) p=getNode();
        if(dep==maxdep){return (void)(cnt[p]^=1);}
        insert(child[p][x&1],x>>1,dep+1);
        return pushup(p);
    }
    void insert(int p,int x){return insert(root[p],x,0);}
    void erase(int p,int x){return insert(root[p],x,0);}
    void add(int p){
        if(!p) return;
        std::swap(child[p][0],child[p][1]);
        add(child[p][0]);
        return pushup(p);
    }
    void addone(int p){return add(root[p]);}
    TRIE_01_DATA_TYPE xorSum(int p){return xorv[root[p]];}
}trie01;