#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* source: idk, copied from sunho */
const int BASE_DIGITS = 18;
const ll BASE = ll(1e18);
template<typename T>
struct myvector {
    T storage;
    size_t size_;
    T* data;
    T* inner;
    myvector() : size_(0), storage(T{}), data(&storage), inner(nullptr) {}
    myvector(size_t sz) : size_(sz), storage(T{}), data(&storage), inner(nullptr) {
        if (sz > 1) {
            __init_vec(sz);
        }
    }

    myvector(const myvector& other) : size_(other.size_), storage(other.storage), inner(nullptr) {
        if (!inner) {
            data = &storage;
        }
    }

    myvector(myvector&& other) : size_(other.size_), storage(other.storage), inner(nullptr) {
        if (!inner) {
            data = &storage;
        }
    }

    myvector& operator=(const myvector& other) {
        size_ = other.size_;
        storage = other.storage;
        //inner = other.inner;
        if (!inner) {
            data = &storage;
        }
        return *this;
    }

    myvector& operator=(myvector&& other) {
        size_ = other.size_;
        storage = other.storage;
        //inner = other.inner;
        if (!inner) {
            data = &storage;
        }
        return *this;
    }

    void __init_vec(size_t sz) {
        data = new T[sz];
    }

    myvector(const T* bg, const T* ed) : size_(ed - bg), storage(T{}), data(&storage) {
        if (size_ == 0) {
            return;
        }
        if (size_ == 1) {
            storage = *bg;
            return;
        }
        assert(false);
        __init_vec(size_);
        //data = vector<T>(bg, ed);
    }
    void clear() {
        if (data) {
            //clear
        }
        size_ = 0;
    }
    void push_back(const T& x) {
        if (size_ == 0 && !inner) {
            size_++;
            storage = x;
            return;
        }
        if (!data) {
            assert(false);
            /* data.push_back(storage); */
            /* data.push_back(x); */
            /* small = 1; */
        } else {
            assert(false);
            /* data.push_back(x); */
        }
        size_++;
    }
    void pop_back() {
        if (data) {
            //data.pop_back();
        }
        size_--;
    }
    bool empty() const {
        return size_ == 0;
    }
    const T& back() const {
        return data[size_ - 1];
        //return data.back();
    }
    size_t size() const {
        return size_;
    }
    const T* begin() const {
        return &data[0];
        //return data.data();
    }
    const T* end() const {
        return &data[0] + size_;
    }
    T* begin() {
        return &data[0];
        //return data.data();
    }
    T* end() {
        return &data[0] + size_;
        //return data.data() + size_;
    }
    const T& operator[](size_t i) const {
        return data[i];
    }
    T& operator[](size_t i) {
        return data[i];
    }
    void resize(size_t sz) {
        if (sz == 0) {
            clear();
            return;
        }
        if (sz == 1 && size_ == 0 && !inner) {
            size_++;
            return;
        }
        if (sz == 1 && size_ == 1 && !inner) {
            return;
        }
        assert(false);
        size_ = sz;
        //data.resize(sz);
        /* if (small == 0 && size_ == 1 && sz > 1) { */
        /*   data[0] = storage; */
        /* } */
    }
};

struct bigint {
    myvector<ll> a;
    int sign;
    char size_sgn;

    // -------------------- Constructors -------------------- 
    // Default constructor.
    bigint() : sign(1), size_sgn(0) {}

    // Constructor from long long.
    bigint(long long v) {
        *this = v;
    }
    bigint& operator = (long long v) {
        sign = 1;
        if (v < 0) {
            sign = -1;
            v = -v;
        }
        a.clear();
        for (; v > 0; v = v / BASE)
            a.push_back(v % BASE);
        assert(a.size() <= 1);
        size_sgn = sign == 1 ? (int)a.size() : -(int)a.size();
        return *this;
    }

    long long single() const {
        return isZero() ? 0ll : sign == 1 ? a[0] : -a[0];
    }

    // Initialize from string.
    bigint(const string& s) {
        read(s);
    }

    // -------------------- Input / Output --------------------
    void read(const string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = (int)s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    friend istream& operator>>(istream& stream, bigint& v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const bigint& v) {
        if (v.sign == -1 && !v.isZero())
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int)v.a.size() - 2; i >= 0; --i)
            stream << setw(BASE_DIGITS) << setfill('0') << v.a[i];
        return stream;
    }

    // -------------------- Comparison --------------------
    bool operator<(const bigint& v) const {
        if (size_sgn != v.size_sgn) {
            return size_sgn < v.size_sgn;
        } else {
            for (int i = ((int)a.size()) - 1; i >= 0; i--)
                if (a[i] != v.a[i])
                    return sign == 1 ? a[i] < v.a[i] : a[i] > v.a[i];
            return false;
        }
    }

    bool operator>(const bigint& v) const {
        return v < *this;
    }
    bool operator<=(const bigint& v) const {
        return !(v < *this);
    }
    bool operator>=(const bigint& v) const {
        return !(*this < v);
    }
    bool operator==(const bigint& v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const bigint& v) const {
        return *this < v || v < *this;
    }

    // Returns:
    // 0 if |x| == |y|
    // -1 if |x| < |y|
    // 1 if |x| > |y|
    friend int __compare_abs(const bigint& x, const bigint& y) {
        if (x.a.size() != y.a.size()) {
            return x.a.size() < y.a.size() ? -1 : 1;
        }

        for (int i = ((int)x.a.size()) - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) {
                return x.a[i] < y.a[i] ? -1 : 1;
            }
        }
        return 0;
    }

    // -------------------- Unary operator - and operators +- --------------------
    bigint operator-() const {
        bigint res = *this;
        if (isZero()) return res;

        res.sign = -sign;
        res.size_sgn = sign == 1 ? (int)a.size() : -(int)a.size();
        return res;
    }

    // Note: sign ignored.
    void __internal_add(const bigint& v) {
        if (a.size() < v.a.size()) {
            a.resize(v.a.size());
        }
        for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry; ++i) {
            if (i == (int)a.size()) a.push_back(0);

            a[i] += carry + (i < (int)v.a.size() ? v.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
        size_sgn = sign == 1 ? (int)a.size() : -(int)a.size();
    }

    // Note: sign ignored.
    void __internal_sub(const bigint& v) {
        for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
            a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        this->trim();
    }

    bigint operator += (const bigint& v) {
        if (sign == v.sign) {
            __internal_add(v);
        } else {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                bigint vv = v;
                swap(*this, vv);
                __internal_sub(vv);
            }
        }
        return *this;
    }

    bigint operator -= (const bigint& v) {
        if (sign == v.sign) {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                bigint vv = v;
                swap(*this, vv);
                __internal_sub(vv);
                this->sign = -this->sign;
                this->size_sgn = this->sign == 1 ? (int)this->a.size() : -(int)this->a.size();
            }
        } else {
            __internal_add(v);
        }
        return *this;
    }

    // Optimize operators + and - according to
    // https://stackoverflow.com/questions/13166079/move-semantics-and-pass-by-rvalue-reference-in-overloaded-arithmetic
    template< typename L, typename R >
    typename std::enable_if<
        std::is_convertible<L, bigint>::value&&
        std::is_convertible<R, bigint>::value&&
        std::is_lvalue_reference<R&&>::value,
        bigint>::type friend operator + (L&& l, R&& r) {
        bigint result(std::forward<L>(l));
        result += r;
        return result;
    }
    template< typename L, typename R >
    typename std::enable_if<
        std::is_convertible<L, bigint>::value&&
        std::is_convertible<R, bigint>::value&&
        std::is_rvalue_reference<R&&>::value,
        bigint>::type friend operator + (L&& l, R&& r) {
        bigint result(std::move(r));
        result += l;
        return result;
    }

    template< typename L, typename R >
    typename std::enable_if<
        std::is_convertible<L, bigint>::value&&
        std::is_convertible<R, bigint>::value,
        bigint>::type friend operator - (L&& l, R&& r) {
        bigint result(std::forward<L>(l));
        result -= r;
        return result;
    }

    // -------------------- Operators * / % --------------------
    friend pair<bigint, bigint> divmod(const bigint& a1, const bigint& b1) {
        assert(b1 > 0);  // divmod not well-defined for b < 0.

        long long norm = BASE / (b1.a.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q = 0, r = 0;
        q.a.resize(a.a.size());

        for (int i = (int)a.a.size() - 1; i >= 0; i--) {
            r *= BASE;
            r += a.a[i];
            long long s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            long long s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            long long d = ((long long)BASE * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0) {
                r += b, --d;
            }
            q.a[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        auto res = make_pair(q, r / norm);
        if (res.second < 0) res.second += b1;
        return res;
    }
    bigint operator/(const bigint& v) const {
        if (v < 0) return divmod(-*this, -v).first;
        return divmod(*this, v).first;
    }

    bigint operator%(const bigint& v) const {
        return divmod(*this, v).second;
    }

    void operator/=(long long v) {
        assert(v > 0);  // operator / not well-defined for v <= 0.
        if (llabs(v) >= BASE) {
            *this /= bigint(v);
            return;
        }
        if (v < 0)
            sign = -sign, v = -v;
        ll rem = 0;
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            __int128_t cur = a[i] + rem * (__int128_t)BASE;
            a[i] = (ll)(cur / v);
            rem = (ll)(cur % v);
        }
        trim();
    }

    bigint operator/(long long v) const {
        assert(v > 0);  // operator / not well-defined for v <= 0.

        if (llabs(v) >= BASE) {
            return *this / bigint(v);
        }
        bigint res = *this;
        res /= v;
        return res;
    }
    void operator/=(const bigint& v) {
        *this = *this / v;
    }

    long long operator%(long long v) const {
        assert(v > 0);  // operator / not well-defined for v <= 0.
        assert(v < BASE);
        ll m = 0;
        for (int i = (int)a.size() - 1; i >= 0; --i)
            m = (a[i] + m * (__int128_t)BASE) % v;
        return m * sign;
    }

    void operator*=(long long v) {
        if (llabs(v) >= BASE) {
            *this *= bigint(v);
            return;
        }
        if (v < 0)
            sign = -sign, v = -v;
        ll carry = 0;
        for (int i = 0; i < (int)a.size() || carry; ++i) {
            if (i == (int)a.size())
                a.push_back(0);
            __int128_t cur = a[i] * (__int128_t)v + carry;
            carry = (ll)(cur / BASE);
            a[i] = (ll)(cur % BASE);
            //asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
            /*
             int val;
             __asm {
             lea esi, cur
             mov eax, [esi]
             mov edx, [esi+4]
             mov ecx, base
             div ecx
             mov carry, eax
             mov val, edx;
             }
             a[i] = val;
             */
        }
        trim();
    }

    bigint operator*(long long v) const {
        if (llabs(v) >= BASE) {
            return *this * bigint(v);
        }
        bigint res = *this;
        res *= v;
        return res;
    }

    // Convert BASE 10^old --> 10^new.
    static myvector<ll> convert_base(const myvector<ll>& a, int old_digits, int new_digits) {
        myvector<long long> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int)p.size(); i++)
            p[i] = p[i - 1] * 10;
        myvector<ll> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back((int)(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int)cur);
        while (!res.empty() && !res.back())
            res.pop_back();
        return res;
    }

    bigint mul_simple(const bigint& v) const {
        bigint res;
        res.sign = sign * v.sign;
        res.a.resize(a.size() + v.a.size());
        for (int i = 0; i < (int)a.size(); ++i)
            if (a[i]) {
                ll carry = 0;
                for (int j = 0; j < (int)v.a.size() || carry; ++j) {
                    __int128_t cur = res.a[i + j] + (__int128_t)a[i] * (j < (int)v.a.size() ? v.a[j] : 0) + carry;
                    carry = (ll)(cur / BASE);
                    res.a[i + j] = (ll)(cur % BASE);
                }
            }
        res.trim();
        return res;
    }

    typedef myvector<long long> vll;

    static vll karatsubaMultiply(const vll& a, const vll& b) {
        int n = (int)a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }

        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());

        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);

        for (int i = 0; i < k; i++)
            a2[i] += a1[i];
        for (int i = 0; i < k; i++)
            b2[i] += b1[i];

        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int)a1b1.size(); i++)
            r[i] -= a1b1[i];
        for (int i = 0; i < (int)a2b2.size(); i++)
            r[i] -= a2b2[i];

        for (int i = 0; i < (int)r.size(); i++)
            res[i + k] += r[i];
        for (int i = 0; i < (int)a1b1.size(); i++)
            res[i] += a1b1[i];
        for (int i = 0; i < (int)a2b2.size(); i++)
            res[i + n] += a2b2[i];
        return res;
    }

    bigint mul_karatsuba(const bigint& v) const {
        myvector<ll> x6 = convert_base(this->a, BASE_DIGITS, 6);
        myvector<ll> y6 = convert_base(v.a, BASE_DIGITS, 6);
        vll x(x6.begin(), x6.end());
        vll y(y6.begin(), y6.end());
        while (x.size() < y.size())
            x.push_back(0);
        while (y.size() < x.size())
            y.push_back(0);
        while (x.size() & (x.size() - 1))
            x.push_back(0), y.push_back(0);
        vll c = karatsubaMultiply(x, y);
        bigint res;
        res.sign = sign * v.sign;
        long long carry = 0;
        for (int i = 0; i < (int)c.size(); i++) {
            long long cur = c[i] + carry;
            res.a.push_back((int)(cur % 1000000));
            carry = cur / 1000000;
        }
        res.a = convert_base(res.a, 6, BASE_DIGITS);
        res.trim();
        return res;
    }

    void operator*=(const bigint& v) {
        *this = *this * v;
    }
    bigint operator*(const bigint& v) const {
        if (a.size() * v.a.size() <= 1000111) return mul_simple(v);
        return mul_karatsuba(v);
    }

    // -------------------- Misc --------------------
    bigint abs() const {
        bigint res = *this;
        res.sign = 1;
        res.size_sgn = (int)res.a.size();
        return res;
    }
    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
        size_sgn = sign == 1 ? (int)a.size() : -(int)a.size();
    }

    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }

    friend bigint gcd(const bigint& x, const bigint& y) {
        return y.isZero() ? x : gcd(y, x % y);
    }
    friend bigint lcm(const bigint& x, const bigint& y) {
        return x / gcd(x, y) * y;
    }
};
