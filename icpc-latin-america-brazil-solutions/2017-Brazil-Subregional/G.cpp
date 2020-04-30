#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

int dp[100100][60];
int t, m, n;

//Solve(Dificuldade, tempo Restante)
int solve(int u, int tam){
	if(tam == 1)
		return 1;

	if(dp[u][tam] != -1LL)
		return dp[u][tam];

	//Se tiver no máximo só posso descer
	if(u == m)
		return dp[u][tam] = solve(u-1LL, tam-1LL);

	//Se tiver no mínimo só posso subir
	if(u == n)
		return dp[u][tam] = solve(u+1LL, tam-1LL);

	//Posso escolher as duas opções
	return dp[u][tam] = (solve(u-1LL, tam-1LL) + solve(u+1LL, tam-1LL))%MOD;
	
}

int main(){	
	memset(dp, -1, sizeof(dp));
	
	cin >> t >> n >> m;

	int res = 0;
	
	//Iniciar de todos os valores possíveis
	for(long i=n; i<=m; i++){
		res = (res + solve(i, t))%MOD;
	}
	
	cout << res << endl;
	
	return 0;
}