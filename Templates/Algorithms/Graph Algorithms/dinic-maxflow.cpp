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

const int N=510;
struct EDGE{
    int to,iv;
    i64 fl,cp;
};
std::vector<EDGE> e[N];

void addEdge(int u,int v,int cp){
	e[u].push_back({v,(int)e[v].size(),0,cp});
	e[v].push_back({u,(int)e[u].size()-1,0,0});
}

namespace MAXFLOW{
	const i64 INF=0x3f3f3f3f3f3f3f3fll;
	int s,t,n;
	int dep[N],nowc[N];

	bool bfs(){
		int i,u;
		std::queue<int> Q;
		for(i=0;i<=n;++i) dep[i]=nowc[i]=0;
		dep[s]=1;
		Q.push(s);
		while(!Q.empty()){
			u=Q.front(),Q.pop();
			for(auto [v,_,fl,cp]:e[u]) if(fl<cp&&!dep[v]) dep[v]=dep[u]+1,Q.push(v); 
		}
		return dep[t];
	}

	i64 flow(int u,i64 f){
		if(u==t||!f) return f;
		i64 d=0,r=0;
		while(nowc[u]<e[u].size()){
			auto &[v,iv,fl,cp]=e[u][nowc[u]];
			if(dep[v]==dep[u]+1&&(d=flow(v,std::min(f-r,cp-fl)))){
				fl+=d;
				e[v][iv].fl-=d;
				r+=d;
				if(r==f) return r;
			}
			nowc[u]++;
		}
		return r;
	}

	i64 get(int _s,int _t,int _n){
		s=_s,t=_t,n=_n;
		i64 res=0;
		while(bfs())
			res+=flow(s,INF);
		return res;
	}
}


int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    int i,u,v,cp;
    int n=read();
    int m=read();
    int s=read();
	int t=read();

    while(m--){
        u=read();v=read();cp=read();
        addEdge(u,v,cp);
    }

	print(MAXFLOW::get(s,t,n));

    return 0;
}