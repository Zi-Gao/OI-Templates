#include<bits/stdc++.h>

// #define NOBUG
// #define ONLINE_JUDGE
#define il inline __attribute((always_inline)) 

#ifdef NOBUG
#define dbg(...) fprintf (stderr, __VA_ARGS__)
#else
#define dbg(...) void()
#endif

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;

#define getu(x) typename std::make_unsigned<x>::type
template<typename T=int>il T read(){getu(T)x=0;char c=getchar(),f=0;while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=x*10+(c&15),c=getchar();return f?-x:x;}char ous[50];template<typename T>il void print(const T&x){if(x==0)return putchar('0'),void();getu(T)y=x;if(x<0)y=-y,putchar('-');char*p=ous;while(y){*(p++)=y%10;y/=10;}while(p>ous)putchar(*(--p)|'0');}


namespace POL{
    // #define forceIl
    #define forceIl inline __attribute((always_inline))

    using u32=unsigned int;
    using i64=long long;
    using u64=unsigned long long;

    const u32 NTTp=998244353;
    const u32 NTTphi=NTTp-1;
    const u32 NTTg=3;
    const u32 NTTInvg=332748118;
    const int POL_SIZE=4000000;

    int rev[POL_SIZE],NTTLen,NTTk,nowInv;
    u32 W[2][30],invs[POL_SIZE];

    forceIl int ln2(int x){return 31^__builtin_clz(x);}
    forceIl u32& reduce(u32 &x){
        if(x>=NTTp) x-=NTTp;
        return x;
    }
    forceIl u32 qpow(u32 base,u32 e){
        u32 res=1;
        while(e){
            if(e&1) res=(u64)res*base%NTTp;
            base=(u64)base*base%NTTp;
            e>>=1;
        }
        return res;
    }
    forceIl u32 invNum(u32 n){return qpow(n,NTTp-2);}
    forceIl void init(){
        int i=0,lg=ln2(POL_SIZE);
        for(i=0;i<=lg;++i)
            W[0][i]=qpow(NTTg,(NTTp-1)/(2<<i)),
            W[1][i]=qpow(NTTInvg,(NTTp-1)/(2<<i));
        nowInv=2,invs[1]=1;
    }
    forceIl void initInv(int k){
        int i;
        for(i=nowInv;i<=k;++i) invs[i]=NTTp-(u64)NTTp/i*invs[NTTp%i]%NTTp;
        nowInv=i;
    }
    forceIl void qInit(int len){
        NTTLen=1<<(NTTk=ln2(len));
        if(NTTLen<len) NTTLen*=2,++NTTk;
    }
    forceIl void initLen(int len){
        int i;
        qInit(len);
        for(i=0;i<NTTLen;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(NTTk-1));
        return;
    }

    struct POL{
        std::vector<u32> items;

        forceIl void push_back(u32 x){items.push_back(x);}
        forceIl void pop_back(){items.pop_back();}
        forceIl int size() const {return items.size();}
        forceIl void resize(int x){items.resize(x);}
        forceIl void resize(int x,u32 v){items.resize(x,v);}
        forceIl void clear(){items.clear();}
        forceIl void reverse(){std::reverse(items.begin(),items.end());}
        forceIl u32& operator [] (const int x){return items[x];}
        forceIl u32 operator [] (const int x) const {return items[x];}

        forceIl POL operator + (const POL &o) const{
            int i;
            POL res;
            res=*this;
            res.resize(std::max(size(),o.size()));
            for(i=0;i<o.size();++i) reduce(res[i]+=o[i]);
            return res;
        }
        forceIl POL operator + (const u32 &o) const{
            POL res=*this;
            reduce(res[0]+=o);
            return res;
        }
        forceIl friend POL operator + (const u32 &o,const POL &x){return x+o;}
        forceIl POL operator - (const POL &o) const{
            int i;
            POL res;
            res=*this;
            res.resize(std::max(size(),o.size()));
            for(i=0;i<o.size();++i) reduce(res[i]+=NTTp-o[i]);
            return res;
        }
        forceIl POL operator - (const u32 &o) const{
            POL res=*this;
            reduce(res[0]+=NTTp-o);
            return res;
        }
        forceIl friend POL operator - (const u32 &o,POL x){
            for(auto &i:x.items) reduce(i=NTTp-i);
            reduce(x[0]+=o);
            return x;
        }
        forceIl friend POL operator * (const u32 &o,const POL &x){return o*x;}
        forceIl friend POL operator / (const u32 &o,const POL &x){return x.inv()*o;}

        forceIl POL deriv() const{
            POL res=*this;
            if(items.empty()) return res;
            int i;
            for(i=1;i<size();++i) res[i-1]=(u64)res[i]*i%NTTp;
            res.pop_back();
            return res;
        }
        forceIl POL integ() const{
            POL res=*this;
            if(items.empty()) return res;
            int i;
            initInv(size());
            res.push_back(0);
            for(i=size();~i;--i) res[i]=(u64)res[i-1]*invs[i]%NTTp;
            return res;
        }

        forceIl POL xPow(int k,int len){
            POL res;
            res.resize(len);
            for(int i=0;i*k<len;++i) res[i*k]=items[i];
            return res;
        }
        forceIl POL xPow(int k){return xPow(k,(size()-1)*k+1);}
        
        forceIl POL shift(int k,int len){
            POL res;
            res.resize(len);
            for(int i=0;i+k<len;++i) res[i+k]=items[i];
            return res;
        }
        forceIl POL shift(int k){return shift(k,size()+k);}

        forceIl friend POL operator * (POL A,POL B){
            int i,j,len=A.size()+B.size();

            if((i64)A.size()*B.size()<=(len*ln2(len)*6)){
                POL res;
                res.resize(len);
                for(i=0;i<A.size();++i) for(j=0;j<B.size();++j)
                    res[i+j]=(res[i+j]+(u64)A[i]*B[j])%NTTp;
                return res;
            }else{
                qInit(len);
                A.resize(NTTLen);
                B.resize(NTTLen);
                qntt2(A,B,0);
                for(i=0;i<NTTLen;++i) A[i]=(u64)A[i]*B[i]%NTTp;
                A.qntt(1);
                A.resize(len);
                return A;
            }
        }
        forceIl POL operator * (const u32 o) const{
            POL res=*this;
            for(auto &item:res.items) item=(u64)item*o%NTTp;
            return res;
        }

        forceIl friend POL operator / (POL F,POL G){
            int n=F.size(),m=G.size();
            F.reverse(),G.reverse();
            F.resize(n-m+1);
            G.resize(n-m+1);
            F=F*G.inv();
            F.resize(n-m+1);
            F.reverse();
            return F;
        }
        forceIl POL operator / (u32 o) const{
            POL res=*this;
            o=invNum(o);
            for(auto &item:res.items) item=(u64)item*o%NTTp;
            return res;
        }

        forceIl POL operator % (const POL &G) const{
            POL res=*this-G*(*this/G);
            res.resize(G.size()-1);
            return res;
        }
        forceIl std::pair<POL,POL> getDiv(const POL &G) const{
            POL P=*this/G;
            POL Q=*this-P*G;
            Q.resize(G.size()-1);
            return {P,Q};
        }

        forceIl POL inv() const{
            int i,len,L=1,l,j,k;
            u32 w1,w,x,y;
            POL A,B;
            while(L<size()) L<<=1;
            B.resize(1);
            B[0]=invNum(items[0]);
            for(len=2;len<=L;len<<=1){
                A.clear(),A.resize(len*2);
                for(i=0;i<std::min(size(),len);++i) A[i]=items[i];
                
                qInit(len<<1);
                A.resize(NTTLen),B.resize(NTTLen);
                qntt2(A,B,0);

                for(i=0;i<NTTLen;++i) B[i]=(2+NTTp-(u64)B[i]*A[i]%NTTp)*B[i]%NTTp;
                B.qntt(1);
                B.resize(len);
            }
            B.resize(size());
            return B;
        }

        forceIl POL ln() const{
            POL res=(deriv()*inv()).integ();
            res.resize(size());
            return res;
        }
        forceIl POL exp() const{
            int i=0,len,L=1;
            POL A,B;
            while(L<size()) L<<=1;
            B.resize(1);
            B[0]=1;
            for(len=1;len<=L;len<<=1){
                A.resize(len);
                for(;i<std::min(size(),len);++i) A[i]=items[i];
                B=B*(A-B.ln()+1);
            }
            B.resize(size());
            return B;
        }
        forceIl POL pow(u32 e,u32 ephi,int p) const{
            int i;
            u32 x,invX;
            POL res=*this;

            invX=invNum(x=items[p]);
            res.items.erase(res.items.begin(),res.items.begin()+p);
            for(auto &item:res.items) item=(u64)item*invX%NTTp;
            res=res.ln();
            for(auto &item:res.items) item=(u64)item*e%NTTp;
            res=res.exp();
            
            x=qpow(x,ephi);
            for(auto &item:res.items) item=(u64)item*x%NTTp;

            std::vector<u64> now;
            for(i=0;i<e*p;++i) now.push_back(0);
            res.items.insert(res.items.begin(),now.begin(),now.end());

            return res;
        }
        forceIl POL operator ^ (const char *s) const{
            int i=0,p;
            u32 e=0,ephi=0;
            for(p=0;p<size();++p)
                if(items[p]) break;
            while(s[i]){
                if((e*10+(s[i]&15))*p>=size()){
                    POL res;
                    res.resize(size());
                    return res;
                }
                e=((u64)e*10+(s[i]&15))%NTTp;
                ephi=((u64)ephi*10+(s[i]&15))%NTTphi;
                ++i;
            }
            if(p==size()){
                POL res;
                res.resize(1,1);
                res.resize(size());
                return res;
            }
            return pow(e,ephi,p);
        }
        forceIl POL operator ^ (u32 e) const{
            int p;
            for(p=0;p<size();++p)
                if(items[p]) break;
            if(p==size()&&e==0){
                POL res;
                res.resize(1,1);
                res.resize(size());
                return res;
            }
            if(p&&(e>=size()||e*p>=size())){
                POL res;
                res.resize(size());
                return res;
            }
            return pow(e%NTTp,e%NTTphi,p);
        }

        forceIl POL sqrt(){
            int i=0,len,L=1;
            POL A,B;
            while(L<size()) L<<=1;
            B.resize(1,1);
            for(len=1;len<=L;len<<=1){
                A.resize(len);
                for(;i<std::min(size(),len);++i) A[i]=items[i];
                B=(A*B.inv()+B)/2;
            }
            B.resize(size());
            return B;
        }

        friend void mul(int p,int l,int r,std::vector<u32> &x,std::vector<POL> &pols){
            if(l==r){
                if(pols.size()<=p) pols.resize(p+1);
                pols[p].push_back(NTTp-x[l]);
                pols[p].push_back(1);
                return;
            }
            int mid=(l+r)>>1,lc=p<<1,rc=p<<1|1;
            mul(lc,l,mid,x,pols),mul(rc,mid+1,r,x,pols);
            pols[p]=pols[lc]*pols[rc];
            pols[p].pop_back();
        }

        forceIl POL subMul(POL a,POL b) const {
            int i;
            int n=a.size();
            int m=b.size();
            std::reverse(b.items.begin(),b.items.end());
            b=a*b;
            for(i=0;i<n;++i) a[i]=b[i+m-1];
            return a;
        }
        void initVals(int p,int l,int r,std::vector<u32> &x,std::vector<POL> &pols) const {
            if(l==r){
                if(pols.size()<=p) pols.resize(p+1);
                pols[p].push_back(1);
                pols[p].push_back(NTTp-x[l]);
                return;
            }
            int mid=(l+r)>>1,lc=p<<1,rc=p<<1|1;
            initVals(lc,l,mid,x,pols),initVals(rc,mid+1,r,x,pols);
            pols[p]=pols[lc]*pols[rc];
            pols[p].pop_back();
        }
        void solveEval(int p,int l,int r,POL now,std::vector<u32> &res,std::vector<POL> &pols) const {
            if(l==r){
                res[l]=now[0];
                return;
            }
            now.resize(r-l+1);
            int mid=(l+r)>>1,lc=p<<1,rc=p<<1|1;
            solveEval(lc,l,mid,subMul(now,pols[rc]),res,pols);
            solveEval(rc,mid+1,r,subMul(now,pols[lc]),res,pols);
            return;
        }
        forceIl std::vector<u32> eval(std::vector<u32> x) const{
            if(x.empty()) return std::vector<u32>();
            int n=std::max(size(),(int)x.size());
            int m=x.size();
            POL pol=*this;
            std::vector<POL> pols;
            std::vector<u32> res;
            x.resize(n),res.resize(n);
            initVals(1,0,n-1,x,pols);
            solveEval(1,0,n-1,subMul(pol,pols[1].inv()),res,pols);
            res.erase(res.begin()+m,res.end());
            return res;
        }

        POL solveInterp(int p,int l,int r,std::vector<u32> &y,std::vector<u32> &vals,std::vector<POL> &pols) const {
            if(l==r){
                POL res;
                res.push_back((u64)y[l]*invNum(vals[l])%NTTp);
                return res;
            }
            int mid=(l+r)>>1,lc=p<<1,rc=p<<1|1;
            return solveInterp(lc,l,mid,y,vals,pols)*pols[rc]+solveInterp(rc,mid+1,r,y,vals,pols)*pols[lc];
        }
        forceIl void interp(std::vector<u32> x,std::vector<u32> y){
            if(x.empty()){
                clear();
                return;
            }
            std::vector<POL> pols;
            std::vector<u32> vals;
            mul(1,0,x.size()-1,x,pols);
            POL H=pols[1];
            vals=H.deriv().eval(x);
            *this=solveInterp(1,0,x.size()-1,y,vals,pols);
            resize(x.size());
            return;
        }

        forceIl void ntt(int flg){//0: DFT  1:IDFT
            int i,l,j,k,lg;
            u32 w,t;
            for(i=0;i<NTTLen;++i) if(i<rev[i]) std::swap(items[i],items[rev[i]]);
            for(l=1,lg=0;l<NTTLen;l<<=1,++lg)
                for(j=0;j<NTTLen;j+=(l<<1))
                    for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                        t=(u64)w*items[k+l]%NTTp;
                        reduce(items[k+l]=items[k]+NTTp-t);
                        reduce(items[k]+=t);
                    }
            if(flg){
                t=invNum(NTTLen);
                for(auto &item:items) item=(u64)item*t%NTTp;
            }
        }

        forceIl friend void ntt2(POL &A,POL &B,char flg){ 
            int i,l,j,k,lg;
            u32 w,t;
            for(i=0;i<NTTLen;++i) if(i<rev[i]) std::swap(A.items[i],A.items[rev[i]]),std::swap(B.items[i],B.items[rev[i]]);
            for(l=1,lg=0;l<NTTLen;l<<=1,++lg)
                for(j=0;j<NTTLen;j+=(l<<1))
                    for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                        t=(u64)w*A.items[k+l]%NTTp;
                        reduce(A.items[k+l]=A.items[k]+NTTp-t);
                        reduce(A.items[k]+=t);
                        t=(u64)w*B.items[k+l]%NTTp;
                        reduce(B.items[k+l]=B.items[k]+NTTp-t);
                        reduce(B.items[k]+=t);
                    }
            if(flg){
                t=invNum(NTTLen);
                for(auto &item:A.items) item=(u64)item*t%NTTp;
                for(auto &item:B.items) item=(u64)item*t%NTTp;
            }
        }

        forceIl void qntt(char flg){//0: DFT  1:IDFT
            int i,l,j,k,lg;
            u32 w,t;
            if(flg==0){
                for(l=NTTLen/2,lg=NTTk-1;l;l>>=1,--lg)
                    for(j=0;j<NTTLen;j+=(l<<1))
                        for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                            t=(u64)(items[k]-items[k+l]+NTTp)*w%NTTp;
                            reduce(items[k]+=items[k+l]);
                            items[k+l]=t;
                        }
            }else{
                for(l=1,lg=0;l<NTTLen;l<<=1,++lg)
                    for(j=0;j<NTTLen;j+=(l<<1))
                        for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                            t=(u64)w*items[k+l]%NTTp;
                            reduce(items[k+l]=items[k]+NTTp-t);
                            reduce(items[k]+=t);
                        }
                t=invNum(NTTLen);
                for(auto &item:items) item=(u64)item*t%NTTp;
            }
        }

        forceIl friend void qntt2(POL &A,POL &B,char flg){
            int i,l,j,k,lg;
            u32 w,t;
            if(flg==0){
                for(l=NTTLen/2,lg=NTTk-1;l;l>>=1,--lg)
                    for(j=0;j<NTTLen;j+=(l<<1))
                        for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                            t=(u64)(A.items[k]-A.items[k+l]+NTTp)*w%NTTp;
                            reduce(A.items[k]+=A.items[k+l]);
                            A.items[k+l]=t;
                            t=(u64)(B.items[k]-B.items[k+l]+NTTp)*w%NTTp;
                            reduce(B.items[k]+=B.items[k+l]);
                            B.items[k+l]=t;
                        }
            }else{
                for(l=1,lg=0;l<NTTLen;l<<=1,++lg)
                    for(j=0;j<NTTLen;j+=(l<<1))
                        for(k=j,w=1;k<j+l;++k,w=(u64)w*W[flg][lg]%NTTp){
                            t=(u64)w*A.items[k+l]%NTTp;
                            reduce(A.items[k+l]=A.items[k]+NTTp-t);
                            reduce(A.items[k]+=t);
                            t=(u64)w*B.items[k+l]%NTTp;
                            reduce(B.items[k+l]=B.items[k]+NTTp-t);
                            reduce(B.items[k]+=t);
                        }
                t=invNum(NTTLen);
                for(auto &item:A.items) item=(u64)item*t%NTTp;
                for(auto &item:B.items) item=(u64)item*t%NTTp;
            }
        }
    };

    struct INIT{
        INIT(){init();}
    }INITS;
};
#define Poly POL::POL

Poly A,B;
char s[200000];
std::vector<u32> x,y;


int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif


    // P3803 【模板】多项式乘法（FFT）
    // int i;
    // int n=read();
    // int m=read();
    // A.resize(n+1),B.resize(m+1);
    // for(i=0;i<=n;++i) A[i]=read();
    // for(i=0;i<=m;++i) B[i]=read();
    // A=A*B;
    // for(i=0;i<=n+m;++i) print(A[i]),putchar(' ');

    //P4238 【模板】多项式乘法逆
    // int i;
    // int n=read();
    // A.resize(n);
    // for(i=0;i<n;++i) A.items[i]=read();
    // A=A.inv();
    // for(i=0;i<n;++i) print(A[i]),putchar(' ');

    //P4512 【模板】多项式除法
    // int i;
    // int n=read();
    // int m=read();
    // A.resize(n+1),B.resize(m+1);
    // for(i=0;i<=n;++i) A[i]=read();
    // for(i=0;i<=m;++i) B[i]=read();
    // auto res=A.getDiv(B);
    // for(i=0;i<=n-m;++i) print(res.first[i]),putchar(' ');
    // putchar('\n');
    // for(i=0;i<=m-1;++i) print(res.second[i]),putchar(' ');

    //P4725 【模板】多项式对数函数（多项式 ln）
    // int i;
    // int n=read();
    // A.resize(n);
    // for(i=0;i<n;++i) A.items[i]=read();
    // A=A.ln();
    // for(i=0;i<n;++i) print(A.items[i]),putchar(' ');;

    //P4726 【模板】多项式指数函数（多项式 exp）
    // int i;
    // int n=read();
    // A.resize(n);
    // for(i=0;i<n;++i) A.items[i]=read();
    // A=A.exp();
    // for(i=0;i<n;++i) print(A.items[i]),putchar(' ');

    //P5273 【模板】多项式幂函数（加强版）
    // int i;
    // int n=read();
    // scanf("%s",s);
    // A.resize(n);
    // for(i=0;i<n;++i) A[i]=read();
    // A=A^s;
    // for(i=0;i<n;++i) print(A[i]),putchar(' ');

    //P5205 【模板】多项式开根
    // int i;
    // int n=read();
    // A.resize(n);
    // for(i=0;i<n;++i) A[i]=read();
    // A=A.sqrt();
    // for(i=0;i<n;++i) print(A[i]),putchar(' ');

    //P5050 【模板】多项式多点求值
    // int i;
    // int n=read();
    // int m=read();
    // A.resize(n+1);
    // for(i=0;i<=n;++i) A[i]=read();
    // for(i=0;i<m;++i) x.push_back(read());

    // auto res=A.eval(x);
    // for(auto val:res) print(val),putchar('\n');

    //P5158 【模板】多项式快速插值
    // int i;

    // int n=read();
    // x.resize(n),y.resize(n);
    // for(i=0;i<n;++i){
    //     x[i]=read();y[i]=read();
    // }
    // A.interp(x,y);

    // for(i=0;i<n;++i) print(A[i]),putchar(' ');

    return 0;
}