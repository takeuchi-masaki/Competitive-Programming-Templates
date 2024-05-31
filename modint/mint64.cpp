#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll MOD = 2942570579247449;
/*
modular int for use with >32 bit modulo
faster than using 128-bit but slower than 2^61 - 1 version for string hashing
*/
typedef struct mint64 {
    uint64_t val;
    mint64() : val(0) {}
    mint64(ll v) : val((v + MOD) % MOD) {}
    mint64(ll a, ll b) : mint64(a) { *this /= mint64(b); } // a * b^-1
    inline constexpr mint64& operator+=(mint64 const& b) { val += b.val; if (val >= MOD) val -= MOD; return *this; }
    inline constexpr mint64& operator-=(mint64 const& b) { val += MOD - b.val; if (val >= MOD) val -= MOD; return *this; }
    inline constexpr mint64& operator*=(mint64 const& b) { // kactl modmul
        int64_t res = this->val * b.val - MOD * uint64_t(1.L / MOD * this->val * b.val);
        val = res + MOD * (res < 0) - MOD * (res >= (int64_t)MOD); return *this;
    }
    friend inline mint64 mexp(mint64 b, ll e) { mint64 res(1); for (; e; b *= b, e /= 2) if (e & 1) res *= b; return res; }
    friend inline mint64 inverse(mint64 a) { return mexp(a, MOD - 2); }
    inline mint64& operator/=(mint64 const& b) { return *this *= inverse(b); }
    friend inline mint64 operator+(mint64 a, mint64 const b) { return a += b; }
    friend inline mint64 operator-(mint64 a, mint64 const b) { return a -= b; }
    friend inline mint64 operator-(mint64 const a) { return MOD - a; }
    friend inline mint64 operator*(mint64 a, mint64 const b) { return a *= b; }
    friend inline mint64 operator/(mint64 a, mint64 const b) { return a /= b; }
    friend inline istream& operator>>(istream& is, mint64& a) { ll in; is >> in; a = mint64(in); return is; }
    friend inline ostream& operator<<(ostream& os, mint64 const& a) { return os << a.val; }
    friend inline bool operator==(mint64 const& a, mint64 const& b) { return a.val == b.val; }
    friend inline bool operator!=(mint64 const& a, mint64 const& b) { return a.val != b.val; }
} mint;

int main() {


}