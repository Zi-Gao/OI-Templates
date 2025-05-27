#define INV_DATA_TYPE long long

INV_DATA_TYPE qpow(register INV_DATA_TYPE base,register INV_DATA_TYPE p){
    register INV_DATA_TYPE ans=1;
    register INV_DATA_TYPE e=p-2;
    base%=p;
    while(e){
        if(e&1) ans=ans*base%p;
        base=base*base%p;
        e>>=1;
    }
    return ans;
}

INV_DATA_TYPE inv(INV_DATA_TYPE n,INV_DATA_TYPE p){
    return qpow(n,p);
}