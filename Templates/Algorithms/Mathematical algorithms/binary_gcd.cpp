template<typename T>
T gcd(T a, T b){
    int i=std::__countr_zero(a),j=std::__countr_zero(b),k=std::min(i,j);
    T dif;
    b>>=j;
    while(a){
        a>>=i;
        i=std::__countr_zero(dif=b-a);
        b=std::min(a,b);
        a=dif<0?-dif:dif;
    }
    return b<<k;
}