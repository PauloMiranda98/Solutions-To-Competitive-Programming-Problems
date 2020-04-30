#include <bits/stdc++.h>
using namespace std;
struct WaveletTree{
private:
	typedef int t_wavelet;
	t_wavelet lo, hi;
	WaveletTree *l=nullptr, *r=nullptr;
	vector<t_wavelet> a;
public:
	template <class MyIterator>
	WaveletTree(MyIterator begin, MyIterator end, t_wavelet minX, t_wavelet maxX){
		lo = minX, hi = maxX;
		if (lo == hi or begin >= end)
			return;
		t_wavelet mid = (lo + hi - 1) / 2;
		auto f = [mid](int x) {
			return x <= mid;
		};
		a.reserve(end - begin + 2);
		a.push_back(0);
		for (auto it = begin; it != end; it++)
			a.push_back(a.back() + f(*it));
		
		auto pivot = stable_partition(begin, end, f);
		l = new WaveletTree(begin, pivot, lo, mid);
		r = new WaveletTree(pivot, end, mid + 1, hi);
	}
	inline int b(int i){
		return i - a[i];
	}
	//swap v[i] with v[i+1]
	//1-indexed
	void swap(int i){
		if (lo == hi or a.size() <= 2)
			return;
		if(a[i-1]+1==a[i] and a[i]+1==a[i+1])
			l->swap(a[i]);
		else if(b(i-1)+1==b(i) and b(i)+1==b(i+1))
			r->swap(b(i));
		else if(a[i-1]+1==a[i])
			a[i]--;			
		else
			a[i]++;								
	}
	//kth smallest element in range [i, j]
	//1-indexed
	int kth(int i, int j, int k){
//		cout << i << " " << j << endl;
		if (i > j)
			return 0;
		if (lo == hi)
			return lo;
		int inLeft = a[j] - a[i - 1];
		int i1 = a[i - 1] + 1, j1 = a[j];
		int i2 = b(i - 1) + 1, j2 = b(j);
		if (k <= inLeft)
			return l->kth(i1, j1, k);
		return r->kth(i2, j2, k - inLeft);
	}
	//Amount of numbers in the range [i, j] Less than or equal to k
	//1-indexed
	int lte(int i, int j, int k){
		if (i > j or k < lo)
			return 0;
		if (hi <= k)
			return j - i + 1;
		int i1 = a[i - 1] + 1, j1 = a[j];
		int i2 = b(i - 1) + 1, j2 = b(j);
		return l->lte(i1, j1, k) + r->lte(i2, j2, k);
	}
	//Amount of numbers in the range [i, j] equal to k
	//1-indexed
	int count(int i, int j, int k){
		if (i > j or k < lo or k > hi)
			return 0;
		if (lo == hi)
			return j - i + 1;
		t_wavelet mid = (lo + hi - 1) / 2;
		int i1 = a[i - 1] + 1, j1 = a[j];
		int i2 = b(i - 1) + 1, j2 = b(j);
		if (k <= mid)
			return l->count(i1, j1, k);
		return r->count(i2, j2, k);
	}
	~WaveletTree(){
		if(l) delete l;
		if(r) delete r;
	}
};

int n, q;
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> q;
	vector<int> v(n);
	for(int i=0; i<n; i++)
		cin >> v[i];	
	WaveletTree wt(v.begin(), v.end(), 0, 1e9 + 1);
	while(q--){
		char op;
		cin >> op;
		if(op == 'Q'){
			int a, b, k;
			cin >> a >> b >> k;
			cout << wt.kth(a, b, k) << endl;
		}else{
			int w;
			cin >> w;
			wt.swap(w);
		}
	}
	return 0;
}