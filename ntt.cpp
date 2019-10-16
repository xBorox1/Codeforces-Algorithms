#define make_pair mp
#define emplace_back pb
#include <bits/stdc++.h>
using namespace std;
mt19937 mt_rand(time(0));
const long long MOD = 998244353;
const long long G = 3;

typedef vector<int> VI;

long long pot(long long a, long long p) {
	if(p == 0) return 1;
	long long w = pot(a, p / 2);
	w = w * w % MOD;
	if(p % 2) w = (w * a) % MOD;
	return w;
}

int bit_reverse(int x, int logn) {
	int n = 0;
	for(int i=0;i<logn;i++) {
		n <<= 1;
		n |= (x & 1);
		x >>= 1;
	}
	return n;
}

VI NTT(VI &A, bool num) {
	int n = A.size();
	int logn = 0;
	int nn = n;
	while(nn) {
		nn /= 2;
		logn++;
	}
	logn--;

	VI B = {};

	for(int i=0;i<n;i++) {
		int rev = bit_reverse(i, logn);
		B.pb(A[rev]);
	}

	for(int s=1;s<=logn;s++) {
		int m = 1 << s;
		int m2 = m / 2;
		long long root = 1;
		long long p = (MOD - 1) / (long long)m;
		long long pom = pot(G, p);
		if(num) pom = pot(pom, MOD - 2);

		for(int j=0;j<m2;j++) {
			for(int k=j;k<n;k+=m) {
				long long t = root * (long long)B[k+m2];
			        long long u = B[k];	
				B[k] = (u + t) % MOD;
				B[k+m2] = (u - t) % MOD;
				if(B[k+m2] < 0) B[k+m2] += MOD;
			}
			root = (root * pom) % MOD;
		}
	}

	return B;
}

VI to_size(VI &A, int size) {
	while(size != A.size()) A.pb(0);
	return A;
}

VI operator *(VI &A, VI &B) {
	int size = A.size() + B.size() - 1;
	int p = 1;
	while(p < size) p *= 2;
	size = p;

	A = to_size(A, size);
	B = to_size(B, size);

	VI AC = NTT(A, false);
	VI BC = NTT(B, false);

	VI C;
	C.resize(size);
	for(int i=0;i<size;i++) C[i] = ((long long)AC[i] * (long long)BC[i]) % MOD;
	C = NTT(C, true);
	long long inv = pot(size, MOD - 2);
	for(int i=0;i<size;i++) C[i] = ((long long)C[i] * inv) % MOD;
	while(C.back() == 0) C.pop_back();

	return C;
}

int main()
{
	return 0;
}
