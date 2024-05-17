#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T> bool chmin(T& a, const T& b) { return (b < a ? a = b, 1 : 0); }
template <class T> bool chmax(T& a, const T& b) { return (b > a ? a = b, 1 : 0); }
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define vec vector
#define vi vector<ll>
#define pii pair<ll, ll>

// https://algo-logic.info/segment-tree/
// https://ei1333.github.io/algorithm/segment-tree.html

/**
 * Lazy Proportional Segment tree
 * for min/max query, change default to LLONG_MAX or LLONG_MIN
 * for range sum query, in scale_lazy, a.val *= len;
 * to use less memory, change to 0-indexing and set lazy size to n
*/
struct Tree {
    typedef ll T;
    struct L {
        bool isSet = false;
        T val = 0;
        bool operator == (L& m) const { return val == m.val && isSet == m.isSet; }
    };
    const T def = 0;
    const L ldef = { false, 0 };
    T combine_data(T a, T b) { return max(a, b); } // change here to min/max(a, b) or a + b
    L scale_lazy(L a, int len) {
        // a.val *= len; // for lazy range sum query
        return a;
    }
    T combine_data_lazy(T a, L b) { return (b.isSet ? b.val : a + b.val); }
    L combine_lazy(L a, L b) {
        if (b.isSet) return b;
        a.val += b.val;
        return a;
    }
    int n;
    vector<T> data;
    vector<L> lazy;
    Tree(int n_) {
        n = 1; while (n < n_) n *= 2;
        data.assign(n * 2, def);
        lazy.assign(n * 2, ldef);
    }
    Tree(vector<T>& v) : Tree(int(v.size())) {
        for (int i = 0; i < (int)v.size(); i++) data[i + n] = v[i];
        for (int k = n - 1; k > 0; k--) data[k] = combine_data(data[2 * k], data[2 * k + 1]);
    }
    void eval(int k, int len) {
        if (lazy[k] == ldef) return;
        if (k < n) {
            lazy[k * 2 + 0] = combine_lazy(lazy[k * 2 + 0], lazy[k]);
            lazy[k * 2 + 1] = combine_lazy(lazy[k * 2 + 1], lazy[k]);
        }
        data[k] = combine_data_lazy(data[k], scale_lazy(lazy[k], len));
        lazy[k] = ldef;
    }
    void update(int a, int b, L x, int k, int l, int r) {
        eval(k, r - l);
        if (a <= l && r <= b) {
            lazy[k] = combine_lazy(lazy[k], x);
            eval(k, r - l);
        } else if (a < r && l < b) {
            update(a, b, x, k * 2 + 0, l, (l + r) / 2);
            update(a, b, x, k * 2 + 1, (l + r) / 2, r);
            data[k] = combine_data(data[k * 2 + 0], data[k * 2 + 1]);
        }
    }
    void update(int a, int b, L x) { update(a, b, x, 1, 0, n); }
    void add(int a, int b, T x) { update(a, b, { false, x }); }
    void set(int a, int b, T x) { update(a, b, { true, x }); }
    T query(int a, int b, int k, int l, int r) {
        eval(k, r - l);
        if (r <= a || b <= l) {
            return def;
        } else if (a <= l && r <= b) {
            return data[k];
        } else {
            T vl = query(a, b, k * 2 + 0, l, (l + r) / 2);
            T vr = query(a, b, k * 2 + 1, (l + r) / 2, r);
            return combine_data(vl, vr);
        }
    }
    T query(int a, int b) { return query(a, b, 1, 0, n); }
    int lower_bound(int a, int b, T x) { return lower_bound(a, b, x, 1, 0, n); }
    int lower_bound(int a, int b, T x, int k, int l, int r) {
        eval(k, r - l);
        if (data[k] < x || r <= a || b <= l) {
            return -1;
        } else if (k >= n) {
            return k - n;
        } else {
            int vl = lower_bound(a, b, x, 2 * k, l, (l + r) / 2);
            if (vl != -1) {
                return vl;
            } else {
                return lower_bound(a, b, x, 2 * k + 1, (l + r) / 2, r);
            }
        }
    }
};
