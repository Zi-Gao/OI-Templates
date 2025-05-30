#include<cstring>
#define TRIE_TYPE char
const int TRIE_DATA_SIZE=128;
const int TRIE_TREE_SIZE=100;

struct TRIE{
    int next[TRIE_TREE_SIZE][TRIE_DATA_SIZE],nown;
    bool book[TRIE_TREE_SIZE];

    void insert(char *s){
        int pos=0,len=strlen(s);
        for(register int i=0;i<len;++i)
            pos=next[pos][s[i]]?next[pos][s[i]]:(next[pos][s[i]]=++nown);
        book[pos]=1;
        return;
    }

    bool find(char *s,int len){
        int pos=0;
        for(register int i=0;i<len;++i){
            if(!next[pos][s[i]]) return 0;
            pos=next[pos][s[i]];
        }
        return book[pos];
    }

    void del(char *s){
        int pos=0;
        int len=strlen(s);
        for(register int i=0;i<len;++i){
            if(!next[pos][s[i]]) return;
            pos=next[pos][s[i]];
        }
        book[pos]=0;
        return;
    }

    void clear(){
        memset(this,0,sizeof(TRIE));
        return;
    }
};