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

const int N          = 600 + 5;
const int inf        = (int)2e9 + 5;
const ll  Inf        = (ll)1e18 + 5;
const int mod        = (int)1e9 + 7;
const ll  Mod        = (ll)1e9 + 7;




string s, t;

int lcs[N][N];
ll dp[N][N];


int solve() {
	cin >> s >> t;
	fill(lcs, 0);
	int n = sz(s), m = sz(t);
	for (int i = 0; i <= max(n, m); i++) {
		dp[i][0] = dp[0][i] = 1;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i] == t[j]) lcs[i + 1][j + 1] = lcs[i][j] + 1;
			else lcs[i + 1][j + 1] = max(lcs[i][j + 1], lcs[i + 1][j]);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1];
			else {
				if (lcs[i - 1][j] == lcs[i][j - 1]) dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				else {
					if (lcs[i - 1][j] > lcs[i][j - 1]) dp[i][j] = dp[i - 1][j];
					else dp[i][j] = dp[i][j - 1];
				}
			}
		}
	}
	printf("%d %lld\n", sz(s) + sz(t) - lcs[n][m], dp[n][m]);
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



