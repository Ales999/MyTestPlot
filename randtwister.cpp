#include "randtwister.h"
#include <QTime>

// Need for linker static member
// https://msdn.microsoft.com/en-us/library/b1b5y48f.aspx
uint32_t RandTwister::mt[];
uint16_t  RandTwister::index;

// Constructor
RandTwister::RandTwister(void)
{
    QTime midnight(0,0,0); qsrand( midnight.secsTo(QTime::currentTime()) );
    uint32_t qseed = this->randf(1,8,0); // pick_a_number(1,101);
    //uint32_t sta1[1] = { qseed };
    //auto _aftershift = xorshift32( sta1 );

    //QTime midnight(0,0,0); qsrand( midnight.secsTo(QTime::currentTime()) );
    //qseed = qrand();
    //qseed = ( qseed / (double)(RAND_MAX/100-0.5) ) * 10;

    Initialize( qseed );
}
// Constructor
RandTwister::RandTwister(const uint32_t seed)
{
    QTime midnight(0,0,0); qsrand( midnight.secsTo(QTime::currentTime()) );
    this->Initialize(seed);
}

#ifndef RAND_TW_LMAX
#define RAND_TW_LMAX 1000000000
#endif
#ifndef RAND_TW_LMIN
#define RAND_TW_LMIN 100000000
#endif


//
double RandTwister::GetRandVolume()
{
    double _ret = 0.0;
    ptrdiff_t _tmp = 0; // long

    _tmp = this->ExtractU32();

    while (_tmp < RAND_TW_LMIN )
    {
        _tmp = _tmp * 3.1415926;
    }

    while(_tmp > RAND_TW_LMAX )
    {
        _tmp = _tmp >> 1;
    }

    int r1 = this->randf(1,4,0);
    int r2 = this->randf(1,5,0);
    int r3 = this->randf(1,7,0);
    int sign = this->randf(1,1,1);

    _ret = (double)_tmp/100000000000.0;

    if ( r1 == 5)   { _ret *=5; qDebug("X_2"); }
    if ( r2 == 15)  { _ret *=10; qDebug("X_3"); }
    if ( r3 == 40)  { _ret *=100; qDebug("X_6"); }

    qDebug("%.8f\t, r1=%d, r2=%d, r3=%d, sign=%d",_ret, r1, r2, r3, sign);
    return _ret;
}

// Re-init with a given seed
void RandTwister::ReInitialize()
{
    _seed = this->randf(1,8,0);
    Initialize( _seed );
}

// Private initialise
void RandTwister::Initialize(const uint32_t seed)
{
    assert(seed != 0);

    uint32_t  i;
    this->_seed = seed;

    mt[0] = this->_seed;

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

/* The state word must be initialized to non-zero */
uint32_t RandTwister::xorshift32(uint32_t state[1])
{
        uint32_t x = state[0];
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        state[0] = x;
        return x;
}

/* The state array must be initialized to not be all zero */
uint32_t RandTwister::xorshift128(uint32_t state[4])
{
        uint32_t t = state[3];
        t ^= t << 11;
        t ^= t >> 8;
        state[3] = state[2]; state[2] = state[1]; state[1] = state[0];
        t ^= state[0];
        t ^= state[0] >> 19;
        state[0] = t;
        return t;
}

/**
 * Function generates a random float using the upper_bound float to determine
 * the upper bound for the exponent and for the fractional part.
 * @param min_exp sets the minimum number (closest to 0) to 1 * e^min_exp (min -127)
 * @param max_exp sets the maximum number to 2 * e^max_exp (max 126)
 * @param sign_flag if sign_flag = 0 the random number is always positive, if
 *              sign_flag = 1 then the sign bit is random as well
 * @return a random float
 * Using this function randf(0, 8, 0) will return a random number between 0.0 and 255.0
 */
float RandTwister::randf(int min_exp, int max_exp, char sign_flag) {
    assert(min_exp <= max_exp);

    int min_exp_mod = min_exp + 126;

    int sign_mod = sign_flag + 1;
    int frac_mod = (1 << 23);

    int s = qrand() % sign_mod;  // note x % 1 = 0
    int e = (qrand() % max_exp) + min_exp_mod;
    int f = qrand() % frac_mod;

    int tmp = (s << 31) | (e << 23) | f;

    float r = (float)*((float*)(&tmp));

    /** uncomment if you want to see the structure of the float. */
//    printf("%x, %x, %x, %x, %f\n", (s << 31), (e << 23), f, tmp, r);

    return r;
}


/*
// Random Number Generation in C++17
std::default_random_engine & RandTwister::global_urng( )
{
 static std::default_random_engine u{};
 return u;
}

int RandTwister::pick_a_number( int from, int thru )
{
 static std::uniform_int_distribution<> d{};
 using parm_t = decltype(d)::param_type;
 return d( global_urng(), parm_t{from, thru} );
}

double RandTwister::pick_a_number( double from, double upto )
{
 static std::uniform_real_distribution<> d{};
 using parm_t = decltype(d)::param_type;
 return d( global_urng(), parm_t{from, upto} );
}
// End Random Generation in C++
*/

