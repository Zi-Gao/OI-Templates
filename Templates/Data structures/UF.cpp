const int UFDS_SIZE=100010;
struct UF{
	int par[UFDS_SIZE];
	void build(int n){for(int i=0;i<=n;++i)par[i]=i;}
    template<int dep> inline __attribute((always_inline)) constexpr int fold(int u){
        if constexpr (dep==0) return par[u];
        else return par[u]=fold<dep-1>(par[u]);
    }
    inline __attribute((always_inline)) int find(int u){while(u!=par[u]) u=fold<2>(u);return u;}
	void merge(int i,int j){par[find(i)]=find(j);}
	void clear(){for(int i=1;i<UFDS_SIZE;i++) par[i]=i;}
};