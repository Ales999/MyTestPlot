#ifndef RANDTWISTER_H
#define RANDTWISTER_H

#include <algorithm>
#include <array>
#include <iostream>     // std::cout
#include <numeric>      // std::iota
#include <random>
#include <cassert>

// Mersenne Twister
// https://en.wikipedia.org/wiki/Mersenne_Twister

#include <stdint.h>


class RandTwister
{
public:
    RandTwister(void);
    RandTwister(const uint32_t seed);
    double GetRandVolume();

    enum
    {
        // Assumes W = 32 (omitting this)
        N = 624,
        M = 397,
        R = 31,
        A = 0x9908B0DF,

        F = 1812433253,

        U = 11,
        // Assumes D = 0xFFFFFFFF (omitting this)

        S = 7,
        B = 0x9D2C5680,

        T = 15,
        C = 0xEFC60000,

        L = 18,

        MASK_LOWER = (1ull << R) - 1,
        MASK_UPPER = (1ull << R)
    };

    static uint32_t  mt[N];
    static uint16_t  index;

    void ReInitialize();
    static void Twist();
    uint32_t ExtractU32();
    // sign_flag: 0 - always positive, 1 -> random bit
    float randf(int min_exp, int max_exp, char sign_flag);
    //int pick_a_number( int from, int thru );
    //double pick_a_number( double from, double upto );
//

private:
    uint32_t _seed;
    void Initialize(const uint32_t  seed);
    uint32_t xorshift32(uint32_t state[1]);
    uint32_t xorshift128(uint32_t state[4]);
    //
    std::default_random_engine & global_urng( );
    void randomize( );


};

#endif // RANDTWISTER_H
