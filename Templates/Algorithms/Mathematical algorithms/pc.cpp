#define PC_DATA_TYPE long long

const PC_DATA_TYPE PC_MOD=998244353;
const PC_DATA_TYPE PC_DATA_SIZE=1000010;

PC_DATA_TYPE inv[PC_DATA_SIZE],fact[PC_DATA_SIZE],invfact[PC_DATA_SIZE];

void init_pc(int n){
    register int i;
    for(inv[0]=0,inv[1]=fact[0]=fact[1]=invfact[0]=invfact[1]=1,i=2;i<=n;++i)
        invfact[i]=invfact[i-1]*(inv[i]=PC_MOD-PC_MOD/i*inv[PC_MOD%i]%PC_MOD)%PC_MOD,fact[i]=fact[i-1]*i%PC_MOD;
    return;
}

PC_DATA_TYPE A(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return fact[n]*invfact[n-m]%PC_MOD;
}
PC_DATA_TYPE C(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return fact[n]*invfact[n-m]%PC_MOD*invfact[m]%PC_MOD;
}