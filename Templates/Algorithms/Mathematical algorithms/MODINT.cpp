#define MODINT_TYPE long long
#define barK (64)

namespace MODINT{
	unsigned long long d;
    __uint128_t m;
    inline __attribute((always_inline)) void init(const long long &mod){
        m=(((__uint128_t)1)<<barK)/(d=mod);
        return;
    }

    inline __attribute((always_inline)) unsigned long long mod(const unsigned long long &x){
        register unsigned long long w=(m*x)>>barK;
        w=x-w*d;
        return w>=d?w-d:w;
    }

    MODINT_TYPE exgcd(MODINT_TYPE a,const MODINT_TYPE b,MODINT_TYPE &x,MODINT_TYPE &y){
        if(!b){
            x=1;
            y=0;
            return a;
        }
        MODINT_TYPE d=exgcd(b,a%b,y,x);
        y-=a/b*x;
        return d;
    }

    inline __attribute((always_inline)) MODINT_TYPE inv(const MODINT_TYPE &n,const MODINT_TYPE &p){
        MODINT_TYPE x,y;
        exgcd(n,p,x,y);
        x%=p;
        return x>=0?x:x+p;
    }

    struct MODNUM{
        MODINT_TYPE val;
        inline __attribute((always_inline)) MODNUM(const MODINT_TYPE &x){
            if(x<0){
                val=d-mod(-x);
                if(val>=d) val-=d;
            }else val=mod(x);
            return;
        }
        inline __attribute((always_inline)) MODNUM(){val=0;}
        inline __attribute((always_inline)) MODNUM operator + (const MODNUM& o) const{return (MODNUM){(val+o.val>=d)?(val+o.val-d):(val+o.val)};}
        inline __attribute((always_inline)) MODNUM operator + (const MODINT_TYPE& o) const{return *this+MODNUM(o);}
        friend inline __attribute((always_inline)) MODNUM operator + (const MODINT_TYPE &o,const MODNUM&a){return a+o;}
        inline __attribute((always_inline)) MODNUM operator - (const MODNUM& o) const{return (MODNUM){(val-o.val<0)?(val-o.val+d):(val-o.val)};}
        inline __attribute((always_inline)) MODNUM operator - (const MODINT_TYPE& o) const{return *this-MODNUM(o);}
        friend inline __attribute((always_inline)) MODNUM operator - (const MODINT_TYPE &o,const MODNUM&a){return MODNUM(o)-a;}
        inline __attribute((always_inline)) MODNUM operator * (const MODNUM& o) const{return (MODNUM){mod(val*o.val)};}
        inline __attribute((always_inline)) MODNUM operator * (const MODINT_TYPE& o) const{return *this*MODNUM(o);}
        friend inline __attribute((always_inline)) MODNUM operator * (const MODINT_TYPE &o,const MODNUM&a){return a*o;}
        inline __attribute((always_inline)) MODNUM operator / (const MODNUM& o) const{return (MODNUM){mod(val*inv(o.val,d))};}
        inline __attribute((always_inline)) MODNUM operator / (const MODINT_TYPE& o) const{return *this/MODNUM(o);}
        friend inline __attribute((always_inline)) MODNUM operator / (const MODINT_TYPE &o,const MODNUM&a){return MODNUM(o)/a;}

        inline __attribute((always_inline)) MODNUM operator ++(){
            ++val;
            if(val>=d) val-=d;
            return *this;
        }
        inline __attribute((always_inline)) MODNUM operator ++(const int){
            MODNUM tmp=*this;
            ++val;
            if(val>=d) val-=d;
            return tmp;
        }
        inline __attribute((always_inline)) MODNUM operator --(){
            --val;
            if(val<0) val+=d;
            return *this;
        }
        inline __attribute((always_inline)) MODNUM operator --(const int){
            MODNUM tmp=*this;
            --val;
            if(val<0) val+=d;
            return tmp;
        }

        inline __attribute((always_inline)) MODNUM& operator += (const MODNUM& o) {return *this=*this+o;}
        inline __attribute((always_inline)) MODNUM& operator += (const MODINT_TYPE& o) {return *this=*this+o;}
        inline __attribute((always_inline)) MODNUM& operator -= (const MODNUM& o) {return *this=*this-o;}
        inline __attribute((always_inline)) MODNUM& operator -= (const MODINT_TYPE& o) {return *this=*this-o;}
        inline __attribute((always_inline)) MODNUM& operator *= (const MODNUM& o) {return *this=*this*o;}
        inline __attribute((always_inline)) MODNUM& operator *= (const MODINT_TYPE& o) {return *this=*this*o;}
        inline __attribute((always_inline)) MODNUM& operator /= (const MODNUM& o) {return *this=*this/o;}
        inline __attribute((always_inline)) MODNUM& operator /= (const MODINT_TYPE& o) {return *this=*this/o;}

        inline __attribute((always_inline)) operator MODINT_TYPE(){return val;}
    };
};