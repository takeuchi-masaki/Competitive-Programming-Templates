#include <bits/stdc++.h>
using namespace std;
template<typename T> istream& operator>>(istream& in, pair<T, T>& p) { return in >> p.first >> p.second; };
template<typename T> istream& operator>>(istream& in, vector<T>& a) { for (auto& x : a) in >> x; return in; };
template<typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream& os, const T_container& v) { os << '{'; string sep; for (const T& x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() {}
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << H << " "; dbg_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) dbg_out(__VA_ARGS__), cout << "(" << #__VA_ARGS__ << ") [" << __LINE__ << "]" << endl;
#else
#define dbg(...)
#endif
using ll = long long;
using ld = long double;
[[maybe_unused]] const ld EPS = 1e-9;
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
// const int MOD = 1000000007;
// const int MOD = 998244353;

/*
    Iterative Proportional Lazy Segment Tree with Add/Set
    Range Operations:
        add(a, b, val) : add val to range [a, b)
        set(a, b, val) : set range [a, b) as val
    Single Operations:
        add_val(a, val) : add val to position a
        set_val(a, val) : set position a to val
    Queries:
        query(a, b) : get query of range [a, b)
        get_val(a) : get value at position a
        lower_bound(a, b, x) : get first idx within range [a, b) >= x or -1
    To Change:
        modify combine_data to min/max, etc
        modify default value 'def'
        if range add/set + range sum, scale lazy value with length
*/
struct Tree {
    typedef ll T; // monoid T
    struct L { // lazy L
        bool isSet = false;
        T val = 0;
        bool operator == (L& o) const { return val == o.val && isSet == o.isSet; }
    };
    static constexpr T def = LLONG_MIN; // change here
    static constexpr L ldef = { false, 0 };
    T combine_data(T a, T b) { // change here
        return max(a, b);
    }
    T combine_data_lazy(T a, L b) { return (b.isSet ? b.val : a + b.val); }
    L combine_lazy(L a, L b) { return (!b.isSet ? a.val += b.val, a : b); }
    L scale_lazy(L a, int len) { // use len for rangesum
        // a.val *= len;
        return a;
    }
    int n, h;
    vector<T> data;
    vector<L> lazy;
    Tree(int _n) { init(_n); }
    Tree(const vector<T>& v) {
        init(int(v.size()));
        for (int i = 0; i < int(v.size()); i++) data[n + i] = v[i];
        for (int i = n - 1; i; i--) data[i] = combine_data(data[i << 1], data[i << 1 | 1]);
    }
    void init(int _n) {
        n = 1, h = 0; while (n < _n) { n <<= 1, h++; }
        data.assign(n << 1, def), lazy.assign(n << 1, ldef);
    }
    inline T reflect(int k, int len) {
        if (lazy[k] == ldef) return data[k];
        return combine_data_lazy(data[k], scale_lazy(lazy[k], len));
    }
    inline void eval(int k, int len) {
        if (lazy[k] == ldef) return;
        if (k < n) {
            lazy[k << 1 | 0] = combine_lazy(lazy[k << 1 | 0], lazy[k]);
            lazy[k << 1 | 1] = combine_lazy(lazy[k << 1 | 1], lazy[k]);
        }
        data[k] = reflect(k, len);
        lazy[k] = ldef;
    }
    inline void push(int k) {
        for (int i = h, len = 1 << h; i; i--, len >>= 1) eval(k >> i, len);
    }
    inline void recalc(int k) {
        int len = 1;
        while (k >>= 1) {
            data[k] = combine_data(reflect(k << 1, len), reflect(k << 1 | 1, len));
            len <<= 1;
        }
    }
    void update(int a, int b, L x) {
        if (a >= b) return;
        push(a += n), push(b += n - 1);
        for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) lazy[l] = combine_lazy(lazy[l], x), l++;
            if (r & 1) --r, lazy[r] = combine_lazy(lazy[r], x);
        }
        recalc(a), recalc(b);
    }
    void add(int a, int b, T val) { update(a, b, { false, val }); }
    void set(int a, int b, T val) { update(a, b, { true, val }); }
    T query(int a, int b) {
        if (a >= b) return def;
        push(a += n), push(b += n - 1);
        T vl = def, vr = def;
        for (int l = a, r = b + 1, len = 1; l < r; l >>= 1, r >>= 1, len <<= 1) {
            if (l & 1) vl = combine_data(vl, reflect(l++, len));
            if (r & 1) vr = combine_data(reflect(--r, len), vr);
        }
        return combine_data(vl, vr);
    }
    void set_val(int a, T x) {
        push(a += n);
        data[a] = x;
        lazy[a] = ldef;
        recalc(a);
    }
    void add_val(int a, T x) {
        push(a += n);
        data[a] += x;
        lazy[a] = ldef;
        recalc(a);
    }
    T get_val(int a) {
        push(a += n);
        return reflect(a, 1);
    }
    int lower_bound(int a, int b, T x) { return lower_bound(a, b, x, 1, 0, n); }
    int lower_bound(int a, int b, T x, int k, int l, int r) { // default: find leftmost index >= x
        eval(k, r - l);
        if (data[k] < x || r <= a || b <= l) return -1;
        if (k >= n) return k - n;
        int vl = lower_bound(a, b, x, k << 1, l, (l + r) / 2);
        if (vl != -1) {
            return vl;
        } else {
            return lower_bound(a, b, x, k << 1 | 1, (l + r) / 2, r);
        }
    }
    void debug() { // prints all ranges, for debugging
        auto interval = [&](int i, auto&& interval) -> pair<int, int> {
            if (i >= n) return { i - n, i - n + 1 };
            pair<int, int> l = interval(i * 2, interval);
            pair<int, int> r = interval(i * 2 + 1, interval);
            if (l.second != r.first) return { -1, -1 };
            return { l.first, r.second };
            };
        for (int i = 1; i < 2 * n; i++) {
            auto res = interval(i, interval);
            cout << i << ": [" << res.first << ", " << res.second << ") " << data[i];
            if (i < n) cout << " {" << lazy[i].isSet << " " << lazy[i].val << "}";
            cout << '\n';
        }
        cout << endl;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vec<ll> A(n);
    for (auto& x : A) cin >> x;

    Tree tree(A);
    int type, a, b, x;
    rep(_, 0, q) {
        cin >> type >> a >> b >> x;
        if (type == 1) {
            tree.add(a - 1, b, x);
        } else if (type == 2) {
            tree.set(a - 1, b, x);
        } else {
            int res = tree.lower_bound(a - 1, b, x);
            cout << (res == -1 ? res : res + 1) << '\n';
        }
    }
}

signed main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    cin.exceptions(cin.failbit);

    auto start_time = chrono::steady_clock::now();
    solve();
    auto end_time = chrono::steady_clock::now();
    cout << "\nruntime: " << fixed << setprecision(2)
        << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e6
        << " ms\n";
}