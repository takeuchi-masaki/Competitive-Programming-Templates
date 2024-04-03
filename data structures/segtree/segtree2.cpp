#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Tree {
    typedef ll T;
    static constexpr T unit = LLONG_MIN;
    int n;
    vector<T> data;
    T combine(T a, T b) {
        return max(a, b);
    }
    /* initialize size to closest power of 2 */
    Tree(int _n) {
        n = 1; while (n < _n) n <<= 1;
        data.assign(n * 2, unit);
    }
    /* O(n) construction */
    Tree(vector<T>& v) : Tree((int)v.size()) {
        for (int i = 0; i < n; i++) data[i + n] = v[i];
        for (int i = n - 1; i > 0; i--) data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }
    /*  add: data[pos += n] += val
        set: data[pos += n] = val  */
    void update(int pos, T val) {
        for (data[pos += n] = val; pos >>= 1; )
            data[pos] = combine(data[pos << 1], data[pos << 1 | 1]);
    }
    /* query [b, e) */
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b >>= 1, e >>= 1) {
            if (b & 1) ra = combine(ra, data[b++]);
            if (e & 1) rb = combine(data[--e], rb);
        }
        return combine(ra, rb);
    }
    /*  default: for max
        find first idx within [a, b) >= val */
    int lower_bound(int a, int b, T val) {
        int l = 0, r = n, node = 1;
        if (data[node] < val || a > r || b < l) return -1;
        while (node < n) {
            node *= 2;
            int mid = l + (r - l) / 2;
            if (mid >= a && l <= b && data[node] >= val) {
                r = mid;
            } else {
                l = mid;
                if (r < a || l > b || data[++node] < val) return -1;
            }
        }
        return node - n;
    }
    /* data at single position 'i' */
    inline T operator[] (int i) { return data[i + n]; }
    /* prints all ranges, for debugging */
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
            cout << '\n';
        }
        cout << endl;
    }
};

int main() {
    vector<int> A = { 1, 5, 2, 9, -5 };
    int n = int(A.size());
    Tree maxtree(n);
    for (int i = 0; i < n; i++) {
        maxtree.update(i, A[i]);
    }
    maxtree.debug();

    for (int i = 0; i < n; i++) {
        cout << maxtree.query(0, i + 1) << ' ';
    }
    cout << '\n';

    maxtree.update(3, -1);
    for (int i = 0; i < n; i++) {
        cout << maxtree.query(i, n) << " ";
    }
    cout << '\n';
}