#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include <debugoutput.h> // https://github.com/takeuchi-masaki/Competitive-Programming-Templates/blob/main/debugoutput.h
#else
#define dbg(...)
#define ass(...)
#endif
typedef long long ll;
[[maybe_unused]] constexpr int INF = 0x3f3f3f3f;
[[maybe_unused]] constexpr ll LINF = 0x3f3f3f3f3f3f3f3f;
template<class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool chmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }
template<class A, class B> istream& operator>> (istream& is, pair<A, B>& p) { return is >> p.first >> p.second; }
template<class T> istream& operator>> (istream& is, vector<T>& V) { for (auto& v : V) is >> v; return is; }
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define rrep(i, a, b) for (int i = int(a); i >= int(b); i--)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define len(x) (int)(x).size()
#define pii pair<ll, ll>
#define pb push_back
#define vec vector


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