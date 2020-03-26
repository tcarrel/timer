#pragma once


#include<SDL.h>



struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;

    Color();
    Color( Uint8 red, Uint8 gre, Uint8 blu );

    void set_draw( SDL_Renderer* rend, Uint8 = 255 );
};

