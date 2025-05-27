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

FLOW_TYPE sum[NNNN];

void addEdge(int u,int v,FLOW_TYPE lo,FLOW_TYPE up){
    addEdge(u,v,up-lo);
    sum[v]+=lo,sum[u]-=lo;
    return;
}

FLOW_TYPE get(int s,int t,int n){
    register int i,ss=n+1,tt=n+2;
    register FLOW_TYPE cntF=0,res;
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

    register int i,ss,tt,u,v,lo,up,res;
    
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