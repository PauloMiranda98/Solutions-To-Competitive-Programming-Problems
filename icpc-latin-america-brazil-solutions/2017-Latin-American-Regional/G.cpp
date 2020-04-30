#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;
const int MOD = 1000000007;
struct Nand{
	int x, y, f;
};

Nand v[MAXN];
int n;
int dp[MAXN][4];
int memo[MAXN][2];

inline int modMul(int a, int b){
	return (a*1LL*b)%MOD;
}

inline int modSum(int a, int b){
	int ret = a+b;
	if(ret >= MOD)
		return ret-MOD;
	return ret;
}

inline int modSub(int a, int b){
	int ret = a-b;
	if(ret < 0)
		return ret+MOD;
	return ret;
}

int count(int u, int value){
	if(u == 0)
		return 1;
	if(memo[u][value] != -1)
		return memo[u][value];

	Nand node = v[u];
	int op00 = modMul(count(node.x, 0), count(node.y, 0));
	int op01 = modMul(count(node.x, 0), count(node.y, 1));
	int op10 = modMul(count(node.x, 1), count(node.y, 0));
	int op11 = modMul(count(node.x, 1), count(node.y, 1));

	if(value == 0)
		return memo[u][value] = op11;
	else
		return memo[u][value] = modSum(op00, modSum(op01, op10));
}

int solve(int u, int value){
	if(u == 0){
		if(value < 2)
			return 1;
		else
			return 0;
	}
	if(dp[u][value] != -1)
		return dp[u][value];
	Nand node = v[u];
	if(value == 0){//A qnt de jeitos de fazer subarvore u ficar False e eh a resposta certa
		if(node.f == -1){
			return dp[u][value] = modMul(solve(node.x, 1), solve(node.y, 1));
		}else if(node.f == 0){
			return dp[u][value] = count(u, 0);
		}else{
			return dp[u][value] = 0;
		}
	}else if(value == 1){//A qnt de jeitos de fazer subarvore u ficar True e eh a resposta certa
		int op0 = modMul(solve(node.x, 0), modSum(solve(node.y, 1), modSum(solve(node.y, 2), solve(node.y, 3))));
		int op1 = modMul(modSum(solve(node.x, 1), modSum(solve(node.x, 2), solve(node.x, 3))), solve(node.y, 0));
		int op2 = modMul(solve(node.x, 0), solve(node.y, 0));
		int op3 = modSum(modMul(solve(node.x, 2), solve(node.y, 3)), modMul(solve(node.x, 3), solve(node.y, 2)));

		if(node.f == -1){
			return dp[u][value] = modSum(modSum(op0, op1), modSum(op2, op3));
		}else if(node.f == 0){
			return dp[u][value] = 0;
		}else{
			return dp[u][value] = count(u, 1);
		}
	}else if(value == 2){
		if(node.f == -1){
			return dp[u][value] = modSub(count(u, 1), solve(u, 1));
		}else if(node.f == 0){
			return dp[u][value] = count(u, 1);
		}else{
			return dp[u][value] = 0;
		}
	}else{
		if(node.f == -1){
			return dp[u][value] = modSub(count(u, 0), solve(u, 0));
		}else if(node.f == 0){
			return dp[u][value] = 0;
		}else{
			return dp[u][value] = count(u, 0);
		}
	}
}

int main() {
	memset(dp, -1, sizeof(dp));	
	memset(memo, -1, sizeof(memo));
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for(int i=1; i<=n; i++)
		cin >> v[i].x >> v[i].y >> v[i].f;	
	cout << modSum(solve(1, 2), solve(1, 3)) << endl;
	return 0;
}