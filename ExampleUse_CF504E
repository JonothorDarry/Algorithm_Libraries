//https://codeforces.com/contest/504/submission/50572317
#include <stdio.h>
#include <vector>
#define trdef for (int z=1;z<n;z++)	scanf ("%d %d", &a, &b), tr[a].push_back(b), tr[b].push_back(a), ij[a]++, ij[b]++
typedef long long ll;
using namespace std;
const int C=1201001, D=400001, L=22;
 
vector <vector <int> > tr(D);
int ij[D], a, b, n;
 
struct pathway{
	int a, b, dir, len;//Ścieżyna w hld, a-początek, b - koniec, kierunek(0-dół, 1-góra), len-długość.
};
 
 
//Sort przez zliczanie
int pom[C], pom2[C], pom3[C], tw[C];
void countsort(int t1[], int t2[], int t3[], int n){
	int i, lst=0, c, mx=0;
	for (i=0;i<=n;i++){
		tw[t1[i]]++;
		if (t1[i]>mx)	mx=t1[i];
	}
	
	for (i=0;i<=mx;i++)	if (tw[i]>0)	c=tw[i], tw[i]=lst, lst+=c;
	for (i=0;i<=n;i++){
		c=tw[t1[i]];
		pom[c]=t1[i], pom2[c]=t2[i], pom3[c]=t3[i];
		tw[t1[i]]++;
	}
	for (i=0;i<=n;i++)	tw[i]=0, t1[i]=pom[i], t2[i]=pom2[i], t3[i]=pom3[i];
	for (i=n;i<=mx;i++)	tw[i]=0;
}
//lcp 2 kolejnych pozycji, L ustawić na co najmniej sufit logn+1
int tk[L][C], pw[L], pos[C], pa[C], pb[C];
int lcp(int a, int b, int j){
	int wn=0;
	while (j>=0){
		if (tk[j][a]!=tk[j][b])	j--;
		else wn+=pw[j], a+=pw[j], b+=pw[j];
	}
	return wn;
}
//sa- tablica, której kolejnymi wartościami są pozycje w tekście k o dł. n, na których zaczynają się kolejne najmniejsze sufixy; lcp - lcpv[i] - lcp pomiędzy sa[i], sa[i+1]
void suf_arr(int k[], int n, int sa[], int lcpv[]){
	int i, j;
	for (i=0;i<L;i++)	pw[i]=1<<i;
	for (i=0;i<n;i++)	tk[0][i]=k[i];
	for (j=1;pw[j]<n;j+=1){
		for (i=0;i<n;i++){
			if (i+pw[j-1]<n)	pb[i]=tk[j-1][i+pw[j-1]];
			else pb[i]=0;
			pa[i]=tk[j-1][i];
			pos[i]=i;
		}
		
		countsort(pb, pa, pos, n-1);
		countsort(pa, pb, pos, n-1);
		
		tk[j][pos[0]]=1;
		for (i=1;i<n;i++){
			if ((pa[i]>pa[i-1])||(pa[i]==pa[i-1]&&pb[i]>pb[i-1]))	tk[j][pos[i]]=tk[j][pos[i-1]]+1;
			else tk[j][pos[i]]=tk[j][pos[i-1]];
		}
	}
	for (i=0;i<n;i++)	pa[i]=tk[j-1][i], pos[i]=i;
	countsort(pa, pos, pb, n-1);
	for (i=0;i<n-1;i++)	sa[i]=pos[i], lcpv[i]=lcp(pos[i], pos[i+1], j-1);
	lcpv[n-1]=0, sa[n-1]=pos[n-1];
}
 
//dekompozycja(hld) + podrasowana penetracja
//mxson - największy rozmiarem syn
int dep[D], pre[D], par[L][D], son[D], s[D], ji[D], prv[D], nxt[D], mxson[D];
void proc_tree(int a, int n, vector <vector <int> > &tab, int ij[]){
	int is=0, b, ip=2;
	for (int z=1;z<=n;z++)	ji[z]=ij[z];
	s[0]=a, is=1, pre[a]=1, dep[a]=1;
	while (is>0){
		a=s[is-1];
		if (ji[a]>0&&par[0][a]==tab[a][ji[a]-1])	ji[a]--;
		if (ji[a]>0) b=s[is]=tab[a][ji[a]-1], par[0][b]=a, pre[b]=ip, dep[b]=is+1, ji[a]--, ip++, is++;
		
		else{
			son[a]++;
			son[par[0][a]]+=son[a];
			if (son[a]>mxson[par[0][a]])	nxt[par[0][a]]=a, mxson[par[0][a]]=son[a];
			is--;
		}
	}
	
	for (int z=1;z<=n;z++)	if (nxt[z]>0)	prv[nxt[z]]=z;
}
 
void prep_lca(int f, int n){
	par[0][1]=1;
	for (int j=1;j<f;j++){
		for (int i=1;i<=n;i++){
			par[j][i]=par[j-1][par[j-1][i]];
		}
	}
}
//Czy a jest przodkiem b?
int anc(int a, int b){
	if (pre[a]<=pre[b]&&pre[a]+son[a]>pre[b])	return 1;
	return 0;
}
 
int kth_anc(int a, int k){
	int i=0;
	while (k>0){
		if (k%2==1)	a=par[i][a];
		k/=2, i++;
	}
	return a; 
}
 
//zamienić f!
int lca (int a, int b, int f=21){
	if (anc(a, b)==1)	return a;
	if (anc(b, a)==1)	return b;
	
	int i=f, x=a;
	while (i>=0){
		if (anc(par[i][x], b)==1)	i--;
		else x=par[i][x];
	}
	return par[0][x];
}
 
char k[C], qq, g[C];
int all[C], m=0, sa[C], lp[C], ps[C], ps2[C], rl[C];
//pos - pozycja v w drzewie przedziałowym, beg - początek łańcucha w valu(ew. zmienić na 1. wyraz), parch - przejście do poprzedniego łańcucha (łańcuch -> v), vch - v należy do łańcucha vch[v]
int vch[C], beg[C], parch[C], f[C];
void hld(int n){
	int ich=0, x, j=0, jj=0;
	
	for (int i=1;i<=n;i++){
		if (prv[i]==0){
			x=i, beg[ich]=i, parch[ich]=par[0][x];
			while (nxt[x]!=0){
				vch[x]=ich;
				g[j]=k[x], ps[j]=x, j++;			
				x=nxt[x];
			}
			g[j]=k[x], ps[j]=x;
			
			for (jj=0;jj<=j;jj++)	all[m]=g[jj]+600011, rl[m]=ps[jj], m++;
			all[m]=2*ich, m++;
			for (jj=j;jj>=0;jj--)	all[m]=g[jj]+600011, rl[m]=-ps[jj], m++;
			all[m]=2*ich+1, m++;
			
			j=0, jj=0;
			vch[x]=ich;
			ich++;
		}
	}
}
 
pathway pure[2][42], pp[42];
int ip[2], rmq[L][C], lg2[C];
 
void rain_upon_the_pure(int a, int b, int x, int ll){
	int i=0, j=0, gg=0;
	
	while (1){
		if (vch[a]==vch[x])	{
			if (a!=x)	pure[ll][i].a=a, pure[ll][i].b=x, pure[ll][i].dir=1, pure[ll][i].len=dep[a]-dep[x]+1, a=x, i++, gg=1;
			break;
		}
		else pure[ll][i].a=a, pure[ll][i].b=beg[vch[a]], pure[ll][i].dir=1, pure[ll][i].len=dep[a]-dep[beg[vch[a]]]+1, a=parch[vch[a]];
		i++;
	}
	
	while (1){
		if (vch[b]==vch[x])	{
			if (gg==0)	pp[j].a=b, pp[j].b=x, pp[j].dir=0, pp[j].len=dep[b]-dep[x]+1, j++, b=x;
			break;
		}
		else pp[j].a=b, pp[j].b=beg[vch[b]], pp[j].dir=0, pp[j].len=dep[b]-dep[beg[vch[b]]]+1, b=parch[vch[b]];
		j++;
	}
	for (j--;j>=0;j--)	pure[ll][i]=pp[j], i++;
	ip[ll]=i;
}
 
int qlcp(pathway a, pathway b){
	int x, y, s;
	if (a.dir==1)	x=ps[a.a];
	else			x=ps2[a.b];
	if (b.dir==1)	y=ps[b.a];
	else			y=ps2[b.b];
	
	if (x>y)	x=x+y, y=x-y, x=x-y;
	if (x==y)	return min(a.len, b.len);
	
	y--;
	s=lg2[y-x];
	
	return min(rmq[s][x], rmq[s][y-pw[s]+1]);
}
 
int main(){
	int i, j, q, x, y, a, b, c, d, wynn=0;
	lg2[0]=lg2[1]=0;
	for (i=2;i<C;i++)	lg2[i]=lg2[i/2]+1;
	
	scanf ("%d", &n);
	qq=getchar();
	for (i=1;i<=n;i++)	k[i]=getchar();
	trdef;
	
	proc_tree(1, n, tr, ij);
	prep_lca(L, n);
	hld(n);
	suf_arr(all, m, sa, lp);
	
	for (i=0;i<m;i++){
		if (rl[sa[i]]<0)		ps[-rl[sa[i]]]=i;
		else if (rl[sa[i]]>0)	ps2[rl[sa[i]]]=i;
	}
	//for (i=1;i<=n;i++)	printf ("%d %d %d\n", i, ps[i], ps2[i]);
	
	for (i=0;i<m;i++)	rmq[0][i]=lp[i];
	for (j=1;j<L;j++){
		for (i=0;i<m;i++){
			if (i+pw[j-1]<m)	rmq[j][i]=min(rmq[j-1][i], rmq[j-1][i+pw[j-1]]);
			else rmq[j][i]=rmq[j-1][i];
		}
	}
	
	scanf ("%d", &q);
	while (q--){
		scanf ("%d %d %d %d", &a, &b, &c, &d);
		x=lca(a, b), y=lca(c, d);
		wynn=0;
		
		rain_upon_the_pure(a, b, x, 0);
		rain_upon_the_pure(c, d, y, 1);
		
		/*pathway r;
		for (i=0;i<ip[0];i++)	r=pure[0][i], printf ("%d %d %d %d\n", r.a, r.b, r.dir, r.len);
		printf ("\n");
		for (i=0;i<ip[1];i++)	r=pure[1][i], printf ("%d %d %d %d\n", r.a, r.b, r.dir, r.len);
		printf ("\n");*/
		
		for (i=0,j=0;i<ip[0]&&j<ip[1];){
			x=qlcp(pure[0][i], pure[1][j]);
			y=min(pure[0][i].len, pure[1][j].len);			
			wynn=wynn+min(x, y);
			if (x<y) break;
			
			if (pure[0][i].len==pure[1][j].len)	i++, j++;
			else if (pure[0][i].len<pure[1][j].len)	{
				if (pure[1][j].dir==1)	pure[1][j].a=kth_anc(pure[1][j].a, y);
				else					pure[1][j].b=kth_anc(pure[1][j].a, pure[1][j].len-y-1);
				pure[1][j].len=dep[pure[1][j].a]-dep[pure[1][j].b]+1;
				i++;
			}
			else{
				if (pure[0][i].dir==1)	pure[0][i].a=kth_anc(pure[0][i].a, y);
				else					pure[0][i].b=kth_anc(pure[0][i].a, pure[0][i].len-y-1);
				pure[0][i].len=dep[pure[0][i].a]-dep[pure[0][i].b]+1;
				j++;
			}
			
		}
		printf ("%d\n", wynn);
	}
	
return 0;}
