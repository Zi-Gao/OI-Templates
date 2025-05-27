const int SAM_SIGMA=26,SAM_SIZ=100010;

struct SAM{
	struct state{
		int len,link,next[SAM_SIGMA];
	}sta[SAM_SIZ<<1];
	int cnt,last,pos[SAM_SIZ];
	void init(){
		sta[1].len=sta[1].link=0;
		memset(sta[cnt=last=1].next,0,sizeof(sta[0].next));
	}
	int getNode(){
		++cnt;
		memset(sta[cnt].next,0,sizeof(sta[cnt].next));
		return cnt;
	}
	void add(char c){
		register int p=last,q,u,v;
		sta[u=getNode()].len=sta[last].len+1;
		while(p&&!sta[p].next[c]){
			sta[p].next[c]=u;
			p=sta[p].link;
		}
		if(p==0) sta[u].link=1;
		else{
			q=sta[p].next[c];
			if(sta[p].len+1==sta[q].len) sta[u].link=q;
			else{
				v=++cnt;
				sta[v]=sta[q];
				sta[v].len=sta[p].len+1;
				while(p&&sta[p].next[c]==q){
					sta[p].next[c]=v;
					p=sta[p].link;
				}
				sta[q].link=sta[u].link=v;
			}
		}
		last=u;
	}

    SAM(){init();}
};