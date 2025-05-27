const int EULER_SIZE=100010;

std::bitset<EULER_SIZE> notPri;
int phi[EULER_SIZE],mu[EULER_SIZE],sig_0[EULER_SIZE],num[EULER_SIZE],sig_1[EULER_SIZE],minPriS[EULER_SIZE];
std::vector<int> pris;

void eulerSieve(int n){
    register int cnt=0;
    register int i,j;
    phi[1]=mu[1]=sig_0[1]=sig_1[1]=notPri[1]=1;
    for(i=2;i<=n;++i){
        if(!notPri[i]){
            pris.push_back(i);
            phi[i]=i-1;
            mu[i]=-1;
            sig_0[i]=2;
            num[i]=1;
            sig_1[i]=minPriS[i]=i+1;
        }
        for(auto pri:pris){
            if(pri*i>n) break;
            notPri[pri*i]=1;
            if(!(i%pri)){
                phi[pri*i]=phi[i]*pri;
                mu[pri*i]=0;
                num[pri*i]=num[i]+1;
                sig_0[pri*i]=sig_0[i]/num[pri*i]*(num[pri*i]+1);
                minPriS[pri*i]=minPriS[i]*pri+1;
                sig_1[i*pri]=sig_1[i]/minPriS[i]*minPriS[pri*i];
                break;
            }
            phi[pri*i]=phi[i]*phi[pri];
            mu[pri*i]=-mu[i];
            num[pri*i]=1;
            sig_0[pri*i]=sig_0[i]<<1;
            sig_1[pri*i]=sig_1[pri]*sig_1[i];
            minPriS[pri*i]=pri+1;
        }
    }
    return;
}