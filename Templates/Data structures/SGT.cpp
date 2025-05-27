#define SGT_DATA_TYPE long long
#define SGT_TAG_TYPE long long
#define lC ((p)<<1)
#define rC (lC|1)
#define getMid int mid=(((l)+(r))>>1)

const int SGT_SIZE=100000;

struct SGT_NODE{
    SGT_DATA_TYPE data;
    SGT_TAG_TYPE tag;
    SGT_NODE(){
        data=tag=0;
        return;
    }
};

struct SGT_TREE{
    SGT_NODE tree[SGT_SIZE<<2];
    int L,R;
    void pushup(int p){return (void)(tree[p].data=tree[lC].data+tree[rC].data);}
    void down(int p,int l,int r,SGT_TAG_TYPE tag){return (void)(tree[p].tag+=tag,tree[p].data+=tag*(r-l+1));}
    void pushdown(int p,int l,int r,int mid){return (void)(down(lC,l,mid,tree[p].tag),down(rC,mid+1,r,tree[p].tag),tree[p].tag=0);}
    void build(int p,int l,int r,SGT_DATA_TYPE *data){
        if(l==r) return (void)(tree[p].data=data[l]);
        getMid;
        build(lC,l,mid,data);
        build(rC,mid+1,r,data);
        return pushup(p);
    }
    void modify(int p,int l,int r,int s,int t,SGT_TAG_TYPE tag){
        if(s<=l&&r<=t) return down(p,l,r,tag);
        getMid;
        pushdown(p,l,r,mid);
        if(s<=mid) modify(lC,l,mid,s,t,tag);
        if(mid<t) modify(rC,mid+1,r,s,t,tag);
        return pushup(p);
    }
    SGT_DATA_TYPE query(int p,int l,int r,int s,int t){
        if(s<=l&&r<=t) return tree[p].data;
        getMid;
        pushdown(p,l,r,mid);
        return (s<=mid?query(lC,l,mid,s,t):0)+(mid<t?query(rC,mid+1,r,s,t):0);
    }
    void build(int l,int r,SGT_DATA_TYPE *data){
        L=l,R=r;
        return build(1,L,R,data);
    }
    void modify(int s,int t,SGT_TAG_TYPE tag){return modify(1,L,R,s,t,tag);}
    SGT_DATA_TYPE query(int s,int t){return query(1,L,R,s,t);}
};