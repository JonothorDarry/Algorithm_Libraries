//https://codeforces.com/contest/1055/submission/51302547
#include <stdio.h>
#include <vector>
using namespace std;
typedef long long ll;
const int C=1000001, D=63, H=62;
 
int lmost[5*C], lst=1, a, b, n;
ll pw[D], f[2*C], v[C], wynn=0, ps[C], dead[C];
 
int leftmost(ll a){
	ll v3=pw[H]-pw[21];
	int k=0;
	
	for (;;a/=pw[21]){
		if ((a&v3)==0)	return k+lmost[a];
		k+=21;
	}
}
 
int tri[2*C][2], len[2*C], sumv[2*C];
void insert(ll a){
	int j=0, pr=-1, gg, v1, v2;
	ll mk, k;
	
	while (1){
		mk=pw[H]-pw[H-len[j]];
		k=((a^f[j])&mk);
		
		if (k!=0){
			gg=leftmost(k);
			len[lst]=H-gg;
			len[lst+1]=H;
			f[lst]=f[lst+1]=a;
			v1=(((a&pw[gg-1])>0)?1:0);
			
			tri[lst][v1]=lst+1;
			tri[lst][1-v1]=j;
			tri[pr][v2]=lst;
			
			sumv[lst]=sumv[j]+1, sumv[lst+1]++;
			lst+=2;
			return;
		}
		
		sumv[j]++;
		if (len[j]==H)	return;
		gg=(((pw[H-len[j]-1]&a)>0)?1:0);
		if (tri[j][gg]==0){
			tri[j][gg]=lst;
			
			len[lst]=H;
			f[lst]=a;
			sumv[lst]++;
			lst++;
			
			return;				
		}
		else	pr=j, v2=gg, j=tri[j][gg];
	}
}
 
 
 
int main(){
	int k, i, j, a, x, RR;
	ll summ=0, V;
	
	pw[0]=1;
	for (i=1;i<D;i++)		pw[i]=pw[i-1]*2;
	for (i=1;i<pw[22];i++)	lmost[i]=lmost[i/2]+1;
	
	scanf ("%d %lld", &n, &V);
	for (i=2;i<=n;i++){
		scanf ("%d %lld", &a, &v[i]);
		v[i]^=v[a];
	}
	for (i=1;i<=n;i++)	insert(v[i]);
	
	for (j=1;j<=H;j++){
		for (i=1;i<=n;i++){
			if (dead[i])	continue;
			
			k=(((v[i]&pw[H-j])>0)?1:0);
			if (len[ps[i]]>=j){
				x=(((f[ps[i]]&pw[H-j])>0)?1:0);
				if (x==k)	summ+=sumv[ps[i]];
			}
			else if (tri[ps[i]][k]>0)	summ+=sumv[tri[ps[i]][k]];
		}
		
		if (summ>=V)	RR=0;
		else V-=summ, wynn+=pw[H-j], RR=1;
		
		for (i=1;i<=n;i++){
			if (dead[i])	continue;
			
			k=(((v[i]&pw[H-j])>0)?1:0);
			if (RR==1)	k=1-k;
			
			if (len[ps[i]]>=j){
				x=(((f[ps[i]]&pw[H-j])>0)?1:0);
				if (x!=k)	dead[i]=1;
			}
			else if (tri[ps[i]][k]>0)	ps[i]=tri[ps[i]][k];	
			else dead[i]=1;	
		}
		summ=0;
	}
	
	printf ("%lld\n", wynn);
	
return 0;}
