void zfunc(int n,char *s,int *z){
    register int i,l,r;
    for(i=2,l=1,r=1;i<=n;++i){
        if(i<=r&&z[i-l+1]<r-i+1) z[i]=z[i-l+1];
        else{
            z[i]=std::max(0,r-i+1);
            while(i+z[i]<=n&&s[i+z[i]]==s[1+z[i]]) ++z[i];
        }
        if(i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
    return;
}