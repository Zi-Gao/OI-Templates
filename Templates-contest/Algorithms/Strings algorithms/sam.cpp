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