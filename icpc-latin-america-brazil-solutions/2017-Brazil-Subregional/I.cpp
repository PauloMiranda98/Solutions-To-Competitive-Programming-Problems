#include <bits/stdc++.h>
#define MAXN 10100

using namespace std;

int n, c;
int imposto[MAXN];
bool visitado[MAXN];
long int acumulado = 0;

vector< pair<int, int> > grafo[MAXN];

void bfs(int v){
		
	visitado[v] = true;
	
	for(auto viz : grafo[v]){
		int u = viz.first;
		int p = viz.second;
		
		if(!visitado[u]){								
			bfs(u);
			
			imposto[v] += imposto[u];
			
			int aux = (imposto[u]+c-1)/c;
			
			if(aux > 0)
				acumulado += p*(2*aux);
		}
	}	
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin >> n >> c;
    
    for(int i=1; i<=n; i++){
		cin >> imposto[i];
	}
	
	for(int i=1; i<n; i++){
		int a, b, p;
		
		cin >> a >> b >> p;
		
		grafo[a].push_back(make_pair(b, p));
		grafo[b].push_back(make_pair(a, p));		
	}
	bfs(1);
	
	cout << acumulado << endl;
	
	return 0;
}