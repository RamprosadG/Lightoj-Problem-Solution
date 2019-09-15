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

const int N          = 3e4 + 5;
const int inf        = (int)2e9 + 5;
const ll  Inf        = (ll)1e18 + 5;
const int mod        = (int)1e9 + 7;
const ll  Mod        = (ll)1e9 + 7;

struct Journey {
	vi g[N];
	int st[N], et[N], tree[N], t, mx;
	int par[18][N], dep[N];

	Journey() {
		for (int i = 0; i < N; i++) {
			tree[i] = 0;
			g[i].clear();
		}
		par[0][1] = 1;
		t = 0, mx = 3e4 + 2;
	}

	void add(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}

	void dfs(int u, int p = -1, int d = 0) {
		st[u] = ++t;
		dep[u] = d;
		for (int i = 1; i <= 17; i++) {
			par[i][u] = par[i - 1][par[i - 1][u]];
		}
		for (int v : g[u]) {
			if (p == v) continue;
			par[0][v] = u;
			dfs(v, u, d + 1);
		}
		et[u] = t;
	}

	int lca(int u, int v) {
		if (dep[u] < dep[v]) swap(u, v);
		for (int i = 17; i >= 0 && u != v; i--) {
			if (dep[par[i][u]] >= dep[v]) u = par[i][u];
		}
		if (u == v) return u;
		for (int i = 17; i >= 0; i--) {
			if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
		}
		return par[0][u];
	}

	void update(int x, int val) {
		while (x <= mx) {
			tree[x] += val;
			x += (x & -x);
		}
	}

	int query(int x) {
		int ans = 0;
		while (x > 0) {
			ans += tree[x];
			x -= (x & -x);
		}
		return ans;
	}
};

int a[N];

int solve() {
	int n = in();
	for (int i = 1; i <= n; i++) {
		a[i] = in();
	}
	Journey dp;
	for (int i = 1; i < n; i++) {
		int u = in() + 1, v = in() + 1;
		dp.add(u, v);
	}
	dp.dfs(1);
	for (int i = 1; i <= n; i++) {
		dp.update(dp.st[i], a[i]);
		dp.update(dp.et[i] + 1, -a[i]);
	}
	int m = in();
	while (m--) {
		int ck = in();
		if (!ck) {
			int u = in() + 1, v = in() + 1;
			int l = dp.lca(u, v);
			int ans = dp.query(dp.st[u]) + dp.query(dp.st[v]) - dp.query(dp.st[l]) * 2 + a[l];
			printf("%d\n", ans);
		}
		else {
			int u = in() + 1, val = in();
			int x = val - a[u];
			dp.update(dp.st[u], x);
			dp.update(dp.et[u] + 1, -x);
			a[u] = val;
		}
	}
	return 0;
}

int main() {
	int test = 1, tc = 0;
	scanf("%d", &test);
	while (test--) {
		printf("Case %d:\n", ++tc);
		solve();
	}
	return 0;
}


