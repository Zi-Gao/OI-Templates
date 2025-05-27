#define DET_TYPE double
const DET_TYPE det_eps=1e-8;
inline int det_cmp(DET_TYPE x){return fabs(x)<det_eps?0:(x<0?-1:1);}
DET_TYPE getDet_real(std::vector<DET_TYPE> *a,int n){
    register int i,j,k,max;
    register DET_TYPE ans=1,x;
    for(i=0;i<n;++i){
        max=i;
        for(j=i+1;j<=n;++j)if(det_cmp(a[max][i]-a[j][i])<0) max=i;
        if(max!=i) a[max].swap(a[i]);
        for(j=i+1;j<n;++j){
            x=a[j][i]/a[i][i];
            for(k=i;k<n;++k)
                a[j][k]-=x*a[i][k];
        }
    }
    for(i=0;i<n;++i)
        ans*=a[i][i];
    return ans;
}