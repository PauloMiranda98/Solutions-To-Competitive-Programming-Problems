#include <iostream>
#include <algorithm>

using namespace std;

long vetor[2000];

bool compara(long a, long b){
	return a > b;
}

int main(){	
	long int n, qtd, soma;
	
	cin >> n >> qtd;
	
	soma = qtd;
	
	for(int i=0; i<n; i++)
		cin >> vetor[i];
	
	sort(vetor, vetor+n, compara);
	
	while( (soma < n) && (vetor[soma] == vetor[qtd-1]) ){
		soma++;
	}
	
	cout << soma << endl;
	
	return 0;
}