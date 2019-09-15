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

const int N          = 2e5 + 5;
const int inf        = (int)2e9 + 5;
const ll  Inf        = (ll)1e18 + 5;
const int mod        = (int)1e9 + 7;
const ll  Mod        = (ll)1e9 + 7;

struct Segment_Tree {

	ll tree[4 * N], prop[4 * N];

	Segment_Tree() {
		for (int i = 0; i < 4 * N; i++) {
			tree[i] = prop[i] = 0;
		}
	}

	void propagate(int pos) {
		tree[pos * 2] += prop[pos];
		tree[pos * 2 + 1] += prop[pos];
		prop[pos * 2] += prop[pos];
		prop[pos * 2 + 1] += prop[pos];
		prop[pos] = 0;
	}

	void update(int pos, int left, int right, int x, int y, ll val) {
		if (left > y || right < x) return;
		if (left >= x && right <= y) {
			tree[pos] += val;
			prop[pos] += val;
			return;
		}
		propagate(pos);
		int mid = (left + right) >> 1;
		update(pos * 2, left, mid, x, y, val);
		update(pos * 2 + 1, mid + 1, right, x, y, val);
		tree[pos] = min(tree[pos * 2], tree[pos * 2 + 1]);
	}

	ll query(int pos, int left, int right, int x, int y) {
		if (left > y || right < x) return LONG_MAX;
		if (left >= x && right <= y) return tree[pos];
		propagate(pos);
		int mid = (left + right) >> 1;
		ll m = query(pos * 2, left, mid, x, y);
		ll n = query(pos * 2 + 1, mid + 1, right, x, y);
		return min(m, n);
	}
};

int solve() {
	int n = in(), mx = 0;
	std::vector<int> type(n + 1), height(n + 1);
	for (int i = 1; i <= n; i++) {
		type[i] = in(), height[i] = in();
		smax(mx, type[i]);
	}
	std::vector<int> last(mx + 1), pre(max(n + 1, mx + 1));
	for (int i = 1; i <= n; i++) {
		pre[i] = last[type[i]];
		last[type[i]] = i;
	}

	Segment_Tree dp;

	ll ans;

	stack < pair<pii, int>> st;
	st.push({{ -1, -1}, inf});
	int L = 0;
	for (int i = 1; i <= n; i++) {
		smax(L, pre[i]);
		while (st.top().ss < height[i]) {
			dp.update(1, 0, n, st.top().ff.ff, st.top().ff.ss, -1LL * st.top().ss);
			st.pop();
		}
		st.push({{st.top().ff.ss + 1, i - 1}, height[i]});
		dp.update(1, 0, n, st.top().ff.ff, st.top().ff.ss, 1LL * st.top().ss);
		ans = dp.query(1, 0, n, L, i - 1);
		dp.update(1, 0, n, i, i, ans);
	}
	printf("%lld\n", ans);
	return 0;
}

int main() {
	int test = 1, tc = 0;
	scanf("%d", &test);
	while (test--) {
		printf("Case %d: ", ++tc);
		solve();
	}
	return 0;
}



