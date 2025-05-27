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