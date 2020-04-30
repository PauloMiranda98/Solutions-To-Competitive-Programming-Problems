#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

typedef long long ll;

const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 6002;
ll v[MAXN];
ll dp[2][MAXN];
ll c1[MAXN];
ll c2[MAXN];
ll sum1[MAXN];
ll sum2[MAXN];
int n, b, c;

inline ll C1(int i, int j){
	if(i > j)
		return 0;
	return ((c1[j]-c1[i-1]) - (i-1)*(sum1[j]-sum1[i-1]));
}

inline ll C2(int i, int j){
	if(i > j)
		return 0;
	return ((c2[i]-c2[j+1]) - (n-j)*(sum2[i]-sum2[j+1]));
}

inline ll C(int i, int j){
	if(i>j)
		return 0;
	if(i == j)
		return v[i];
	int mid = (i+j)>>1;
	return C1(i, mid) + C2(mid+1, j);
}

bool k_curr, k_old;
inline void calculateDP(int l, int r, int opt_l, int opt_r){
  if (l > r)
    return;
  int mid = (l + r) >> 1;
  ll ans = INFLL;
  int opt = mid;
  ll aux = INFLL;
  for (int i = opt_l; i <= min(opt_r, mid - 1); i++){
    aux = dp[k_old][i] + C(i + 1, mid-1);
    if (ans > aux){
      opt = i;
      ans = aux;
    }
  }
  dp[k_curr][mid] = ans;
  calculateDP(l, mid - 1, opt_l, opt);
  calculateDP(mid + 1, r, opt, opt_r);
}

int main() {	
	scanf("%d %d %d", &n, &b, &c);
	int x;
	for(int i=1; i<=n; i++){
		scanf("%d", &x);
		v[i] = x*1LL*c;
	}			
	c1[0] = sum1[0] = 0;
	c2[n+1] = sum2[n+1] = 0;	
	for(int i=1; i<=n; i++){
		c1[i] = c1[i-1] + i*1LL*v[i];
		sum1[i] = sum1[i-1] + v[i];
	}		
	for(int i=1; i<=n; i++){
		c2[n-i+1] = c2[n-i+2] + i*1LL*v[n-i+1];
		sum2[n-i+1] = sum2[n-i+2] + v[n-i+1];
	}	
	for(int i = 1; i <= n; i++)
		dp[0][i] = C2(1, i-1);
	dp[1][0] = INFLL;
	dp[0][0] = INFLL;
	
	for(int k=1; k<=n; k++){
		if(k > 1)
			putchar(' ');
		ll ans = INFLL, aux;
		for(int i=1; i<=n; i++){
			aux = C1(i+1, n) + dp[(k-1)&1][i];
			if(aux < ans)
				ans = aux;
		}
		printf("%lld", k*1LL*b + ans);
		k_curr = k&1;
		k_old = (k-1)&1;		
		if(k < n)
			calculateDP(1, n, 1, n - 1);
	}
	putchar('\n');
	
	return 0;
}
