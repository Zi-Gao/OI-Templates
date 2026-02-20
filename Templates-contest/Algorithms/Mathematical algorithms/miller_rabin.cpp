long long mrPri[7]={2,325,9375,28178,450775,9780504,1795265022};
inline __attribute((always_inline)) long long mrQpow(__int128_t b,__int128_t e,long long mod){
    register __int128_t res=1;
    b%=mod;
    while(e){
        if(e&1) (res*=b)%=mod;
        (b*=b)%=mod;
        e>>=1;
    }
    return res;
}
bool millerRabin(long long n){
    if(n<3||(!(n&1))) return n==2;
    register int i;
    register long long u=n-1,t=0,v,s;
    while(!(u&1)) u/=2,++t;
    for(i=0;i<7;++i){
        v=mrQpow(mrPri[i],u,n);
        if(v==0||v==1||v==n-1) continue;
        for(s=0;s<t;++s){
            if(v==n-1) break;
            v=(__int128_t)v*v%n;
        }
        if(s==t) return false;
    }
    return true;
}