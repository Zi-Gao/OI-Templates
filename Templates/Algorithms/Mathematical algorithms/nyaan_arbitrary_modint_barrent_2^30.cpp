struct Barrett {
    using u32 = unsigned int;
    using i64 = long long;
    using u64 = unsigned long long;
    u32 m;
    u64 im;
    Barrett() : m(), im() {}
    Barrett(int n) : m(n), im(u64(-1) / m + 1) {}
    constexpr inline i64 quo(u64 n) {
        u64 x = u64((__uint128_t(n) * im) >> 64);
        u32 r = n - x * m;
        return m <= r ? x - 1 : x;
    }
    constexpr inline i64 rem(u64 n) {
        u64 x = u64((__uint128_t(n) * im) >> 64);
        u32 r = n - x * m;
        return m <= r ? r + m : r;
    }
    constexpr inline std::pair<i64, int> quorem(u64 n) {
        u64 x = u64((__uint128_t(n) * im) >> 64);
        u32 r = n - x * m;
        if (m <= r) return {x - 1, r + m};
        return {x, r};
    }
    constexpr inline i64 pow(u64 n, i64 p) {
        u32 a = rem(n), r = m == 1 ? 0 : 1;
        while (p) {
            if (p & 1) r = rem(u64(r) * a);
            a = rem(u64(a) * a);
            p >>= 1;
        }
        return r;
    }
};

template <int id>
struct ArbitraryModIntBase {
    int x;

    ArbitraryModIntBase() : x(0) {}

    ArbitraryModIntBase(int64_t y) {
        int z = y % get_mod();
        if (z < 0) z += get_mod();
        x = z;
    }

    ArbitraryModIntBase &operator+=(const ArbitraryModIntBase &p) {
        if ((x += p.x) >= get_mod()) x -= get_mod();
        return *this;
    }

    ArbitraryModIntBase &operator-=(const ArbitraryModIntBase &p) {
        if ((x += get_mod() - p.x) >= get_mod()) x -= get_mod();
        return *this;
    }

    ArbitraryModIntBase &operator*=(const ArbitraryModIntBase &p) {
        x = rem((unsigned long long)x * p.x);
        return *this;
    }

    ArbitraryModIntBase &operator/=(const ArbitraryModIntBase &p) {
        *this *= p.inverse();
        return *this;
    }

    ArbitraryModIntBase operator-() const { return ArbitraryModIntBase(-x); }
    ArbitraryModIntBase operator+() const { return *this; }

    ArbitraryModIntBase operator+(const ArbitraryModIntBase &p) const {
        return ArbitraryModIntBase(*this) += p;
    }

    ArbitraryModIntBase operator-(const ArbitraryModIntBase &p) const {
        return ArbitraryModIntBase(*this) -= p;
    }

    ArbitraryModIntBase operator*(const ArbitraryModIntBase &p) const {
        return ArbitraryModIntBase(*this) *= p;
    }

    ArbitraryModIntBase operator/(const ArbitraryModIntBase &p) const {
        return ArbitraryModIntBase(*this) /= p;
    }

    bool operator==(const ArbitraryModIntBase &p) const { return x == p.x; }

    bool operator!=(const ArbitraryModIntBase &p) const { return x != p.x; }

    ArbitraryModIntBase inverse() const {
        int a = x, b = get_mod(), u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            std::swap(a -= t * b, b);
            std::swap(u -= t * v, v);
        }
        return ArbitraryModIntBase(u);
    }

    ArbitraryModIntBase pow(int64_t n) const {
        ArbitraryModIntBase ret(1), mul(x);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    int get() const { return x; }

    inline unsigned int rem(unsigned long long p) { return barrett().rem(p); }

    static inline Barrett &barrett() {
        static Barrett b;
        return b;
    }

    static inline int &get_mod() {
        static int mod = 0;
        return mod;
    }

    static void set_mod(int md) {
        assert(0 < md && md <= (1LL << 30) - 1);
        get_mod() = md;
        barrett() = Barrett(md);
    }
};

using mint=ArbitraryModIntBase<-1>;