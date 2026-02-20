#define CRT_DATA_TPYE long long
CRT_DATA_TPYE CRT_exgcd(CRT_DATA_TPYE a,CRT_DATA_TPYE b,CRT_DATA_TPYE &x,CRT_DATA_TPYE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    CRT_DATA_TPYE d=CRT_exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

CRT_DATA_TPYE CRT_inv(CRT_DATA_TPYE n,CRT_DATA_TPYE p){
    CRT_DATA_TPYE x,y;
    CRT_exgcd(n,p,x,y);
    x%=p;
    return x>=0?x:x+p;
}

CRT_DATA_TPYE CRT(int n,CRT_DATA_TPYE *a,CRT_DATA_TPYE *mod){
    register int i;
    CRT_DATA_TPYE M=1,m,ans=0;
    for(i=0;i<n;++i) M*=mod[i];
    for(i=0;i<n;++i)
        m=M/mod[i],(ans+=a[i]*m%M*CRT_inv(m,mod[i]))%=M;
    return ans;
}