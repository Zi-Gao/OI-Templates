#define QPOW_DATA_TYPE long long
#define QPOW_DATA_E_TYPE QPOW_DATA_TYPE
QPOW_DATA_TYPE qpow(register QPOW_DATA_TYPE base,register QPOW_DATA_E_TYPE e){
    register QPOW_DATA_TYPE res=1;
    while(e){
        if(e&1) res*=base;
        base*=base;
        e>>=1;
    }
    return res;
}