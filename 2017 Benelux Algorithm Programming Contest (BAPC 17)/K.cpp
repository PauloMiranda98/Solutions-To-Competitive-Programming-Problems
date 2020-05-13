#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using pii = pair<int, int>;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const int MAXN = 1010;

char mat[MAXN][MAXN];
bool used[MAXN];
int n;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
		
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> mat[i][j];
		}
	}
	vector<int> ans;
	queue<int> q;
	used[0] = true;
	q.push(0);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		ans.EB(u);
		for(int i=0; i<n; i++){
			if(mat[u][i] == '1' and !used[i]){
				q.push(i);
				used[i] = true;
			}
		}
	}
	if((int)ans.size() == n){
		reverse(all(ans));
		for(int x: ans)
			cout << x << " ";
		cout << endl;
	}else{
		cout << "impossible" << endl;
	}
	return 0;
}
