#include <iostream>
#include <algorithm>

using namespace std;

int vetor[100010];

string mapa[12] = {"do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si"};

int main(){	
	long int n;
	
	cin >> n;
	
	for(int i=0; i<n; i++){
		cin >> vetor[i];	
		vetor[i] -= 1;
	}
	
	for(int i=0; i < 12; i++){
		long cont = 0;
		
		for(long int j=0; j < n; j++){
			if(vetor[j]%12 == 0+i)
				cont++;
			else if(vetor[j]%12 == (2+i)%12)
				cont++;
			else if(vetor[j]%12 == (4+i)%12)
				cont++;
			else if(vetor[j]%12 == (5+i)%12)
				cont++;
			else if(vetor[j]%12 == (7+i)%12)
				cont++;
			else if(vetor[j]%12 == (9+i)%12)
				cont++;
			else if(vetor[j]%12 == (11+i)%12)
				cont++;
		}
		
		if(cont == n){
			cout << mapa[i] << endl;
			return 0;
		}
		
	}
	
	cout << "desafinado" << endl;
	
	return 0;
}