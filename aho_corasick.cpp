    #define make_pair mp
    #define push_back pb
    #include <iostream>
    #include <cstdio>
    #include <stack>
    #include <algorithm>
    #include <set>
    #include <queue>
    #include <vector>
    #include <cmath>
    #include <bitset>
    #include <map>
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
     
    string rev(string s) {
    	string res;
    	res.clear();
    	for(int i=s.length()-1;i>=0;i--) res += s[i];
    	return res;
    }
     
    int main()
    {
    	ios_base::sync_with_stdio(0);
    	cin>>t>>n;
    	for(int i=1;i<=n;i++) {
    		cin>>s[i];
    		add(s[i]);
    	}
    	build();
     
    	int v = 1;
    	for(int i=0;i<t.length();i++) {
    		int let = t[i] - 'a';
    		v = trie[v][let];
    		pref[i] = cnt[v];
    	}
     
    	siz = 1;
    	for(int i=0;i<N;i++) {
    		for(int j=0;j<S;j++) trie[i][j] = 0;
    		cnt[i] = 0;
    		fail[i] = 0;
    	}
     
    	for(int i=1;i<=n;i++) add(rev(s[i]));
    	build();
     
    	v = 1;
    	for(int i=t.length() - 1;i>=0;i--) {
    		int let = t[i] - 'a';
    		v = trie[v][let];
    		suf[i] = cnt[v];
    	}
     
    	long long ans = 0;
    	for(int i=0;i<t.length()-1;i++) ans += (long long)pref[i] * (long long)suf[i+1];
    	printf("%lld", ans);
     
    	return 0;
    }
