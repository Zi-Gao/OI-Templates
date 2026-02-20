## Algorithms

### Graph Algorithms

**dinic-maxflow.cpp**

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_int int
#define OUTPUT_int long long
INPUT_int read(){INPUT_int x=0;char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_int x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define FLOW_TYPE long long

const int NNNN=100010;
const FLOW_TYPE FLOW_INF=0x3f3f3f3f3f3f3f3fll;

struct EDGE{
	int to,invE;
	FLOW_TYPE flow,cap;
};

std::vector<EDGE> e[NNNN];

void addEdge(int u,int v,FLOW_TYPE cap){
	e[u].push_back((EDGE){v,e[v].size(),0,cap});
	e[v].push_back((EDGE){u,e[u].size()-1,0,0});
	return;
}

namespace MAXFLOW{
	int dep[NNNN],nowCur[NNNN],n,s,t;
	int bfs(){
		std::queue<int> Q;
		int i,u,v;
		for(i=1;i<=n;++i) dep[i]=nowCur[i]=0;
		dep[s]=1;
		Q.push(s);
		while(!Q.empty()){
			u=Q.front();
			Q.pop();
			for(auto edge:e[u]){
				if(!dep[v=edge.to]&&edge.cap>edge.flow){
					dep[v]=dep[u]+1;
					Q.push(v);
				}
			}
		}
		return dep[t];
	}

	FLOW_TYPE dfs(int u,FLOW_TYPE flow,int t){
		if((u==t)||(!flow)) return flow;
		int v;
		FLOW_TYPE cp,fl,d,res=0;
		for(;nowCur[u]<e[u].size();){
			auto &edge=e[u][nowCur[u]++];
			v=edge.to;
			cp=edge.cap;
			fl=edge.flow;
			if(dep[v]==dep[u]+1&&(d=dfs(v,std::min(cp-fl,flow-res),t))){
				res+=d;
				edge.flow+=d;
				e[v][edge.invE].flow-=d;
				if(res==flow) return res;
			}
		}
		return res;
	}

	FLOW_TYPE get(int _s,int _t,int _n){
		s=_s,t=_t,n=_n;
		FLOW_TYPE maxflow=0;
		while(bfs())
			maxflow+=dfs(s,FLOW_INF,t);
		return maxflow;
	}
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    int i,u,v,cap;
    int n=read();
    int m=read();
    int s=read();
    int t=read();

    for(i=0;i<m;++i){
        u=read();
        v=read();
        cap=read();
        addEdge(u,v,cap);
        addEdge(v,u,0);
    }

    print(MAXFLOW::get(s,t,n));

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

**isap-lim.cpp**

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_int int
#define OUTPUT_int long long
INPUT_int read(){INPUT_int x=0;char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_int x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define FLOW_TYPE long long

const int NNNN=100010;
const FLOW_TYPE FLOW_INF=0x3f3f3f3f3f3f3f3fll;

struct EDGE{
	int to,invE;
	FLOW_TYPE flow,cap;
};

std::vector<EDGE> e[NNNN];

void addEdge(int u,int v,FLOW_TYPE cap){
	e[u].push_back((EDGE){v,e[v].size(),0,cap});
	e[v].push_back((EDGE){u,e[u].size()-1,0,0});
	return;
}

namespace MAXFLOW{
	int dep[NNNN],nowCur[NNNN],dis[NNNN],cnt[NNNN],s,t,n;

	FLOW_TYPE sap(int u,FLOW_TYPE flow){
		if(u==t||!flow) return flow;
		int v;
		FLOW_TYPE cp,fl,d,res=0;
		for(;nowCur[u]<e[u].size();++nowCur[u]){
			auto &edge=e[u][nowCur[u]];
			v=edge.to,cp=edge.cap,fl=edge.flow;
			if(dis[u]==dis[v]+1&&(d=sap(v,std::min(cp-fl,flow-res)))){
				res+=d,edge.flow+=d,e[v][edge.invE].flow-=d;
				if(res==flow||dis[s]>=n) return res;
			}
		}
		if(!(--cnt[dis[u]])) dis[s]=n;
		cnt[++dis[u]]++;
		return res;
	}

	FLOW_TYPE get(int _s,int _t,int _n,FLOW_TYPE res=0){
		s=_s,t=_t,n=_n;
		int i;
		for(i=1;i<=n;++i) dis[i]=cnt[i]=0;
		while(dis[s]<n){
			for(i=1;i<=n;++i) nowCur[i]=0;
			res+=sap(s,FLOW_INF);
		}
		return res;
	}
}

FLOW_TYPE sum[NNNN];

void addEdge(int u,int v,FLOW_TYPE lo,FLOW_TYPE up){
    addEdge(u,v,up-lo);
    sum[v]+=lo,sum[u]-=lo;
    return;
}

FLOW_TYPE get(int s,int t,int n){
    int i,ss=n+1,tt=n+2;
    FLOW_TYPE cntF=0,res;
    for(i=1;i<=n;++i)
        if(sum[i]>0) addEdge(ss,i,sum[i]),cntF+=sum[i];
        else if(sum[i]<0) addEdge(i,tt,-sum[i]);

    addEdge(t,s,FLOW_INF);

    if(cntF!=MAXFLOW::get(ss,tt,tt)) return -1;
    else{
        res=e[t].back().flow;
        e[s].pop_back(),e[t].pop_back();
        return res+MAXFLOW::get(s,t,n);
    }
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    int i,ss,tt,u,v,lo,up,res;
    
    int n=read();
    int m=read();
    int s=read();
    int t=read();

    for(i=0;i<m;++i){
        u=read();v=read();lo=read(),up=read();
        addEdge(u,v,lo,up);
    }

    res=get(s,t,n);

    if(res==-1) printf("please go home to sleep");
    else print(res);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

**isap-maxflow.cpp**

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_int int
#define OUTPUT_int long long
INPUT_int read(){INPUT_int x=0;char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_int x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define FLOW_TYPE long long

const int NNNN=100010;
const FLOW_TYPE FLOW_INF=0x3f3f3f3f3f3f3f3fll;

struct EDGE{
	int to,invE;
	FLOW_TYPE flow,cap;
};

std::vector<EDGE> e[NNNN];

void addEdge(int u,int v,FLOW_TYPE cap){
	e[u].push_back((EDGE){v,e[v].size(),0,cap});
	e[v].push_back((EDGE){u,e[u].size()-1,0,0});
	return;
}

namespace MAXFLOW{
	int dep[NNNN],nowCur[NNNN],dis[NNNN],cnt[NNNN],s,t,n;

	FLOW_TYPE sap(int u,FLOW_TYPE flow){
		if(u==t||!flow) return flow;
		int v;
		FLOW_TYPE cp,fl,d,res=0;
		for(;nowCur[u]<e[u].size();++nowCur[u]){
			auto &edge=e[u][nowCur[u]];
			v=edge.to,cp=edge.cap,fl=edge.flow;
			if(dis[u]==dis[v]+1&&(d=sap(v,std::min(cp-fl,flow-res)))){
				res+=d,edge.flow+=d,e[v][edge.invE].flow-=d;
				if(res==flow||dis[s]>=n) return res;
			}
		}
		if(!(--cnt[dis[u]])) dis[s]=n;
		cnt[++dis[u]]++;
		return res;
	}

	FLOW_TYPE get(int _s,int _t,int _n,FLOW_TYPE res=0){
		s=_s,t=_t,n=_n;
		int i;
		for(i=1;i<=n;++i) dis[i]=cnt[i]=0;
		while(dis[s]<n){
			for(i=1;i<=n;++i) nowCur[i]=0;
			res+=sap(s,FLOW_INF);
		}
		return res;
	}
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    int i,u,v,cap;
    int n=read();
    int m=read();
    int s=read();
    int t=read();

    for(i=0;i<m;++i){
        u=read();
        v=read();
        cap=read();
        addEdge(u,v,cap);
        addEdge(v,u,0);
    }

    print(MAXFLOW::get(s,t,n));

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

**isap-mincost.cpp**

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_int int
#define OUTPUT_int long long
INPUT_int read(){INPUT_int x=0;char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_int x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define FLOW_TYPE long long

const int NNNN=100010;
const FLOW_TYPE FLOW_INF=0x3f3f3f3f3f3f3f3fll;

struct EDGE{
	int to,invE;
	FLOW_TYPE flow,cap,w;
};

std::vector<EDGE> e[NNNN];

void addEdge(int u,int v,FLOW_TYPE cap,FLOW_TYPE w){
	e[u].push_back((EDGE){v,e[v].size(),0,cap,w});
	e[v].push_back((EDGE){u,e[u].size()-1,0,0,-w});
	return;
}

namespace MAXFLOW{
	int dep[NNNN],nowCur[NNNN],s,t,n;
    FLOW_TYPE dis[NNNN];
    std::bitset<NNNN> vis;

    bool spfa(){
        int i,u,v;
        FLOW_TYPE cp,fl,w;
        std::queue<int> Q;
        for(i=0;i<=n;++i) dis[i]=FLOW_INF,vis[i]=0;
        dis[s]=0,Q.push(s);
        while(!Q.empty()){
            u=Q.front(),Q.pop();
            vis[u]=0;
            for(auto edge:e[u]){
                v=edge.to,fl=edge.flow,cp=edge.cap,w=edge.w;
                if(fl<cp&&dis[u]+w<dis[v]){
                    dis[v]=dis[u]+w;
                    if(!vis[v])
                        Q.push(v),vis[v]=1;
                }
            }
        }
        return dis[t]!=FLOW_INF;
    }

	FLOW_TYPE sap(int u,FLOW_TYPE flow){
		if(u==t||!flow) return flow;
        vis[u]=1;
		int v;
		FLOW_TYPE cp,fl,w,d,res=0;
		for(;nowCur[u]<e[u].size();++nowCur[u]){
			auto &edge=e[u][nowCur[u]];
			v=edge.to,cp=edge.cap,fl=edge.flow,w=edge.w;
			if((!vis[v])&&dis[u]+w==dis[v]&&(d=sap(v,std::min(cp-fl,flow-res)))){
				res+=d,edge.flow+=d,e[v][edge.invE].flow-=d;
				if(res==flow) return res;
			}
		}
		return res;
	}

	std::pair<FLOW_TYPE,FLOW_TYPE> get(int _s,int _t,int _n,FLOW_TYPE resFlow=0,FLOW_TYPE resCost=0){
		s=_s,t=_t,n=_n;
		FLOW_TYPE flow;
		int i;
		while(spfa()){
			for(i=0;i<=n;++i) nowCur[i]=vis[i]=0;
			resFlow+=(flow=sap(s,FLOW_INF));
            resCost+=flow*dis[t];
		}
		return {resFlow,resCost};
	}
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    int i,u,v,cap,w;
    int n=read();
    int m=read();
    int s=read();
    int t=read();

    for(i=0;i<m;++i){
        u=read();
        v=read();
        cap=read();
        w=read();
        addEdge(u,v,cap,w);
    }

    auto res=MAXFLOW::get(s,t,n);
    print(res.first),putchar(' '),print(res.second);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

### Mathematical algorithms

**Barrett_mod.cpp**

```cpp
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
```

**binary_gcd.cpp**

```cpp
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
```

**BSGS.cpp**

```cpp
#define BSGS_TYPE long long

BSGS_TYPE getLog(BSGS_TYPE a,BSGS_TYPE b,BSGS_TYPE p){
    std::unordered_map<BSGS_TYPE,BSGS_TYPE> mp;
    register BSGS_TYPE lim=std::ceil(std::sqrt(p)),now,pw;
    register int i;
    for(i=0,now=b,pw=1;i<=lim;++i,(now*=a)%=p){
        mp[now]=i;
        if(i) (pw*=a)%=p;
    }
    for(i=1,now=pw;i<=lim;++i,(now*=pw)%=p){
        auto it=mp.find(now);
        if(it!=mp.end()) return lim*i-it->second;
    }
    return -1;
}
```

**CRT.cpp**

```cpp
#define CRT_DATA_TPYE long long
CRT_DATA_TPYE CRT_exgcd(CRT_DATA_TPYE a,CRT_DATA_TPYE b,CRT_DATA_TPYE &x,CRT_DATA_TPYE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    CRT_DATA_TPYE d=CRT_exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

CRT_DATA_TPYE CRT_inv(CRT_DATA_TPYE n,CRT_DATA_TPYE p){
    CRT_DATA_TPYE x,y;
    CRT_exgcd(n,p,x,y);
    x%=p;
    return x>=0?x:x+p;
}

CRT_DATA_TPYE CRT(int n,CRT_DATA_TPYE *a,CRT_DATA_TPYE *mod){
    register int i;
    CRT_DATA_TPYE M=1,m,ans=0;
    for(i=0;i<n;++i) M*=mod[i];
    for(i=0;i<n;++i)
        m=M/mod[i],(ans+=a[i]*m%M*CRT_inv(m,mod[i]))%=M;
    return ans;
}
```

**det.cpp**

```cpp
#define DET_TYPE long long
DET_TYPE getDet(std::vector<DET_TYPE> *a,int n,const DET_TYPE mod){
    register int i,j,k;
    register char dt=1;
    register long long ans=1,x;
    for(i=0;i<n;++i)
        for(j=i+1;j<n;++j){
            while(a[i][i]){
                x=a[j][i]/a[i][i];
                for(k=i;k<n;++k)
                    a[j][k]=(a[j][k]+mod-x*a[i][k]%mod)%mod;
                std::swap(a[i],a[j]),dt^=1;
            }
            std::swap(a[i],a[j]),dt^=1;
        }
    for(i=0;i<n;++i) (ans*=a[i][i])%=mod;
    return (mod+(dt?ans:(mod-ans)))%mod;
}
```

**det_real.cpp**

```cpp
#define DET_TYPE double
const DET_TYPE det_eps=1e-8;
inline int det_cmp(DET_TYPE x){return fabs(x)<det_eps?0:(x<0?-1:1);}
DET_TYPE getDet_real(std::vector<DET_TYPE> *a,int n){
    register int i,j,k,max;
    register DET_TYPE ans=1,x;
    for(i=0;i<n;++i){
        max=i;
        for(j=i+1;j<=n;++j)if(det_cmp(a[max][i]-a[j][i])<0) max=i;
        if(max!=i) a[max].swap(a[i]);
        for(j=i+1;j<n;++j){
            x=a[j][i]/a[i][i];
            for(k=i;k<n;++k)
                a[j][k]-=x*a[i][k];
        }
    }
    for(i=0;i<n;++i)
        ans*=a[i][i];
    return ans;
}
```

**EulerSieve.cpp**

```cpp
const int EULER_SIZE=100010;

std::bitset<EULER_SIZE> notPri;
int phi[EULER_SIZE],mu[EULER_SIZE],sig_0[EULER_SIZE],num[EULER_SIZE],sig_1[EULER_SIZE],minPriS[EULER_SIZE];
std::vector<int> pris;

void eulerSieve(int n){
    register int cnt=0;
    register int i,j;
    phi[1]=mu[1]=sig_0[1]=sig_1[1]=notPri[1]=1;
    for(i=2;i<=n;++i){
        if(!notPri[i]){
            pris.push_back(i);
            phi[i]=i-1;
            mu[i]=-1;
            sig_0[i]=2;
            num[i]=1;
            sig_1[i]=minPriS[i]=i+1;
        }
        for(auto pri:pris){
            if(pri*i>n) break;
            notPri[pri*i]=1;
            if(!(i%pri)){
                phi[pri*i]=phi[i]*pri;
                mu[pri*i]=0;
                num[pri*i]=num[i]+1;
                sig_0[pri*i]=sig_0[i]/num[pri*i]*(num[pri*i]+1);
                minPriS[pri*i]=minPriS[i]*pri+1;
                sig_1[i*pri]=sig_1[i]/minPriS[i]*minPriS[pri*i];
                break;
            }
            phi[pri*i]=phi[i]*phi[pri];
            mu[pri*i]=-mu[i];
            num[pri*i]=1;
            sig_0[pri*i]=sig_0[i]<<1;
            sig_1[pri*i]=sig_1[pri]*sig_1[i];
            minPriS[pri*i]=pri+1;
        }
    }
    return;
}
```

**exCRT.cpp**

```cpp
#define EXCRT_DATA_TPYE long long
EXCRT_DATA_TPYE EXCRT_exgcd(EXCRT_DATA_TPYE a,EXCRT_DATA_TPYE b,EXCRT_DATA_TPYE &x,EXCRT_DATA_TPYE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    EXCRT_DATA_TPYE d=EXCRT_exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

EXCRT_DATA_TPYE exCRT(int n,EXCRT_DATA_TPYE *a,EXCRT_DATA_TPYE *mod){
    register int i;
    EXCRT_DATA_TPYE M=mod[0],A=a[0],p,q,gcd;
    for(i=1;i<n;++i){
        gcd=EXCRT_exgcd(mod[i],-M,p,q);
        if((A-a[i])%gcd)
            return -1;
        M=mod[i]/gcd*M;
        if(M<0) M=-M;
        A=((mod[i]*p%M*((A-a[i])/gcd)+a[i])%M+M)%M;
    }
    return A;
}
```

**exGCD.cpp**

```cpp
#define EXGCD_DATA_TYPE long long
EXGCD_DATA_TYPE exgcd(EXGCD_DATA_TYPE a,EXGCD_DATA_TYPE b,EXGCD_DATA_TYPE &x,EXGCD_DATA_TYPE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    EXGCD_DATA_TYPE d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
```

**exLucas.cpp**

```cpp
#define EXLC_TYPE long long

EXLC_TYPE exLC_exgcd(EXLC_TYPE a,EXLC_TYPE b,EXLC_TYPE &x,EXLC_TYPE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    EXLC_TYPE d=exLC_exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

EXLC_TYPE exLC_inv(EXLC_TYPE n,EXLC_TYPE p){
    EXLC_TYPE x,y;
    exLC_exgcd(n,p,x,y);
    x%=p;
    return x>=0?x:x+p;
}

long long exLC_a[100],exLC_mod[100],exLC_p,exLC_pk,pk_fact;

EXLC_TYPE exLC_qpow(register EXLC_TYPE base,register EXLC_TYPE e){
    register EXLC_TYPE res=1;
    base%=exLC_pk;
    while(e){
        if(e&1) (res*=base)%=exLC_pk;
        (base*=base)%=exLC_pk,e>>=1;
    }
    return res;
}

EXLC_TYPE mulPx(register EXLC_TYPE n){
    EXLC_TYPE res=1,i;
    while(n){
        (res*=exLC_qpow(pk_fact,n/exLC_pk))%=exLC_pk;
        for(i=exLC_pk*(n/exLC_pk);i<=n;++i) if(i%exLC_p) (res*=i%exLC_pk)%=exLC_pk;
        n/=exLC_p;
    }
    return res;
}

EXLC_TYPE getE(register EXLC_TYPE n){
    register EXLC_TYPE res=0;
    while(n>=exLC_p) res+=n/exLC_p,n/=exLC_p;
    return res;
}

EXLC_TYPE CPK(register EXLC_TYPE n,register EXLC_TYPE m,const register EXLC_TYPE _p,const register EXLC_TYPE _pk){
    register EXLC_TYPE i;
    exLC_p=_p,exLC_pk=_pk;
    for(i=pk_fact=1;i<exLC_pk;++i) if(i%exLC_p) (pk_fact*=i%exLC_pk)%=exLC_pk;
    register EXLC_TYPE A=mulPx(n),invB=exLC_inv(mulPx(m),exLC_pk),invC=exLC_inv(mulPx(n-m),exLC_pk),pw=exLC_qpow(exLC_p,getE(n)-getE(m)-getE(n-m));
    return A*invB%exLC_pk*invC%exLC_pk*pw%exLC_pk;
}

EXLC_TYPE CExLC(register EXLC_TYPE n,register EXLC_TYPE m,const register EXLC_TYPE p){
    register EXLC_TYPE cp=p,cnt=0,ans=0,i,pk,tm;
    for(i=2;i*i<=cp;++i)
        if(!(cp%i)){
            pk=1;
            while(!(cp%i)) pk*=i,cp/=i;
            exLC_mod[cnt]=pk,exLC_a[cnt++]=CPK(n,m,i,pk);
        }
    if(cp!=1) exLC_mod[cnt]=cp,exLC_a[cnt++]=CPK(n,m,cp,cp);
    for(i=0;i<cnt;++i) tm=p/exLC_mod[i],(ans+=exLC_a[i]*tm%p*exLC_inv(tm,exLC_mod[i]))%=p;
    return ans;
}
```

**flSum.cpp**

```cpp
#define FLSUM_TYPE long long
const FLSUM_TYPE FLSUM_MOD=mod;
FLSUM_TYPE flSum(FLSUM_TYPE n,FLSUM_TYPE a,FLSUM_TYPE b,FLSUM_TYPE c){
	FLSUM_TYPE ac=a/c,bc=b/c,m=(a*n+b)/c;
	if(!a) return (n+1)*bc%FLSUM_MOD;
	if(a>=c||b>=c) return (n*(n+1)/2%FLSUM_MOD*ac+(n+1)*bc+flSum(n,a%c,b%c,c))%FLSUM_MOD;
	return (m*n+FLSUM_MOD-flSum(m-1,c,c-b-1,a))%FLSUM_MOD;
}
```

**FWT.cpp**

```cpp
const long long FWT_MOD=998244353;

void FWT_MUL(long long *A,long long *B,int n){
    register int i;
    for(i=0;i<n;++i) (A[i]*=B[i])%=FWT_MOD;
    return;
}

void FWT_OR(long long *f,long long x,int n){
    register int i,j,k,o;
    for(o=2,k=1;o<=n;o<<=1,k<<=1)
        for(i=0;i<n;i+=o)
            for(j=0;j<k;++j)
                (f[i+j+k]+=f[i+j]*x)%=FWT_MOD;
    return;
}

void FWT_AND(long long *f,long long x,int n){
    register int i,j,k,o;
    for(o=2,k=1;o<=n;o<<=1,k<<=1)
        for(i=0;i<n;i+=o)
            for(j=0;j<k;++j)
                (f[i+j]+=f[i+j+k]*x)%=FWT_MOD;
    return;
}

void FWT_XOR(long long *f,long long x,int n){
    register int i,j,k,o;
    for(o=2,k=1;o<=n;o<<=1,k<<=1)
        for(i=0;i<n;i+=o)
            for(j=0;j<k;++j)
                f[i+j]+=f[i+j+k],
                f[i+j+k]=f[i+j]-f[i+j+k]+FWT_MOD-f[i+j+k],
                (f[i+j]*=x)%=FWT_MOD,(f[i+j+k]*=x)%=FWT_MOD;
    return;
}
```

**inv_n.cpp**

```cpp
#define INV_DATA_TYPE long long

void getinv(INV_DATA_TYPE *invs,INV_DATA_TYPE p,int n){
    register int i;
    invs[0]=0;
    invs[1]=1;

    for(i=2;i<=n;++i){
        invs[i]=p-p/i*invs[p%i]%p;
    }

    return;
}
```

**miller_rabin.cpp**

```cpp
long long mrPri[7]={2,325,9375,28178,450775,9780504,1795265022};
inline __attribute((always_inline)) long long mrQpow(__int128_t b,__int128_t e,long long mod){
    register __int128_t res=1;
    b%=mod;
    while(e){
        if(e&1) (res*=b)%=mod;
        (b*=b)%=mod;
        e>>=1;
    }
    return res;
}
bool millerRabin(long long n){
    if(n<3||(!(n&1))) return n==2;
    register int i;
    register long long u=n-1,t=0,v,s;
    while(!(u&1)) u/=2,++t;
    for(i=0;i<7;++i){
        v=mrQpow(mrPri[i],u,n);
        if(v==0||v==1||v==n-1) continue;
        for(s=0;s<t;++s){
            if(v==n-1) break;
            v=(__int128_t)v*v%n;
        }
        if(s==t) return false;
    }
    return true;
}
```

**pol_fft.cpp**

```cpp
const long long NTTp=998244353;
const long long NTTg=3;
const long long NTTInvg=332748118;
const int POL_SIZE=4000000;

double FFTPI=acos(-1);

struct POL{
    int len,FFTLen,rev[POL_SIZE];
    std::complex<double> items[POL_SIZE];

    void initRev(int k){
        register int i;
        for(i=0;i<FFTLen;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
        return;
    }
    int initLen(){
        register int k=0;
        FFTLen=1;
        while(FFTLen<=len) ++k,FFTLen<<=1;
        return k;
    }
    void init(){initRev(initLen());}

    void fft(char flg){
        register int i,l,j,k;
        register std::complex<double> w1,w,x,y;
        for(i=0;i<FFTLen;++i) if(i<rev[i]) std::swap(items[i],items[rev[i]]);
        for(l=1;l<FFTLen;l<<=1)
            for(j=0,w1=exp(std::complex<double>(0,FFTPI*flg/l));j<FFTLen;j+=(l<<1))
                for(k=j,w=1;k<j+l;++k,w*=w1){
                    x=items[k];
                    y=w*items[k+l];
                    items[k]=x+y;
                    items[k+l]=x-y;
                }
        if(flg==-1) for(i=0;i<FFTLen;++i) items[i]/=FFTLen;

        return;
    }

    friend POL operator * (POL a,POL b){
        register int i;
        a.len=b.len=a.len+b.len;
        a.init(),b.init();
        a.fft(1);
        b.fft(1);
        for(i=0;i<a.FFTLen;++i) a.items[i]*=b.items[i];
        a.fft(-1);
        return a;
    }

	void clear(){
		for(register int i=0;i<=len;++i) items[i]=0;
		len=0;
		return;
	}
};
```

**pol_ntt.cpp**

```cpp
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


namespace POL{
    // #define forceIl
    #define forceIl inline __attribute((always_inline))

    using u32=unsigned int;
    using i64=long long;
    using u64=unsigned long long;

    const u32 NTTp=998244353;
    const u32 NTTphi=NTTp-1;
    const u32 NTTg=3;
    const u32 NTTInvg=332748118;
    const int POL_SIZE=4000000;

    int rev[POL_SIZE],NTTLen,NTTk,nowInv;
    u32 W[2][30],invs[POL_SIZE];

    forceIl int ln2(int x){return 31^__builtin_clz(x);}
    forceIl u32& reduce(u32 &x){
        if(x>=NTTp) x-=NTTp;
        return x;
    }
    forceIl u32 qpow(u32 base,u32 e){
        u32 res=1;
        while(e){
            if(e&1) res=(u64)res*base%NTTp;
            base=(u64)base*base%NTTp;
            e>>=1;
        }
        return res;
    }
    forceIl u32 invNum(u32 n){return qpow(n,NTTp-2);}
    forceIl void init(){
        int i=0,lg=ln2(POL_SIZE);
        for(i=0;i<=lg;++i)
            W[0][i]=qpow(NTTg,(NTTp-1)/(2<<i)),
            W[1][i]=qpow(NTTInvg,(NTTp-1)/(2<<i));
        nowInv=2,invs[1]=1;
    }
    forceIl void initInv(int k){
        int i;
        for(i=nowInv;i<=k;++i) invs[i]=NTTp-(u64)NTTp/i*invs[NTTp%i]%NTTp;
        nowInv=i;
    }
    forceIl void qInit(int len){
        NTTLen=1<<(NTTk=ln2(len));
        if(NTTLen<len) NTTLen*=2,++NTTk;
    }
    forceIl void initLen(int len){
        int i;
        qInit(len);
        for(i=0;i<NTTLen;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(NTTk-1));
        return;
    }

    struct Poly{
        std::vector<u32> items;

        forceIl void push_back(u32 x){items.push_back(x);}
        forceIl void pop_back(){items.pop_back();}
        forceIl int size() const {return items.size();}
        forceIl void resize(int x){items.resize(x);}
        forceIl void resize(int x,u32 v){items.resize(x,v);}
        forceIl void clear(){items.clear();}
        forceIl void reverse(){std::reverse(items.begin(),items.end());}
        forceIl u32& operator [] (const int x){return items[x];}
        forceIl u32 operator [] (const int x) const {return items[x];}

        forceIl Poly operator + (const Poly &o) const{
            int i;
            Poly res;
            res=*this;
            res.resize(std::max(size(),o.size()));
            for(i=0;i<o.size();++i) reduce(res[i]+=o[i]);
            return res;
        }
        forceIl Poly operator + (const u32 &o) const{
            Poly res=*this;
            reduce(res[0]+=o);
            return res;
        }
        forceIl friend Poly operator + (const u32 &o,const Poly &x){return x+o;}
        forceIl Poly operator - (const Poly &o) const{
            int i;
            Poly res;
            res=*this;
            res.resize(std::max(size(),o.size()));
            for(i=0;i<o.size();++i) reduce(res[i]+=NTTp-o[i]);
            return res;
        }
        forceIl Poly operator - (const u32 &o) const{
            Poly res=*this;
            reduce(res[0]+=NTTp-o);
            return res;
        }
        forceIl friend Poly operator - (const u32 &o,Poly x){
            for(auto &i:x.items) reduce(i=NTTp-i);
            reduce(x[0]+=o);
            return x;
        }
        forceIl friend Poly operator * (const u32 &o,const Poly &x){return o*x;}
        forceIl friend Poly operator / (const u32 &o,const Poly &x){return x.inv()*o;}

        forceIl Poly deriv() const{
            Poly res=*this;
            if(items.empty()) return res;
            int i;
            for(i=1;i<size();++i) res[i-1]=(u64)res[i]*i%NTTp;
            res.pop_back();
            return res;
        }
        forceIl Poly integ() const{
            Poly res=*this;
            if(items.empty()) return res;
            int i;
            initInv(size());
            res.push_back(0);
            for(i=size();~i;--i) res[i]=(u64)res[i-1]*invs[i]%NTTp;
            return res;
        }

        forceIl Poly xPow(int k,int len){
            Poly res;
            res.resize(len);
            for(int i=0;i*k<len;++i) res[i*k]=items[i];
            return res;
        }
        forceIl Poly xPow(int k){return xPow(k,(size()-1)*k+1);}
        
        forceIl Poly shift(int k,int len){
            Poly res;
            res.resize(len);
            for(int i=0;i+k<len;++i) res[i+k]=items[i];
            return res;
        }
        forceIl Poly shift(int k){return shift(k,size()+k);}

        forceIl friend Poly operator * (Poly A,Poly B){
            int i,j,len=A.size()+B.size();

            if((i64)A.size()*B.size()<=(len*ln2(len)*6)){
                Poly res;
                res.resize(len);
                for(i=0;i<A.size();++i) for(j=0;j<B.size();++j)
                    res[i+j]=(res[i+j]+(u64)A[i]*B[j])%NTTp;
                return res;
            }else{
                qInit(len);
                A.resize(NTTLen);
                B.resize(NTTLen);
                qntt2(A,B,0);
                for(i=0;i<NTTLen;++i) A[i]=(u64)A[i]*B[i]%NTTp;
                A.qntt(1);
                A.resize(len);
                return A;
            }
        }
        forceIl Poly operator * (const u32 o) const{
            Poly res=*this;
            for(auto &item:res.items) item=(u64)item*o%NTTp;
            return res;
        }

        forceIl friend Poly operator / (Poly F,Poly G){
            int n=F.size(),m=G.size();
            F.reverse(),G.reverse();
            F.resize(n-m+1);
            G.resize(n-m+1);
            F=F*G.inv();
            F.resize(n-m+1);
            F.reverse();
            return F;
        }
        forceIl Poly operator / (u32 o) const{
            Poly res=*this;
            o=invNum(o);
            for(auto &item:res.items) item=(u64)item*o%NTTp;
            return res;
        }

        forceIl Poly operator % (const Poly &G) const{
            Poly res=*this-G*(*this/G);
            res.resize(G.size()-1);
            return res;
        }
        forceIl std::pair<Poly,Poly> getDiv(const Poly &G) const{
            Poly P=*this/G;
            Poly Q=*this-P*G;
            Q.resize(G.size()-1);
            return {P,Q};
        }

        forceIl Poly inv() const{
            int i,len,L=1,l,j,k;
            u32 w1,w,x,y;
            Poly A,B;
            while(L<size()) L<<=1;
            B.resize(1);
            B[0]=invNum(items[0]);
            for(len=2;len<=L;len<<=1){
                A.clear(),A.resize(len*2);
                for(i=0;i<std::min(size(),len);++i) A[i]=items[i];
                
                qInit(len<<1);
                A.resize(NTTLen),B.resize(NTTLen);
                qntt2(A,B,0);

                for(i=0;i<NTTLen;++i) B[i]=(2+NTTp-(u64)B[i]*A[i]%NTTp)*B[i]%NTTp;
                B.qntt(1);
                B.resize(len);
            }
            B.resize(size());
            return B;
        }

        forceIl Poly ln() const{
            Poly res=(deriv()*inv()).integ();
            res.resize(size());
            return res;
        }
        forceIl Poly exp() const{
            int i=0,len,L=1;
            Poly A,B;
            while(L<size()) L<<=1;
            B.resize(1);
            B[0]=1;
            for(len=1;len<=L;len<<=1){
                A.resize(len);
                for(;i<std::min(size(),len);++i) A[i]=items[i];
                B=B*(A-B.ln()+1);
            }
            B.resize(size());
            return B;
        }
        forceIl Poly pow(u32 e,u32 ephi,int p) const{
            int i;
            u32 x,invX;
            Poly res=*this;

            invX=invNum(x=items[p]);
            res.items.erase(res.items.begin(),res.items.begin()+p);
            for(auto &item:res.items) item=(u64)item*invX%NTTp;
            res=res.ln();
            for(auto &item:res.items) item=(u64)item*e%NTTp;
            res=res.exp();
            
            x=qpow(x,ephi);
            for(auto &item:res.items) item=(u64)item*x%NTTp;

            std::vector<u64> now;
            for(i=0;i<e*p;++i) now.push_back(0);
            res.items.insert(res.items.begin(),now.begin(),now.end());

            return res;
        }
        forceIl Poly operator ^ (const char *s) const{
            int i=0,p;
            u32 e=0,ephi=0;
            for(p=0;p<size();++p)
                if(items[p]) break;
            while(s[i]){
                if((e*10+(s[i]&15))*p>=size()){
                    Poly res;
                    res.resize(size());
                    return res;
                }
                e=((u64)e*10+(s[i]&15))%NTTp;
                ephi=((u64)ephi*10+(s[i]&15))%NTTphi;
                ++i;
            }
            if(p==size()){
                Poly res;
                res.resize(1,1);
                res.resize(size());
                return res;
            }
            return pow(e,ephi,p);
        }
        forceIl Poly operator ^ (u32 e) const{
            int p;
            for(p=0;p<size();++p)
                if(items[p]) break;
            if(p==size()&&e==0){
                Poly res;
                res.resize(1,1);
                res.resize(size());
                return res;
            }
            if(p&&(e>=size()||e*p>=size())){
                Poly res;
                res.resize(size());
                return res;
            }
            return pow(e%NTTp,e%NTTphi,p);
        }

        forceIl Poly sqrt(){
            int i=0,len,L=1;
            Poly A,B;
            while(L<size()) L<<=1;
            B.resize(1,1);
            for(len=1;len<=L;len<<=1){
                A.resize(len);
                for(;i<std::min(size(),len);++i) A[i]=items[i];
                B=(A*B.inv()+B)/2;
            }
            B.resize(size());
            return B;
        }

        friend void mul(int p,int l,int r,std::vector<u32> &x,std::vector<Poly> &pols){
            if(l==r){
                if(pols.size()<=p) pols.resize(p+1);
                pols[p].push_back(NTTp-x[l]);
                pols[p].push_back(1);
                return;
            }
            int mid=(l+r)>>1,lc=p<<1,rc=p<<1|1;
            mul(lc,l,mid,x,pols),mul(rc,mid+1,r,x,pols);
            pols[p]=pols[lc]*pols[rc];
            pols[p].pop_back();
        }

        forceIl Poly subMul(Poly a,Poly b) const {
            int i;
            int n=a.size();
            int m=b.size();
            std::reverse(b.items.begin(),b.items.end());
            b=a*b;
            for(i=0;i<n;++i) a[i]=b[i+m-1];
            return a;
        }
        void initVals(int p,int l,int r,std::vector<u32> &x,std::vector<Poly> &pols) const {
            if(l==r){
                if(pols.size()<=p) pols.resize(p+1);
                pols[p].push_back(1);
                pols[p].push_back(NTTp-x[l]);
                return;
            }
            int mid=(l+r)>>1,lc=p<<1,rc=p<<1|1;
            initVals(lc,l,mid,x,pols),initVals(rc,mid+1,r,x,pols);
            pols[p]=pols[lc]*pols[rc];
            pols[p].pop_back();
        }
        void solveEval(int p,int l,int r,Poly now,std::vector<u32> &res,std::vector<Poly> &pols) const {
            if(l==r){
                res[l]=now[0];
                return;
            }
            now.resize(r-l+1);
            int mid=(l+r)>>1,lc=p<<1,rc=p<<1|1;
            solveEval(lc,l,mid,subMul(now,pols[rc]),res,pols);
            solveEval(rc,mid+1,r,subMul(now,pols[lc]),res,pols);
            return;
        }
        forceIl std::vector<u32> eval(std::vector<u32> x) const{
            if(x.empty()) return std::vector<u32>();
            int n=std::max(size(),(int)x.size());
            int m=x.size();
            Poly pol=*this;
            std::vector<Poly> pols;
            std::vector<u32> res;
            x.resize(n),res.resize(n);
            initVals(1,0,n-1,x,pols);
            solveEval(1,0,n-1,subMul(pol,pols[1].inv()),res,pols);
            res.erase(res.begin()+m,res.end());
            return res;
        }

        Poly solveInterp(int p,int l,int r,std::vector<u32> &y,std::vector<u32> &vals,std::vector<Poly> &pols) const {
            if(l==r){
                Poly res;
                res.push_back((u64)y[l]*invNum(vals[l])%NTTp);
                return res;
            }
            int mid=(l+r)>>1,lc=p<<1,rc=p<<1|1;
            return solveInterp(lc,l,mid,y,vals,pols)*pols[rc]+solveInterp(rc,mid+1,r,y,vals,pols)*pols[lc];
        }
        forceIl void interp(std::vector<u32> x,std::vector<u32> y){
            if(x.empty()){
                clear();
                return;
            }
            std::vector<Poly> pols;
            std::vector<u32> vals;
            mul(1,0,x.size()-1,x,pols);
            Poly H=pols[1];
            vals=H.deriv().eval(x);
            *this=solveInterp(1,0,x.size()-1,y,vals,pols);
            resize(x.size());
            return;
        }

        forceIl void ntt(int flg){//0: DFT  1:IDFT
            int i,l,j,k,lg;
            u32 w,t;
            for(i=0;i<NTTLen;++i) if(i<rev[i]) std::swap(items[i],items[rev[i]]);
            for(l=1,lg=0;l<NTTLen;l<<=1,++lg)
                for(j=0;j<NTTLen;j+=(l<<1))
                    for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                        t=(u64)w*items[k+l]%NTTp;
                        reduce(items[k+l]=items[k]+NTTp-t);
                        reduce(items[k]+=t);
                    }
            if(flg){
                t=invNum(NTTLen);
                for(auto &item:items) item=(u64)item*t%NTTp;
            }
        }

        forceIl friend void ntt2(Poly &A,Poly &B,char flg){ 
            int i,l,j,k,lg;
            u32 w,t;
            for(i=0;i<NTTLen;++i) if(i<rev[i]) std::swap(A.items[i],A.items[rev[i]]),std::swap(B.items[i],B.items[rev[i]]);
            for(l=1,lg=0;l<NTTLen;l<<=1,++lg)
                for(j=0;j<NTTLen;j+=(l<<1))
                    for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                        t=(u64)w*A.items[k+l]%NTTp;
                        reduce(A.items[k+l]=A.items[k]+NTTp-t);
                        reduce(A.items[k]+=t);
                        t=(u64)w*B.items[k+l]%NTTp;
                        reduce(B.items[k+l]=B.items[k]+NTTp-t);
                        reduce(B.items[k]+=t);
                    }
            if(flg){
                t=invNum(NTTLen);
                for(auto &item:A.items) item=(u64)item*t%NTTp;
                for(auto &item:B.items) item=(u64)item*t%NTTp;
            }
        }

        forceIl void qntt(char flg){//0: DFT  1:IDFT
            int i,l,j,k,lg;
            u32 w,t;
            if(flg==0){
                for(l=NTTLen/2,lg=NTTk-1;l;l>>=1,--lg)
                    for(j=0;j<NTTLen;j+=(l<<1))
                        for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                            t=(u64)(items[k]-items[k+l]+NTTp)*w%NTTp;
                            reduce(items[k]+=items[k+l]);
                            items[k+l]=t;
                        }
            }else{
                for(l=1,lg=0;l<NTTLen;l<<=1,++lg)
                    for(j=0;j<NTTLen;j+=(l<<1))
                        for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                            t=(u64)w*items[k+l]%NTTp;
                            reduce(items[k+l]=items[k]+NTTp-t);
                            reduce(items[k]+=t);
                        }
                t=invNum(NTTLen);
                for(auto &item:items) item=(u64)item*t%NTTp;
            }
        }

        forceIl friend void qntt2(Poly &A,Poly &B,char flg){
            int i,l,j,k,lg;
            u32 w,t;
            if(flg==0){
                for(l=NTTLen/2,lg=NTTk-1;l;l>>=1,--lg)
                    for(j=0;j<NTTLen;j+=(l<<1))
                        for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                            t=(u64)(A.items[k]-A.items[k+l]+NTTp)*w%NTTp;
                            reduce(A.items[k]+=A.items[k+l]);
                            A.items[k+l]=t;
                            t=(u64)(B.items[k]-B.items[k+l]+NTTp)*w%NTTp;
                            reduce(B.items[k]+=B.items[k+l]);
                            B.items[k+l]=t;
                        }
            }else{
                for(l=1,lg=0;l<NTTLen;l<<=1,++lg)
                    for(j=0;j<NTTLen;j+=(l<<1))
                        for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                            t=(u64)w*A.items[k+l]%NTTp;
                            reduce(A.items[k+l]=A.items[k]+NTTp-t);
                            reduce(A.items[k]+=t);
                            t=(u64)w*B.items[k+l]%NTTp;
                            reduce(B.items[k+l]=B.items[k]+NTTp-t);
                            reduce(B.items[k]+=t);
                        }
                t=invNum(NTTLen);
                for(auto &item:A.items) item=(u64)item*t%NTTp;
                for(auto &item:B.items) item=(u64)item*t%NTTp;
            }
        }
    };

    struct INIT{
        INIT(){init();}
    }INITS;
};
using POL::Poly;

Poly A,B;
char s[200000];
std::vector<u32> x,y;


int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif


    // P3803 【模板】多项式乘法（FFT）
    // int i;
    // int n=read();
    // int m=read();
    // A.resize(n+1),B.resize(m+1);
    // for(i=0;i<=n;++i) A[i]=read();
    // for(i=0;i<=m;++i) B[i]=read();
    // A=A*B;
    // for(i=0;i<=n+m;++i) print(A[i]),putchar(' ');

    //P4238 【模板】多项式乘法逆
    // int i;
    // int n=read();
    // A.resize(n);
    // for(i=0;i<n;++i) A.items[i]=read();
    // A=A.inv();
    // for(i=0;i<n;++i) print(A[i]),putchar(' ');

    //P4512 【模板】多项式除法
    // int i;
    // int n=read();
    // int m=read();
    // A.resize(n+1),B.resize(m+1);
    // for(i=0;i<=n;++i) A[i]=read();
    // for(i=0;i<=m;++i) B[i]=read();
    // auto res=A.getDiv(B);
    // for(i=0;i<=n-m;++i) print(res.first[i]),putchar(' ');
    // putchar('\n');
    // for(i=0;i<=m-1;++i) print(res.second[i]),putchar(' ');

    //P4725 【模板】多项式对数函数（多项式 ln）
    // int i;
    // int n=read();
    // A.resize(n);
    // for(i=0;i<n;++i) A.items[i]=read();
    // A=A.ln();
    // for(i=0;i<n;++i) print(A.items[i]),putchar(' ');;

    //P4726 【模板】多项式指数函数（多项式 exp）
    // int i;
    // int n=read();
    // A.resize(n);
    // for(i=0;i<n;++i) A.items[i]=read();
    // A=A.exp();
    // for(i=0;i<n;++i) print(A.items[i]),putchar(' ');

    //P5273 【模板】多项式幂函数（加强版）
    // int i;
    // int n=read();
    // scanf("%s",s);
    // A.resize(n);
    // for(i=0;i<n;++i) A[i]=read();
    // A=A^s;
    // for(i=0;i<n;++i) print(A[i]),putchar(' ');

    //P5205 【模板】多项式开根
    // int i;
    // int n=read();
    // A.resize(n);
    // for(i=0;i<n;++i) A[i]=read();
    // A=A.sqrt();
    // for(i=0;i<n;++i) print(A[i]),putchar(' ');

    //P5050 【模板】多项式多点求值
    // int i;
    // int n=read();
    // int m=read();
    // A.resize(n+1);
    // for(i=0;i<=n;++i) A[i]=read();
    // for(i=0;i<m;++i) x.push_back(read());

    // auto res=A.eval(x);
    // for(auto val:res) print(val),putchar('\n');

    //P5158 【模板】多项式快速插值
    // int i;

    // int n=read();
    // x.resize(n),y.resize(n);
    // for(i=0;i<n;++i){
    //     x[i]=read();y[i]=read();
    // }
    // A.interp(x,y);

    // for(i=0;i<n;++i) print(A[i]),putchar(' ');

    return 0;
}
```

**xor_shift.cpp**

```cpp
/*
(13, 17, 5), 
(3, 13, 7), 
(13, 17, 15)
*/
u32 xorshift32(u32 x) {
    x^=x<<13;
    x^=x>>17;
    x^=x<<5;
    return x;
}


/*
(13, 7, 17), 
(21, 35, 4), 
(13, 11, 25)
*/
u64 xorshift64(u64 x) {
    x^=x<<13;
    x^=x>>7;
    x^=x<<17;
    return x;
}
```

### Strings algorithms

**ac.cpp**

```cpp
#include<queue>
#include<vector>
#include<cstring>
#define AC_TYPE char
const int AC_DATA_SIZE=26;
const int AC_TREE_SIZE=200000+10;

struct AC{
    std::vector<int> failtree[AC_TREE_SIZE];
    int next[AC_TREE_SIZE][AC_DATA_SIZE],fail[AC_TREE_SIZE],add[AC_TREE_SIZE],tot[AC_TREE_SIZE],cnt,id;

    void addEdge(int u,int v){
        failtree[u].push_back(v);
    }

    void insert(char *s,int len){
        register int pos=0,i;
        for(i=0;i<len;++i)
            pos=(next[pos][s[i]]?next[pos][s[i]]:(next[pos][s[i]]=(++cnt)));
        add[++id]=pos;
        return;
    }

    void build(){
        std::queue<int> Q;
        register int i,u;
        for(i=0;i<AC_DATA_SIZE;++i)
            if(next[0][i]) Q.push(next[0][i]);
        while(!Q.empty()){
            u=Q.front();
            Q.pop();
            for(i=0;i<AC_DATA_SIZE;++i)
                if(next[u][i]){
                    fail[next[u][i]]=next[fail[u]][i];
                    Q.push(next[u][i]);
                }else next[u][i]=next[fail[u]][i];
        }
        return;
    }

    void dfs(int u){
        for(auto v:failtree[u]){
            dfs(v);
            tot[u]+=tot[v];
        }
        return;
    }

    void find(char *s,int len){
        register int pos=0,i;
        for(i=0;i<len;++i){
            pos=next[pos][s[i]];
            ++tot[pos];
        }

        for(i=1;i<=cnt;++i) addEdge(fail[i],i);

        dfs(0);
        return;
    }
};
```

**kmp.cpp**

```cpp
void getkmp(int n,char *str,int *nxt){
	register int i,j;
	for(i=2,j=0;i<=n;++i){
        while(j&&str[i]!=str[j+1]) j=nxt[j];
        if(str[i]==str[j+1]) ++j;
        nxt[i]=j;
	}
}

void getmatch(int n,int m,char *pat,char *txt,int *nxt){
    register int i,j;

    for(i=1,j=0;i<=m;++i){
        while(j&&txt[i]!=pat[j+1]) j=nxt[j];
        if(txt[i]==pat[j+1]) ++j;
        if(j==n){
            /*something*/
            j=nxt[j];
        }
    }
}
```

**manacher.cpp**

```cpp
const int MA_SIZE=2200'0010;
const char MA_ch='#';

int Ma_d[MA_SIZE];
char Ma_s[MA_SIZE];

void Manacher(int len,char *s,int *d1,int *d2){
    register int i,l=0,r=-1,k,n=len<<1;
    for(i=0;i<=n;++i)
        if(i&1) Ma_s[i]=s[i>>1];
        else Ma_s[i]=MA_ch;
    for(i=0;i<n;++i){
        k=(i>r)?1:std::min(Ma_d[l+r-i],r-i+1);
        while(0<=i-k&&i+k<=n&&Ma_s[i-k]==Ma_s[i+k]) ++k;
        Ma_d[i]=--k;
        if(i+k>r) l=i-k,r=i+k;
        if(i&1) d1[i>>1]=k;
        else d2[i>>1]=k;
    }
    return;
}
```

**sa.cpp**

```cpp
const int SA_SIZE=100010;
int oldrk[SA_SIZE<<1],cnt[SA_SIZE],id[SA_SIZE];
void solveSA(int n,char *s,int *sa,int *rk){
    register int i,p=0,l,max;
    for(i=1;i<=n;++i) sa[i]=i,p=std::max(p,rk[i]=s[i]);

    for(l=0;l<n;l=std::max(1,l*2)){
        memcpy(oldrk,rk,sizeof(int)*(n+1));

        max=p,p=0;
        memset(cnt,0,sizeof(int)*(max+1));

        for(i=n-l+1;i<=n;++i) id[++p]=i;
        for(i=1;i<=n;++i) if(sa[i]>l) id[++p]=sa[i]-l;

        for(i=1;i<=n;++i) ++cnt[rk[i]];
        for(i=1;i<=max;++i) cnt[i]+=cnt[i-1];
        for(i=n;i;--i) sa[cnt[rk[id[i]]]--]=id[i];

        for(i=1,p=0;i<=n;++i) rk[sa[i]]=(p+=(oldrk[sa[i]]!=oldrk[sa[i-1]]||oldrk[sa[i]+l]!=oldrk[sa[i-1]+l]));

        if(p==n) break;
    }
    return;
}
```

**sam.cpp**

```cpp
const int N=1000010;

struct SAM{
    int len[N<<1],link[N<<1],nxt[N<<1][26],lat,cnt;
    void init(){
        lat=cnt=1;
    }
    int add(char c){
        int u=++cnt,v,p=lat,q;
        len[u]=len[lat]+1;
        while(p&&!nxt[p][c]) nxt[p][c]=u,p=link[p];
        if(!p) link[u]=1;
        else{
            q=nxt[p][c];
            if(len[p]+1==len[q]) link[u]=q;
            else{
                link[v=++cnt]=link[q],len[v]=len[p]+1;
                link[u]=link[q]=v;
                memcpy(nxt[v],nxt[q],sizeof(nxt[v]));
                while(p&&nxt[p][c]==q) nxt[p][c]=v,p=link[p];
            }
        }
        return lat=u;
    }
}sam;
```

**trie.cpp**

```cpp
#include<cstring>
#define TRIE_TYPE char
const int TRIE_DATA_SIZE=128;
const int TRIE_TREE_SIZE=100;

struct TRIE{
    int next[TRIE_TREE_SIZE][TRIE_DATA_SIZE],nown;
    bool book[TRIE_TREE_SIZE];

    void insert(char *s){
        int pos=0,len=strlen(s);
        for(register int i=0;i<len;++i)
            pos=next[pos][s[i]]?next[pos][s[i]]:(next[pos][s[i]]=++nown);
        book[pos]=1;
        return;
    }

    bool find(char *s,int len){
        int pos=0;
        for(register int i=0;i<len;++i){
            if(!next[pos][s[i]]) return 0;
            pos=next[pos][s[i]];
        }
        return book[pos];
    }

    void del(char *s){
        int pos=0;
        int len=strlen(s);
        for(register int i=0;i<len;++i){
            if(!next[pos][s[i]]) return;
            pos=next[pos][s[i]];
        }
        book[pos]=0;
        return;
    }

    void clear(){
        memset(this,0,sizeof(TRIE));
        return;
    }
};
```

**zFunc.cpp**

```cpp
void zfunc(int n,char *s,int *z){
    register int i,l,r;
    for(i=2,l=1,r=1;i<=n;++i){
        if(i<=r&&z[i-l+1]<r-i+1) z[i]=z[i-l+1];
        else{
            z[i]=std::max(0,r-i+1);
            while(i+z[i]<=n&&s[i+z[i]]==s[1+z[i]]) ++z[i];
        }
        if(i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
    return;
}
```

### Tree algorithms

**lca.cpp**

```cpp
#define ln(x) 31^__builtin_clz(x)
int cntDfn,dfn[100010],parsour[100010],depsour[100010];
#define ST_DATA_TYPE int
#define ST_TYPE >
const int ST_MAXI=100010;
const int ST_MAXJ=30;
ST_DATA_TYPE ST_CALC(ST_DATA_TYPE a,ST_DATA_TYPE b){return depsour[a]<depsour[b]?a:b;}
struct ST{
	ST_DATA_TYPE f[ST_MAXJ][ST_MAXI];

	void build(int size){
		register int i,j;
		int k=ln(size);
		for(j=1;j<=k;++j)
			for(i=1;i<=size-(1<<j)+1;++i)
				f[j][i]=ST_CALC(f[j-1][i],f[j-1][i+(1<<(j-1))]);
		return;
	}

	ST_DATA_TYPE query(int l,int r){
        if(l==r) return l;
        l=dfn[l];
        r=dfn[r];
        if(l>r) std::swap(l,r);
        ++l;
		int k=ln(r-l+1);
        int u=f[k][l];
        int v=f[k][r-(1<<k)+1];
        if(depsour[u]<depsour[v]) return parsour[u];
        else return parsour[v];
	}
}st;

void dfsLca(int u,int p){
    depsour[u]=depsour[p]+1;
    st.f[0][dfn[u]=++cntDfn]=u;
    parsour[u]=p;
    for(auto v:e[u])
        if(v!=p)
            dfsLca(v,u);
}

int getDis(int u,int v){return depsour[u]+depsour[v]-(depsour[st.query(u,v)]<<1);}
```

## Data structures

**fhq_treap.cpp**

```cpp
const int FHQ_DATA_SIZE=2000010;

std::mt19937 mt;

template<typename T=int>
struct FHQTreap{
    struct FHQNODE{
        int lChild,rChild,size,rnd;
        T val;
    };
    FHQNODE tree[FHQ_DATA_SIZE];
    int mem[FHQ_DATA_SIZE],top,root;

    void build(int n){
        mt=std::mt19937(time(0));
        int i;
        for(i=0;i<=n;++i) mem[i]=i;
        top=n;
        root=0;
        return;
    }

    int getMem(){return mem[top--];}
    void rMem(int pos){return (void)(mem[++top]=pos);}
    int getNode(T data){
        int pos=getMem();
        tree[pos].lChild=tree[pos].rChild=0;
        tree[pos].size=1;
        tree[pos].val=data;
        tree[pos].rnd=rand();
        return pos;
    }
    void rTree(int p){
        if(!p) return;
        rTree(tree[p].lChild);
        rTree(tree[p].rChild);
        return rMem(p);
    }

    void pushup(int p){return (void)(tree[p].size=tree[tree[p].lChild].size+tree[tree[p].rChild].size+1);}

    void split(int p,int &x,int &y,T val){
        if(!p){return (void)(x=y=0);}
        if(tree[p].val<=val) x=p,split(tree[p].rChild,tree[p].rChild,y,val);
        else y=p,split(tree[p].lChild,x,tree[p].lChild,val);
        pushup(p);
        return;
    }
    void split_rank(int p,int &x,int &y,int rank){
        if(!rank){return (void)(x=0,y=p);}
        if(tree[tree[p].lChild].size<rank) x=p,split_rank(tree[p].rChild,tree[p].rChild,y,rank-tree[tree[p].lChild].size-1);
        else y=p,split_rank(tree[p].lChild,x,tree[p].lChild,rank);
        pushup(p);
        return;
    }

    int merge(int u,int v){
        if((!u)||(!v)) return u|v;
        if(tree[u].rnd<tree[v].rnd){
            tree[u].rChild=merge(tree[u].rChild,v);
            pushup(u);
            return u;
        }
        tree[v].lChild=merge(u,tree[v].lChild);
        pushup(v);
        return v;
    }

    int insert_rank(T data,int rk){
        int pos=getNode(data),x,y;
        split_rank(root,x,y,rk);
        root=merge(merge(x,pos),y);
        return pos;
    }
    void insert_rank_n(T *data,int cnt,int rk){
        int i;
        int x,y=0,z;
        split_rank(root,x,z,rk);
        for(i=0;i<cnt;++i) y=merge(y,getNode(data[i]));
        root=merge(merge(x,y),z);
    }
    int insert(T data){
        int pos=getNode(data),x,y;
        split(root,x,y,data);
        root=merge(merge(x,pos),y);
        return pos;
    }

    void erase_rank(int rk){
        int x,y,z;
        split_rank(root,x,z,rk);
        split_rank(x,x,y,rk-1);
        root=merge(x,z);
        return rMem(y);
    }
    void erase_rank_range(int l,int r){
        int x,y,z;
        split_rank(root,x,z,r);
        split_rank(x,x,y,l-1);
        root=merge(x,z);
        return rTree(y);
    }
    void erase(T data){
        int x,y,z;
        split(root,x,y,data-1);
        split(y,y,z,data);
        root=merge(merge(x,tree[y].lChild),merge(tree[y].rChild,z));
        rMem(y);
    }

    int findRank(T data){
        int x,y,res;
        split(root,x,y,data-1);
        res=tree[x].size+1;
        root=merge(x,y);
        return res;
    }
    T findKthNum(int &p,int k){
        int x,y,z;
        split_rank(p,x,z,k);
        split_rank(x,x,y,k-1);
        T res=tree[y].val;
        p=merge(merge(x,y),z);
        return res;
    }
    T findPre(T data){
        int x,y;
        split(root,x,y,data-1);
        T res=findKthNum(x,tree[x].size);
        root=merge(x,y);
        return res;
    }
    T findNxt(T data){
        int x,y;
        split(root,x,y,data);
        T res=findKthNum(y,1);
        root=merge(x,y);
        return res;
    }
};
```

**LSGT.cpp**

```cpp
#define LSGT_DATA_TYPE long double
#define LSGT_Y_DATA_TYPE int
#define lC ((p)<<1)
#define rC (lC|1)
#define getMid int mid=(((l)+(r))>>1)
const LSGT_DATA_TYPE LSGT_EXP=1e-20;

char LSGT_CMP(LSGT_DATA_TYPE a,LSGT_DATA_TYPE b){
    if(a-b>LSGT_EXP) return 1;
    if(b-a>LSGT_EXP) return -1;
    return 0;
}

struct LSGT_LINE{
    int id;
    LSGT_DATA_TYPE b,k;
    LSGT_DATA_TYPE calc(int pos){return k*pos+b;}
    friend char cmp(LSGT_LINE a,LSGT_LINE b,int pos){
        LSGT_DATA_TYPE v1=a.calc(pos);
        LSGT_DATA_TYPE v2=b.calc(pos);
        char res=LSGT_CMP(v1,v2);
        if(!res) res=(a.id<b.id)?1:(a.id==b.id?0:-1);
        return res;
    }
    friend LSGT_LINE lmax(LSGT_LINE a,LSGT_LINE b,int pos){
        char res=cmp(a,b,pos);
        if(res==-1) return b;
        return a;
    }
};

const int LSGT_TREE_SIZE=100000;
const int LSGT_LINE_SIZE=100000;

struct LSGT_TREE{
    int tree[LSGT_TREE_SIZE<<2];
    LSGT_LINE lines[LSGT_LINE_SIZE];
    int L,R;
    void down(int p,int l,int r,int tag){
        getMid;
        if(cmp(lines[tree[p]],lines[tag],mid)==-1) std::swap(tree[p],tag);
        if(cmp(lines[tree[p]],lines[tag],l)==-1) down(lC,l,mid,tag);
        if(cmp(lines[tree[p]],lines[tag],r)==-1) down(rC,mid+1,r,tag);
        return;
    }
    void insert(int p,int l,int r,int s,int t,int tag){
        if(s<=l&&r<=t) return down(p,l,r,tag);
        getMid;
        if(s<=mid) insert(lC,l,mid,s,t,tag);
        if(mid<t) insert(rC,mid+1,r,s,t,tag);
        return;
    }
    LSGT_LINE query(int p,int l,int r,int pos){
        if(l==r) return lines[tree[p]];
        getMid;
        if(pos<=mid) return lmax(lines[tree[p]],query(lC,l,mid,pos),pos);
        else return lmax(lines[tree[p]],query(rC,mid+1,r,pos),pos);
    }
    void build(int l,int r){
        lines[0].id=lines[0].k=0;
        lines[0].b=0;
        return (void)(L=l,R=r);
    }
    void insert(int s,int t,LSGT_LINE tag){
        lines[tag.id]=tag;
        return insert(1,L,R,s,t,tag.id);
    }
    void insert(LSGT_LINE tag){
        lines[tag.id]=tag;
        return down(1,L,R,tag.id);
    }
    void insert(int x0,LSGT_Y_DATA_TYPE y0,int x1,LSGT_Y_DATA_TYPE y1,int id){
        LSGT_LINE line;
        line.id=id;
        if(x0>x1) std::swap(x0,x1),std::swap(y0,y1);
        if(x0==x1) line.b=std::max(y0,y1),line.k=0;
        else line.k=((LSGT_DATA_TYPE)(y0  -y1))/((LSGT_DATA_TYPE)(x0-x1)),line.b=y0-line.k*x0;
        return insert(x0,x1,line);
    }
    LSGT_LINE query(int pos){return query(1,L,R,pos);}
};
```

