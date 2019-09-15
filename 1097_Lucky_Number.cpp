#include<bits/stdc++.h>
using namespace std;

#define ll             long long
#define LL             long long
#define pii            pair<int, int>
#define pll            pair<ll, ll>
#define pil            pair<int, ll>
#define pli            pair<ll, int>
#define vi             vector<int>
#define vl             vector<ll>
#define vii            vector<pii>
#define vll            vector<pll>
#define vil            vector<pil>
#define vli            vector<pli>
#define pb             push_back
#define ppb            pop_back
#define mp             make_pair
#define ff             first
#define ss             second
#define sz(x)          (int)x.size()
#define TN             typename
#define all(v)         v.begin(), v.end()
#define fill(a, b)     memset(a, b, sizeof(a))
#define endl           '\n'

template <TN T> T gcd(T a, T b) {return !b ? a : gcd(b, a % b);}
template <TN T> T lcm(T a, T b) {return a * (b / gcd(a, b));}
template <TN T> T sqr(T a) {return a * a;}
template <TN T> T cube(T a) {return a * a * a;}
template <TN T> inline void smin(T &a, T b) {a = a < b ? a : b;}
template <TN T> inline void smax(T &a, T b) {a = a > b ? a : b;}

template <TN T> inline void Int(T &n) {
	n = 0; int f = 1; register int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) n = (n << 3) + (n << 1) + ch - '0';
	n = n * f;
}

#define error(args...) {vector <string> _v = split(#args, ','); err(_v.begin(), args); cout << endl;}
vector <string> split(const string &s, char c) {
	vector <string> v;
	stringstream ss(s); string x;
	while (getline(ss, x, c)) v.emplace_back(x);
	return move(v);
}
void err(vector <string> :: iterator it) {}
template <typename T, typename... Args>
void err(vector <string> :: iterator it, T a, Args... args) {
	cout << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << ", ";
	err(++it, args...);
}

inline int in() {int n; scanf("%d", &n); return n;}
inline ll Lin() {ll n; scanf("%lld", &n); return n;}
inline double Din() {double n; scanf("%lf", &n); return n;}

inline int add(int a, int b, int mod) {a += b; return a >= mod ? a - mod : a;}
inline int sub(int a, int b, int mod) {a -= b; return a < 0 ? a + mod : a;}
inline int mul(int a, int b, int mod) {return (ll)a * b % mod;}

const int N          = 2e6 + 5;
const int inf        = (int)2e9 + 5;
const ll  Inf        = (ll)1e18 + 5;
const int mod        = (int)1e9 + 7;
const ll  Mod        = (ll)1e9 + 7;

struct BIT {
	ll tree[N];
	int mx = 1429431;

	BIT() {
		for (int i = 0; i <= mx; i++) {
			tree[i] = 0;
		}
	}

	void update(int x, int val) {
		while (x <= mx) {
			tree[x] += val;
			x += (x & -x);
		}
	}

	ll sum(int x) {
		ll sum = 0;
		while (x > 0) {
			sum += tree[x];
			x -= (x & -x);
		}
		return sum;
	}

	int query(int x) {
		int ans = 0;
		for (int i = 20; i >= 0; i--) {
			int mask = (1 << i);
			if (ans + mask <= mx && tree[ans + mask] <= x) {
				x -= tree[ans + mask];
				ans += mask;
			}
		}
		return ans + 1;
	}
};

BIT dp;

void process() {
	int n = 1e5, mx = 1429431;

	for (int i = 1; i <= mx; i += 2) {
		dp.update(i, 1);
	}


	for (int i = 2; i <= n; i++) {
		int num = dp.query(i - 1);
		//error(i, num);
		for (int j = (mx / num) * num; j > 0; j -= num) {
			int del_num = dp.query(j - 1);
			dp.update(del_num, -1);
		}
	}
}

int solve() {
	int n = in();
	printf("%d\n", dp.query(n - 1));
	return 0;
}

int main() {
	process();
	int test = 1, tc = 0;
	scanf("%d", &test);
	while (test--) {
		printf("Case %d: ", ++tc);
		solve();
	}
	return 0;
}



