#include <bits/stdc++.h>
using namespace std;
#include <debugoutput.h>
using ll = long long;
using ld = long double;
[[maybe_unused]] const int INF = 0x3f3f3f3f;
[[maybe_unused]] const ll LINF = 0x3f3f3f3f3f3f3f3f;
template<class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
#define vec vector
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pb push_back
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define rrep(i, a, b) for (int i = int(a); i >= int(b); i--)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define vi vector<int>

#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) // [a, b]
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n = int(1e4);
    int q = int(1e4);
    ll MX = ll(1e9);
    cout << n << " " << q << '\n';
    rep(i, 0, n) {
        cout << uid(-MX, MX) << " ";
    }
    rep(i, 0, q) {
        int type = uid(1, 3);
        int idx1 = uid(1, n), idx2 = uid(1, n);
        cout << type << ' ' << min(idx1, idx2) << " " << max(idx1, idx2)
            << " " << uid(-MX, MX) << '\n';
    }
}

signed main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    cin.exceptions(cin.failbit);

    freopen("large.in", "w", stdout);

    solve();
}