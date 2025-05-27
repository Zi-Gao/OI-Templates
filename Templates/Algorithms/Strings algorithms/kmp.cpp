void getkmp(int n,char *str,int *nxt){
	register int i,j;
	for(i=2,j=0;i<=n;++i){
        while(j&&str[i]!=str[j+1]) j=nxt[j];
        if(str[i]==str[j+1]) ++j;
        nxt[i]=j;
	}
}

void getmatch(int n,int m,char *pat,char *txt,int *nxt){
    register int i,j;

    for(i=1,j=0;i<=m;++i){
        while(j&&txt[i]!=pat[j+1]) j=nxt[j];
        if(txt[i]==pat[j+1]) ++j;
        if(j==n){
            /*something*/
            j=nxt[j];
        }
    }
}