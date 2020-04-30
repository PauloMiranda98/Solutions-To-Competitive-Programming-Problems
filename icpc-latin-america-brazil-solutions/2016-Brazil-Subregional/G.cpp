#include <bits/stdc++.h>

using namespace std;
#define endl '\n'

typedef long long int ll;

long int n, p;
const int MAXN = 510;
ll matriz[MAXN][MAXN];
ll ac[MAXN][MAXN];
ll unique1 = MAXN*MAXN + 1;
ll unique2 = MAXN*MAXN + 2; 
long int sum(int a, int b, int x, int y){
	return ac[x][y] - ac[x][b-1] - ac[a-1][y] + ac[a-1][b-1];
}

int main(){		
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> p;
	
	for(int i=0; i<p; i++){
		int a, b;
		cin >> a >> b;
		
		matriz[a][b] = unique1;
		ac[a][b] = unique1;
	}
	
	for(int i=0; i<p; i++){
		int a, b;
		cin >> a >> b;
		
		matriz[a][b] = unique2;
		ac[a][b] = unique2;
	}
	
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			ac[i][j] += ac[i-1][j];
		}
	}

	for(int j=1; j<=n; j++){
		for(int i=1; i<=n; i++){
			ac[i][j] += ac[i][j-1];
		}
	}
	
	ll p=0, b=0; 
	
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int t=0; max(i,j)+t<=n; t++){			
				int r = sum(i, j, i+t, j+t);
				
				if(r == 0)
					continue;
				else if((r%unique1)==0)
					p++;
				else if((r%unique2)==0)
					b++;
				else
					break;
			}
		}
	}
	
	cout << p << " " << b << "\n";
	return 0;
}
