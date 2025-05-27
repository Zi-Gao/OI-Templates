#include<cstdio>
#include<algorithm>
//  #define ONLINE_JUDGE
#define INPUT_DATA_TYPE long long
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){ char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

#include<cstring>
#define BIT_DATA_TYPE long long
const int BIT_SIZE=100010;
long long mod;
struct BIT{
    BIT_DATA_TYPE tree[BIT_SIZE];
    int size;
    void build(BIT_DATA_TYPE*data,int datasize){
        size=datasize;
        for(register int i=1;i<=datasize;++i){
            tree[i]+=data[i];
            tree[i]%=mod;
            tree[i+lowbit(i)]+=tree[i];
            tree[i+lowbit(i)]%=mod;
        }
        return;
    }

    BIT_DATA_TYPE getsum(int l,int r){
        return ((presum(r)-presum(l-1))%mod+mod)%mod;
    }

    BIT_DATA_TYPE presum(int pos){
        BIT_DATA_TYPE sum=0;
        while(pos){
            sum+=tree[pos];
            pos-=lowbit(pos);
            sum%=mod;
        }
        return sum;
    }

    void add(BIT_DATA_TYPE data,int pos){
        while(pos<=size){
            tree[pos]+=data;
            pos+=lowbit(pos);
        }
    }

    BIT_DATA_TYPE lowbit(BIT_DATA_TYPE x){return x&-x;}
};
struct RBIT{
    BIT tree1,tree2;
    BIT_DATA_TYPE a[BIT_SIZE],b[BIT_SIZE];
    int size;
    void build(int n){
        tree1.size=tree2.size=size=n;
        return;
    }

    void update(int l,int r,BIT_DATA_TYPE c){
        tree1.add(c,l);
        tree2.add(c*l,l);
        if(r+1<=size) tree1.add(-c,r+1);
        if(r+1<=size) tree2.add(-c*(r+1),r+1);
        return;
    }

    BIT_DATA_TYPE query(int l,int r){
        register BIT_DATA_TYPE ans=(tree1.presum(r)*(r+1)-tree2.presum(r))%mod;
        if(l-1) ans-=tree1.presum(l-1)*(l)-tree2.presum(l-1);

        return (ans%mod+mod)%mod;
    }
}rbit;

struct EDGE{
    int to,next;
    EDGE(){
        next=-1;
    }
}e[100010<<1];

int tot,cntid,head[100010],depths[100010],parents[100010],cnttree[100010],hson[100010],id[100010],linktop[100010],ans;
long long vsource[100010];

void addEdge(int u,int v){
    e[tot].to=v;
    e[tot].next=head[u];
    head[u]=tot;
    ++tot;
    return;
}

void dfsinti(int u,int p){
    depths[u]=depths[p]+1;
    parents[u]=p;
    cnttree[u]=1;
    for(int i=head[u];~i;i=e[i].next)
        if(e[i].to!=p){
            dfsinti(e[i].to,u);
            cnttree[u]+=cnttree[e[i].to];
            if(cnttree[e[i].to]>cnttree[hson[u]]) hson[u]=e[i].to;
        }
}

void dfslink(int u,int top){
    id[u]=++cntid;
    rbit.update(id[u],id[u],vsource[u]);
    linktop[u]=top;
    if(!hson[u]) return;
    dfslink(hson[u],top);
    for(int i=head[u];~i;i=e[i].next)
        if(e[i].to!=parents[u]&&e[i].to!=hson[u])
            dfslink(e[i].to,e[i].to);
}

void rangeAdd(int u,int v,long long c){
    c%=mod;
    while(linktop[u]!=linktop[v]){
        if(depths[linktop[u]]<depths[linktop[v]]) u^=v,v=u^v,u=u^v;
        rbit.update(id[linktop[u]],id[u],c);
        u=parents[linktop[u]];
    }
    if(depths[u]>depths[v]) u^=v,v=u^v,u=u^v;
    rbit.update(id[u],id[v],c);
}

long long rangeQuery(int u,int v){
    register long long ans=0;
    while(linktop[u]!=linktop[v]){
        if(depths[linktop[u]]<depths[linktop[v]]) u^=v,v=u^v,u=u^v;
        ans=(ans+rbit.query(id[linktop[u]],id[u]))%mod;
        u=parents[linktop[u]];
    }
    if(depths[u]>depths[v]) u^=v,v=u^v,u=u^v;
    ans=(ans+rbit.query(id[u],id[v]))%mod;
    return ans;
}

void treeAdd(int u,long long c){
    c%=mod;
    rbit.update(id[u],id[u]+cnttree[u]-1,c);
}

long long treeQuery(int u){
    return rbit.query(id[u],id[u]+cnttree[u]-1);
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    #endif

    register char op;
    register int i,u,v;
    register long long w;
    int n=read();
    int m=read();
    int root=read();
    mod=read();
    for(i=1;i<=n;++i) head[i]=-1,vsource[i]=read()%mod;
    for(i=1;i<n;++i){
        u=read();
        v=read();
        addEdge(u,v);
        addEdge(v,u);
    }

    dfsinti(root,0);
    rbit.build(n);
    dfslink(root,root);
    for(i=0;i<m;++i){
        op=read();
        if(op==1){
            u=read();
            v=read();
            w=read();
            rangeAdd(u,v,w);
        }else if(op==2){
            u=read();
            v=read();
            print(rangeQuery(u,v));putchar('\n');
        }else if(op==3){
            u=read();
            w=read();
            treeAdd(u,w);
        }else{
            u=read();
            print(treeQuery(u));putchar('\n');
        }
    }

    #ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    #endif
    return 0;
}