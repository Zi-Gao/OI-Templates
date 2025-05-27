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
	int dep[NNNN],nowCur[NNNN],n,s,t;
	int bfs(){
		std::queue<int> Q;
		register int i,u,v;
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
		register int v;
		register FLOW_TYPE cp,fl,d,res=0;
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
		register FLOW_TYPE maxflow=0;
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