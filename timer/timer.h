#pragma once



#include<SDL.h>



enum Place
{
    Place_MINUTES_10s,
    Place_MINUTES_1s,
    Place_SECONDS_10s,
    Place_SECONDS_1s,

    Place_COUNT
};



class Timer
{

    Uint32 total_ms_{ 999 };
    Uint32 previous_tick{ 0 };

    void decrement_by_ms( Uint32 t );

public:

    Timer( Timer& t );
    Timer( Uint8 min, Uint8 sec, Uint32 ms = 999 );
    Timer( Uint32 ms_total );
    Timer& operator=( Timer& t );

    Uint32 minutes_tens_place( void );
    Uint32 minutes_ones_place( void );
    Uint32 seconds_tens_place( void );
    Uint32 seconds_ones_place( void );

    Uint32 get_digit( int place );

    void start( void );
    void update( void );

    void setting_timer( Uint32 m10, Uint32 m1, Uint32 s10, Uint32 s1, Uint32 ms = 0 );
    void setting_timer( Uint8 m, Uint8 s, Uint32 ms = 0 );
    bool done( void );

    Uint32 minutes( void );
    Uint32 seconds( void );
    Uint32 milliseconds_in_second( void );
    Uint32 milliseconds( void );
};

