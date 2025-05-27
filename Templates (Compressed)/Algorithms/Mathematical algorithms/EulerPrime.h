#include<cstdio>
#include<bitset>
const int EULER_PRIME_MAX_NUM=100000000+10;std::bitset<EULER_PRIME_MAX_NUM>isPrime;int prime[EULER_PRIME_MAX_NUM];void Euler(int n){register int cnt=0;register int i,j;for(i=2;i<=n;++i){if(!isPrime[i])prime[++cnt]=i;for(j=1;j<=cnt&&prime[j]*i<=n;++j){isPrime[prime[j]*i]=1;if(!(i%prime[j]))break;}}}