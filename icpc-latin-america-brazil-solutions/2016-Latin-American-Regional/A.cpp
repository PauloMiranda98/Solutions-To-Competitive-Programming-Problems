#include <iostream>

using namespace std;

int main() {
	int a, b, c, d;
	
	cin >> a >> b >> c >> d;	
	
	//Para facilitar, vamos ordenar os valores
	if(b < a)
		swap(a, b); //A função swap troca os valores de A e B
	if(c < a)
		swap(a, c); 
	if(d < a)
		swap(a, d);
		
	//Após isso, o menor valor está em A. Vamos ordenar o restante.
	if(c < b)
		swap(b, c); 
	if(d < b)
		swap(b, d);

	//Depois disso, o B tem o segundo menor valor.
	if(d < c)
		swap(c, d);

	//Após essas trocas, temos: a <= b <= c <= d;
	
	int resultado = (a+d) - (b+c);
	//Atenção (a+d)-(b+c) é diferente de (a+d)-b+c
	
	if(resultado < 0)
		resultado *= -1;
		
	cout << resultado << "\n";
	
	return 0;
}