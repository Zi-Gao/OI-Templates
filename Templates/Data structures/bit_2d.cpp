#define BIT_DATA_TYPE int
const int BIT_SIZE_N=6000;
const int BIT_SIZE_M=6000;

struct BIT{
    BIT_DATA_TYPE tree[BIT_SIZE_N][BIT_SIZE_M];
    int n,m;
    void build(register int n_,register int m_){
        n=n_,m=m_;
        return;
    }
    BIT_DATA_TYPE getsum(int x0,int y0,int x1,int y1){return presum(x1,y1)-presum(x0-1,y1)-presum(x1,y0-1)+presum(x0-1,y0-1);}
    BIT_DATA_TYPE presum(register int x,register int y){
        register int i,j;
        register BIT_DATA_TYPE sum=0;
        for(i=x;i;i-=lowbit(i))
            for(j=y;j;j-=lowbit(j))
                sum+=tree[i][j];
        return sum;
    }
    void add(register BIT_DATA_TYPE data,register int x,register int y){
        register int i,j;
        for(i=x;i<=n;i+=lowbit(i))
            for(j=y;j<=m;j+=lowbit(j))
                tree[i][j]+=data;
        return;
    }
    inline int lowbit(BIT_DATA_TYPE x){return x&-x;}
    void clear(register int x,register int y){
        register int i,j;
        for(i=x;i<=n;i+=lowbit(i))
            for(j=y;j<=m;j+=lowbit(j))
                tree[i][j]=0;
        return;
    }
    void clear(){
        memset(this,0,sizeof(BIT));
        return;
    }
};