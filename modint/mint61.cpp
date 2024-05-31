#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
modular int Mersenne Prime 2^61 - 1
for use with Rabin-Karp String Hashing
*/
typedef struct mint61 {
    static constexpr uint64_t MOD = (1LL << 61) - 1;
    uint64_t val;
    mint61() : val(0) {}
    mint61(int64_t v) : val((v + MOD) % MOD) {}
    mint61(int64_t a, int64_t b) : mint61(a) { *this /= mint61(b); } // a * b^-1
    inline constexpr mint61& operator+=(mint61 const& b) { val += b.val; if (val >= MOD) val -= MOD; return *this; }
    inline constexpr mint61& operator-=(mint61 const& b) { val += MOD - b.val; if (val >= MOD) val -= MOD; return *this; }
    inline constexpr mint61& operator*=(mint61 const& b) {
        uint64_t l1 = (uint32_t)val, h1 = val >> 32, l2 = (uint32_t)b.val, h2 = b.val >> 32;
        uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        val = (l & MOD) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        val = (val & MOD) + (val >> 61); val = (val & MOD) + (val >> 61); val--;
        return *this;
    }
    friend inline mint61 mexp(mint61 b, int64_t e) { mint61 res(1); for (; e; b *= b, e /= 2) if (e & 1) res *= b; return res; }
    friend inline mint61 inverse(mint61 a) { return mexp(a, MOD - 2); } // assumes a, MOD coprime
    inline mint61 operator/=(mint61 const& b) { return *this *= inverse(b); }
    friend inline mint61 operator+(mint61 a, mint61 const b) { return a += b; }
    friend inline mint61 operator-(mint61 a, mint61 const b) { return a -= b; }
    friend inline mint61 operator-(mint61 const a) { return 0 - a; }
    friend inline mint61 operator*(mint61 a, mint61 const b) { return a *= b; }
    friend inline mint61 operator/(mint61 a, mint61 const b) { return a /= b; }
    friend inline istream& operator>>(istream& is, mint61& a) { int64_t in; is >> in; a = mint61(in); return is; }
    friend inline ostream& operator<<(ostream& os, mint61 const& a) { return os << a.val; }
    friend inline bool operator==(mint61 const& a, mint61 const& b) { return a.val == b.val; }
    friend inline bool operator!=(mint61 const& a, mint61 const& b) { return a.val != b.val; }
} mint;

int main() {


}