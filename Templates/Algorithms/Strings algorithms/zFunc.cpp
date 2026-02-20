void zfunc(int n,char *s,int *z){
    int i,l,r;
    for(i=1,l=r=0;i<n;++i){
        if(z[i-l]<r-i) z[i]=z[i-l];
        else{
            z[i]=std::max(0,r-i);
            while(i+z[i]<n&&s[i+z[i]]==s[z[i]]) ++z[i];
        }
        if(i+z[i]>r) l=i,r=i+z[i];
    }
    return;
}