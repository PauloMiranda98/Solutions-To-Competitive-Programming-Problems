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

class Bit{
private:
	typedef long long t_bit;
	int nBit;
	int nLog;
	vector<t_bit> bit;	
public:
	Bit(int n){ 
		nBit = n;
		nLog = 20;
		bit.resize(nBit+1, 0);
	}	
  //1-indexed
	t_bit get(int i){	
		t_bit s = 0;
		for(; i > 0; i -= (i & -i))
			s = max(s, bit[i]);		
		return s;
	}
  //1-indexed
	void add(int i, t_bit value){				
		for(; i <= nBit; i += (i & -i))
			bit[i] = max(bit[i], value);
	}
};

map<pii, ll> mp;
vector<int> comp;
int getID(int x){
	int p = lower_bound(all(comp), x) - comp.begin();
	return p+1;
}
struct Tuple{
	int b, f;
	ll d;
	Tuple(){}
	Tuple(int b, int f, ll d): b(b), f(f), d(d){}
};
vector<Tuple> v;
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		int b, f, d;
		cin >> b >> f >> d;
		mp[pii(b, f)] += d;
		comp.EB(b);
		comp.EB(f);
	}
	sort(all(comp));
	comp.erase(unique(all(comp)), comp.end());
	for(auto p: mp)
		v.EB(p.F.F, p.F.S, p.S);		
	n = v.size();
	Bit bt(3*n);
	int i = 0;
	ll mx = 0;
	while(i<n){
		int k = i;
		int x = v[i].b;
		while(k<n and v[k].b == x){
			Tuple &t = v[k];
			int b = getID(t.b);
			int f = getID(t.f);
			ll d = bt.get(f-1) + t.d;
			mx = max(mx, d);
 			t = Tuple(b, f, d); 
			k++;
		}
		for(; i<k; i++)
			bt.add(v[i].f, v[i].d);			
	}
	cout << mx << endl;
	return 0;
}