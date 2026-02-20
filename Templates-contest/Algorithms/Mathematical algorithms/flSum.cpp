#define FLSUM_TYPE long long
const FLSUM_TYPE FLSUM_MOD=mod;
FLSUM_TYPE flSum(FLSUM_TYPE n,FLSUM_TYPE a,FLSUM_TYPE b,FLSUM_TYPE c){
	FLSUM_TYPE ac=a/c,bc=b/c,m=(a*n+b)/c;
	if(!a) return (n+1)*bc%FLSUM_MOD;
	if(a>=c||b>=c) return (n*(n+1)/2%FLSUM_MOD*ac+(n+1)*bc+flSum(n,a%c,b%c,c))%FLSUM_MOD;
	return (m*n+FLSUM_MOD-flSum(m-1,c,c-b-1,a))%FLSUM_MOD;
}