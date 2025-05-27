#include<cstring>
#define BIT_DATA_TYPE long long
#include<cstring>
#define BIT_DATA_TYPE int
const int BIT_SIZE=100000;
struct BIT{
    BIT_DATA_TYPE tree[BIT_SIZE];
    int size;

    void build(BIT_DATA_TYPE *data,int datasize){
        size=datasize;
        for(register int i=1;i<=datasize;++i){
            tree[i]+=data[i];
            tree[i+lowbit(i)]+=tree[i];
        }
        return;
    }

    BIT_DATA_TYPE getsum(int l,int r){
        return presum(r)-presum(l-1);
    }

    BIT_DATA_TYPE presum(int pos){
        BIT_DATA_TYPE sum=0;
        while(pos){
            sum+=tree[pos];
            pos-=lowbit(pos);
        }
        return sum;
    }

    void add(BIT_DATA_TYPE data,int pos){
        while(pos<=size){
            tree[pos]+=data;
            pos+=lowbit(pos);
        }
    }

    BIT_DATA_TYPE lowbit(BIT_DATA_TYPE x){
        return x&-x;
    }

    void clear(){
        memset(this,0,sizeof(BIT));
        return;
    }
};
struct RBIT{
	BIT tree1,tree2;
	int size;
	void build(BIT_DATA_TYPE *arr,int n){
		BIT_DATA_TYPE *a=new BIT_DATA_TYPE[BIT_SIZE];
		BIT_DATA_TYPE *b=new BIT_DATA_TYPE[BIT_SIZE];
		register int i;
		register BIT_DATA_TYPE last=0;
		size=n;
        for(i=1;i<=n;++i){
            a[i]=arr[i]-last;
            b[i]=a[i]*i;
            last=arr[i];
        }
		tree1.build(a,n);
        tree2.build(b,n);
	}

	void update(int l,int r,BIT_DATA_TYPE c){
        tree1.add(c,l);
        tree2.add(c*l,l);
        if(r+1<=size) tree1.add(-c,r+1);
        if(r+1<=size) tree2.add(-c*(r+1),r+1);
        return;
	}

	BIT_DATA_TYPE query(int l,int r){
		register BIT_DATA_TYPE ans=tree1.presum(r)*(r+1)-tree2.presum(r);
		if(l-1) ans-=tree1.presum(l-1)*(l)-tree2.presum(l-1);
		return ans;
	}
};