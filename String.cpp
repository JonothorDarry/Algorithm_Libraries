#include <stdio.h>
typedef long long ll;
const int C=100001, L=21;

void reverse(char t[], char t2[], int n)	{for (int i=0;i<n;i++)	t2[i]=t[n-i-1];}

//Wczytywanie stringa
int sget(char tab[]){
	for (int z=0;;z++){
		tab[z]=getchar();
		if (tab[z]<=32)	return z;
	}
}

//lepszy sget
int sget2(char tab[]){
	bool ff=0;
	for (int z=0;;z++){
		tab[z]=getchar();
		if (tab[z]>32)	ff=1;
		if (tab[z]<=32&&ff==1)	return z;
		else if (tab[z]<=32) z--;
	}
}

//p - dos³ownie ojciec, martwy - -1
void KM(char tab[], int p[], int n){
	p[0]=-1;
	for (int i=1;i<n;i++){
		p[i]=p[i-1];
		for (;p[i]>-1;p[i]=p[p[i]])	if (tab[i]==tab[p[i]+1])	break;
		if (tab[i]==tab[p[i]+1])	p[i]++;
	}
}

//zaznacza w tab1 tabliczkê Pi od tab2
void FindStr(char tab1[], int n1, char tab2[], int n2, int p[], int p2[]){
	int j=-1;
	for (int i=0;i<n1;i++){
		while (j>=0&&tab1[i]!=tab2[j+1])	j=p[j];
		
		if (tab1[i]==tab2[j+1])	j++;
		p2[i]=j+1;
		if (j+1==n2)	j=p[j];
	}	
}



//Trie - Rzut na drzewo
//Trie - struktura, iss - czy dany  punkt jest koñcem stringa, lst - koniec trie; argumenty - string i d³ugoœæ
int trie[C][26], iss[C], lst=1;
void insert(char tab[], int n){
	int a=0, i, x;
	for (i=0;i<n;i++){
		x=tab[i]-97;
		if (trie[a][x]==0)	trie[a][x]=lst, a=lst, lst++;
		else a=trie[a][x];
	}
	iss[a]=1;
}


//Aho-corasick z Trie
//fal[a] - fa³szywa krawêdŸ, do której siê odwo³uje a (wy¿ej w trie)
int F[C], cF[C], iF=0, jF, fal[C];
void false_flag(){
	int i, a;
	F[0]=0, iF=0, jF=1, fal[0]=0;
	
	for (;iF<jF;iF++){
		a=F[iF];
		for (;fal[a]>0;fal[a]=fal[fal[a]])	if (trie[fal[a]][cF[iF]]>0)	break;
		//trie[fal[a]][cF[iF]]!=a eliminuje przypadek, gdy litera jest pierwsza od korzenia - wtedy fal=0, nie ona sama.
		if (trie[fal[a]][cF[iF]]>0&&trie[fal[a]][cF[iF]]!=a&&a!=0)	fal[a]=trie[fal[a]][cF[iF]];
		
		for (i=0;i<26;i++)	{
			if (trie[a][i]!=0){
				F[jF]=trie[a][i], cF[jF]=i, fal[F[jF]]=fal[a], jF++;
			}
		}
	}
}

//Poszukiwanie wyrazów ze s³ownika w stringu k - Aho-corasick - zawsze matchowany maksymalny substring - fun[i]-punkt w trie, do którego mo¿na dojœæ do danego indeksu
int fun[C];
void penetrate(char k[], int n){
	int i, a=0, x;
	for (i=0;i<n;i++){
		x=k[i]-97;
		while (trie[a][x]==0&&a>0)	a=fal[a];
		if (trie[a][x]>0)			a=trie[a][x];
		fun[i]=a;
	}
}



//Znalezienie Suffix array + lcp - zwraca kolejne pozycje w tekœcie i lcp pomiêdzy 2 kolejnymi punktami

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
//lcp 2 kolejnych pozycji, L ustawiæ na co najmniej sufit logn+1
int tk[L][C], pw[L], pos[C], pa[C], pb[C];
int lcp(int a, int b, int j){
	int wn=0;
	while (j>=0){
		if (tk[j][a]!=tk[j][b])	j--;
		else wn+=pw[j], a+=pw[j], b+=pw[j];
	}
	return wn;
}
//sa- tablica, której kolejnymi wartoœciami s¹ pozycje w tekœcie k o d³. n, na których zaczynaj¹ siê kolejne najmniejsze sufixy; lcp - lcpv[i] - lcp pomiêdzy sa[i], sa[i+1]
void suf_arr(char k[], int n, int sa[], int lcpv[]){
	int i, j;
	for (i=0;i<L;i++)	pw[i]=1<<i;
	for (i=0;i<n;i++)	tk[0][i]=k[i]-96;
	for (j=1;pw[j-1]<n;j+=1){
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
