#include <iostream>

using namespace std;

string s;
bool ehVogal(char c){
	return (c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u');
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> s;

	int i = 0;
	int j = s.size() - 1;
	bool engracada = true;
	while (i <= j){
		while ((i <= j) and !ehVogal(s[i]))
			i++;
		while ((j >= i) and !ehVogal(s[j]))
			j--;

		if (i > j)
			break;
		if (s[i] != s[j])
			engracada = false;
		i++;
		j--;
	}

	if (engracada)
		cout << "S" << "\n";
	else
		cout << "N" << "\n";

	return 0;
}
