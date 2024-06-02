// put after #include<bits/stdc++.h>, using namespace std
// based off of tatyam's template: https://codeforces.com/profile/tatyam
void _print() { putchar(' '); }
void _print(bool a) { printf("%d", a); }
void _print(int a) { printf("%d", a); }
void _print(unsigned a) { printf("%u", a); }
void _print(long a) { printf("%ld", a); }
void _print(long long a) { printf("%lld", a); }
void _print(unsigned long long a) { printf("%llu", a); }
void _print(char a) { printf("%c", a); }
void _print(char a[]) { printf("%s", a); }
void _print(const char a[]) { printf("%s", a); }
void _print(float a) { printf("%.15f", a); }
void _print(double a) { printf("%.15f", a); }
void _print(long double a) { printf("%.15Lf", a); }
void _print(const string& a) { for (auto&& i : a) _print(i); }
template<class...Ts> void _print(const tuple<Ts...>& tup) {
    apply(
        [](auto& head, auto&... args) {
        ((_print(head), _print(", "), _print(args)), ...);
    }, tup);
}
template<class T> void _print(const complex<T>& a) {
    if (a.real() >= 0) _print('+'); _print(a.real());
    if (a.imag() >= 0) _print('+'); _print(a.imag()); _print('i');
}
template<class T> void _print(const vector<T>&);
template<class T, size_t size> void _print(const array<T, size>&);
template<class T, class L> void _print(const pair<T, L>& p);
template<class T, size_t size> void _print(const T(&)[size]);
template<class T> void _print(const vector<T>& a) { if (a.empty()) return; _print(a[0]); for (auto i = a.begin(); ++i != a.end(); ) { printf(", "); _print(*i); } }
template<class T> void _print(const deque<T>& a) { if (a.empty()) return; _print(a[0]); for (auto i = a.begin(); ++i != a.end(); ) { printf(", "); _print(*i); } }
template<class T, size_t size> void _print(const array<T, size>& a) { _print(a[0]); for (auto i = a.begin(); ++i != a.end(); ) { printf(", "); _print(*i); } }
template<class T, class L> void _print(const pair<T, L>& p) { _print(p.first); printf(", "); _print(p.second); }
template<class T, size_t size> void _print(const T(&a)[size]) { _print(a[0]); for (auto i = a; ++i != end(a); ) { printf(", "); _print(*i); } }
template<class T> void _print(const T& a) { cout << a; }
void out() {}
template<class T> void out(const T& t) { _print(t); }
template<class Head, class... Tail> void out(const Head& head, const Tail&... tail) { _print(head); printf("}, {"); out(tail...); }

#define dbg(...) _print("[{"), out(__VA_ARGS__), cout << "}](" << #__VA_ARGS__ << ")[" << __LINE__ << "]" << endl;
#define ass(condition, message)\
   (!(condition)) ?\
      (std::cerr << "Assertion failed: (" << #condition << "), "\
      << "function " << __FUNCTION__\
      << ", file " << __FILE__\
      << ", line " << __LINE__ << "."\
      << std::endl << message << std::endl, abort(), 0) : 1
#define ass(condition) assert(condition)
