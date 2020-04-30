#include <bits/stdc++.h>
#define F first
#define S second 
using namespace std;
typedef pair<int, int> pii;

vector<int> sort_cyclic_shifts(vector<int> &s) {
    int n = s.size();
    const int alphabet = 302;

	vector<int> p(n), c(n), cnt(max(alphabet, n), 0);

    for(int i = 0; i < n; i++)
        cnt[s[i]]++;
    for(int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for(int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for(int i = 1; i < n; i++) {
        if(s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

	vector<int> pn(n), cn(n);
    for(int h = 0; (1 << h) < n; ++h) {
        for(int i = 0; i < n; i++){ //Ordenando pelo second no RadixSort
            pn[i] = p[i] - (1 << h);
            if(pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for(int i = 0; i < n; i++)
            cnt[c[p[i]]]++;
        for(int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for(int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for(int i = 1; i < n; i++) {
            pii cur = pii(c[p[i]], c[(p[i] + (1 << h)) % n]);
            pii prev = pii(c[p[i-1]], c[(p[i-1] + (1 << h)) % n]);
            if(cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> suffix_array_construction(vector<int> &s) {
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    return sorted_shifts;
}

int n;
const int MOD = 1000000007;
vector<int> v, init;
vector<int> mp;
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	scanf("%d", &n);
	v.reserve(4*100001+n);
	init.reserve(n);
	for(int i=0; i<n; i++){
		int k;
		scanf("%d", &k);
		init.push_back(v.size());
		for(int j=0; j<k; j++){
			int x;
			scanf("%d", &x);
			v.push_back(x);
		}
		v.push_back(301);
	}
	vector<int> suff = suffix_array_construction(v);
	mp.resize(v.size() + 2);
	for(int i=0; i<(int)v.size(); i++)
		mp[suff[i]] = i;
	
	set<pii> st;
	for(int x: init)
		st.insert(pii(mp[x], x));
	int ans = 0;
	while(!st.empty()){
		auto front = st.begin();
		pii top = *front;
		st.erase(front);
		ans = ((ans+v[top.S])*365LL)%MOD;
		if(v[top.S + 1] != 301)
			st.insert(pii(mp[top.S+1], top.S + 1));
	}
	printf("%d\n", ans);
	return 0;
}