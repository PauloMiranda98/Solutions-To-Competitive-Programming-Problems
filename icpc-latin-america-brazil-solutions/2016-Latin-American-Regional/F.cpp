#include <bits/stdc++.h>

#define MAXN 90010
#define MOD 1000000007LL

using namespace std;
typedef long long ll;

int n, c, s;
int vet[110];

int pos(int i, int se){
	if( (se==1) and (i==n))
		return 1;

	if( (se==-1) and (i==1))
		return n;

	return i + se;		
}

int main(){		
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> c >> s;
	
	int p = 1;
	vet[p]++;
	
	for(int i=1; i<=c; i++){
		int x;
		cin >> x;
		p = pos(p, x);
		vet[p]++;
	}	
		
	cout << vet[s] << endl;
	
	return 0;	
}
