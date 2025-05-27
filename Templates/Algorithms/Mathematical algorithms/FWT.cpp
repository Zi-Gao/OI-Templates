const long long FWT_MOD=998244353;

void FWT_MUL(long long *A,long long *B,int n){
    register int i;
    for(i=0;i<n;++i) (A[i]*=B[i])%=FWT_MOD;
    return;
}

void FWT_OR(long long *f,long long x,int n){
    register int i,j,k,o;
    for(o=2,k=1;o<=n;o<<=1,k<<=1)
        for(i=0;i<n;i+=o)
            for(j=0;j<k;++j)
                (f[i+j+k]+=f[i+j]*x)%=FWT_MOD;
    return;
}

void FWT_AND(long long *f,long long x,int n){
    register int i,j,k,o;
    for(o=2,k=1;o<=n;o<<=1,k<<=1)
        for(i=0;i<n;i+=o)
            for(j=0;j<k;++j)
                (f[i+j]+=f[i+j+k]*x)%=FWT_MOD;
    return;
}

void FWT_XOR(long long *f,long long x,int n){
    register int i,j,k,o;
    for(o=2,k=1;o<=n;o<<=1,k<<=1)
        for(i=0;i<n;i+=o)
            for(j=0;j<k;++j)
                f[i+j]+=f[i+j+k],
                f[i+j+k]=f[i+j]-f[i+j+k]+FWT_MOD-f[i+j+k],
                (f[i+j]*=x)%=FWT_MOD,(f[i+j+k]*=x)%=FWT_MOD;
    return;
}