#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

using D = long double;
using P = complex<D>;
const D eps = 1e-12, inf = 1e15, pi = acos(-1), e = exp(1.);

D cross(P a, P b) { return imag(conj(a) * b); }
D cross(P a, P b, P c) { return cross(b - a, c - a); }
D dot(P a, P b) { return real(conj(a) * b); }
P scale(P a, D len) { return a * (len / abs(a)); }
P rotate(P p, D ang) { return p * polar(D(1), ang); }
D angle(P a, P b) { return arg(b) - arg(a); }
int ccw(P a, P b, P c) {
    b -= a; c -= a;
    if (cross(b, c) > eps)  return +1;  // counter clockwise
    if (cross(b, c) < -eps) return -1;  // clockwise
    if (dot(b, c) < 0)      return +2;  // c--a--b on line
    if (norm(b) < norm(c))  return -2;  // a--b--c on line
    return 0;
}
