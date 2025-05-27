#define GJ_TYPE double
GJ_TYPE eps=1e-7;
/*
-1:infinite solutions
0: no solution
1: only one solution
*/
int GJSolve(std::vector<GJ_TYPE> *mat,int n){
    register int r,c,i,j,maxR;
    for(r=c=0;c<n;++c){
        maxR=r;
        for(i=r+1;i<n;++i) if(fabs(mat[i][c])>fabs(mat[maxR][c])) maxR=i;
        if(maxR!=r) mat[maxR].swap(mat[r]);

        if(fabs(mat[r][c])<eps) continue;

        for(i=n;i>=c;--i) mat[r][i]/=mat[r][c];
        for(i=0;i<n;++i)
            if(i!=r&&fabs(mat[i][c])>eps)
                for(j=n;j>=c;--j)
                    mat[i][j]-=mat[r][j]*mat[i][c];
        ++r;
    }
    if(r<n)
        for(i=r;i<n;++i)
            if(fabs(mat[i][n])>eps)
                return 0;

    return r<n?r-n:1;
}