#include <bits/stdc++.h>
using namespace std;

int main(){
	int n; cin >> n;
	int cnt = 1;
	int a[n];
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}
	
	for (int i = 0; i < n - 1; i++){
		if (a[i + 1] < a[i]){
			cnt++;
		}
	}
	cout << cnt << endl;
	
	return 0;
}