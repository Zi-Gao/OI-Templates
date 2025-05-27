#define EXGCD_DATA_TYPE long long
EXGCD_DATA_TYPE exgcd(EXGCD_DATA_TYPE a,EXGCD_DATA_TYPE b,EXGCD_DATA_TYPE &x,EXGCD_DATA_TYPE &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    EXGCD_DATA_TYPE d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}