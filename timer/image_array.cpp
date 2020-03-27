#include "image_array.h"



Image_Array::~Image_Array( void )
{
    if( red )
    {
        if( green == red )
        {
            green = nullptr;
        }
        if( blue == red )
        {
            blue = nullptr;
        }
        if( alpha == red )
        {
            alpha = nullptr;
        }
        delete[] red;
        red = nullptr;
    }
    if( green )
    {
        if( red == green )
        {
            red = nullptr;
        }
        if( blue == green )
        {
            blue = nullptr;
        }
        if( alpha == green )
        {
            alpha = nullptr;
        }
        delete[] green;
        green = nullptr;
    }
    if( blue )
    {
        if( red == blue )
        {
            red = nullptr;
        }
        if( green == blue )
        {
            green = nullptr;
        }
        if( alpha == blue )
        {
            alpha = nullptr;
        }
        delete[] blue;
        blue = nullptr;
    }
    if( alpha )
    {
        if( red == alpha )
        {
            red = nullptr;
        }
        if( blue == alpha )
        {
            blue = nullptr;
        }
        if( green == alpha )
        {
            green = nullptr;
        }
        delete[] alpha;
        alpha = nullptr;
    }
}

