#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include <debugoutput.h>
#else
#define dbg(...)
#endif
typedef long long ll;
[[maybe_unused]] constexpr int INF = 0x3f3f3f3f;
[[maybe_unused]] constexpr ll LINF = 0x3f3f3f3f3f3f3f3f;
template<class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool chmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }
#define rep(i, a, b) for (int i = int(a), i##_max_ = int(b); i < i##_max_; i++)
#define rrep(i, a, b) for (int i = int(a), i##_min_ = int(b); i >= i##_min_; i--)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define len(x) (int)(x).size()
#define vec vector
#define pii pair<ll, ll>


void solve() {

}

signed main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    cin.exceptions(cin.failbit);
    int T = 1;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        solve();
    }
}