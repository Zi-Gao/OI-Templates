#define QPOW_DATA_TYPE long long
const QPOW_DATA_TYPE QPOW_MOD=1000000007;
QPOW_DATA_TYPE qpow(register QPOW_DATA_TYPE base,register QPOW_DATA_TYPE e){
    register QPOW_DATA_TYPE res=1;
    base%=QPOW_MOD;
    while(e){
        if(e&1) (res*=base)%=QPOW_MOD;
        (base*=base)%=QPOW_MOD;
        e>>=1;
    }
    return res;
}