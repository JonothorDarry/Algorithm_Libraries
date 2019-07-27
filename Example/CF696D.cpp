//https://codeforces.com/contest/696/submission/50393992
#include <stdio.h>
#include <vector>
typedef long long ll;
using namespace std;
const int C=202;
 
int trie[C][26], iss[C], lst=1, ev[C];
void insert(char tab[], int n, int w){
	int a=0, i, x;
	for (i=0;i<n;i++){
		x=tab[i]-97;
		if (trie[a][x]==0)	trie[a][x]=lst, a=lst, lst++;
		else a=trie[a][x];
	}
	iss[a]=1, ev[a]+=w;
}
 
 
//Aho-corasick z Trie
//fal[a] - fałszywa krawędź, do której się odwołuje a (wyżej w trie)
int F[C], cF[C], iF=0, jF, fal[C];
void false_flag(){
	int i, a;
	F[0]=0, iF=0, jF=1, fal[0]=0;
	
	for (;iF<jF;iF++){
		a=F[iF];
		for (;fal[a]>0;fal[a]=fal[fal[a]])	if (trie[fal[a]][cF[iF]]>0)	break;
		//trie[fal[a]][cF[iF]]!=a eliminuje przypadek, gdy litera jest pierwsza od korzenia - wtedy fal=0, nie ona sama.
		if (trie[fal[a]][cF[iF]]>0&&trie[fal[a]][cF[iF]]!=a&&a!=0)	fal[a]=trie[fal[a]][cF[iF]];
		
		ev[a]+=ev[fal[a]];
		
		for (i=0;i<26;i++)	{
			if (trie[a][i]!=0){
				F[jF]=trie[a][i], cF[jF]=i, fal[F[jF]]=fal[a], jF++;
			}
		}
	}
}
 
//Wczytywanie stringa
int sget(char tab[]){
	for (int z=0;;z++){
		tab[z]=getchar();
		if (tab[z]<=32)	return z;
	}
}
 
ll l, dp[C][C], mx=0;
int n, v[C], cor[C][C];
char q, ff[C];
 
void pw(int a[][C], ll b[][C], int a2[][C], ll b2[][C], int pa[][C], ll pb[][C], int n){
	int i, j, k;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			for (k=0;k<n;k++){
				pa[i][j]=max(pa[i][j], a[i][k]*a2[k][j]);
				pb[i][j]=max(pb[i][j], a[i][k]*a2[k][j]*(b[i][k]+b2[k][j]));
			}
		}
	}
}
 
void cop(ll a[][C], ll b[][C], int n){
	int i, j;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			b[i][j]=a[i][j];
		}
	}
}
void cop2(int a[][C], int b[][C], int n){
	int i, j;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			b[i][j]=a[i][j];
		}
	}
}
 
 
ll pdp[C][C], rdp[C][C];
int pcor[C][C], rcor[C][C];
void power_matrix(long long b, int n){
	int i, j;
	for (i=0;i<n;i++)	rcor[i][i]=1;
	
	for (;b>0;b/=2){
		if (b%2==1)	pw(cor, dp, rcor, rdp, pcor, pdp, n), cop(pdp, rdp, n), cop2(pcor, rcor, n);
		pw(cor, dp, cor, dp, pcor, pdp, n), cop(pdp, dp, n), cop2(pcor, cor, n);
	}
	
}
 
 
int main(){
	int i, x, j, a;
	
	scanf ("%d %lld", &n, &l);
	for (i=0;i<n;i++)	scanf ("%d", &v[i]);
	q=getchar();
	
	for (i=0;i<n;i++){
		x=sget(ff);
		insert(ff, x, v[i]);
	}
	false_flag();
	
	
	for (i=0;i<lst;i++){
		for (j=0;j<26;j++){
			a=i;
			while (trie[a][j]==0&&a>0)	a=fal[a];
			if (trie[a][j]>0)	dp[i][trie[a][j]]=ev[trie[a][j]], cor[i][trie[a][j]]=1;
			else cor[i][0]=1;
		}
	}
	power_matrix(l, lst);	
	
	for (i=0;i<lst;i++)	if (rdp[0][i]>mx)	mx=rdp[0][i];
	printf ("%lld\n", mx);
	
return 0;}
