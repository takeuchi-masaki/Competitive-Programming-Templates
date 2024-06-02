#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;
/* modular int for static MOD s.t. MOD * MOD < UINT32_MAX */
typedef struct mint32 {
    uint64_t val;
    constexpr mint32() : val(0) {}
    constexpr mint32(int64_t v) : val((v + MOD) % MOD) {}
    constexpr mint32(int64_t a, int64_t b) : mint32(a) { *this /= mint32(b); } // a * b^-1
    constexpr mint32& operator+=(mint32 const& b) { val += b.val; if (val >= MOD) val -= MOD; return *this; }
    constexpr mint32& operator-=(mint32 const& b) { val += MOD - b.val; if (val >= MOD) val -= MOD; return *this; }
    constexpr mint32& operator*=(mint32 const& b) { val = (val * b.val) % MOD; return *this; }
    friend constexpr mint32 mexp(mint32 b, int64_t e) { mint32 res(1); for (; e; b *= b, e /= 2) if (e & 1) res *= b; return res; }
    friend constexpr mint32 inverse(mint32 a) { return mexp(a, MOD - 2); } // assumes a, MOD coprime
    constexpr mint32& operator/=(mint32 const& b) { return *this *= inverse(b); }
    friend constexpr mint32 operator+(mint32 a, mint32 const b) { return a += b; }
    friend constexpr mint32 operator-(mint32 a, mint32 const b) { return a -= b; }
    friend constexpr mint32 operator-(mint32 const a) { return 0 - a; }
    friend constexpr mint32 operator*(mint32 a, mint32 const b) { return a *= b; }
    friend constexpr mint32 operator/(mint32 a, mint32 const b) { return a /= b; }
    friend constexpr istream& operator>>(istream& is, mint32& a) { int64_t in; is >> in; a = in; return is; }
    friend constexpr ostream& operator<<(ostream& os, mint32 const& a) { return os << a.val; }
    friend constexpr bool operator==(mint32 const& a, mint32 const& b) { return a.val == b.val; }
    friend constexpr bool operator!=(mint32 const& a, mint32 const& b) { return a.val != b.val; }
} mint;

int main() {}
