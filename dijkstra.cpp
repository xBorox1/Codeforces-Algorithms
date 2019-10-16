#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 1e5 + 5;
const long long INF = 1e18;
int n;
typedef pair<long long, int> P;
priority_queue<P, vector<P>, greater<P> > q;
vector< P > v[N];
bool inv[N];
long long odl[N];
void Dijkstra(int z) {
	q.push({0, z});
	for(int i=1;i<=n;i++) odl[i] = INF;
	odl[z] = 0;
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if(inv[x]) continue;
		inv[x] = 1;
		for(auto p : v[x]) {
			int y = p.second;
			long long d = p.first;
			if(odl[y] > odl[x] + d) {
				odl[y] = odl[x] + d;
				if(!inv[y]) q.push({odl[y], y});
			}
		}
	}
}
int main()
{
	scanf("%d", &n);
	return 0;
}
