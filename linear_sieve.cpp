#include <bits/stdc++.h>
using namespace std;

/**
 * linear sieve:
 * source: https://github.com/mzhang2021/cp-library/blob/master/implementations/math/LinearSieve.h
*/
const int MAX = int(4e6);
bitset<MAX> is_prime;
vector<int> primes;
void sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i < MAX; i++) {
        if (is_prime[i]) primes.push_back(i);
        for (int j = 0; j < (int)primes.size() && primes[j] <= (MAX - 1) / i; j++) {
            is_prime[i * primes[j]] = 0;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    /* 31ms g++20 custom invocation */
    sieve();
}