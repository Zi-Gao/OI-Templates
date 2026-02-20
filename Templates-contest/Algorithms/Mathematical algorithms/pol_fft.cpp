const long long NTTp=998244353;
const long long NTTg=3;
const long long NTTInvg=332748118;
const int POL_SIZE=4000000;

double FFTPI=acos(-1);

struct POL{
    int len,FFTLen,rev[POL_SIZE];
    std::complex<double> items[POL_SIZE];

    void initRev(int k){
        register int i;
        for(i=0;i<FFTLen;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
        return;
    }
    int initLen(){
        register int k=0;
        FFTLen=1;
        while(FFTLen<=len) ++k,FFTLen<<=1;
        return k;
    }
    void init(){initRev(initLen());}

    void fft(char flg){
        register int i,l,j,k;
        register std::complex<double> w1,w,x,y;
        for(i=0;i<FFTLen;++i) if(i<rev[i]) std::swap(items[i],items[rev[i]]);
        for(l=1;l<FFTLen;l<<=1)
            for(j=0,w1=exp(std::complex<double>(0,FFTPI*flg/l));j<FFTLen;j+=(l<<1))
                for(k=j,w=1;k<j+l;++k,w*=w1){
                    x=items[k];
                    y=w*items[k+l];
                    items[k]=x+y;
                    items[k+l]=x-y;
                }
        if(flg==-1) for(i=0;i<FFTLen;++i) items[i]/=FFTLen;

        return;
    }

    friend POL operator * (POL a,POL b){
        register int i;
        a.len=b.len=a.len+b.len;
        a.init(),b.init();
        a.fft(1);
        b.fft(1);
        for(i=0;i<a.FFTLen;++i) a.items[i]*=b.items[i];
        a.fft(-1);
        return a;
    }

	void clear(){
		for(register int i=0;i<=len;++i) items[i]=0;
		len=0;
		return;
	}
};