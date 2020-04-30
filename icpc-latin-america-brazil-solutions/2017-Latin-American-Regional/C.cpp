#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3fLL
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1000000007;
int k, n;
int v[10010];
int f[10010];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> k >> n;
	for(int i=0; i<n; i++){
		cin >> v[i];
		f[v[i]]++;		
	}
	if(n%k == 0){
		int x = n/k;
		int a=0, b=0, c=0;
		int plus=-1, minus=-1;
		for(int i=1; i<=k; i++){
			if(f[i] == x){
				a++;
			}else if(f[i] == x+1){
				b++;
				plus=i;
			}else if(f[i] == x-1){
				c++;			
				minus=i;
			}
		}
		if(a+b+c == k and b==1 and c==1)
			cout << "-" << plus <<" +" << minus << endl;
		else
			cout << '*' << endl;					
	}else if((n+1)%k == 0){
		int x = (n+1)/k;
		int a=0, b=0;
		int minus=-1;
		for(int i=1; i<=k; i++){
			if(f[i] == x){
				a++;
			}else if(f[i] == x-1){
				b++;
				minus=i;
			}
		}
		if(a+b == k and b==1)
			cout << "+" << minus << endl;
		else
			cout << '*' << endl;							
	}else if((n-1)%k == 0){
		int x = (n-1)/k;
		int a=0, b=0;
		int plus=-1;
		for(int i=1; i<=k; i++){
			if(f[i] == x){
				a++;
			}else if(f[i] == x+1){
				b++;
				plus=i;
			}
		}
		if(a+b == k and b==1)
			cout << "-" << plus << endl;
		else
			cout << '*' << endl;									
	}else{
		cout << '*' << endl;
	}
	return 0;
}