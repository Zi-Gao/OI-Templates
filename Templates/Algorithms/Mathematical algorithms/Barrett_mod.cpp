using u32=unsigned int;
using u64=unsigned long long;
using u128=__uint128_t;

struct Barrett_Mod{
	u64 d,m;
    void init(u64 mod){d=mod,m=-d/d+1;}
    inline __attribute((always_inline)) u64 operator ()(const u64 &x) const {
        u64 w=x-u64(((u128)m*x)>>64)*d;
        if(w>=d) w-=d;
        return w;
    }
    inline __attribute((always_inline)) u64 operator /(const u64 &x) const {
        u64 w=((u128)m*x)>>64;
        if((w+1)*d<=x) ++w;
        return w;
    }
};