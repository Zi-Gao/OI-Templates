#include<ctime>
#include<random>
#define STRINGHASH_MOD %mod
std::mt19937 STRINGHASH_MT(time(NULL));const unsigned long long STRINGHASH_MAX_MOD=1000000;const unsigned long long STRINGHASH_MIN_MOD=100000;unsigned long long mod=STRINGHASH_MT()%(STRINGHASH_MAX_MOD-STRINGHASH_MIN_MOD)+STRINGHASH_MIN_MOD;unsigned long long stringhash(int len,char*s,unsigned long long*w){register unsigned long long ans=0;register int i;for(i=0;i<len;++i)ans=(ans+s[i]*w[i])STRINGHASH_MOD;return ans;}