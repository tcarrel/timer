#include "timer.h"



Timer::Timer( Timer& t )
    :
    Timer( t.total_ms_ )
{}



Timer::Timer( Uint8 min, Uint8 sec, Uint32 ms )
{
    set( min, sec, ms );
}



Timer::Timer( Uint32 ms_total )
    :
    total_ms_( ms_total )
{}



Timer& Timer::operator=( Timer& t )
{
    total_ms_ = t.total_ms_;

    return *this;
}



Uint32 Timer::minutes_tens_place( void )
{
    return minutes() / 10;
}

Uint32 Timer::minutes_ones_place( void )
{
    return minutes() % 10;
}

Uint32 Timer::seconds_tens_place( void )
{
    return seconds() / 10;
}

Uint32 Timer::seconds_ones_place( void )
{
    return seconds() % 10;
}



Uint32 Timer::get_digit( int place )
{
    switch( place )
    {
    case Place_MINUTES_10s:
        return minutes_tens_place();
    case Place_MINUTES_1s:
        return minutes_ones_place();
    case Place_SECONDS_10s:
        return seconds_tens_place();
    case Place_SECONDS_1s:
        return seconds_ones_place();
    default:
        return 0xffff'ffff;
    }
}



void Timer::start( void )
{
    previous_tick = SDL_GetTicks();
}



void Timer::update( void )
{
    if( done() )
    {
        return;
    }

    auto now = SDL_GetTicks();
    auto elapsed = now - previous_tick;

    decrement_by_ms( elapsed );

    previous_tick = now;
}



void Timer::set( Uint32 m10, Uint32 m1, Uint32 s10, Uint32 s1, Uint32 ms )
{
    set( static_cast<Uint8>( ( m10 * 10 ) + m1 ), static_cast<Uint8>( ( s10 * 10 ) + s1 ), ms );
}



void Timer::set( Uint8 m, Uint8 s, Uint32 ms )
{
    total_ms_ = ( static_cast<Uint32>( m ) * 60000 ) + ( static_cast<Uint32>( s ) * 1000 ) + ms;
}



bool Timer::done( void )
{
    return total_ms_ == 0;
}

Uint32 Timer::minutes( void )
{
    return total_ms_ / 60000;
}

Uint32 Timer::seconds( void )
{
    return ( total_ms_ / 1000 ) % 60;
}

Uint32 Timer::milliseconds_in_second( void )
{
    return total_ms_ % 1000;
}

Uint32 Timer::milliseconds( void )
{
    return total_ms_;
}



void Timer::decrement_by_ms( Uint32 t )
{
    if( total_ms_ == 0 )
    {
        return;
    }


    if( t >= total_ms_ )
    {
        total_ms_ = 0;
        return;
    }

    total_ms_ -= t;
}
