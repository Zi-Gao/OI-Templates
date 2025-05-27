#define BA_TYPE int
const int BA_MAX_SIZE=100010;
const int BA_MAX_SQRT_SIZE=400;

struct BA{
    int len,id[BA_MAX_SIZE];
    BA_TYPE arr[BA_MAX_SIZE],tag[BA_MAX_SQRT_SIZE],sum[BA_MAX_SQRT_SIZE];
    void build(int n,BA_TYPE *data){
        register int i;
        len=std::sqrt(n);
        for(i=1;i<=n;++i) arr[i]=data[i],id[i]=(i-1)/len+1,sum[id[i]]+=arr[i];
        return;
    }

    void add(int l,int r,BA_TYPE c){
        register int i;
        int begin=id[l],end=id[r];
        if(begin==end){
            for(i=l;i<=r;++i) arr[i]+=c,sum[begin]+=c;
            return;
        }
        for(i=l;id[i]==begin;++i) arr[i]+=c,sum[begin]+=c;
        for(i=begin+1;i<end;++i) tag[i]+=c,sum[i]+=c*len;
        for(i=r;id[i]==end;--i) arr[i]+=c,sum[end]+=c;
        return;
    }

    long long query(int l,int r){
        register int i;
        register long long ans=0;
        int begin=id[l],end=id[r];
        if(begin==end){
            for(i=l;i<r;++i) ans+=arr[i]+tag[begin];
            return ans;
        }
        for(i=l;id[i]==begin;++i) ans+=arr[i]+tag[begin];
        for(i=begin+1;i<end;++i) ans+=sum[i];
        for(i=r;id[i]==end;--i) ans+=arr[i]+tag[end];
        return ans;
    }
};