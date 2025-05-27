#define EXCRT_DATA_TPYE long long
EXCRT_DATA_TPYE EXCRT_exgcd(EXCRT_DATA_TPYE a,EXCRT_DATA_TPYE b,EXCRT_DATA_TPYE &x,EXCRT_DATA_TPYE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    EXCRT_DATA_TPYE d=EXCRT_exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

EXCRT_DATA_TPYE exCRT(int n,EXCRT_DATA_TPYE *a,EXCRT_DATA_TPYE *mod){
    register int i;
    EXCRT_DATA_TPYE M=mod[0],A=a[0],p,q,gcd;
    for(i=1;i<n;++i){
        gcd=EXCRT_exgcd(mod[i],-M,p,q);
        if((A-a[i])%gcd)
            return -1;
        M=mod[i]/gcd*M;
        if(M<0) M=-M;
        A=((mod[i]*p%M*((A-a[i])/gcd)+a[i])%M+M)%M;
    }
    return A;
}
