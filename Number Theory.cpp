#include <stdio.h>
#include <vector>
#define C 1001
typedef long long ll;
using namespace std;

long long cn[C][C], M=1000000007;

void newton(int f, int M){
	int i=1, j=1;
	cn[0][0]=1;
	for (i=1;i<=f;i++)	{
		cn[i][0]=1;
		for (j=1;j<=i;j++)	cn[i][j]=(cn[i-1][j-1]+cn[i-1][j])%M;
	}
}

inline ll pow (ll a, ll b, ll M){
	if (b==0)	return 1;
	ll c=1;
	while (b>0){
		if (b%2==1)	c=(c*a)%M;
		b/=2;
		a=(a*a)%M;
	}
	return c;
}


pair <int, int> Euclid (int a, int b){
	int x1=0, x2=1, y1=1, y2=0, q=a/b, r=a-q*b, x, y, wynn;
	x=1, y=y2-(q-1)*y1;
	while (r!=0){
		a=b, b=r;
		x=x2-q*x1, x2=x1, x1=x;
		y=y2-q*y1, y2=y1, y1=y;
		wynn=r, q=a/b, r=a-q*b;
	}
	return make_pair (x,y);
}

inline ll fib(ll b, ll M){
	ll c1=1, c2=1, c3=1, c4=0, a1=1, a2=1, a3=1, a4=0, p1, p2, p3, p4;
	while (b>0){
		if (b%2==1)	{
			p1=c1*a1+c2*a3;
			p2=c1*a2+c2*a4;
			p3=c3*a1+c4*a3;
			p4=c3*a2+c4*a4;
			c1=p1%M, c2=p2%M, c3=p3%M, c4=p4%M;
		}
		
		p1=a1*a1+a2*a3;
		p2=a1*a2+a2*a4;
		p3=a3*a1+a4*a3;
		p4=a3*a2+a4*a4;
		a1=p1%M, a2=p2%M, a3=p3%M, a4=p4%M;
		b/=2;
	}
	
	return c4;
}


int f[C];
void supfactor(int v){
	int i, j;
	f[1]=1;
	for (i=2;i*i<v;i++){
		if (f[i]==0) for (j=i;j<v;j+=i)	f[j]=i;
	}
	
	for (;i<v;i++)	if (f[i]==0)	f[i]=i;
}


int dv[C], sgn[C], a[20], lim;
void generate(int n){
	int j=0, i=0;
	dv[0]=1, lim=1;
	while (i<n){
		while (j<lim){
			dv[j+lim]=dv[j]*a[i];
			sgn[j+lim]=(sgn[j]^1);
			j++;
		}
		j=0, lim=lim*2, i++;
	}
}

inline long long cn(int n, int k) {return (((fac[n]*af[k])%M)*af[n-k])%M;}
