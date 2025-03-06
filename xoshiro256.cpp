#pragma once
#include <chrono>
#include <cstdint>
#include <cmath>

constexpr static uint64_t splitmix64(uint64_t x) { // https://doi.org/10.1145/2714064.2660195
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

/*
    xoshiro256++ https://prng.di.unimi.it/xoshiro256plusplus.c
    States initialized using splitmix as suggested
*/
struct xoshiro256 {
    uint64_t state[4]; // 256 bits state
    static inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }
    xoshiro256() {
        uint64_t x = std::chrono::steady_clock::now().time_since_epoch().count();
        for (int i = 0; i < 4; i++) {
            x = splitmix64(x);
            state[i] = x;
        }
    }
    /*
        generates a random number between [0, u64 max]
    */
    uint64_t random64() {
        const uint64_t result = rotl(state[0] + state[3], 23) + state[0];
        const uint64_t t = state[1] << 17;
        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];
        state[2] ^= t;
        state[3] = rotl(state[3], 45);
        return result;
    }
    /*
        get unbiased random number in range [0, high) from uniformly random 2^n
        Fast Random Integer Generation in an Interval (Lemire, 2018) https://arxiv.org/abs/1805.10941
    */
    uint64_t nextInt(uint64_t high) {
        uint64_t x = random64();
        __uint128_t m = (__uint128_t)x * (__uint128_t)high;
        uint64_t l = (uint64_t)m;
        if (l < high) {
            uint64_t t = -high % high;
            while (l < t) {
                x = random64();
                m = (__uint128_t)x * (__uint128_t)high;
                l = (uint64_t)m;
            }
        }
        return uint64_t(m >> 64);
    }
    /*
        uniform int distribution
        get a random number in the range [low, high]
    */
    uint64_t nextInt(uint64_t low, uint64_t high) {
        uint64_t range = high - low + 1;
        return nextInt(range) + low;
    }
};


#include <iostream>
int main() {
    xoshiro256 rng{};
    int cnt[6] = {};
    for (int i = 0; i < int(1e6); i++) {
        cnt[rng.nextInt(0, 5)]++;
    }

    for (int i = 0; i < 6; i++) {
        std::cout << cnt[i] << "\n";
    }
}
