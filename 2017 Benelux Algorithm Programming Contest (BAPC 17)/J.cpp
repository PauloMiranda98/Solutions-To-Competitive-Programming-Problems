#include <bits/stdc++.h>

#define F first
#define S second
#define EB emplace_back
#define all(x) x.begin(),x.end()
#define endl '\n'
#define W(x) cerr << "\033[31m"<<  #x << " = " << x << "\033[0m" << endl;

using namespace std;
typedef long long ll;
class Bit{
private:
	typedef ll t_bit;
	int nBit;
	int nLog;
	vector<t_bit> bit;
public:
	Bit(int n){
		nBit = n+1;
		nLog = 20;
		bit.resize(nBit + 2, 0);
	}
	//1-indexed
	t_bit get(int i){
		i++;
		t_bit s = 0;
		for (; i > 0; i -= (i & -i))
			s += bit[i];
		return s;
	}
	//1-indexed
	void add(int i, t_bit value){
		i++;
		assert(i>0 and i<=nBit);
			
		for (; i <= nBit; i += (i & -i))
			bit[i] += value;
	}
	t_bit lower_bound(t_bit value){
		t_bit sum = 0;
		int pos = 0;
		for (int i = nLog; i >= 0; i--){
			if ((pos + (1 << i) <= nBit) and (sum + bit[pos + (1 << i)] < value)){
				sum += bit[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return pos + 1;
	}
};
const int MAXN = 1000010; 
Bit bit[2] = {Bit(MAXN), Bit(MAXN)};
void update(int p, int sgn){
	bool parity = p&1;
	int sum = 0, lastEven = 2, lastOdd = 1;
	for(int i=1; min(lastEven, lastOdd)<MAXN; i++){
		sum += i;
		if(sum%2==0){
			bit[parity].add(max(p-sum, 0), sgn*i);
			bit[parity].add(max(p-lastEven+1, 0), -sgn*i);
			bit[parity].add(min(p+lastEven, MAXN), sgn*i);
			bit[parity].add(min(p+sum+1, MAXN), -sgn*i);
			lastEven = sum + 1;
		}else{
			bit[!parity].add(max(p-sum, 0), sgn*i);
			bit[!parity].add(max(p-lastOdd+1, 0), -sgn*i);
			bit[!parity].add(min(p+lastOdd, MAXN), sgn*i);
			bit[!parity].add(min(p+sum+1, MAXN), -sgn*i);
			lastOdd = sum + 1;
		}
	}
}
ll query(int p){
	return bit[p&1].get(p);
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);		
	int n, t;
	cin >> n >> t;	
	for(int i=0; i<n; i++){
		int x;
		cin >> x;
		update(x, +1);
	}
	int q;
	cin >> q;
	while(q--){
		char op; int p;
		cin >> op >> p;
		if(op == '+')
			update(p, +1);
		else if(op == '-')
			update(p, -1);
		else
			t = p;
		cout << query(t) << endl;
	}
	return 0;
}
