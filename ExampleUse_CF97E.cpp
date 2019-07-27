#include <stdio.h>
#include <vector>
#define grdef for (int z=0;z<m;z++)		scanf ("%d %d", &a, &b), gr[a].push_back(b), gr[b].push_back(a), ij[a]++, ij[b]++
#define grdef2 for (int z=0;z<m;z++)	scanf ("%d %d", &a, &b), gr[a].push_back(b), gr[b].push_back(a), E[a].push_back(z), E[b].push_back(z), ij[a]++, ij[b]++

using namespace std;
typedef long long ll;
const int C=100001;

vector <vector <int> > gr(C), E(C), tr(C), trE(C);
int ij[C], a, b, n, m, ijt[C];

//Mosty, artykulacja, dwuspójne składowe : Br[x]=1 - x-ta krawędź mostem; PA[x]=1 - x-ty wierzchołek mostem; Bcc[x] x-ta krawędź należy do Bcc[x] dwuspójnej składowej Rcc[x] - x-ta krawędź po krojeniu mostów należy do Rcc[x] spójnej składowej
//argumenty - n liczba wierzchołków, Ep - wektor numerów krawędzi, gr - graf; Poprawność sprawdzona - 7/10
int s[C], se[C], sv[C], is=0, ise=0, isv=0, ji[C], ple[C], preo[C], ip=1, low[C], parr[C], nos[C], col=1, Rcc[C], col2=1, ss[C], iss=0, cor[C];
bool bicol[C];

int Br[C], PA[C], Bcc[C];
bool ch[C], chE[C];
void graph_slayer(int n, vector <vector <int> > &gr, vector <vector <int> > &Ep, int ij[]){
    int a, i, b, root, j;
    for (i=1;i<=n;i++)	ji[i]=ij[i], ch[i]=chE[i]=0;

    for (i=1;i<=n;i++){
        if (ch[i]==0)	ch[i]=1, s[0]=i, sv[0]=i, is=1, ise=0, isv=1, iss++, ss[i]=iss, preo[i]=low[i]=ip, ip++, root=i, bicol[i]=0;
        while (is>0){
            a=s[is-1];
            ss[a]=iss;
            while (ji[a]>0&&ch[gr[a][ji[a]-1]]==1)	{
                if (chE[Ep[a][ji[a]-1]]==0){
                    low[a]=min(low[a], preo[gr[a][ji[a]-1]]);
                    chE[Ep[a][ji[a]-1]]=1, se[ise]=Ep[a][ji[a]-1],  ise++;
                }
                ji[a]--;
            }
            if (ji[a]>0){
                nos[a]++;
                b=s[is]=sv[isv]=gr[a][ji[a]-1];
                tr[a].push_back(b), tr[b].push_back(a);
                trE[a].push_back(E[a][ji[a]-1]), trE[b].push_back(E[a][ji[a]-1]);
                ijt[a]++, ijt[b]++;

                bicol[b]=(!bicol[a]);
                chE[Ep[a][ji[a]-1]]=1;
                ch[b]=1, parr[b]=a;
                se[ise]=Ep[a][ji[a]-1], ple[b]=ise;
                low[b]=preo[b]=ip, ip++;
                ji[a]--, is++, ise++, isv++;
            }
            else{
                low[parr[a]]=min(low[parr[a]], low[a]);
                if (low[a]==preo[a]&&parr[a]!=0)	Br[se[ple[a]]]=1;
                if (low[a]==preo[a])	{
                    for (;sv[isv]!=a;isv--)	Rcc[sv[isv-1]]=col2;
                    col2++;
                }

                if (low[a]>=preo[parr[a]]&&a!=root){
                    if (parr[a]!=root||(parr[a]==root&&nos[parr[a]]>1))	PA[parr[a]]=1;
                    for (j=ple[a];j<ise;j++)	Bcc[se[j]]=col;
                    col++, ise=ple[a];
                }
                is--;
            }
        }
    }
}


int pre[C], dep[C], son[C], par[21][C], summ[C];
void proc_tree(int a, int n, vector <vector <int> > &tab){
    if (ch[a]==1)	return;
    s[0]=a, is=1, pre[a]=1, dep[a]=1, ip=2, summ[a]=0;
    int b;

    while (is>0){
        a=s[is-1];
        ch[a]=1;
        if (ji[a]>0&&tab[a][ji[a]-1]==par[0][a])	ji[a]--;
        if (ji[a]>0)	{
            b=s[is]=tab[a][ji[a]-1], pre[b]=ip, par[0][b]=a, dep[b]=is+1;
            if (cor[Bcc[trE[a][ji[a]-1]]]==1)	summ[b]=summ[a]+1;
            else summ[b]=summ[a];
            ip++, is++, ji[a]--;
        }
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

//zamienić i!
int lca (int a, int b, int f=18){
    if (anc(a, b)==1)	return a;
    if (anc(b, a)==1)	return b;

    int i=f, x=a;
    while (i>=0){
        if (anc(par[i][x], b)==1)	i--;
        else x=par[i][x];
    }
    return par[0][x];
}


int main(){
    int i, j, q, x, k, l;
    scanf ("%d %d", &n, &m);
    grdef2;
    graph_slayer(n, gr, E, ij);
    for (i=1;i<=n;i++){
        for (j=0;j<ij[i];j++){
            if (bicol[i]==bicol[gr[i][j]])	cor[Bcc[E[i][j]]]=1;
        }
    }

    for(i=1;i<=n;i++)	ji[i]=ijt[i], ch[i]=0;
    for (i=1;i<=n;i++)	proc_tree(i, n, tr);

    prep_lca(19, n);
    scanf ("%d", &q);
    while (q--){
        scanf ("%d %d", &a, &b);
        if (ss[a]!=ss[b]){
            printf ("No\n");
            continue;
        }
        x=lca(a, b);
        k=summ[a]+summ[b]-2*summ[x];
        l=dep[a]+dep[b]-2*dep[x];
        if (l%2==1||k>0)	printf ("Yes\n");
        else printf ("No\n");
    }

return 0;}
