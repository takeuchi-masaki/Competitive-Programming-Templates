#include <bits/stdc++.h>
using namespace std;

/*
    Based off of Kactl Segtree
https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
*/
struct Tree {
    typedef long long T;
    static constexpr T unit = LLONG_MIN;
    int n;
    vector<T> data;
    T combine(T a, T b) {
        return max(a, b);
    }
    Tree(int _n) : n(_n), data(_n * 2) {}
    /*  add: data[pos += n] += val
        set: data[pos += n] = val  */
    void update(int i, T val) {
        for (data[i += n] = val; i /= 2; ) {
            data[i] = combine(data[i * 2], data[i * 2 + 1]);
        }
    }
    /* query [b, e) */
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b & 1) ra = combine(ra, data[b++]);
            if (e & 1) rb = combine(data[--e], rb);
        }
        return combine(ra, rb);
    }
};

int main() {
    vector<int> A = { 1, 5, 2, 9, -5 };
    int n = int(A.size());
    Tree maxtree(n);
    for (int i = 0; i < n; i++) {
        maxtree.update(i, A[i]);
    }

    for (int i = 0; i < int(maxtree.data.size()); i++) {
        cout << i << ": " << maxtree.data[i] << '\n';
    }
    cout << '\n';

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