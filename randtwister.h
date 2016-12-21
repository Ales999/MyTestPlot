#ifndef RANDTWISTER_H
#define RANDTWISTER_H

// Mersenne Twister
// https://en.wikipedia.org/wiki/Mersenne_Twister

#include <stdint.h>


class RandTwister
{
public:
    RandTwister();

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

    void Initialize(const uint32_t  seed);
    static void Twist();
    uint32_t ExtractU32();
//




};

#endif // RANDTWISTER_H