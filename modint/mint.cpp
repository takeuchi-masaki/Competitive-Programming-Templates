#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;
/* modular int for MOD s.t. MOD * MOD < UINT32_MAX */
typedef struct mint32 {
    uint64_t val;
    mint32() : val(0) {}
    mint32(int64_t v) : val((v + MOD) % MOD) {}
    mint32(int64_t a, int64_t b) : mint32(a) { *this /= mint32(b); } // a * b^-1
    inline constexpr mint32& operator+=(mint32 const& b) { val += b.val; if (val >= MOD) val -= MOD; return *this; }
    inline constexpr mint32& operator-=(mint32 const& b) { val += MOD - b.val; if (val >= MOD) val -= MOD; return *this; }
    inline constexpr mint32& operator*=(mint32 const& b) { val = (val * b.val) % MOD; return *this; }
    friend inline mint32 mexp(mint32 b, int64_t e) { mint32 res(1); for (; e; b *= b, e /= 2) if (e & 1) res *= b; return res; }
    friend inline mint32 inverse(mint32 a) { return mexp(a, MOD - 2); } // assumes a, MOD coprime
    inline mint32& operator/=(mint32 const& b) { return *this *= inverse(b); }
    friend inline mint32 operator+(mint32 a, mint32 const b) { return a += b; }
    friend inline mint32 operator-(mint32 a, mint32 const b) { return a -= b; }
    friend inline mint32 operator-(mint32 const a) { return 0 - a; }
    friend inline mint32 operator*(mint32 a, mint32 const b) { return a *= b; }
    friend inline mint32 operator/(mint32 a, mint32 const b) { return a /= b; }
    friend inline istream& operator>>(istream& is, mint32& a) { int64_t in; is >> in; a = mint32(in); return is; }
    friend inline ostream& operator<<(ostream& os, mint32 const& a) { return os << a.val; }
    friend inline bool operator==(mint32 const& a, mint32 const& b) { return a.val == b.val; }
    friend inline bool operator!=(mint32 const& a, mint32 const& b) { return a.val != b.val; }
} mint;

int main() {}