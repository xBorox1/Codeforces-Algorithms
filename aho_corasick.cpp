#define make_pair mp
#define push_back pb
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, S = 26;
int n, trie[N][S], siz = 1, cnt[N], pref[N], suf[N];
int fail[N];
string t, s[N];
 
void add(string s) {
	int v = 1;
	for(int i=0;i<s.length();i++) {
		int let = s[i] - 'a';
		if(trie[v][let] == 0) {	
			siz++;
			trie[v][let] = siz;
		}
		v = trie[v][let];
	}
	cnt[v]++;
}
 
void build() {
	queue<int> q;
	while(!q.empty()) q.pop();
 
	fail[1] = 1;
	for(int i=0;i<S;i++) if(trie[1][i] == 0) {
	       	trie[1][i] = 1;
	}
	else {
		fail[trie[1][i]] = 1;
		q.push(trie[1][i]);
	}
 
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		for(int i=0;i<S;i++) {
			int x = trie[v][i];
			if(x == 0) {
				trie[v][i] = trie[fail[v]][i];
			}
			else {
				q.push(x);
				fail[x] = trie[fail[v]][i];
			}
		}
		cnt[v] += cnt[fail[v]];
	}
}
 
int main()
{
	return 0;
}
