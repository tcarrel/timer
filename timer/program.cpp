


#ifdef _DEBUG
# include<iostream>
#endif

#include<cstdio>



#include "global_constants.h"
#include "program.h"
#include "color.h"



void Program::poll_events( void )
{
    key.reset();

    while( SDL_PollEvent( &event_handler_ ) )
    {
        switch( event_handler_.type )
        {
        case SDL_QUIT:
            quit_ = true;
            continue;
        case SDL_WINDOWEVENT:
            react_to_window_event( event_handler_.window.event );
            continue;
        case SDL_KEYUP:
            update_key_states( event_handler_.key );
            continue;
        default:
            continue;
        }
    }
}



void Program::react_to_window_event( Uint8 e )
{
    if( frame_first )
    {
        switch( e )
        {
        default:

        case SDL_WINDOWEVENT_RESIZED:
            update_window_size();
            break;
        }
        frame_first = false;
    }
}

void Program::update_key_states( SDL_KeyboardEvent keyvent )
{
    if( keyvent.windowID == SDL_GetWindowID( window_ ) )
    {
        switch( keyvent.keysym.sym )
        {
        case SDLK_ESCAPE:
            key.esc = true;
            return;
        case SDLK_DOWN:
            key.down = true;
            return;
        case SDLK_KP_ENTER: //fall through.
        case SDLK_RETURN:
            if( keyvent.keysym.mod != KMOD_ALT )
            {
                return;
            }
            // fall through.
        case SDLK_F11:
            key.f11 = true;
            return;
        case SDLK_LEFT:
            key.left = true;
            return;
        case SDLK_RIGHT:
            key.right = true;
            return;
        case SDLK_SPACE:
            key.spacebar = true;
            return;
        case SDLK_UP:
            key.up = true;
            return;
        default:
            return;
        }
    }
}



bool Program::start_frame( void )
{
    poll_events();

    if( previous_state_ != state_ )
    {
        previous_state_ = state_;
        state_changed_ = true;
    }
    else
    {
        state_changed_ = false;
    }


    update_title();

    border_color_.set_draw( renderer_ );
    SDL_RenderClear( renderer_ );

    set_bg_draw_color();
    SDL_RenderFillRect( renderer_, &timer_area_ );

    SDL_Rect red{ BORDER_THICKNESS, BORDER_THICKNESS, 0, timer_area_.h };

    red.w = static_cast<int>( static_cast<double>( timer_area_.w ) * percentage_remaining_ );
    red.x += timer_area_.w - red.w;

    set_fg_draw_color();
    SDL_RenderFillRect( renderer_, &red );

    frame_first = true;

    return !quit_;
}



void Program::end_frame( void )
{

    SDL_RenderPresent( renderer_ );
}



SDL_Texture* Program::create_texture_from_Image_Array( Image_Array* arr )
{
    auto surf = SDL_CreateRGBSurface( 0,
                                      static_cast<int>( arr->w ), static_cast<int>( arr->h ), 32,
                                      arr->rmask, arr->gmask, arr->bmask, arr->amask );

    for( unsigned i = 0; i < arr->p; i++ )
    {
        *( reinterpret_cast<Uint32*>( surf->pixels ) + i ) = SDL_MapRGBA( surf->format, 255, 255, 255, arr->alpha[ i ] );
    }

    auto tex = SDL_CreateTextureFromSurface( renderer_, surf );
    if( !tex )
    {
#ifdef _DEBUG
        std::cerr << "Could not generate texture:\nSDL Error:\t" << SDL_GetError() << '\n';
#endif // !_DEBUG

    }

    SDL_FreeSurface( surf );
    surf = nullptr;
    delete arr;
    arr = nullptr;
    return tex;
}



Program::Program()
{
    snprintf( window_title_, TITLE_MAX_LENGTH, "%s", "Timer - Stopped" );

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
#ifdef _DEBUG
        std::cerr << "SDL Could not initialize.\nSDL Error:\t" << SDL_GetError() << '\n';
#endif // _DEBUG
        return;
    }

    window_ = SDL_CreateWindow(
        window_title_,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        TIMER_WIDTH + ( 2 * BORDER_THICKNESS ), TIMER_HEIGHT + ( 2 * BORDER_THICKNESS ),
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE );
    if( !window_ )
    {
#ifdef _DEBUG
        std::cerr << "Could not create window.\nSDL Error:\t" << SDL_GetError() << '\n';
#endif // _DEBUG

        return;
    }
    update_window_size();

    renderer_ = SDL_CreateRenderer( window_, -1, 0 );
    if( !renderer_ )
    {
#ifdef _DEBUG
        std::cerr << "Could not create renderer.\nSDL Error:\t" << SDL_GetError() << '\n';
#endif // _DEBUG

        return;
    }

    if( !load_sprites() )
    {
        return;
    }

    SDL_SetRenderDrawBlendMode( renderer_, SDL_BLENDMODE_BLEND );

    successful_init_ = true;
}



Program::~Program()
{
    for( auto& d : digits_ )
    {
        if( d )
        {
            SDL_DestroyTexture( d );
            d = nullptr;
        }
    }

    if( colon_ )
    {
        SDL_DestroyTexture( colon_ );
        colon_ = nullptr;
    }

    if( renderer_ )
    {
        SDL_DestroyRenderer( renderer_ );
        renderer_ = nullptr;
    }
    if( window_ )
    {
        SDL_DestroyWindow( window_ );
        window_ = nullptr;
    }
    SDL_Quit();
}



int Program::main_loop( void )
{
    if( !successful_init_ )
    {
        return -1;
    }

    for( ; start_frame(); end_frame() )
    {
        if( key.f11 )
        {
            if( is_fullscreen_ )
            {
                SDL_SetWindowFullscreen( window_, 0 );
            }
            else
            {
                SDL_SetWindowFullscreen( window_, SDL_WINDOW_FULLSCREEN_DESKTOP );
            }
        }

        if( show_time_ )
        {
            auto m10 = timer_.minutes_tens_place();
            auto m1 = timer_.minutes_ones_place();
            auto s10 = timer_.seconds_tens_place();
            auto s1 = timer_.seconds_ones_place();

            SDL_RenderCopy( renderer_, digits_[ m10 ], nullptr, character_positions + MINUTES_TENS );
            SDL_RenderCopy( renderer_, digits_[ m1 ], nullptr, character_positions + MINUTES_ONES );
            SDL_RenderCopy( renderer_, colon_, nullptr, character_positions + COLON );
            SDL_RenderCopy( renderer_, digits_[ s10 ], nullptr, character_positions + SECONDS_TENS );
            SDL_RenderCopy( renderer_, digits_[ s1 ], nullptr, character_positions + SECONDS_ONES );
        };

        switch( state_ )
        {
        case Program_State::SETTING:
            set_to();
            continue;
        case Program_State::TIMING:
            time();
            continue;
        case Program_State::BEEPING:
            beep();
            continue;
        default:
            return -11;
        }
    }

    return 0;
}



void Program::time( void )
{
    static bool started = false;

    if( !started )
    {
        started = true;
        previous_timer_ = timer_;
        timer_.start();
    }

    timer_.update();
    update_remaining_time();

    if( key.spacebar )
    {
        state_ = Program_State::SETTING;
        started = false;
    }

    if( timer_.ms_remain() == 0 )
    {
        state_ = Program_State::BEEPING;
        started = false;
    }
}



void Program::set_to( void )
{
    static int selected = MINUTES_ONES;

    if( key.spacebar )
    {
        state_ = Program_State::TIMING;
        previous_timer_ = timer_;
        return;
    }

    if( key.esc )
    {
        timer_ = previous_timer_;
        return;
    }

    if( key.left )
    {
        --selected;
        if( selected < MINUTES_TENS )
        {
            selected = SECONDS_ONES;
        }
        if( selected == COLON )
        {
            selected = MINUTES_ONES;
        }
    }

    if( key.right )
    {
        ++selected;
        if( selected > SECONDS_ONES )
        {
            selected = MINUTES_TENS;
        }
        if( selected == COLON )
        {
            selected = SECONDS_TENS;
        }
    }

    SDL_SetRenderDrawColor( renderer_, hl_color_.r, hl_color_.g, hl_color_.b, 255 );
    SDL_RenderDrawRect( renderer_, &character_positions[ selected ] );

    if( key.up )
    {
        switch( selected )
        {
        case MINUTES_TENS:
            timer_.minutes_up_ten();
            break;
        case MINUTES_ONES:
            timer_.minutes_up_one();
            break;
        case SECONDS_TENS:
            timer_.seconds_up_ten();
            break;
        case SECONDS_ONES:
            timer_.seconds_up_one();
        default:
            break;
        }
    }
    else if( key.down )
    {
        switch( selected)
        {
        case MINUTES_TENS:
            timer_.minutes_down_ten();
            break;
        case MINUTES_ONES:
            timer_.minutes_down_one();
            break;
        case SECONDS_TENS:
            timer_.seconds_down_ten();
            break;
        case SECONDS_ONES:
            timer_.seconds_down_one();
            break;
        default:
            break;
        }
    }
    total_time_ = timer_.ms_remain();
    update_remaining_time();
}



void Program::beep( void )
{
    static Timer flash{0,1};
    static bool reset = true;

    if( reset )
    {
        flash.set_to( 0, 0, 499 );
        flash.start();
        show_time_ = !show_time_;
        reset = false;
    }

    flash.update();
    if( flash.done() )
    {
        reset = true;
    }

    if( key.spacebar || key.esc )
    {
        reset = true;
        show_time_ = true;
        timer_ = previous_timer_;
        state_ = Program_State::SETTING;
    }
}



void Program::update_remaining_time( void )
{
    time_remaining_ = timer_.ms_remain();
    percentage_remaining_ = static_cast<double>( time_remaining_ ) / static_cast<double>( total_time_ );
}

void Program::update_title( void )
{
    switch( state_ )
    {
    case Program_State::BEEPING: // Fallthrough...
    case Program_State::SETTING:
        if( state_changed_ )
        {
            snprintf( window_title_, TITLE_MAX_LENGTH, "%s - %s", PROGRAM_NAME, state_name( state_ ) );
            SDL_SetWindowTitle( window_, window_title_ );
        }
        return;
    default:
        break;
    }

    snprintf( window_title_,
              TITLE_MAX_LENGTH,
              "%s - %s: %i:%02i.%03i",
              PROGRAM_NAME,
              state_name( state_ ),
              timer_.current_m(),
              timer_.current_s(),
              timer_.current_ms() );
    SDL_SetWindowTitle( window_, window_title_ );
}



void Program::set_bg_draw_color( void )
{
    bg_color_.set_draw( renderer_, 255 );
}



void Program::set_fg_draw_color( void )
{
    fg_color_.set_draw( renderer_, 255 );
}



void Program::update_scale_factor( double aspect_ratio )
{
    if( aspect_ratio > TIMER_ASPECT_RATIO ) // Window wider than timer.
    {
        if( window_size_.h == 0 )
        {
            scale_factor_ = 0;
        }
        else
        {
            scale_factor_ = static_cast<double>( timer_area_.h ) / TIMER_HEIGHT_d;
        }
        timer_x_0 = (( window_size_.w - scaled_timer_width() ) / 2) - BORDER_THICKNESS;
        timer_y_0 = BORDER_THICKNESS;

        return;
    }

    if( window_size_.w == 0 ) // Window taller than timer.
    {
        scale_factor_ = 0;
    }
    else
    {
        scale_factor_ = static_cast<double>( timer_area_.w ) / TIMER_WIDTH_d;
    }
    timer_x_0 = BORDER_THICKNESS;
    timer_y_0 = ( ( window_size_.h - scaled_timer_height() ) / 2 ) - BORDER_THICKNESS;
}

int Program::number_height( void )
{
    return static_cast<int>( static_cast<double>( CHARACTER_HEIGHT ) * scale_factor_ );
}

int Program::number_width( void )
{
    return static_cast<int>( static_cast<double>( NUMBER_WIDTH ) * scale_factor_ );
}

int Program::colon_height( void )
{
    return number_height();
}

int Program::colon_width( void )
{
    return static_cast<int>( static_cast<double>( COLON_WIDTH ) * scale_factor_ );
}

int Program::scaled_timer_height( void )
{
    return static_cast<int>( TIMER_HEIGHT_d * scale_factor_ );
}

int Program::scaled_timer_width( void )
{
    return static_cast<int>( TIMER_WIDTH_d * scale_factor_ );
}



bool Program::load_sprites( void )
{
    digits_[ 0 ] = create_texture_from_Image_Array( get_ALPHA_0() );
    digits_[ 1 ] = create_texture_from_Image_Array( get_ALPHA_1() );
    digits_[ 2 ] = create_texture_from_Image_Array( get_ALPHA_2() );
    digits_[ 3 ] = create_texture_from_Image_Array( get_ALPHA_3() );
    digits_[ 4 ] = create_texture_from_Image_Array( get_ALPHA_4() );
    digits_[ 5 ] = create_texture_from_Image_Array( get_ALPHA_5() );
    digits_[ 6 ] = create_texture_from_Image_Array( get_ALPHA_6() );
    digits_[ 7 ] = create_texture_from_Image_Array( get_ALPHA_7() );
    digits_[ 8 ] = create_texture_from_Image_Array( get_ALPHA_8() );
    digits_[ 9 ] = create_texture_from_Image_Array( get_ALPHA_9() );
    for( unsigned i = 0; i < 10; i++ )
    {
        if( !digits_[ i ] )
        {
            return BAD;
        }
    }

    colon_ = create_texture_from_Image_Array( get_ALPHA_COLON() );
    if( !colon_ )
    {
        return BAD;
    }

    return GOOD;
}



void Program::update_window_size( void )
{
    SDL_GetWindowPosition( window_, &window_size_.x, &window_size_.y );
    SDL_GetWindowSize( window_, &window_size_.w, &window_size_.h );
    timer_area_.x = BORDER_THICKNESS;
    timer_area_.y = BORDER_THICKNESS;
    timer_area_.w = window_size_.w - ( 2 * BORDER_THICKNESS );
    timer_area_.h = window_size_.h - ( 2 * BORDER_THICKNESS );
    timer_aspect_ratio_ = static_cast<double>( timer_area_.w ) / static_cast<double>( timer_area_.h );
    window_aspect_ratio_ = static_cast<double>( window_size_.w ) / static_cast<double>( window_size_.h );
    update_scale_factor( timer_aspect_ratio_ );

    Uint32 flags{ SDL_GetWindowFlags( window_ ) };
    is_fullscreen_ = static_cast<bool>( flags & SDL_WINDOW_FULLSCREEN_DESKTOP );

    
    character_positions[ MINUTES_TENS ].x = timer_x_0;
    character_positions[ MINUTES_TENS ].y = timer_y_0;
    character_positions[ MINUTES_TENS ].w = number_width();
    character_positions[ MINUTES_TENS ].h = number_height();

    character_positions[ MINUTES_ONES ].x = character_positions[ MINUTES_TENS ].x + number_width();
    character_positions[ MINUTES_ONES ].y = character_positions[ MINUTES_TENS ].y;
    character_positions[ MINUTES_ONES ].w = number_width();
    character_positions[ MINUTES_ONES ].h = number_height();

    character_positions[ COLON ].x = character_positions[ MINUTES_ONES ].x + number_width();
    character_positions[ COLON ].y = character_positions[ MINUTES_TENS ].y;
    character_positions[ COLON ].w = colon_width();
    character_positions[ COLON ].h = colon_height();

    character_positions[ SECONDS_TENS ].x = character_positions[ COLON ].x + colon_width();
    character_positions[ SECONDS_TENS ].y = character_positions[ COLON ].y;
    character_positions[ SECONDS_TENS ].w = number_width();
    character_positions[ SECONDS_TENS ].h = number_height();

    character_positions[ SECONDS_ONES ].x = character_positions[ SECONDS_TENS ].x + number_width();
    character_positions[ SECONDS_ONES ].y = character_positions[ SECONDS_TENS ].y;
    character_positions[ SECONDS_ONES ].w = number_width();
    character_positions[ SECONDS_ONES ].h = number_height();
}



void Program::KEYS::reset( void )
{
    up = false;
    down = false;
    left = false;
    right = false;
    spacebar = false;
    esc = false;
    f11 = false;
}



const char* state_name( Program_State state )
{
    switch( state )
    {
    case Program_State::SETTING:
        return "Stopped";
    case Program_State::TIMING:
        return "Remaining";
    case Program_State::BEEPING:
        return "Beeping";
    default:
        return "";
    }
}
