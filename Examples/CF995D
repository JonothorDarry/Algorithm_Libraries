//https://codeforces.com/contest/995/submission/41969279
#include <stdio.h>
const int C=7500001, D=20, GG=200;
typedef long long ll;
 
int v[2][C], lst[2][C], pos[2][C], end[501], ie=GG, fin, p, desolate=1000000000;
char mv[2][C];
 
ll c;
inline ll pow (ll a, ll b, ll M){
	if (b==0)	return 1;
	c=1;
	while (b>0){
		if (b%2==1)	c=(c*a)%M;
		b/=2;
		a=(a*a)%M;
	}
	return c;
}
 
int pom[C], pom2[C];
void Sebasort (int tab[], int tab2[], int l, int r){
	int lim=2, limi=l+1, limj=l+2, j=limi, i=l, k=l;
	while (lim/2<=r-l+1){
		while (i<=r){
			if (limj>r)	limj=r+1;
			if ((tab[j]<tab[i]&&j<limj)||i>=limi)	pom[k]=tab[j], pom2[k]=tab2[j], j++;
			else pom[k]=tab[i], pom2[k]=tab2[i], i++;
			k++;
			if (i==limi&&j==limj)	{
				limi+=lim, limj+=lim, i=j, j=limi;
				if (limj>r)	limj=r+1;
			}
		}
		for (i=l;i<=r;i++)	tab[i]=pom[i], tab2[i]=pom2[i];
		lim*=2, limi=l+lim/2, limj=l+lim, j=limi, i=k=l;
		if (limj>r)	limj=r+1;
	}
}
 
 
inline int add(int a)	{return (a+1)%p;}
inline int rev(int a)	{return pow(a, p-2, p);}
inline int sub(int a){
	if (a==0)	return p-1;
	return (a-1)%p;
}
 
inline int abs(int a){
	if (a>=0)	return a;
	return -a;
}
 
void turn_loose_the_swans(int a, int k){
	int i, j, end=0, beg=0, aend=1;
	v[k][0]=a, lst[k][0]=-1000, mv[k][0]=4;
	
	for (i=0;i<D;i++){
		for (j=beg;j<=end;j++){
			v[k][aend]=rev(add(v[k][j])), v[k][aend+1]=rev(sub(v[k][j]));
			lst[k][aend]=j, lst[k][aend+1]=j;
			mv[k][aend]=1, mv[k][aend+1]=3;
			
			if (mv[k][j]==4)	lst[k][aend+2]=j, v[k][aend+2]=rev(v[k][j]), mv[k][aend+2]=2, aend++;
			aend+=2;
		}
		beg=end+1, end=aend-1;
	}
	fin=end;
}
 
int main(){
	int i=0, j=0, x, bg, a, b;
	
	
	scanf ("%d %d %d", &a, &b, &p);
	turn_loose_the_swans(a, 0);
	turn_loose_the_swans(b, 1);
	for (i=0;i<fin;i++)	pos[0][i]=pos[1][i]=i;
	
	Sebasort(v[0], pos[0], 0, fin-1);
	Sebasort(v[1], pos[1], 0, fin-1);
	
	
	for (i=0;i<fin;){
		if (abs(v[0][i]-v[1][j])<121)	break;
		if (v[0][i]-v[1][j]>0)	j++;
		else i++;
	}
	
	
	x=pos[0][i];
	for (;lst[0][x]!=-1000;x=lst[0][x]){
		if (mv[0][x]==1)		end[ie]=3, end[ie-1]=1, ie--;
		else if (mv[0][x]==3)	end[ie]=3, end[ie-1]=2, ie--;
		else end[ie]=3;
		ie--;
	}
	
	ie++, bg=ie, ie=GG+1;
	
	
	while (v[0][i]!=v[1][j]){
		if (v[0][i]<v[1][j])	end[ie]=1, v[0][i]++;
		else end[ie]=2, v[0][i]--;
		ie++;
	}
	
	x=pos[1][j];
	for (;lst[1][x]!=-1000;x=lst[1][x]){
		if (mv[1][x]==1)		end[ie]=3, end[ie+1]=2, ie++;
		else if (mv[1][x]==3)	end[ie]=3, end[ie+1]=1, ie++;
		else end[ie]=3;
		ie++;
	}
	
	printf ("%d\n", ie-bg);
	for (i=bg;i<ie;i++)	printf ("%d ", end[i]);
	
	
return 0;}
