#include <stdio.h>
#include <vector>
#define grdef for (int z=0;z<m;z++)		scanf ("%d %d", &a, &b), gr[a].push_back(b), gr[b].push_back(a), ij[a]++, ij[b]++
#define grdef2 for (int z=0;z<m;z++)	scanf ("%d %d %I64d", &a, &b, &w), gr[a].push_back(b), gr[b].push_back(a), E[a].push_back(w), E[b].push_back(w), ij[a]++, ij[b]++
#define grdef3 for (int z=0;z<m;z++)	scanf ("%d %d", &a, &b), gr[a].push_back(b), gr[b].push_back(a), E[a].push_back(z), E[b].push_back(z), ij[a]++, ij[b]++

using namespace std;
typedef long long ll;
const int C=100001;

vector <vector <int> > gr(C);
int ij[C], a, b, n, m;


//Mosty, artykulacja, dwuspójne sk³adowe : Br[x]=1 - x-ta krawêdŸ mostem; PA[x]=1 - x-ty wierzcho³ek mostem; Bcc[x] x-ta krawêdŸ nale¿y do Bcc[x] dwuspójnej sk³adowej Rcc[x] - x-ta krawêdŸ po krojeniu mostów nale¿y do Rcc[x] spójnej sk³adowej
//argumenty - n liczba wierzcho³ków, Ep - wektor numerów krawêdzi, gr - graf; Poprawnoœæ sprawdzona - 8/10
int s[C], se[C], sv[C], is=0, ise=0, isv=0, ji[C], ple[C], pre[C], ip=1, low[C], par[C], nos[C], col=1, Rcc[C], col2=1;
int Br[C], PA[C], Bcc[C];
bool ch[C], chE[C];
void graph_slayer(int n, vector <vector <int> > &gr, vector <vector <int> > &Ep, int ij[]){
	int a, i, b, root, j;
	for (i=1;i<=n;i++)	ji[i]=ij[i], ch[i]=chE[i]=0, par[i]=0;
	
	for (i=1;i<=n;i++){
		if (ch[i]==0)	ch[i]=1, s[0]=i, sv[0]=i, is=1, ise=0, isv=1, pre[i]=low[i]=ip, ip++, root=i;
		while (is>0){
			a=s[is-1];
			while (ji[a]>0&&ch[gr[a][ji[a]-1]]==1)	{
				if (chE[Ep[a][ji[a]-1]]==0){
					low[a]=min(low[a], pre[gr[a][ji[a]-1]]);
					chE[Ep[a][ji[a]-1]]=1, se[ise]=Ep[a][ji[a]-1],  ise++;
				}
				ji[a]--;
			}
			if (ji[a]>0){
				nos[a]++;
				b=s[is]=sv[isv]=gr[a][ji[a]-1];
				chE[Ep[a][ji[a]-1]]=1;
				ch[b]=1, par[b]=a;
				se[ise]=Ep[a][ji[a]-1], ple[b]=ise;
				low[b]=pre[b]=ip, ip++;
				ji[a]--, is++, ise++, isv++;
			}
			else{
				low[par[a]]=min(low[par[a]], low[a]);
				if (low[a]==pre[a]&&par[a]!=0)	Br[se[ple[a]]]=1;
				if (low[a]==pre[a])	{
					for (;sv[isv]!=a;isv--)	Rcc[sv[isv-1]]=col2;
					col2++;
				}	
				
				if (low[a]>=pre[par[a]]&&a!=root){
					if (par[a]!=root||(par[a]==root&&nos[par[a]]>1))	PA[par[a]]=1;
					for (j=ple[a];j<ise;j++)	Bcc[se[j]]=col;
					col++, ise=ple[a];
				}
				is--;
			}
		}
	}
}

//liczba spójnych sk³adowych w grafie - indeksowanie od i, v - która sk³adowa;
int F[C], v[C];
bool check[C];
void nocc(int n){
	int iF=0, jF, i=1, a, j=0, sum=1;
	for (int z=1;z<=n;z++)	check[i]=0;
	
	for (i=1;i<=n;i++){
		if (check[i]==0){
			check[i]=1, F[0]=i, iF=0, jF=1, sum++, v[i]=sum;
			while (iF<jF){
				a=F[iF];
				while (j<ij[a]){
					if (check[gr[a][j]]==0)	check[gr[a][j]]=1, F[jF]=gr[a][j], v[F[jF]]=sum, jF++;
					j++;
				}			
				j=0, iF++;
			}
		}
	}
}

void gradd(int a, int b){
	gr[a].push_back(b);
	gr[b].push_back(a);
	ij[a]++, ij[b]++;
}

//MaxFlow EKarpiem O(N*M*M) - zwraca flow, bierze cap[a][b] - pojemnoœæ œcie¿yny a, b
//argumenty - ¿ród³o, zlew, liczba wierzcho³ków ze ¿ród³em i zlewem
int par[C], check[C], mv[C], F[C];
int MaxFlow(int S, int T, int n){
	int Mx=0, act=0, j, i, a=0, b=0, iF, jF;
	
	mv[S]=Inf, check[S]=1;
	while (1){
		for (i=0;i<=n;i++)	mv[i]=0, check[i]=par[i]=0;
		mv[S]=Inf, check[S]=1;
		//Standardowy BFS w poszukiwaniu zaginionego p³ywu
		F[0]=S;
		for (iF=0,jF=1;iF<jF;iF++){
			a=F[iF];
			for (j=0;j<ij[a];j++){
				if (check[gr[a][j]]==0&&cap[a][gr[a][j]]>0){
					b=F[jF]=gr[a][j], jF++;
					check[b]=1;
					par[b]=a, mv[b]=min(mv[a], cap[a][b]);
					if (b==T)	break;					
				}
			}
			if (b==T)	break;
		}
		//Brak nowej œcie¿yny - kambek, jest - aktualizacja
		if (iF==jF)	return Mx;
		act=mv[b];
		for (;b!=S;b=par[b]){
			a=par[b];
			cap[a][b]-=act;
			cap[b][a]+=act;
		}
		Mx+=act, act=0, a=b=0;
	}
}



//Monumentalny pe³ny dijkstra na kopcu - drogi z s do wszystkich vertexów - argumenty - graf, d³ugoœci, ij, start

ll h[2*C];
int h2[2*C], ih=1;
void exch(int a, int b){
	h[a]+=h[b], h[b]=h[a]-h[b], h[a]-=h[b];
	h2[a]+=h2[b], h2[b]=h2[a]-h2[b], h2[a]-=h2[b];
}

void pop (){
	h[1]=h[ih-1], h2[1]=h2[ih-1], ih--;
	int j=1;
	
	while (j<ih){
		if (j*2<ih&&h[j*2]<h[j]&&(h[j*2+1]>=h[j*2]||j*2+1>=ih))	exch(j, j*2), j=j*2;
		else if (j*2+1<ih&&h[j*2+1]<h[j]&&h[j*2+1]<h[j*2])	exch(j, j*2+1), j=j*2+1;
		else break;
	}
}

void push (ll a, int v){
	h[ih]=a, h2[ih]=v, ih++;
	int j=ih-1;
	
	while (j>1){
		if (h[j/2]>h[j])	exch(j, j/2), j/=2;
		else break;
	}
}

bool check[C];
ll d[C];
void full_dijkstra (vector <vector <int> > &tab, vector <vector <ll> > &e, int ij[], int s){
	int j=0, y;
	ll x;
	
	push(0, s);
	
	while (ih>1){
		x=h[1], y=h2[1];
		pop();
		if (check[y]==1)	continue;
		check[y]=1, d[y]=x;
		for (j=0;j<ij[y];j++)	if (check[tab[y][j]]==0)	push(x+e[y][j], tab[y][j]);
	}
}


//Dijkstra O(V*V)
bool check[C];
ll d[C];
void full_dijkstra (vector <vector <int> > &tab, vector <vector <ll> > &e, int ij[], int s, int n){
	int j=0, i=0, av, b;
	ll x, am=Inf;
	for (j=1;j<=n;j++)	check[j]=0, d[j]=Inf;
	d[s]=0;
	
	while (1){
		am=Inf;
		for (i=1;i<=n;i++){
			if (check[i]==0&&d[i]<am)	am=d[i], av=i;
		}
		
		if (am==Inf)	break;
		check[av]=1;
		
		for (i=0;i<ij[av];i++){
			b=gr[av][i];
			if (d[b]>e[av][i]+d[av])		d[b]=e[av][i]+d[av];
		}
	}
}


//tworzenie mst - f1, f2 to wierzcho³ki, f3 waga, n - liczba V, m - liczba E; tworzy drzewo wag z pozycjami; tworzy vv tab - drzewo i e - krawêdzie
int f1[C], f2[C], f3[C];
void create_mst(int f1[], int f2[], int f3[], int n, int m){
	int i, a, b;
	
	for (i=1;i<=n;i++)	make_set(i);
	Sebasort(f3, f2, f1, 0, m-1);
	
	for (i=0;i<m;i++){
		a=find_set(f1[i]), b=find_set(f2[i]);
		if (a!=b)	{
			find_union(a, b);			
			a=f1[i], b=f2[i];
			
			tab[a].push_back(b), tab[b].push_back(a);
			e[a].push_back(i), e[b].push_back(i);
			ij[a]++, ij[b]++;
		}
	}
}
