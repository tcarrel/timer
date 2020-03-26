#include "timer.h"



Timer::Timer( Timer& t )
    :
    Timer( t.minutes_, t.seconds_ )
{}



Timer::Timer( Uint8 min, Uint8 sec, Uint32 ms )
    :
    minutes_( min ),
    seconds_( sec ),
    milliseconds_( ms )
{
    if( minutes_ > 99 )
    {
        minutes_ = 99;
    }

    if( seconds_ > 99 )
    {
        seconds_ = 99;
    }
}

Timer& Timer::operator=( Timer& t )
{
    minutes_ = t.minutes_;
    seconds_ = t.seconds_;
    milliseconds_ = t.milliseconds_;

    return *this;
}



void Timer::minutes_up_one( void )
{
    ++minutes_;
    if( ( minutes_ % 10 ) == 0 )
    {
        minutes_ -= 10;
    }
    ms_reset();
}



void Timer::minutes_down_one( void )
{
    if( (minutes_ % 10) == 0 )
    {
        minutes_ += 10;
    }
    --minutes_;
    ms_reset();
}



void Timer::seconds_up_one( void )
{
    ++seconds_;
    if( ( seconds_ % 10 ) == 0 )
    {
        seconds_ -= 10;
    }
    ms_reset();
}



void Timer::seconds_down_one( void )
{
    if( ( seconds_ % 10 ) == 0 )
    {
        seconds_ += 10;
    }
    --seconds_;
    ms_reset();
}

void Timer::minutes_up_ten( void )
{
    if( minutes_ > 89 )
    {
        minutes_ %= 10;
    }
    else
    {
        minutes_ += 10;
    }
    ms_reset();
}

void Timer::minutes_down_ten( void )
{
    if( minutes_ < 10 )
    {
        minutes_ += 90;
    }
    else
    {
        minutes_ -= 10;
    }
    ms_reset();
}

void Timer::seconds_up_ten( void )
{
    if( seconds_ > 89 )
    {
        seconds_ %= 10;
    }
    else
    {
        seconds_ += 10;
    }
    ms_reset();
}

void Timer::seconds_down_ten( void )
{
    if( seconds_ < 10 )
    {
        seconds_ += 90;
    }
    else
    {
        seconds_ -= 10;
    }
    ms_reset();
}



int Timer::minutes_tens_place( void )
{
    return minutes_ / 10;
}

int Timer::minutes_ones_place( void )
{
    return minutes_ % 10;
}

int Timer::seconds_tens_place( void )
{
    return seconds_ / 10;
}

int Timer::seconds_ones_place( void )
{
    return seconds_ % 10;
}

int Timer::ms_remain( void )
{
    return
          ( static_cast<int>( minutes_ ) * 60 * 1000 )
        + ( static_cast<int>( seconds_ ) * 1000 )
        +  static_cast<int>( milliseconds_ );
}



void Timer::start( void )
{
    previous_tick = SDL_GetTicks();
}



void Timer::update( void )
{
    if( done() )
    {
        // noise
        return;
    }

    auto now = SDL_GetTicks();
    auto elapsed = now - previous_tick;

    decrement_by_ms( elapsed );

    previous_tick = now;
}



void Timer::set_to( Uint8 m, Uint8 s, Uint32 ms )
{
    minutes_ = m;
    seconds_ = s;
    milliseconds_ = ms;
}



bool Timer::done( void )
{
    return minutes_ == 0 && seconds_ == 0 && milliseconds_ == 0;
}

Uint32 Timer::current_m( void )
{
    return static_cast<Uint32>( minutes_ );
}

Uint32 Timer::current_s( void )
{
    return static_cast<Uint32>( seconds_ );
}

Uint32 Timer::current_ms( void )
{
    return milliseconds_;
}



void Timer::decrement_by_ms( Uint32 t )
{
    if( milliseconds_ == 0 )
    {
        milliseconds_ = 999;
        decrement_one_second();
    }

    while( t > 1000 )
    {
        decrement_one_second();
        t -= 1000;
    }

    if( t > milliseconds_ )
    {
        decrement_one_second();
        t -= milliseconds_;
        milliseconds_ = 999;
    }

    milliseconds_ -= t;
}



void Timer::decrement_one_second( void )
{
    if( seconds_ == 0 )
    {
        if( minutes_ == 0 )
        {
            return;
        }

        seconds_ = 59;
        --minutes_;
        return;
    }

    --seconds_;
}



void Timer::ms_reset( void )
{
    milliseconds_ = 999;
}
