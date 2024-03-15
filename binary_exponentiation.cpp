int binary_expo(int base,int power)
{
	if(power==0) return 1;
	int ret=binary_expo(base,power>>1);
	ret=(ret*ret)%MOD;
	if(power&1) return (ret*ret*base)%MOD;
	else return ret%MOD;
}
