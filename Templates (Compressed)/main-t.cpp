#include<bits/stdc++.h>

// #define NOBUG
// #define ONLINE_JUDGE
#define il inline __attribute((always_inline)) 

#ifdef NOBUG
#define dbg(...) fprintf (stderr, __VA_ARGS__)
#else
#define dbg(...) void()
#endif

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;

#define getu(x) typename std::make_unsigned<x>::type
template<typename T=int>il T read(){getu(T)x=0;char c=getchar(),f=0;while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=x*10+(c&15),c=getchar();return f?-x:x;}char ous[50];template<typename T>il void print(const T&x){if(x==0)return putchar('0'),void();getu(T)y=x;if(x<0)y=-y,putchar('-');char*p=ous;while(y){*(p++)=y%10;y/=10;}while(p>ous)putchar(*(--p)|'0');}

void solve(){
    
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    int T=read();
    while(T--) solve();

    return 0;
}