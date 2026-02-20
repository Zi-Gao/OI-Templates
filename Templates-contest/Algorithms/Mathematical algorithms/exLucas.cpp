#define EXLC_TYPE long long

EXLC_TYPE exLC_exgcd(EXLC_TYPE a,EXLC_TYPE b,EXLC_TYPE &x,EXLC_TYPE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    EXLC_TYPE d=exLC_exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

EXLC_TYPE exLC_inv(EXLC_TYPE n,EXLC_TYPE p){
    EXLC_TYPE x,y;
    exLC_exgcd(n,p,x,y);
    x%=p;
    return x>=0?x:x+p;
}

long long exLC_a[100],exLC_mod[100],exLC_p,exLC_pk,pk_fact;

EXLC_TYPE exLC_qpow(register EXLC_TYPE base,register EXLC_TYPE e){
    register EXLC_TYPE res=1;
    base%=exLC_pk;
    while(e){
        if(e&1) (res*=base)%=exLC_pk;
        (base*=base)%=exLC_pk,e>>=1;
    }
    return res;
}

EXLC_TYPE mulPx(register EXLC_TYPE n){
    EXLC_TYPE res=1,i;
    while(n){
        (res*=exLC_qpow(pk_fact,n/exLC_pk))%=exLC_pk;
        for(i=exLC_pk*(n/exLC_pk);i<=n;++i) if(i%exLC_p) (res*=i%exLC_pk)%=exLC_pk;
        n/=exLC_p;
    }
    return res;
}

EXLC_TYPE getE(register EXLC_TYPE n){
    register EXLC_TYPE res=0;
    while(n>=exLC_p) res+=n/exLC_p,n/=exLC_p;
    return res;
}

EXLC_TYPE CPK(register EXLC_TYPE n,register EXLC_TYPE m,const register EXLC_TYPE _p,const register EXLC_TYPE _pk){
    register EXLC_TYPE i;
    exLC_p=_p,exLC_pk=_pk;
    for(i=pk_fact=1;i<exLC_pk;++i) if(i%exLC_p) (pk_fact*=i%exLC_pk)%=exLC_pk;
    register EXLC_TYPE A=mulPx(n),invB=exLC_inv(mulPx(m),exLC_pk),invC=exLC_inv(mulPx(n-m),exLC_pk),pw=exLC_qpow(exLC_p,getE(n)-getE(m)-getE(n-m));
    return A*invB%exLC_pk*invC%exLC_pk*pw%exLC_pk;
}

EXLC_TYPE CExLC(register EXLC_TYPE n,register EXLC_TYPE m,const register EXLC_TYPE p){
    register EXLC_TYPE cp=p,cnt=0,ans=0,i,pk,tm;
    for(i=2;i*i<=cp;++i)
        if(!(cp%i)){
            pk=1;
            while(!(cp%i)) pk*=i,cp/=i;
            exLC_mod[cnt]=pk,exLC_a[cnt++]=CPK(n,m,i,pk);
        }
    if(cp!=1) exLC_mod[cnt]=cp,exLC_a[cnt++]=CPK(n,m,cp,cp);
    for(i=0;i<cnt;++i) tm=p/exLC_mod[i],(ans+=exLC_a[i]*tm%p*exLC_inv(tm,exLC_mod[i]))%=p;
    return ans;
}