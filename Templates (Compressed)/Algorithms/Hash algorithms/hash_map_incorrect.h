#include<cstdlib>
#include<cstring>
#include<ctime>
#include<random>
#include<bitset>
#define HASH_MAP_DATA_TYPE int
#define HASH_RAND mt()
const int MAX_HASH_TIMES=10;const int MAX_HASH_MOD=(11451481);const int MIN_HASH_MOD=(5451481);std::mt19937 mt(time(NULL));struct HASH_MAP{std::bitset<MAX_HASH_TIMES>hash_map[MAX_HASH_MOD];int hash_times,mod[MAX_HASH_TIMES];HASH_MAP(int in){hash_times=in;for(register int i=0;i<hash_times;++i)mod[i]=((i&2)?mod[i-1]-1:HASH_RAND%(MAX_HASH_MOD-MIN_HASH_MOD)+MIN_HASH_MOD);return;}void insert(HASH_MAP_DATA_TYPE in){for(register int i=0;i<hash_times;++i)hash_map[in%mod[i]][i]=1;return;}bool find(HASH_MAP_DATA_TYPE in){for(register int i=0;i<hash_times;++i)if(!hash_map[in%mod[i]][i])return false;return true;}void clear(){memset(hash_map,0,sizeof(hash_map));return;}};