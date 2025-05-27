const int SA_SIZE=100010;
int oldrk[SA_SIZE<<1],cnt[SA_SIZE],id[SA_SIZE];
void solveSA(int n,char *s,int *sa,int *rk){
    register int i,p=0,l,max;
    for(i=1;i<=n;++i) sa[i]=i,p=std::max(p,rk[i]=s[i]);

    for(l=0;l<n;l=std::max(1,l*2)){
        memcpy(oldrk,rk,sizeof(int)*(n+1));

        max=p,p=0;
        memset(cnt,0,sizeof(int)*(max+1));

        for(i=n-l+1;i<=n;++i) id[++p]=i;
        for(i=1;i<=n;++i) if(sa[i]>l) id[++p]=sa[i]-l;

        for(i=1;i<=n;++i) ++cnt[rk[i]];
        for(i=1;i<=max;++i) cnt[i]+=cnt[i-1];
        for(i=n;i;--i) sa[cnt[rk[id[i]]]--]=id[i];

        for(i=1,p=0;i<=n;++i) rk[sa[i]]=(p+=(oldrk[sa[i]]!=oldrk[sa[i-1]]||oldrk[sa[i]+l]!=oldrk[sa[i-1]+l]));

        if(p==n) break;
    }
    return;
}