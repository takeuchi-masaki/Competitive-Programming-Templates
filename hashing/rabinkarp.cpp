#include <bits/stdc++.h>
using namespace std;

constexpr uint64_t MOD = (1LL << 61) - 1;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uint64_t base = uniform_int_distribution<uint64_t>(331, uint64_t(1e18))(rng) | 1;
struct mint {
    uint64_t val;
    mint() : val(0) {}
    mint(int64_t v) : val((v + MOD) % MOD) {}
    mint(int64_t a, int64_t b) : mint(a) { *this /= mint(b); } // a * b^-1
    mint& operator+=(mint const& b) { val += b.val; if (val >= MOD) val -= MOD; return *this; }
    mint& operator-=(mint const& b) { val += MOD - b.val; if (val >= MOD) val -= MOD; return *this; }
    mint& operator*=(mint const& b) { // kactl modmul
        int64_t res = this->val * b.val - MOD * uint64_t(1.L / MOD * this->val * b.val);
        val = res + MOD * (res < 0) - MOD * (res >= (int64_t)MOD); return *this;
    }
    friend mint mexp(mint b, int64_t e) { mint res(1); for (; e; b *= b, e /= 2) if (e & 1) res *= b; return res; }
    friend mint inverse(mint a) { return mexp(a, MOD - 2); } // assumes a, MOD coprime
    mint& operator/=(mint const& b) { return *this *= inverse(b); }
    friend mint operator+(mint a, mint const b) { return a += b; }
    friend mint operator-(mint a, mint const b) { return a -= b; }
    friend mint operator-(mint const a) { return MOD - a; }
    friend mint operator*(mint a, mint const b) { return a *= b; }
    friend mint operator/(mint a, mint const b) { return a /= b; }
    friend istream& operator>>(istream& is, mint& a) { int64_t in; is >> in; a = mint(in); return is; }
    friend ostream& operator<<(ostream& os, mint const& a) { return os << a.val; }
    friend bool operator==(mint const& a, mint const& b) { return a.val == b.val; }
    friend bool operator!=(mint const& a, mint const& b) { return a.val != b.val; }
};

mint maxpow;
mint compute_hash(const string& s, int length) {
    maxpow = mexp(mint(base), length);
    mint hash{};
    for (int i = 0; i < length; i++) {
        hash = hash * base + s[i];
    }
    return hash;
}

mint roll_hash(mint hash, int nxtidx, const string& s, int length) {
    return (hash * base + s[nxtidx]) - (maxpow * s[nxtidx - length]);
}



int main() {
    // string s, t;
    // cin >> s >> t;
    string s = "abbabb", t = "abb";

    mint pattern_hash = compute_hash(t, int(t.size()));
    mint hash = compute_hash(s, int(t.size()));
    int duplicate_substring_cnt = (pattern_hash == hash);
    for (int i = int(t.size()); i < int(s.size()); i++) {
        hash = roll_hash(hash, i, s, int(t.size()));
        duplicate_substring_cnt += (pattern_hash == hash);
    }
    cout << "duplicate substring count: " << duplicate_substring_cnt << "\n";
}
