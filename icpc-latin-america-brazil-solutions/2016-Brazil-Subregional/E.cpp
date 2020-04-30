#include <bits/stdc++.h>

#define MAXN 90010
#define MOD 1000000007LL

using namespace std;
typedef long long ll;

ll vet[100];
int n;

ll memo_min[66000];
ll memo[66000];
ll memo_max[66000];
ll memo_mask[66000];
ll memo_fat[66000];

ll p16[12];

ll remover(int i, int mask){
	if (mask == 0xffff)
		return 0;

	ll v = vet[i];
	int digit = 0;
	ll res = 0LL;

	while (v > 0){
		int resto = v % 16;
		v /= 16;

		if (mask & (1 << resto)){
			res += p16[digit++] * ll(resto);
		}
	}

	return res;
}

ll valor(int mask){
	if (memo_mask[mask] != -1)
		return memo_mask[mask];

	ll aux = 0LL;

	for (int j = 0; j < n; j++){
		aux += remover(j, mask);
	}

	return memo_mask[mask] = aux;
}

ll fat(int mask){
	if (memo_fat[mask] != -1)
		return memo_fat[mask];

	int bits = 0;

	for (int i = 0; i < 16; i++)
		if (mask & (1 << i))
			bits++;

	ll res = valor(mask);

	for (ll i = 1; i <= ll(bits); i++){
		res *= i;
		res %= MOD;
	}

	return memo_fat[mask] = res;
}

int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	memset(memo_mask, -1, sizeof(memo_mask));
	memset(memo_fat, -1, sizeof(memo_fat));

	p16[0] = 1LL;
	for (int i = 1; i <= 10; i++)
		p16[i] = 16LL * p16[i - 1];

	cin >> hex >> n;

	for (int i = 0; i < n; i++){
		cin >> hex >> vet[i];
	}

	memo[0] = 0LL;
	memo_min[0] = 0LL;
	memo_max[0] = 0LL;

	for (int mask = 1; mask <= 0xffff; mask++){
		ll res = 0LL;
		ll res_min = 0x3f3f3f3f3f3f3f3fLL;
		ll res_max = -0x3f3f3f3f3f3f3f3fLL;

		for (int i = 0; i < 16; i++){
			if (mask & (1 << i)){
				res += memo[mask & (~(1 << i))];
				res %= MOD;

				res_min = min(res_min, memo_min[mask & (~(1 << i))]);
				res_max = max(res_max, memo_max[mask & (~(1 << i))]);
			}
		}

		memo[mask] = (res + fat(mask)) % MOD;
		memo_min[mask] = res_min + valor(mask);
		memo_max[mask] = res_max + valor(mask);
	}

	cout << hex << memo_min[0xffff] << " " << memo_max[0xffff] << " " << memo[0xffff] << endl;

	return 0;
}
