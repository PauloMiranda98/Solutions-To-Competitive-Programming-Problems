#include <bits/stdc++.h>

#define MAXN 90010
#define MOD 1000000007LL
#define int int32_t

using namespace std;
typedef long long ll;

int n, k;
int vet[100010];
priority_queue<int, vector<int>, greater<int> > pq;

int main(){	
	int soma = 0LL;
	
	cin >> n >> k;
	
	for(int i=1; i<=n; i++){
		cin >> vet[i];
		soma += vet[i];
	}	
	
	for(int i=k+1; i<=n; i++){
		if(i%(k+1)==0){
			pq.push(vet[i]);
		}else{
			if(pq.top() < vet[i]){
				pq.pop();
				pq.push(vet[i]);
			}
		}
		
	}
	
	while(!pq.empty()){
		soma -= pq.top();
		pq.pop();
	}
	
	cout << soma << endl;
	
	return 0;	
}