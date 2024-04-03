#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool chmin(auto& a, const auto& b) { return b < a ? a = b, 1 : 0; }
bool chmax(auto& a, const auto& b) { return b > a ? a = b, 1 : 0; }

using T = array<int, 3>;
struct kDTree { // from tatyam https://trap.jp/post/1489/
    using Iter = vector<T>::iterator;
    kDTree* l = nullptr, * r = nullptr;
    int xmin = INT_MAX, xmax = INT_MIN, ymin = INT_MAX, ymax = INT_MIN;
    ll sum = 0;
    kDTree(Iter begin, Iter end, bool divx = true) {
        for (auto p = begin; p != end; p++) {
            auto [x, y, w] = *p;
            chmin(xmin, x);
            chmax(xmax, x);
            chmin(ymin, y);
            chmax(ymax, y);
            sum += w;
        }
        const int size = int(end - begin);
        if (size <= 1) return;
        auto cen = begin + size / 2;
        if (divx) {
            nth_element(begin, cen, end, [](T& a, T& b) { return a[0] < b[0]; });
        } else {
            nth_element(begin, cen, end, [](T& a, T& b) { return a[1] < b[1]; });
        }
        l = new kDTree(begin, cen, !divx);
        r = new kDTree(cen, end, !divx);
    }
    // [-INF, x] * [-INF, y] にある点の重みを数える
    // get the weights of the points in the range [-INF, x] * [-INF, y]
    ll get(int x, int y) const {
        // [xmin, xmax] * [ymin, ymax] と [-INF, x] * [-INF, y] に共通部分がない
        // no intersection between [xmin, xmax] * [ymin, ymax] and [-INF, x] * [-INF, y]
        if (x < xmin || y < ymin) return 0;

        // [xmin, xmax] * [ymin, ymax] 全体が [-INF, x] * [-INF, y] に含まれている
        // the whole range [xmin, xmax] * [ymin, ymax] is within [-INF, x] * [-INF, y]
        if (xmax <= x && ymax <= y) return sum;

        // [xmin, xmax] * [ymin, ymax] の一部が [x1, x2] * [y1, y2] に含まれている -> 子に任せる
        // part of the range [xmin, xmax] * [ymin, ymax] is within [x1, x2] * [y1, y2] -> child evaluates
        return l->get(x, y) + r->get(x, y);
    }
};

int main() {


}