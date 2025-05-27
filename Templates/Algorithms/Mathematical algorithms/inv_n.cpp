#define INV_DATA_TYPE long long

void getinv(INV_DATA_TYPE *invs,INV_DATA_TYPE p,int n){
    register int i;
    invs[0]=0;
    invs[1]=1;

    for(i=2;i<=n;++i){
        invs[i]=p-p/i*invs[p%i]%p;
    }

    return;
}