#define LOWER_BOUND_DATA_TYPE long long
LOWER_BOUND_DATA_TYPE *lower_bound(LOWER_BOUND_DATA_TYPE *first,LOWER_BOUND_DATA_TYPE *last,LOWER_BOUND_DATA_TYPE key){
    register int mid,left=0,right=last-first;
    while(left<right){
        mid=(left+right)>>1;
        if(*(first+mid)<=key) left=mid+1;
        else right=mid;
    }
    return first+left;
}