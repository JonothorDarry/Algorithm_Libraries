typedef long long ll;

int pom[C], pom2[C], pom3[C];
void Sebasort (int tab[], int tab2[], int tab3[], int l, int r){
	int lim=2, limi=l+1, limj=l+2, j=limi, i=l, k=l;
	while (lim/2<=r-l+1){
		while (i<=r){
			if (limj>r)	limj=r+1;
			if ((j<limj&&tab[j]<tab[i])||i>=limi)	pom[k]=tab[j], pom2[k]=tab2[j], pom3[k]=tab3[j], j++;
			else pom[k]=tab[i], pom2[k]=tab2[i], pom3[k]=tab3[i], i++;
			k++;
			if (i==limi&&j==limj)	limi+=lim, limj+=lim, i=j, j=limi;
		}
		for (i=l;i<=r;i++)	tab[i]=pom[i], tab2[i]=pom2[i], tab3[i]=pom3[i];
		lim*=2, limi=l+lim/2, limj=l+lim, j=limi, i=k=l;
	}
}

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

//dowolny indeks
inline int bin (int tab[], int v, int l, int r){
	int m;
	while (l<=r){
		m=(l+r)/2;
		if (tab[m]==v)	return m;
		if (tab[m]>v)	r=m-1;
		else l=m+1;
	}
	return -1;
}

//najni¿szy indeks >=
inline int binup (int tab[], int v, int l, int r){
	int m;
	while (l<=r){
		m=(l+r)/2;
		if (tab[m]>=v)	r=m-1;
		else 			l=m+1;
	}
	return l;
}

//najwy¿szy indeks <=
inline int binlow (int tab[], int v, int l, int r){
	int m;
	while (l<=r){
		m=(l+r)/2;
		if (tab[m]>v)	r=m-1;
		else 			l=m+1;
	}
	return r;
}


inline long long pow (long long a, long long b){
	if (b==0)	return 1;
	long long c=1;
	while (b>1){
		if (b%2==1)	c=c*a;
		b/=2;
		a=a*a;
	}
	return c*a;
}

inline long long NWD (long long a, long long b){
	long long c=a%b;
	while (b!=0){
		c=a%b;
		a=b, b=c;
	}
	return a;
}


void insert(int a, int b, int v){
	int l=n+a, r=n+b;
	load[l] += v, sub[l] += v;
	if(r != l)	load[r] += v, sub[r] += v; 
	while(l >= 1){
		if(l <r-1){
			if(l % 2 == 0) load[l + 1] += v, sub[l + 1] += v;
			if(r % 2 == 1) load[r - 1] += v, sub[r - 1] += v;
		}
		if(r < n) sub[l] = max(sub[2 * l], sub[2*l+1])+load[l], sub[r] = max(sub[2 * r], sub[2*r+1])+load[r];
	l/=2, r/=2;
	}
}


int query (int a, int b){
	int l=n+a, r=n+b, x=0, y=0;
	x=sub[l], y=sub[r];
	while (l>=1){
		if(l<r-1){
			if (r<n)	x+=load[l], y+=load[r];
			if(l % 2 == 0) x=max(x, sub[l+1]);
			if(r % 2 == 1) y=max(y, sub[r-1]);
		}
		else if (r<n) x+=load[l], y+=load[r];
		l/=2, r/=2;
	}
	return max(x, y);
}

long long det (long long ax, long long bx, long long cx, long long ay, long long by, long long cy){
	if (ax*by+ay*cx+bx*cy-cx*by-cy*ax-bx*ay>0)	return 2;
	else if (ax*by+ay*cx+bx*cy-cx*by-cy*ax-bx*ay<0)	return 0;
	return 1;
}

//min w h[1]
int h[2*C], h2[2*C], ih=1;
void pop (){
	h[1]=h[ih-1], h2[1]=h2[ih-1], ih--;
	int j=1, c;
	while (j<ih){
		if (j*2<ih&&h[j*2]<h[j]&&(h[j*2+1]>=h[j*2]||j*2+1>=ih))	c=h[j], h[j]=h[j*2], h[j*2]=c, c=h2[j], h2[j]=h2[j*2], h2[j*2]=c, j=j*2;
		else if (j*2+1<ih&&h[j*2+1]<h[j])	c=h[j], h[j]=h[j*2+1], h[j*2+1]=c, c=h2[j], h2[j]=h2[j*2+1], h2[j*2+1]=c, j=j*2+1;
		else break;
	}
}

void push (int a, int v){
	h[ih]=a, h2[ih]=v, ih++;
	int j=ih-1, c;
	while (j>1){
		if (h[j/2]>h[j])	c=h[j], h[j]=h[j/2], h[j/2]=c, c=h2[j], h2[j]=h2[j/2], h2[j/2]=c, j/=2;
		else break;
	}
}

//int wynn, x, y;
void Euclid (int a, int b){
	int x1=0, x2=1, y1=1, y2=0, q=a/b, r=a-q*b;
	x=1, y=y2-(q-1)*y1;
	while (r!=0){
		a=b, b=r;
		x=x2-q*x1, x2=x1, x1=x;
		y=y2-q*y1, y2=y1, y1=y;
		wynn=r, q=a/b, r=a-q*b;
	}
}


int pr[C], ran[C];
void make_set (int x){
	pr[x]=x, ran[x]=0;
}

int find_set (int x){
	if (x!=pr[x])	pr[x]=find_set(pr[x]);
	return pr[x];
}

void find_union (int a, int b){
	int x=find_set(a), y=find_set(b);
	if (ran[x]>ran[y])	pr[y]=x;
	else pr[x]=y;
	if (ran[x]==ran[y])	ran[y]++;
}



void sum (long long wynn[], long long tab2[], int &x, int y){
	int j=0, c;
	while (j<y){
		wynn[j]+=tab2[j];
		c=wynn[j]/1000000000;
		wynn[j+1]+=c;
		wynn[j]%=1000000000;		
		j++;
	}
	if (j>x&&c==0)	x=j;
	if (j+1>x&&c>0)	x=j+1;
}

// wzorzec mergesega - <1;n>
int sear(int l, int r, int g){
	int wynn=Inf, y, s=1, j=0;
	if (p[0][l]<=g)					wynn=val[0][l];
	if (p[0][r]<=g&&val[0][r]<wynn)	wynn=val[0][r];
	
	
	for (j=0;j<20;j++){
		if (r-l>s&&((l-1)%(2*s))==0){
			y=binup(p[j], g, l+s, l+2*s-1);
			if (y>=l+s&&y<=l+2*s-1&&val[j][y]<wynn)	wynn=val[j][y];
		}
		
		if (r-l>s&&((r-1)%(2*s))!=0){
			y=binup(p[j], g, r-s, r-1);
			if (y>=r-s&&y<=r-1&&val[j][y]<wynn)	wynn=val[j][y];
		}
		
		s*=2;
		l=((l-1)/s)*s+1, r=((r-1)/s)*s+1;	
	}
	return wynn;	
}



//macierzy mno¿enie (I niesprawdzone)
void cop(ll a[][C], ll b[][C], int n){
	int i, j;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			b[i][j]=a[i][j];
		}
	}
}

void pw(ll b[][C], ll b2[][C], ll pb[][C], int n){
	int i, j, k;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			for (k=0;k<n;k++){
				pb[i][j]+=(b[i][k]*b2[k][j]);
			}
		}
	}
}

ll pdp[C][C], rdp[C][C];
void power_matrix(long long b, int n){
	int i, j;
	for (i=0;i<n;i++)	rdp[i][i]=1;
	
	for (;b>0;b/=2){
		if (b%2==1)	pw(dp, rdp, pdp, n), cop(pdp, rdp, n);
		pw(dp, dp, pdp, n), cop(pdp, dp, n);
	}
}


//RMQ
int rmq[L][C], lg2[C];
void rmq_init(int n, int st[]){
	int i, j;
	for (i=0;i<n;i++)	rmq[0][i]=st[i], lg2[i]=((i>1)?(lg2[i/2]+1):0);
	for (i=0;i<L;i++)	pw[i]=1<<i;
	
	for (j=1;j<L;j++){
		for (i=0;i<n;i++){
			if (i+pw[j-1]>=n)	rmq[j][i]=rmq[j-1][i];
			else rmq[j][i]=min(rmq[j-1][i], rmq[j-1][i+pw[j-1]]);
		}
	}
}

//(b>a)
int x;
int rmqq(int a, int b){	
	x=lg2[b-a];
	return min(rmq[x][a], rmq[x][b-pw[x]+1]);	
}





int lst=1, root=1;
struct treap_node{
	int ex=-1, v, l=-1, r=-1, h;
};
treap_node t[C];

void create(int km, int p, int x){
	t[km].v=x, t[km].ex=1, t[km].h=p;
}

//Rozbicie treapa w punkcie a; dodanie ostatniego punktu
void split(int a, int p, int x, int y){
	treap_node z;
	int ln=lst, rn=lst, beg=lst, b;
	create(lst, p, x), lst++;
	
	//Dodanie krawêdzi z ojca do nowego
	z=t[lst-1];
	if (y!=-1){
		if (t[y].v>z.v)	t[y].l=lst-1;
		else t[y].r=lst-1;
	}
	
	while (1){
		//Dodanie z prawej strony nowego v
		if (t[a].v>z.v){
			if (rn==beg)	t[rn].r=a;
			else t[rn].l=a;
			b=a, a=t[b].l;
			t[b].l=-1;
			rn=b;	
		}
		
		//Dodanie z lewej strony nowego v
		else{
			if (ln==beg)	t[ln].l=a;
			else t[ln].r=a;
			b=a, a=t[b].r;
			t[b].r=-1;
			ln=b;
		}
		if (a==-1)	break;
	}
}

void treap_insert(int p, int x){
	int cur=root, last=-1, gg=0;
	while (1){
		//Korzeñ nie istnieje
		if (t[cur].ex==-1)	create(cur, p, x), lst++, gg=1;
		
		else if (t[cur].h>p){
			last=cur;
			//Dodanie z prawej/lewej strony albo przejœcie na t¹ stronê wierzcho³ka
			if (t[cur].v<x&&t[cur].r!=-1)	cur=t[cur].r;
			else if (t[cur].v<x) 			t[cur].r=lst, create(lst, p, x), lst++,	gg=1;
			else if (t[cur].l!=-1)			cur=t[cur].l;
			else 							t[cur].l=lst, create(lst, p, x), lst++, gg=1;
		}
		//Rozbicie, zmiana korzenia(ewentualnie)
		else split(cur, p, x, last), gg=1;
		if (last==-1&&gg==1)	root=lst-1;
		
		if (gg==1)	return;
	}
}

