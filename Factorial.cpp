int factorial[1000008];
const int MOD=1e9+7;

void fact(){
	factorial[0]=1;
	for(int i=1;i<1000008;i++){
		factorial[i]=(factorial[i-1]*i)%MOD;
	}
}
