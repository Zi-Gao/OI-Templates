#define BSGS_TYPE long long

BSGS_TYPE getLog(BSGS_TYPE a,BSGS_TYPE b,BSGS_TYPE p){
    std::unordered_map<BSGS_TYPE,BSGS_TYPE> mp;
    register BSGS_TYPE lim=std::ceil(std::sqrt(p)),now,pw;
    register int i;
    for(i=0,now=b,pw=1;i<=lim;++i,(now*=a)%=p){
        mp[now]=i;
        if(i) (pw*=a)%=p;
    }
    for(i=1,now=pw;i<=lim;++i,(now*=pw)%=p){
        auto it=mp.find(now);
        if(it!=mp.end()) return lim*i-it->second;
    }
    return -1;
}