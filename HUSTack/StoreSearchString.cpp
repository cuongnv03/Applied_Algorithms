#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	set<string> a;
	string s, cmd, k;
	cin.ignore();
	
	do{
		getline(cin, s);
		if (s == "*") break;
		a.insert(s);
	}while(s != "*");
	
	do{
		getline(cin, s);
		if (s == "***") break;
		stringstream ss(s);
		ss >> cmd >> k;
		if (cmd == "find"){
			if (a.find(k) != a.end()){
				cout << "1" << endl;
			}
			else cout << "0" << endl;
		}
		
		if (cmd == "insert"){
			if (a.find(k) == a.end()){
				a.insert(k);
				cout << "1" << endl;
			}
			else cout << "0" << endl;
		}
	}while(s != "***");
	
	return 0;
}
