#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

int d[MAXN], e[MAXN];
int sumD[MAXN], sumE[MAXN];
int d1[MAXN], e1[MAXN];
int n, q;

int left(int i, int d, int vSum[], int v1[]){
    int x=0;
	for(int k=20; k>=0; k--){
		if(x+(1<<k) <= d){
			int pos = i-(x+(1<<k));
			if(pos >= 1 and v1[i-1]-v1[pos-1]==0)
				x += (1<<k);			
		}
	}
	int pos = i-x;
	if(d == x)
		return vSum[i-1]-vSum[pos-1];
	if(pos == 1)
		return vSum[i-1]-vSum[pos-1] + (d-x)*5;
	pos--;
	x++;
	if(v1[i-1]-v1[pos-1])
		return vSum[i-1]-vSum[pos-1] + (d-x);
	else
		return vSum[i-1]-vSum[pos-1] + (d-x)*5;
}

int right(int i, int d, int vSum[], int v1[]){
	int x=0;
	for(int k=20; k>=0; k--){
		if(x+(1<<k) <= d){
			int pos = i+(x+(1<<k));
			if(pos <= n and v1[pos-1]-v1[i-1]==0)
				x += (1<<k);			
		}
	}
	int pos = i+x;
	if(d == x)
		return vSum[pos-1]-vSum[i-1];
	if(pos == n)
		return vSum[pos-1]-vSum[i-1] + (d-x)*5;
	pos++;
	x++;
	if(v1[pos-1]-v1[i-1])
		return vSum[pos-1]-vSum[i-1] + (d-x);
	else
		return vSum[pos-1]-vSum[i-1] + (d-x)*5;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	
	for(int i=1; i<n; i++)
		cin >> d[i];
	for(int i=1; i<n; i++)
		cin >> e[i];
	for(int i=1; i<n; i++){
		sumD[i] = sumD[i-1] + d[i];
		d1[i] = d1[i-1] + (d[i]==1);
		sumE[i] = sumE[i-1] + e[i];
		e1[i] = e1[i-1] + (e[i]==1);
	}
	cin >> q;
	while(q--){
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if(x1 > x2)
			swap(x1, x2);
		if(y1 > y2)
			swap(y1, y2);
		int dx = x2-x1;
		int dy = y2-y1;
		int ans = (sumD[x2-1]-sumD[x1-1]+sumE[y2-1]-sumE[y1-1]);
		if(abs(dx-dy) > 1){
			int delta = (abs(dx-dy)/2);
			if(dx < dy){
				if(d1[x2-1]-d1[x1-1])
					ans += delta*2;					
				else
					ans += 2*min(left(x1, delta, sumD, d1), right(x2, delta, sumD, d1));
			}else{
				if(e1[y2-1]-e1[y1-1])
					ans += delta*2;
				else
					ans += 2*min(left(y1, delta, sumE, e1), right(y2, delta, sumE, e1));							
			}
		}
		cout << ans << endl;
	}
	return 0;
}