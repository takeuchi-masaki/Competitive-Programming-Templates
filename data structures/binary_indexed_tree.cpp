#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct BIT { // from nyaan's library
    int N;
    vector<ll> data;
    BIT(int size) : N(size + 2), data(size + 3) {}

    /* sum [0, i] */
    ll sum(int i) const {
        if (i < 0) return 0;
        ll ret = 0;
        for (++i; i > 0; i -= i & -i) ret += data[i];
        return ret;
    }

    /* sum [l, r] */
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }

    /* add x to idx i */
    void add(int i, ll x) {
        for (++i; i < N; i += i & -i) data[i] += x;
    }

    /* [OPTIONAL] minimize i s.t. sum(i) >= w */
    int lower_bound(ll w) {
        if (w <= 0) return 0;
        int i = 0, H = 31 - __builtin_clz(N);
        for (int k = 1 << H; k; k >>= 1) {
            if (i + k <= N - 1 && data[i + k] < w) {
                w -= data[i + k];
                i += k;
            }
        }
        return i; // i >= N <=> total sum < w
    }
};
struct RangeAddRangeSumBIT { // from nyaan's library
    BIT a, b;
    RangeAddRangeSumBIT(int N) : a(N + 1), b(N + 1) {}
    /* add x to [l, r) */
    void add(int l, int r, ll x) {
        a.add(l, x);
        a.add(r, -x);
        b.add(l, x * (1 - l));
        b.add(r, x * (r - 1));
    }
    /* sum of [l, r) */
    ll sum(int l, int r) {
        --r, --l;
        return a.sum(r) * r + b.sum(r) - a.sum(l) * l - b.sum(l);
    }
};

signed main() {
    vector<ll> arr = { 4, 3, 2, 4, 1, 2 };
    int n = int(arr.size());
    BIT bit(n);
    for (int i = 0; i < n; i++) {
        bit.add(i, arr[i]);
    }

    for (int i = 0; i < n; i++) {
        cout << bit.sum(i) << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = i; j < n; j++) {
            cout << bit.sum(i, j) << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < bit.N; i++) {
        cout << bit.data[i] << " ";
    }
    cout << endl;
}