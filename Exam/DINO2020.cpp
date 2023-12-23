#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n; cin >> n;
	int p[n];
	for (int i = 0; i < n; i++){
		cin >> p[i];
	}
	stack<int> chuong;
	queue<int> hanh_lang;
	for (int i = n - 1; i >= 0; i--){
		chuong.push(p[i]);
	}
	string s; cin >> s;
	
	for (int i = 0; i < s.length(); i++){
		if (s[i] == 'C'){
			if (!chuong.empty()){
				int tmp_C = chuong.top(); chuong.pop();
				hanh_lang.push(tmp_C);
			}
		} else {
			if (!hanh_lang.empty()){
				int tmp_H = hanh_lang.front(); hanh_lang.pop();
				chuong.push(tmp_H);
			}
		}
	}
	
	for (int i = 0; i < n; i++){
		cout << chuong.top() << " ";
		chuong.pop();
	}
	return 0;
}
