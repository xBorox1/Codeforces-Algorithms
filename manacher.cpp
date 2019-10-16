#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 1e5 + 5;
char s[N];

pair< vector<int>, vector<int> > manacher(string &s) {
	int n = s.length();

	vector<int> d1 (n);
	int l=0, r=-1;
	for (int i=0; i<n; ++i) {
		int k = (i>r ? 0 : min (d1[l+r-i], r-i)) + 1;
		while (i+k < n && i-k >= 0 && s[i+k] == s[i-k])  ++k;
		d1[i] = k--;
		if (i+k > r)
			l = i-k,  r = i+k;
	}

	vector<int> d2 (n);
	l=0, r=-1;
	for (int i=0; i<n; ++i) {
		int k = (i>r ? 0 : min (d2[l+r-i+1], r-i+1)) + 1;
		while (i+k-1 < n && i-k >= 0 && s[i+k-1] == s[i-k])  ++k;
		d2[i] = --k;
		if (i+k-1 > r)
			l = i-k,  r = i+k-1;
	}

	return mp(d1, d2);
}

int main()
{
	scanf("%s", s);
	string t = s;
	auto p = manacher(t);

	for(auto x : p.first) cout<<x<<" ";
	cout<<endl;
	for(auto x : p.second) cout<<x<<" ";
	cout<<endl;

	return 0;
}
