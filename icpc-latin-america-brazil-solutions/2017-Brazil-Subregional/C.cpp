#include <iostream>

using namespace std;

long long n, l;

long long mdc(long long a, long long b){
	if(b == 0LL)
		return a;
		
	return mdc(b, a%b);
}

long long mmc(long long a, long long b){
	return (min(a, b) * (max(a, b)/mdc(a, b)) );
}

int main(){
	cin >> n >> l;
	
	long long int maior = 0LL;
	long long int res = 0LL;
	
	long long int valor = 1LL; 
	long long int candidato = l;
	
	for(long int i=0; i < n; i++){
		long long int x;
		cin >> x;
		
		valor = mmc(valor, x);
	}
	
	while(candidato >= 1LL){
		long long atual = mmc(valor, candidato);
		
		if(atual >= maior && atual <= l){
			maior = atual;
			res = candidato;
		}
		
		candidato--;
	}
	
	cout << res << endl;
	
	return 0;
}