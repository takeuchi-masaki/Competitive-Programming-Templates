#include <bits/stdc++.h>
#include <debugoutput.h>
typedef long long ll;
using namespace std;

// https://github.com/sunho/algorithms/blob/master/lib/range_query/merge_sort_tree.cpp
struct MergeSortTree {
    int n;
    vector<vector<int>> tree;
    MergeSortTree(const vector<int>& A) : n(int(A.size())), tree(2 * n) {
        for (int i = 0; i < n; i++) {
            tree[i + n].push_back(A[i]);
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i].resize(tree[i * 2].size() + tree[i * 2 + 1].size());
            merge(begin(tree[i * 2]), end(tree[i * 2]), begin(tree[i * 2 + 1]), end(tree[i * 2 + 1]), tree[i].begin());
        }
    }
    /* How many values are greater than k in range [l, r] */
    int query(int l, int r, int k) {
        int ret = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) ret += tree[l].end() - upper_bound(begin(tree[l]), end(tree[l]), k), l++;
            if (~r & 1) ret += tree[r].end() - upper_bound(begin(tree[r]), end(tree[r]), k), r--;
        }
        return ret;
    }
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
            cout << i << ": [" << res.first << ", " << res.second << ") ";
            dbg(tree[i]);
        }
        cout << endl;
    }
};
