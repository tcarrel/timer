#pragma once



#include<SDL.h>



class Timer
{
    Uint8 minutes_{ 0 };
    Uint8 seconds_{ 0 };

    Uint32 milliseconds_{ 999 };

    Uint32 previous_tick{ 0 };


    void decrement_by_ms( Uint32 t );
    void decrement_one_second( void );

    void ms_reset( void );

public:
    Timer( Timer& t );
    Timer( Uint8 min, Uint8 sec, Uint32 ms = 999 );
    Timer& operator=( Timer& t );

    void minutes_up_one( void );
    void minutes_down_one( void );
    void seconds_up_one( void );
    void seconds_down_one( void );
    void minutes_up_ten( void );
    void minutes_down_ten( void );
    void seconds_up_ten( void );
    void seconds_down_ten( void );

    int minutes_tens_place( void );
    int minutes_ones_place( void );
    int seconds_tens_place( void );
    int seconds_ones_place( void );

    int ms_remain( void );

    void start( void );
    void update( void );

    void set_to( Uint8 m, Uint8 s, Uint32 ms = 999 );
    bool done( void );

    Uint32 current_m( void );
    Uint32 current_s( void );
    Uint32 current_ms( void );
};

