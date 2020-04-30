#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MAXN 100010 
#define NSeg 4*MAXN

struct Node{
	int f[9] = {0};
};

Node tree[NSeg];
Node neutral;
int lazy[NSeg];
int aux[9];
int n, q;
	
inline Node join(Node a, Node b){
	Node r;
	for(int i=0; i<9; i++)
		r.f[i] = a.f[i] + b.f[i];
	return r;
}

inline void upLazy(int &node, int &i, int &j){
	if(lazy[node] != 0){
		for(int k=0; k<9; k++)
			aux[(k+lazy[node])%9] = tree[node].f[k]; 
		for(int k=0; k<9; k++)
			tree[node].f[k] = aux[k]; 
					
		if(i != j){				
			lazy[(node<<1)] += lazy[node];
			lazy[(node<<1)+1] += lazy[node];			
		}
		lazy[node] = 0;
	}
}

void build(int node, int i, int j){
	lazy[node] = 0;
	
	if(i == j){
		tree[node].f[1] = 1;
		return;
	}
	int m = (i+j)/2;
	
	int l = (node<<1);
	int r = l + 1;
	
	build(l, i, m);
	build(r, m+1, j);
	
	tree[node] = join(tree[l], tree[r]);
}

Node query(int node, int i, int j, int a, int b){	
	upLazy(node, i, j);
			
	if( (i>b) or (j<a) )
		return neutral;

	if( (a<=i) and (j<=b) ){
		return tree[node];
	}

	int m = (i+j)/2;
	int l = (node<<1);
	int r = l + 1;
	
	return join( query(l, i, m, a, b), query(r, m+1, j, a, b) );
}

void update(int node, int i, int j, int a, int b, int &value){
	if( (i>j) or (i>b) or (j<a) )
		return;
	
	upLazy(node, i, j);

	if( (a<=i) and (j<=b) ){
		lazy[node] = value;
		upLazy(node, i, j);
	}else{
		int m = (i+j)/2;
		int l = (node<<1);
		int r = l + 1;
		
		update(l, i, m, a, b, value);
		update(r, m+1, j, a, b, value);		
		
		tree[node] = join(tree[l], tree[r]);
	}	
}

inline int query(int a, int b){
	Node no = query(1, 1, n, a, b);
	int f = 0;
	int value = 0;
	for(int i=0; i<9; i++){
		if(no.f[i] >= f){
			f = no.f[i];
			value = i;
		}
	}
	
	return value;
}

inline void update(int a, int b, int value){
	update(1, 1, n, a, b, value);		
}

int main() {		
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	scanf("%d %d", &n, &q);
	
	build(1, 1, n);
		
	for(int i=0; i<q; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		a++;
		b++;
		
		int x = query(a, b);
		update(a, b, x);
	}
	
	for(int i=1; i<=n; i++){
		printf("%d\n", query(i, i));
	}

	return 0;	
}