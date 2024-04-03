#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool chmin(auto& a, const auto& b) { return b < a ? a = b, 1 : 0; }
bool chmax(auto& a, const auto& b) { return a < b ? a = b, 1 : 0; }
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define vec vector
#define vi vector<int>
[[maybe_unused]] const int INF = 0x3f3f3f3f;

// https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm
// https://codeforces.com/contest/840/problem/D
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng) // [a, b]
mt19937 rng(time(nullptr));

const int MX_VAL = int(3e5) + 10;
int cnt[MX_VAL];
vi A;

void remove(int idx) {
    cnt[A[idx]]--;
}
void add(int idx) {
    cnt[A[idx]]++;
}
int get_answer(int l, int r, int nec) {
    int ret = INF;
    rep(_, 0, 80) {
        int randidx = uid(l, r);
        if (cnt[A[randidx]] >= nec) {
            chmin(ret, A[randidx]);
        }
    }
    if (ret == INF) return -1;
    return ret;
}

const int block_size = sqrt(MX_VAL);

struct Query {
    int l, r, nec, idx;
    bool operator<(Query other) const {
        return make_pair(l / block_size, r) <
            make_pair(other.l / block_size, other.r);
    }
};

vector<int> mo_s_algorithm(vector<Query> queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer(q.l, q.r, q.nec);
    }
    return answers;
}

void solve() {
    int n, q;
    cin >> n >> q;
    A.assign(n, 0);
    for (auto& x : A) cin >> x;
    vec<Query> Q;
    int l, r, k;
    rep(i, 0, q) {
        cin >> l >> r >> k;
        int range = r - l + 1;
        int nec = range / k + 1;
        Q.push_back({ l - 1, r - 1, nec, i });
    }
    vi ans = mo_s_algorithm(Q);
    for (int x : ans) cout << x << '\n';
}

int main() {
#ifndef LOCAL
    cin.tie(nullptr);
#endif
    ios::sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    solve();
}