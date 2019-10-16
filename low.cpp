#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 1e5 + 5;
int n;
vector<int> v[N];
int preor[N], preorwsk, low[N], rod[N];
bool inv[N];

void dfs(int x) {
	preor[x] = ++preorwsk;
	low[x] = preor[x];
	for(auto y : v[x]) if(!inv[y]) {
		rod[y] = x;
		dfs(y);
		low[x] = min(low[x], low[y]);
	}
	else if(rod[x] != y) low[x] = min(low[x], preor[y]);
}

vector<int> art() {
	vector<int> ans;
	for(int x=1;x<=n;x++) {
		bool is = 0;
		if(rod[x] == 0 && v[x].size() > 1) is = 1;
		for(auto y : v[x]) if(low[y] >= preor[x]) is = 1;
		if(is) ans.pb(x);
	}
	return ans;
}

vector<int> mos() {
	vector<int> ans;
	for(int x=1;x<=n;x++) if(rod[x] != 0) {
		if(low[x] == preor[x]) ans.pb(x);
	}
	return ans;
}



int main()
{
	scanf("%d", &n);
	return 0;
}
