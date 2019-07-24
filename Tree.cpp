#include <stdio.h>
#include <vector>
#define trdef for (int z=1;z<n;z++)	scanf ("%d %d", &a, &b), tr[a].push_back(b), tr[b].push_back(a), ij[a]++, ij[b]++
using namespace std;
typedef long long ll;
const int C=100001;

vector <vector <int> > tr(C);
int ij[C], a, b, n;

void tradd(int a, int b){
	tr[a].push_back(b);
	tr[b].push_back(a);
	ij[a]++, ij[b]++;
}

int main(){
	scanf ("%d", &n);
	trdef;
return 0;}


//holistyczna penetracja - argumenty - korzeñ, liczba wierzcho³ków, drzewo
//pre - preorder, apre - odwrotnoœæ preordera
int s[C], is=0, ip=1, pre[C], apre[C], dep[C], son[C], par[C], ji[C];
void proc_tree(int a, int n, vector <vector <int> > &tab, int ij[]){
	s[0]=a, is=1, pre[a]=1, apre[1]=a, dep[a]=1, ip=2;
	int b;
	
	for(int z=1;z<=n;z++)	ji[z]=ij[z], par[z]=0;
	
	while (is>0){
		a=s[is-1];
		if (ji[a]>0&&tab[a][ji[a]-1]==par[a])	ji[a]--;
		if (ji[a]>0)	b=s[is]=tab[a][ji[a]-1], pre[b]=ip, apre[ip]=b, par[b]=a, dep[b]=is+1, ip++, is++, ji[a]--;
		else son[a]++, son[par[a]]+=son[a], is--;
	}
}


// lca n*logn+q*logn

int s[C], is=0, ip=1, pre[C], dep[C], son[C], par[21][C], ji[C];
void proc_tree(int a, int n, vector <vector <int> > &tab, int ij[]){
	s[0]=a, is=1, pre[a]=1, dep[a]=1, ip=2;
	int b;
	
	for(int z=1;z<=n;z++)	ji[z]=ij[z];
	
	while (is>0){
		a=s[is-1];
		if (ji[a]>0&&tab[a][ji[a]-1]==par[0][a])	ji[a]--;
		if (ji[a]>0)	b=s[is]=tab[a][ji[a]-1], pre[b]=ip, par[0][b]=a, dep[b]=is+1, ip++, is++, ji[a]--;
		else son[a]++, son[par[0][a]]+=son[a], is--;
	}
}
//f - licba poziomów
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

//k-ty przodek a
int kth_anc(int a, int k){
	int i=0;
	while (k>0){
		if (k%2==1)	a=par[i][a];
		k/=2, i++;
	}
	return a; 
}
//zamieniæ f!
int lca (int a, int b, int f=19){
	if (anc(a, b)==1)	return a;
	if (anc(b, a)==1)	return b;
	
	int i=f, x=a;
	while (i>=0){
		if (anc(par[i][x], b)==1)	i--;
		else x=par[i][x];
	}
	return par[0][x];
}

inline int dis(int a, int b)	{return dep[a]+dep[b]-2*dep[lca(a, b)];}


//dekompozycja(hld) + podrasowana penetracja
//mxson - najwiêkszy rozmiarem syn
int dep[C], pre[C], par[21][C], son[C], s[C], ji[C], v[C], prv[C], nxt[C], mxson[C];
void proc_tree(int a, int n, vector <vector <int> > &tab, int ij[]){
	int is=0, b, ip=2;
	for (int z=1;z<=n;z++)	ji[z]=ij[z];
	s[0]=a, is=1, pre[a]=1, dep[a]=1;
	while (is>0){
		a=s[is-1];
		if (ji[a]>0&&par[0][a]==tab[a][ji[a]-1])	ji[a]--;
		if (ji[a]>0) b=s[is]=tab[a][ji[a]-1], v[b]=e[a][ji[a]-1], par[0][b]=a, pre[b]=ip, dep[b]=is+1, ji[a]--, ip++, is++;
		
		else{
			son[a]++;
			son[par[0][a]]+=son[a];
			if (son[a]>mxson[par[0][a]])	nxt[par[0][a]]=a, mxson[par[0][a]]=son[a];
			is--;
		}		
	}
	
	for (int z=1;z<=n;z++)	if (nxt[z]>0)	prv[nxt[z]]=z;
}
//pos - pozycja v w drzewie przedzia³owym, beg - pocz¹tek ³añcucha, parch - przejœcie do poprzedniego ³añcucha (³añcuch -> v), vch - v nale¿y do ³añcucha vch[v]
int vch[C], beg[C], pos[C], parch[C];
void hld(int n){
	int sum=0, ich=0, x;
	
	for (int i=1;i<=n;i++){
		if (prv[i]==0){
			x=i, beg[ich]=sum, parch[ich]=par[0][x];
			while (nxt[x]!=0){
				vch[x]=ich, pos[x]=sum;
				sum++, x=nxt[x];
			}
			vch[x]=ich, pos[x]=sum;
			sum++, ich++;
		}
	}
}



//Centroid decomposition - pctr-ojciec w dekompozycji, po przetworzeniu drzewa, res którey stopieñ centroida (u¿ywa odwrotnoœci preordera apre z proc_tree)
bool dead[C];
int cnt[C], sonn[C], mxson[C], res[C], ClT[C], par[C], apre[C], pctr[C];
void centroid_decompose(int n){
	int slain=0, i, j, gg, a, b, x, kp=1;
	
	for (slain=0;slain<n;){
		for (j=0;j<=n;j++)	mxson[j]=sonn[j]=0, cnt[j]=0;
		dead[0]=1;
		for(j=n;j>0;j--){
			a=apre[j], sonn[a]++;
			if (dead[a]==1)	continue;
			
			if (sonn[a]>sonn[mxson[par[a]]])	mxson[par[a]]=a;
			if (sonn[a]-sonn[mxson[a]]>=sonn[mxson[a]])	cnt[a]=a;
			else{
				gg=sonn[a]-sonn[a]/2;
				for (x=cnt[mxson[a]];sonn[x]<gg;x=par[x]);
				cnt[a]=x;
			}
			if (dead[par[a]]==1){
				res[cnt[a]]=kp;
				dead[cnt[a]]=1;
				slain++;
				if (ClT[a]!=0)	pctr[cnt[a]]=ClT[a];
			}
			else sonn[par[a]]+=sonn[a];
		}
		for (j=1;j<=n;j++){
			a=apre[j];
			if (dead[par[a]]==1&&res[par[a]]!=kp)	ClT[a]=cnt[a];
			else ClT[a]=ClT[par[a]];
		}
		kp++;
	}
}



//Eleganckie lca z RMQ - O(nlogn)+O(q)
int dep[C], is, fw[2*C], rmq[21][C], ir=0, son[C], pre[C], par[C], ip=0, s[C], ji[C];
void proc_tree(int a, int n, vector <vector <int> > &tab, int ij[]){
	s[0]=a, is=1, dep[a]=1, pre[a]=1, dep[a]=1, ip=2;
	int b;
	for(int z=1;z<=n;z++)	ji[z]=ij[z];
	rmq[0][ir]=a, fw[a]=0, ir=1;
	
	
	while (is>0){
		a=s[is-1];
		if (ji[a]>0&&tab[a][ji[a]-1]==par[a])	ji[a]--;
		if (ji[a]>0)	rmq[0][ir]=b=s[is]=tab[a][ji[a]-1], fw[b]=ir, ir++, par[b]=a, pre[b]=ip, dep[b]=is+1, is++, ip++, ji[a]--;
		else son[a]++, son[par[a]]+=son[a], is--;
	}
}


int lg[C], pw[22];
void prep_lca(int f, int n){
	int x, i, j;
	for (j=1;j<f;j++){
		x=1<<(j-1);
		for (i=0;i+x<n;i++){
			if (i+x<n&&dep[rmq[j-1][i]]>dep[rmq[j-1][i+x]])	rmq[j][i]=rmq[j-1][i+x];
			else rmq[j][i]=rmq[j-1][i];
		}
	}
	lg[0]=0, lg[1]=0, pw[0]=1;
	for (i=2;i<=n;i++)	lg[i]=lg[i/2]+1;
	for (i=1;i<=21;i++)	pw[i]=pw[i-1]*2;
}

int anc(int a, int b){
	if (pre[a]<=pre[b]&&pre[a]+son[a]>pre[b])	return 1;
	return 0;
}

int lca (int a, int b){
	if (anc(a, b))	return a;
	if (anc(b, a))	return b;
	if (fw[a]>fw[b])	a=a+b, b=a-b, a=a-b;
	
	int x=fw[a], dg=lg[fw[b]-fw[a]], y=fw[b]-pw[dg]+1;
	
	if (dep[rmq[dg][x]]>dep[rmq[dg][y]]) return par[rmq[dg][y]];
	return par[rmq[dg][x]];
}
