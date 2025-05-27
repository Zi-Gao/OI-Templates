#define LC_TYPE long long

LC_TYPE LC_mod;

LC_TYPE C(LC_TYPE n,LC_TYPE m);

LC_TYPE CLucas(LC_TYPE n,LC_TYPE m){
    if(n<LC_mod&&m<LC_mod) return C(n,m);
    return C(n%LC_mod,m%LC_mod)*CLucas(n/LC_mod,m/LC_mod)%LC_mod;
}