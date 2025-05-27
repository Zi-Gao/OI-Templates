#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_int int
#define OUTPUT_int long long
INPUT_int read(){register INPUT_int x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_int x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

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
		register int v;
		register FLOW_TYPE cp,fl,d,res=0;
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

	FLOW_TYPE get(int _s,int _t,int _n,register FLOW_TYPE res=0){
		s=_s,t=_t,n=_n;
		register int i;
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

    register int i,u,v,cap;
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