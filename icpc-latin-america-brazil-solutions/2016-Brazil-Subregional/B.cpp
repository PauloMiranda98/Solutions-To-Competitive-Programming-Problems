#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int MAXN = 50010;
int mn[MAXN], p[MAXN];

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
		bit.resize(nBit + 1, 0);
	}
	//1-indexed
	t_bit get(int i){
		t_bit s = 0;
		for (; i > 0; i -= (i & -i))
			s += bit[i];
		return s;
	}
	//1-indexed [l, r]
	t_bit get(int l, int r){
		return get(r) - get(l - 1);
	}
	//1-indexed
	void add(int i, t_bit value){
		assert(i > 0);
		for (; i <= nBit; i += (i & -i))
			bit[i] += value;
	}
	t_bit maxSum(t_bit limit){
		t_bit sum = 0;
		int pos = 0;
		for (int i = nLog; i >= 0; i--){
			if ((pos + (1 << i) <= nBit) and (sum + bit[pos + (1 << i)] <= limit)){
				sum += bit[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return sum;
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
Bit bit(MAXN);
const int BLOCK_SIZE = 700;
int sz;

void remove(int idx){
	bit.add(mn[idx], -1);
	sz--;
}

void add(int idx){
	bit.add(mn[idx], +1);
	sz++;
}

int n, q;
int get_answer(){
	assert(sz == bit.get(MAXN));
	int op1 = bit.lower_bound(sz / 2);
	int sum1 = bit.get(op1);
	int sum2 = bit.maxSum(sz / 2);
	int op2 = bit.lower_bound(sum2);
	if (abs(sum2 * 2 - sz) <= abs(sum1 * 2 - sz))
		return op2;
	else
		return op1;
}

struct Query{
	int l, r, idx;
	bool operator<(Query other) const{
		if (l / BLOCK_SIZE != other.l / BLOCK_SIZE)
			return l < other.l;
		return (l / BLOCK_SIZE & 1) ? (r < other.r) : (r > other.r);
	}
};

vector<int> mo_s_algorithm(vector<Query> queries){
	vector<int> answers(queries.size());
	sort(queries.begin(), queries.end());

	int L = 1, R = 1;
	sz = 0;
	add(1);

	for (Query q : queries){
		while (q.l < L)
			add(--L);
		while (R < q.r)
			add(++R);
		while (L < q.l)
			remove(L++);
		while (q.r < R)
			remove(R--);
		assert(sz == (R - L + 1));
		answers[q.idx] = get_answer();
	}
	return answers;
}
vector<int> adj[MAXN];
void dfs(int u, int x){
	if (mn[u] != 0)
		return;
	mn[u] = x;
	for (int to : adj[u])
		dfs(to, x);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> q;
	for (int i = 1; i <= n; i++){
		int x;
		cin >> x;
		adj[x].push_back(i);
	}
	for (int i = 1; i <= n; i++){
		dfs(i, i);
	}
	vector<Query> v(q);
	for (int i = 0; i < q; i++){
		cin >> v[i].l >> v[i].r;
		v[i].idx = i;
	}
	vector<int> ans = mo_s_algorithm(v);
	for (int x : ans)
		cout << x << endl;
	return 0;
}
