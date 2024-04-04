#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define vec vector
#define vi vector<ll>

// checked on 
// Range Add/Set, Range sum              https://cses.fi/problemset/task/1735/
// Point Update, Binary Search query    https://cses.fi/problemset/task/1143/
// Range Add, Range Min                 https://codeforces.com/problemset/problem/52/C
// Range Add/Set, Binary Search leftmost max >= x   (custom test)
/*
    Iterative Proportional Lazy Segment Tree with Add/Set
    Range Operations:
        add(a, b, val) : add val to range [a, b)
        set(a, b, val) : set range [a, b) as val
    Single Operations:
        add(a, val) : add val to position a
        set(a, val) : set position a to val
    Queries:
        query(a, b) : get query of range [a, b)
        query(a) : get value at position a
        lower_bound(a, b, x) : get first idx within range [a, b) >= x or -1
    To Change:
        modify combine_data to min/max, etc
        modify default value 'def'
        if range add/set + range sum, scale lazy value with length
*/
class Tree {
    typedef ll T; // monoid T
    struct L { // lazy L
        bool isSet = false;
        T val = 0;
        bool operator == (L& o) const { return val == o.val && isSet == o.isSet; }
    };
    static constexpr T def = 0; // change here
    static constexpr L ldef = { false, 0 };
    T combine_data(T a, T b) { // change here
        return max(a, b);
    }
    T combine_data_lazy(T a, L b) { return (b.isSet ? b.val : a + b.val); }
    L combine_lazy(L a, L b) { return (!b.isSet ? a.val += b.val, a : b); }
    L scale_lazy(L a, int len) {
        // a.val *= len; /* for use with range sum */
        return a;
    }
public:
    int n, h;
    vector<T> data;
    vector<L> lazy;
    Tree(int _n) {
        n = 1, h = 0; while (n < _n) { n <<= 1, h++; }
        data.assign(n << 1, def), lazy.assign(n << 1, ldef);
    }
    /* O(n) construction */
    Tree(const vector<T>& v) : Tree((int)v.size()) {
        for (int i = 0; i < int(v.size()); i++) data[n + i] = v[i];
        for (int i = n - 1; i; i--) data[i] = combine_data(data[i << 1], data[i << 1 | 1]);
    }
    /* add [a, B) */
    void add(int a, int b, T val) { update(a, b, { false, val }); }
    /* set [a, b) */
    void set(int a, int b, T val) { update(a, b, { true, val }); }
    /* add to pos a */
    void add(int a, T x) {
        push(a += n);
        data[a] += x;
        lazy[a] = ldef;
        recalc(a);
    }
    /* set pos a */
    void set(int a, T x) {
        push(a += n);
        data[a] = x;
        lazy[a] = ldef;
        recalc(a);
    }
    /* query pos a */
    T query(int a) {
        push(a += n);
        return reflect(a, 1);
    }
    /* query [a, b) */
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
    /* default: find leftmost index >= x */
    int lower_bound(int a, int b, T x) { return lower_bound(a, b, x, 1, 0, n); }
    /* prints all ranges */
    void debug() {
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
private:
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
    int lower_bound(int a, int b, T x, int k, int l, int r) {
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
};

signed main() {
    vi A = { 1, 2, 3, 4, 5 };
    int n = int(A.size());
    Tree tree(A);

    tree.debug();
    cout << tree.query(0, n) << '\n';
    cout << tree.query(0, 2) << '\n';
    tree.set(0, n, 0);
    tree.add(0, n, 2);
    cout << tree.query(0, 2) << '\n';
    tree.debug();
}