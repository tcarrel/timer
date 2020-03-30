#pragma once



#include<type_traits>



template<typename T>
inline void increment_digit( T& d )
{
    static_assert( std::is_arithmetic<T>::value, "Must be arithmetic type." );

    if( d >= static_cast<T>( 9 ) )
    {
        d = static_cast<T>( 0 );
        return;
    }

    ++d;
}



template<typename T>
inline void increment_tens_of_minutes( T& d )
{
    static_assert( std::is_arithmetic<T>::value, "Must be arithmetic type." );

    if( d >= static_cast<T>( 5 ) )
    {
        d = static_cast<T>( 0 );
        return;
    }

    ++d;
}



template<typename T>
inline void decrement_digit( T& d )
{
    static_assert( std::is_arithmetic<T>::value, "Must be arithmetic type." );

    if( d == static_cast<T>( 0 ) )
    {
        d = static_cast<T>( 9 );
        return;
    }

    --d;
}



template<typename T>
inline void decrement_tens_of_minutes( T& d )
{
    static_assert( std::is_arithmetic<T>::value, "Must be arithmetic type." );

    if( d == static_cast<T>( 0 ) )
    {
        d = static_cast<T>( 5 );
        return;
    }

    --d;
}
