#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct BIT { // fenwicktree2d
    vector<vector<ll>> bit;
    int n, m;
    BIT(int n, int m) : n(n), m(m), bit(n, vector<ll>(m)) {}
    // 2d sum from (0, 0)
    ll sum(int x, int y) {
        ll ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }
    // x2 >= x1, y2 >= y1, make sure x1, y1 are greater than 0
    ll sum2d(int x1, int y1, int x2, int y2) {
        assert(x1 > 0 && y1 > 0);
        x1--, y1--;
        return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) + sum(x1, y1);
    }
    void add(int x, int y, ll delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};

// https://nyaannyaan.github.io/library/data-structure-2d/2d-binary-indexed-tree.hpp
template <typename T>
struct BinaryIndexedTree2D {
    int H, W;
    vector<vector<T>> bit;
    BinaryIndexedTree2D(int _H, int _W) : H(_H + 1), W(_W + 1) {
        bit.resize(H + 3, vector<T>(W + 3, 0));
    }
    // 関数の入力のindexは0-originを想定

    // (x,y)にwを足す
    // 範囲外の時は足さない
    void add(int x, int y, T w) {
        if (x < 0 || x >= H || y < 0 || y >= W) return;
        for (int a = (++y, ++x); a <= H; a += a & -a) {
            for (int b = y; b <= W; b += b & -b) {
                bit[a][b] += w;
            }
        }
    }

    // imos法で[(x1,y1) , (x2,y2)]にwを足す
    void imos(int x1, int y1, int x2, int y2, T w) {
        add(x1, y1, w);
        add(x1, y2 + 1, -w);
        add(x2 + 1, y1, -w);
        add(x2 + 1, y2 + 1, w);
    }

    //  [(0,0) , (x,y)]の和　閉区間に注意！
    // x,y<0の時は0 x>=H y>=Wのときはx=H-1,y=W-1とみなす
    // ( imos法の時は (x,y)の値を返す )
    T sum(int x, int y) {
        if (x < 0 || y < 0) return 0;
        if (x >= H) x = H - 1;
        if (y >= W) y = W - 1;
        T ret = 0;
        for (int a = (++y, ++x); a > 0; a -= a & -a) {
            for (int b = y; b > 0; b -= b & -b) {
                ret += bit[a][b];
            }
        }
        return ret;
    }

    // [(x1,y1) , (x2,y2)] の和
    // x1 > x2, y1 > y2の時はswap
    T sum(int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2) return T(0);
        return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) +
            sum(x1 - 1, y1 - 1);
    }
};