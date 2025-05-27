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
        register int i,u,v;
        register FLOW_TYPE cp,fl,w;
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
		register int v;
		register FLOW_TYPE cp,fl,w,d,res=0;
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

	std::pair<FLOW_TYPE,FLOW_TYPE> get(int _s,int _t,int _n,register FLOW_TYPE resFlow=0,register FLOW_TYPE resCost=0){
		s=_s,t=_t,n=_n;
		register FLOW_TYPE flow;
		register int i;
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

    register int i,u,v,cap,w;
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