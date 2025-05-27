#define ln(x) 31^__builtin_clz(x)
#define RMQ_2D_DATA_TYPE int
#define RMQ_2D_TYPE >
RMQ_2D_DATA_TYPE ST_CALC(RMQ_2D_DATA_TYPE a,RMQ_2D_DATA_TYPE b){return a RMQ_2D_TYPE b?a:b;}

const int RMQ_2D_DATA_SIZE_N=1000,RMQ_2D_DATA_SIZE_M=1000,RMQ_2D_DATA_SIZE_I=11,RMQ_2D_DATA_SIZE_J=11;

struct RMQ_2D{
    RMQ_2D_DATA_TYPE st[RMQ_2D_DATA_SIZE_I][RMQ_2D_DATA_SIZE_J][RMQ_2D_DATA_SIZE_N][RMQ_2D_DATA_SIZE_M];
    int sizen,sizem;

    void build(int n,int m){
        register int i,j,x,y;
        sizen=n,sizem=m;
        int kn=ln(n),km=ln(m);
        for(i=0;i<=kn;++i)
            for(j=0;j<=km;++j)
                if(i||j){
                    for(x=1;x<=n-(1<<i)+1;++x)
                        for(y=1;y<=m-(1<<j)+1;++y)
                            if(i) st[i][j][x][y]=ST_CALC(st[i-1][j][x][y],st[i-1][j][x+(1<<(i-1))][y]);
                            else st[i][j][x][y]=ST_CALC(st[i][j-1][x][y],st[i][j-1][x][y+(1<<(j-1))]);
                }
        return;
    }

    RMQ_2D_DATA_TYPE query(int x1,int y1,int x2,int y2){
        int kn=ln(x2-x1+1),km=ln(y2-y1+1);
        return ST_CALC(ST_CALC(st[kn][km][x1][y1],st[kn][km][x2-(1<<kn)+1][y1]),ST_CALC(st[kn][km][x1][y2-(1<<km)+1],st[kn][km][x2-(1<<kn)+1][y2-(1<<km)+1]));
    }
}st;