#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const int N = 1e5 + 5;

//~ vector<long long> witness = {2, 7, 61}; // < 4759123141 = 4e9
vector<long long> witness = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

long long mul(long long a, long long b, long long mod) {
	return (__int128) a * b % mod;
}

long long pot(long long a, long long p, long long mod) {
	if(p == 0) return 1;
	long long w = pot(a, p / 2, mod);
	w = w * w % mod;
	if(p % 2) w = w * a % mod;
	return w;
}

bool test(long long n) {
	if(n == 2) return true;
	if(n < 2 || n % 2 == 0) return false;
	long long d = n - 1, s = 0;
	while(d % 2 == 0) {
		d /= 2;
		++s;
	}
	for(auto i : witness) if(i % n) {
		long long x = pot(i, d, n);
		if(x == 1) continue;
		bool zlozona = true;
		for(int j = 0; j < s; ++j) {
			if(x == n - 1) {
				zlozona = false;
				break;
			}
			x = mul(x, x, n);
		}
		if(zlozona) return false;
	}
	return true;
}

long long f(long long x, long long mod, long long c) {
	long long y = mul(x, x, mod) + c;
	if(y > mod) y -= mod;
	return y;
}

void rho(long long n, vector<long long> & w) {
	if(n <= 1) return;
	if(test(n)) {
		w.push_back(n);
		return;
	}
	for(long long c = 1; true; ++c) {
		long long x = 2, y = 2, d = 1;
		while(d == 1) {
			x = f(x, n, c);
			y = f( f(y,n,c), n, c);
			d = __gcd(abs(x - y), n);
		}
		if(d < n) {
			rho(d, w);
			rho(n / d, w);
			return;
		}
	}
}

vector<long long> rozklad(long long n) {
	vector<long long> w;
	for(int i = 2; i <= 100; ++i) while(n % i == 0) {
		n /= i;
		w.push_back(i);
	}
	rho(n, w);
	sort(w.begin(), w.end());
	return w;
}

long long n;

int main()
{
	scanf("%lld", &n);
	for(auto x : rozklad(n)) cout<<x<<" ";
	return 0;
}
