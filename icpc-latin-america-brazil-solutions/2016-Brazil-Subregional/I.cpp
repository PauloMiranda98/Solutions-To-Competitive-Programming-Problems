#include <bits/stdc++.h>

using namespace std;

long int n, p;

int v[50010];
int e[50010];
int d[50010];

int main(){
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++){
		cin >> v[i];
		e[i] = min(e[i - 1] + 1, v[i]);
	}

	for (int i = n; i >= 1; i--)
		d[i] = min(d[i + 1] + 1, v[i]);

	int res = 0;

	for (int i = 1; i <= n; i++)
		res = max(res, min(e[i], d[i]));

	cout << res << endl;
	return 0;
}
