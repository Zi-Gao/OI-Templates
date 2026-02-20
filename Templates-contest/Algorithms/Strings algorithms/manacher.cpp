const int MA_SIZE=2200'0010;
const char MA_ch='#';

int Ma_d[MA_SIZE];
char Ma_s[MA_SIZE];

void Manacher(int len,char *s,int *d1,int *d2){
    register int i,l=0,r=-1,k,n=len<<1;
    for(i=0;i<=n;++i)
        if(i&1) Ma_s[i]=s[i>>1];
        else Ma_s[i]=MA_ch;
    for(i=0;i<n;++i){
        k=(i>r)?1:std::min(Ma_d[l+r-i],r-i+1);
        while(0<=i-k&&i+k<=n&&Ma_s[i-k]==Ma_s[i+k]) ++k;
        Ma_d[i]=--k;
        if(i+k>r) l=i-k,r=i+k;
        if(i&1) d1[i>>1]=k;
        else d2[i>>1]=k;
    }
    return;
}