#include "randtwister.h"
#include <QTime>

// Need for linker static member
// https://msdn.microsoft.com/en-us/library/b1b5y48f.aspx
uint32_t RandTwister::mt[];
uint16_t  RandTwister::index;

RandTwister::RandTwister()
{
    uint32_t seed;
    QTime midnight(0,0,0);
    seed =  midnight.secsTo(QTime::currentTime());
    // seed = 111;
    Initialize(seed);
}

// Re-init with a given seed
void RandTwister::Initialize(const uint32_t seed)
{
    uint32_t  i;

    mt[0] = seed;

    for ( i = 1; i < N; i++ )
    {
        mt[i] = (F * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
    }

    index = N;
}

void RandTwister::Twist()
{
    uint32_t  i, x, xA;

    for ( i = 0; i < N; i++ )
    {
        x = (mt[i] & MASK_UPPER) + (mt[(i + 1) % N] & MASK_LOWER);

        xA = x >> 1;

        if ( x & 0x1 )
            xA ^= A;

       mt[i] = mt[(i + M) % N] ^ xA;
    }

    index = 0;
}

// Obtain a 32-bit random number
uint32_t RandTwister::ExtractU32()
{
    uint32_t  y;
    int       i = index;

    if ( index >= N )
    {
        Twist();
        i = index;
    }

    y = mt[i];
    index = i + 1;

    y ^= (mt[i] >> U);
    y ^= (y << S) & B;
    y ^= (y << T) & C;
    y ^= (y >> L);

    return y;
}
