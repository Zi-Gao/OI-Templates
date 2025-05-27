#include<cstring>
#define MATRIX_MOD %1000000007
#define MATRIX_DATA_TYPE long long
const int MATRIX_MAX_N=100;
const int MATRIX_MAX_M=100;
struct MATRIX{
    int n,m;
    MATRIX_DATA_TYPE matrix[MATRIX_MAX_N][MATRIX_MAX_M];

    MATRIX operator + (const MATRIX &a) const {
        register int i,j;
        MATRIX ans;
        ans.n=n;
        ans.m=m;
        for(i=0;i<n;++i)
            for(j=0;j<m;++j)
                ans.matrix[i][j]=(matrix[i][j]+a.matrix[i][j])MATRIX_MOD;

        return ans;
    }

    MATRIX operator * (const MATRIX &a) const {
        register int i,j,k;
        MATRIX ans;
        ans.n=n;
        ans.m=a.m;
        for(i=0;i<n;++i)
            for(j=0;j<a.m;++j){
                ans.matrix[i][j]=0;
                for(k=0;k<m;++k)
                    ans.matrix[i][j]=(ans.matrix[i][j]+matrix[i][k]*a.matrix[k][j]MATRIX_MOD)MATRIX_MOD;
            }

        return ans;
    }

    friend MATRIX operator ^ (MATRIX base,register MATRIX_DATA_TYPE exponential){
        register int i,j;
        MATRIX ans;
        ans.n=base.n;
        ans.m=base.n;

        for(i=0;i<ans.n;++i)
            for(j=0;j<ans.m;++j)
                ans.matrix[i][j]=(i==j);

        while(exponential){
            if(exponential&1) ans=ans*base;
            base=base*base;
            exponential>>=1;
        }

        return ans;
    }

    void clear(){
        register int i,j;
        for(i=0;i<n;++i)
            for(j=0;j<m;++j)
                matrix[i][j]=0;
        return;
    }
};