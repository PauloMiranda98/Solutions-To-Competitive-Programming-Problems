#include <iostream>
#include <sstream>
#define ORDEM 2
#define MOD 10000

using namespace std;

long long base[ORDEM][ORDEM];
long long mat[ORDEM][ORDEM];
long long a, b, n;

void mult(long long matA[ORDEM][ORDEM], long long matB[ORDEM][ORDEM]){
	long long aux[ORDEM][ORDEM];
	
	for(int i=0; i < ORDEM; i++){
		for(int j=0; j < ORDEM; j++){
			long long soma = 0LL;
			
			for(int k=0; k < ORDEM; k++){
				soma += (matA[i][k] * matB[k][j])%MOD;
			}
			
			aux[i][j] = soma%MOD;
		}
	}
	
	for(int i=0; i < ORDEM; i++){
		for(int j=0; j < ORDEM; j++){
			matA[i][j] = aux[i][j];
		}
	}
	
}

void expo(long long matA[ORDEM][ORDEM], long long n){
	if(n <= 1LL)
		return;
		
	expo(matA, n/2);
	mult(matA, matA);
	
	if(n % 2LL == 1LL)
		mult(matA, base);
		
}

long long res(long long n){
	if(n == 0LL)
		return 2LL;
	if(n == 1LL)
		return 2LL*a;
	
	base[0][0] = 2LL*a;
	base[0][1] = b - a*a;
	base[1][0] = 1LL;
	base[1][1] = 0LL;
	
	for(int i=0; i < ORDEM; i++){
		for(int j=0; j < ORDEM; j++){
			mat[i][j] = base[i][j];
		}
	}

			
	expo(mat, n - 1LL);
	
	return ( mat[0][0]*2LL*a + mat[0][1]*2LL)%MOD;
}


int main(){
	stringstream ss;	
	int k;
	
	cin >> a >> b >> n >> k;

	long long r = res(n);

	if(a*a > b || ( a*a < b && n%2LL == 0LL) ){
		r = (r-1LL)%MOD;
		if(r < 0)
			r = 100000 + r;
	}
	
	string s;
	ss << "0000";
	ss << r;
	ss >> s;
	
	cout << s[s.size() - k] << endl;		
	
	return 0;
}