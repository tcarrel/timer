#include "color.h"



Color::Color() : Color( 0, 0, 0 )
{}



Color::Color( Uint8 red, Uint8 gre, Uint8 blu )
    :
    r(red),
    g(gre),
    b(blu)
{}



void Color::set_draw( SDL_Renderer* rend, Uint8 alp )
{
    SDL_SetRenderDrawColor( rend, r, g, b, alp );
}
