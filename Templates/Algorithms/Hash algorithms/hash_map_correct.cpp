#include<ctime>
#include<random>
#include<bitset>
const unsigned long long HASH_MAX_MOD=1000000;
const unsigned long long HASH_MIN_MOD=100000;
std::mt19937 HASP_MAP_MT(time(NULL));

struct HASH{
    unsigned long long hash_value[HASH_MAX_MOD];
    std::bitset<HASH_MAX_MOD> hash_book;
    unsigned int mod;
    HASH(){
        mod=HASP_MAP_MT()%(HASH_MAX_MOD-HASH_MIN_MOD)+HASH_MIN_MOD;
        return;
    }

    int getHashValue(unsigned long long key){
        register int pos=key%mod;
        int mod_value=(~(pos-1))?pos-1:mod-1;
        while(pos!=mod_value&&hash_book[pos]){
            if(hash_value[pos]==key) return pos;
            pos=(~(pos-1))?pos-1:mod-1;
        }
        hash_value[pos]=key;
        hash_book[pos]=1;
        return pos;
    }

    int findHashValue(unsigned long long key){
        register int pos=key%mod;
        int mod_value=(~(pos-1))?pos-1:mod-1;
        while(pos!=mod_value&&hash_book[pos]){
            if(hash_value[pos]==key) return pos;
            pos=(~(pos-1))?pos-1:mod-1;
        }
        return -1;
    }
};