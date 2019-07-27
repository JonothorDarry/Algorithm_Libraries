//https://codeforces.com/contest/914/submission/50987283
#include <stdio.h>
#include <vector>
using namespace std;
typedef long long ll;
const int C=100101, K=26, LS=401, LN=301;
 
int sget(char tab[]){
	for (int z=0;;z++){
		tab[z]=getchar();
		if (tab[z]<=32)	return z;
	}
}
 
//Dekompozycja przestrzeni do pierwiastka od 0 do b włącznie, podział co div
int bg[LS], ende[LS], bel[C];
void sqrt_deco(int b, int div){
	int i, ib=-1;
	for (i=0;i<=b;i++){
		if (i%div==0){
			ib++;
			bg[ib]=i;
			if (ib>0)	ende[ib-1]=i-1;
		}
		bel[i]=ib;
	}
	ende[ib]=i-1;
}
 
 
int lens[LN][2*LS], suf[LN][2*LS], All[LN][2*LS][K], trans[LN][2*LS][K], ij[LN][2*LS], Pre[LN][2*LS];
 
void add_trans(int p, int x, int y, int s){
	trans[p][x][y]=s, All[p][x][ij[p][x]]=y, ij[p][x]++;
}
 
vector <vector <int> > tr(C);
int ji[C];
 
void tradd(int a, int b){
	tr[a].push_back(b), tr[b].push_back(a);
	ji[a]++, ji[b]++;
}
 
int s[C], is=0, son[LN][2*LS+1], par[C];
void tree_slay(int p, int a, int n, vector <vector <int> > &tab, int ji[]){
	s[0]=a, is=1;
	int b, i;
	par[a]=0;
	
	while (is>0){
		a=s[is-1];
		if (ji[a]>0&&tab[a][ji[a]-1]==par[a])	ji[a]--;
		if (ji[a]>0)	b=s[is]=tab[a][ji[a]-1], par[b]=a, is++, ji[a]--;
		else son[p][a]+=((Pre[p][a-1]==1)?1:0), son[p][par[a]]+=son[p][a], is--;
	}
	
	for (i=1;i<=n;i++)	ji[i]=0, par[i]=0, tr[i].clear();
}
 
//Tworzenie Automata na zadanym indeksie - od l do r
void create_automata(int p, int l, int r, char k[]){
	int i=0, j, x, last=0, nos=1, y, z, gg;
	
	lens[p][last]=0;
	suf[p][last]=0;
	
	for (i=l;i<=r;i++){
		x=last, last=nos, y=k[i]-97;
		lens[p][nos]=lens[p][x]+1;
		Pre[p][nos]=1;
		
		for (;x>0&&trans[p][x][y]==0;x=suf[p][x]) 	add_trans(p, x, y, nos);
		
		gg=trans[p][x][y];
		if (trans[p][x][y]==0)				add_trans(p, x, y, nos), suf[p][nos]=x;
		else if (lens[p][gg]==lens[p][x]+1)	suf[p][nos]=gg;
		else{
			z=nos+1;
			suf[p][z]=suf[p][gg];
			suf[p][nos]=suf[p][gg]=z;
			lens[p][z]=lens[p][x]+1;
			
			for (j=0;j<ij[p][gg];j++)	add_trans(p, z, All[p][gg][j], trans[p][gg][All[p][gg][j]]);
			
			for (;trans[p][x][y]==gg&&x>0;x=suf[p][x])	trans[p][x][y]=z;
			if (trans[p][x][y]==gg)	trans[p][x][y]=z;
			
			nos++;
		}
		nos++;
	}
	
	for(i=1;i<nos;i++)	tradd(i+1, suf[p][i]+1);
	tree_slay(p, 1, nos, tr, ji);
}
 
void pure_automata(int p){
	int i, j;
	for (i=0;i<2*LS;i++){
		son[p][i]=0;
		suf[p][i]=0;
		for (j=0;j<ij[p][i];j++)	trans[p][i][All[p][i][j]]=0;
		ij[p][i]=0;
		lens[p][i]=0;
		Pre[p][i]=0;
	}
	son[p][i]=0;
}
 
int penetrate_automata(int p, char k[], int n){
	int i, x=0;
	for (i=0;i<n;i++){
		if (trans[p][x][k[i]-97]==0)	break;
		x=trans[p][x][k[i]-97];
	}
	
	if (i<n) return 0;
	else 	 return son[p][x+1];	
}
 
//p - dosłownie ojciec, martwy - -1
void KM(char tab[], int p[], int n){
	p[0]=-1;
	for (int i=1;i<n;i++){
		p[i]=p[i-1];
		for (;p[i]>-1;p[i]=p[p[i]])	if (tab[i]==tab[p[i]+1])	break;
		if (tab[i]==tab[p[i]+1])	p[i]++;
	}
}
 
//zaznacza w tab1 tabliczkę Pi od tab2
int FindStr(char tab1[], int b1, int n1, char tab2[], int n2, int p[]){
	int j=-1, ww=0;
	for (int i=b1;i<=n1;i++){
		while (j>=0&&tab1[i]!=tab2[j+1])	j=p[j];
		
		if (tab1[i]==tab2[j+1])	j++;
		if (j+1==n2)	ww++, j=p[j];
	}
	return ww;
}
 
char k[C], kp[C], qq;
int p[C];
int main(){
	int n, i, j, q, w, a, b, np, wynn=0;
	n=sget(k);
	sqrt_deco(n-1, LS);
	for (i=0;ende[i]>0;i++)		create_automata(i, bg[i], ende[i], k);		
		
	scanf ("%d", &q);	
	
	for (i=0;i<q;i++){
		scanf ("%d", &w);
		if (w==1){
			scanf ("%d", &a); getchar();
			a--;
			k[a]=getchar();
			a=bel[a];
			pure_automata(a);
			create_automata(a, bg[a], ende[a], k);
		}
		
		if (w==2){
			scanf ("%d %d", &a, &b), getchar();
			a--, b--;
			np=sget(kp);
			KM(kp, p, np);
			
			if (bel[a]==bel[b]||np>LS)	wynn=FindStr(k, a, b, kp, np, p);
			else {
				for (j=bel[a]+1;j<bel[b];j++){
					wynn+=FindStr(k, max(ende[j-1]-np+2, a), bg[j]+np-2, kp, np, p);
					wynn+=penetrate_automata(j, kp, np);
				}
				wynn+=FindStr(k, max(ende[j-1]-np+2, a), min(bg[j]+np-2, b), kp, np, p);
				wynn+=FindStr(k, a, ende[bel[a]], kp, np, p);
				wynn+=FindStr(k, bg[bel[b]], b, kp, np, p);	
			}
			
			
			printf ("%d\n", wynn);
			wynn=0;
		}
	}
	
return 0;}
