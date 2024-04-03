#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
    Binary Searchable Iterative Lazy Segment Tree:
    Lazy Add or Lazy Set, Range max or Range min
*/
struct Tree {
    typedef ll T, L;
    static constexpr T def = LLONG_MAX; // change here
    static constexpr L ldef = 0; // change here
    T combine_data(T a, T b) { // change here
        return min(a, b);
    }
    T combine_data_lazy(T a, L b) { // default add, for set: return b;
        return a + b;
    }
    L combine_lazy(L a, L b) { // default add, for set: return b;
        return a + b;
    }
    int n, h;
    vector<T> data;
    vector<L> lazy;
    Tree(int _n) {
        n = 1, h = 0; while (n < _n) { n <<= 1, h++; }
        data.assign(n << 1, def), lazy.assign(n << 1, ldef);
    }
    Tree(vector<T>& V) : Tree((int)V.size()) {
        for (int i = 0; i < (int)V.size(); i++) data[i + n] = V[i];
        for (int i = n - 1; i; i--) data[i] = combine_data(data[i << 1], data[i << 1 | 1]);
    }
    T reflect(int k) {
        if (lazy[k] == ldef) return data[k];
        return combine_data_lazy(data[k], lazy[k]);
    }
    void eval(int k) {
        if (lazy[k] == ldef) return;
        if (k < n) {
            lazy[k << 1 | 0] = combine_lazy(lazy[k << 1 | 0], lazy[k]);
            lazy[k << 1 | 1] = combine_lazy(lazy[k << 1 | 1], lazy[k]);
        }
        data[k] = reflect(k);
        lazy[k] = ldef;
    }
    void push(int k) { for (int i = h; i; i--) eval(k >> i); }
    void recalc(int k) {
        while (k >>= 1) data[k] = combine_data(reflect(k << 1), reflect(k << 1 | 1));
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
    T query(int a, int b) {
        if (a >= b) return def;
        push(a += n), push(b += n - 1);
        T vl = def, vr = def;
        for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) vl = combine_data(vl, reflect(l++));
            if (r & 1) vr = combine_data(reflect(--r), vr);
        }
        return combine_data(vl, vr);
    }
};