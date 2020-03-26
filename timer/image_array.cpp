#include "image_array.h"



Image_Array::~Image_Array( void )
{
    if( red )
    {
        delete[] red;
        red = nullptr;
    }
    if( green )
    {
        delete[] green;
        green = nullptr;
    }
    if( blue )
    {
        delete[] blue;
        blue = nullptr;
    }
    if( alpha )
    {
        delete[] alpha;
        alpha = nullptr;
    }
}

