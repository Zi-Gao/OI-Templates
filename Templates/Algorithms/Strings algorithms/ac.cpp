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