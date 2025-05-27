#define GJ_MOD_TYPE long long
const GJ_MOD_TYPE GJ_mod=998244353;

GJ_MOD_TYPE exgcd(GJ_MOD_TYPE a,GJ_MOD_TYPE b,GJ_MOD_TYPE &x,GJ_MOD_TYPE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    GJ_MOD_TYPE d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

GJ_MOD_TYPE inv(GJ_MOD_TYPE n,GJ_MOD_TYPE p){
    GJ_MOD_TYPE x,y;
    exgcd(n,p,x,y);
    x%=p;
    return x>=0?x:x+p;
}
/*
-1:infinite solutions
0: no solution
1: only one solution
*/
int GJMODSolve(std::vector<GJ_MOD_TYPE> *mat,int n){
    register int r,c,i,j,maxR;
    register GJ_MOD_TYPE invnow;
    for(r=c=0;c<n;++c){
        maxR=r;
        for(i=r+1;i<n;++i) if(mat[i][c]>mat[maxR][c]) maxR=i;
        if(maxR!=r) mat[maxR].swap(mat[r]);

        if(!mat[r][c]) continue;

        invnow=inv(mat[r][c],GJ_mod);
        for(i=n;i>=c;--i) (mat[r][i]*=invnow)%=GJ_mod;
        for(i=0;i<n;++i)
            if(mat[i][c]&&i!=r)
                for(j=n;j>=c;--j)
                    (mat[i][j]+=GJ_mod-mat[r][j]*mat[i][c]%GJ_mod)%=GJ_mod;
        ++r;
    }
    if(r<n)
        for(i=r;i<n;++i)
            if(mat[i][n])
                return 0;

    return r<n?r-n:1;
}