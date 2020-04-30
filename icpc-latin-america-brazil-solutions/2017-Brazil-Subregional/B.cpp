#include <bits/stdc++.h>

using namespace std;

typedef unsigned long int uli;

long int restos[1000000];
int ts[32];

int main() {
	memset(restos, -1, sizeof(restos));
	
	int p, t;
	uli aux;
	uli n, k, soma = 0;
	bool tem = false;
	
	cin >> p >> t >> aux >> k >> n;
	p--;
	
	for(int i=0; i < t; i++){
		cin >> ts[i];
	}
	
	soma += aux%k;
	
	restos[soma] = 0; 
	
	if( (soma == 0) && (n == 1)){
		cout << 0 << " " << 0 << endl;
		tem = true;
	}
	if(!tem)
	for(uli i=1; (i < 2*1000000) ; i++){
		uli a = 0;
		
		for(int j=0; j < t; j++){
			a ^= (aux>>ts[j]);
		}
		
		a &= 1;
		aux = (aux>>1);
		aux |= (a<<p);
		
		soma += aux%k;
		soma %= k;
		if((soma == 0 ) && ((i+1) >= n) ){
			cout << 0 << " " << i << endl;
			tem = true;
			break;			
		}
		
		if(restos[soma] != -1){			
			if((i - restos[soma]) >= n ){
				cout << restos[soma]+1 << " " << i << endl;
				tem = true;
				break;
			}
			
		}else{
			restos[soma] = i;			
		}
		
	}

	if(tem == false)
		cout << "imposivel" << endl;
		
	return 0;
	
}