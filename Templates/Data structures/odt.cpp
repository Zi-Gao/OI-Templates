#define ODT_DATA_TYPE int

struct ODT_NODE{
    ODT_DATA_TYPE l,r,col;
    bool operator < (const ODT_NODE o) const{
        return l<o.l;
    }
};

struct ODT{
    ODT_DATA_TYPE L,R;
    std::set<ODT_NODE> odt;
    auto split(ODT_DATA_TYPE pos){
        if(pos>R) return odt.end();
        auto it=--odt.upper_bound((ODT_NODE){pos,0,0});
        if(it->l==pos) return it;
        int l=it->l,r=it->r,col=it->col;
        odt.erase(it);
        odt.insert((ODT_NODE){l,pos-1,col});
        return odt.insert((ODT_NODE){pos,r,col}).first;
    }

    void assign(ODT_DATA_TYPE l,ODT_DATA_TYPE r,ODT_DATA_TYPE col){
        auto itr=split(r+1),itl=split(l);
        odt.erase(itl,itr);
        bit.add(r-l+1,col);
        odt.insert((ODT_NODE){l,r,col});
    }

    void assign(ODT_DATA_TYPE l,ODT_DATA_TYPE r,ODT_DATA_TYPE col){
        auto itr=split(r+1),itl=split(l);
        for(auto it=itl;it!=itr;++it){
            /*something?*/
        }
        return;
    }

    void build(ODT_DATA_TYPE l,ODT_DATA_TYPE r,ODT_DATA_TYPE col){
        odt.clear();
        odt.insert((ODT_NODE){L=l,R=r,col});
    }
};