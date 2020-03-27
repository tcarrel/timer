#pragma once



#include<SDL.h>
#include<array>
#include<cstdlib>
#include "color.h"
#include "timer.h"
#include "image_array.h"
#include "window_icon.h"
#include "global_constants.h"
#include "jikan_shuuryou.bmp.h"



enum Character_Positions
{
    MINUTES_TENS,
    MINUTES_ONES,
    COLON,
    SECONDS_TENS,
    SECONDS_ONES
};



enum class Program_State
{
    SETTING,
    RUNNING,
    BEEPING,
    PAUSED
};
const char* state_name( Program_State state );
inline bool is_running( Program_State s )
{
    return s == Program_State::RUNNING;
}



class Program
{
    Timer timer_{ 2, 0 };
    Timer previous_timer_{ 2,0 };
    Uint32 total_time_{ 120000 };
    Uint32 time_remaining_{ 120000 };
    double percentage_remaining_{ 1.0 };
    Uint32 set_digits_[ 4 ]{ 0, 2, 0, 0 };
    Uint32 set_ms_{ 0 };

    bool is_time_remaining_{ true };
    bool successful_init_{ false };
    bool quit_{ false };

    const int TITLE_MAX_LENGTH{ 29 };
    char window_title_[ 29 ]{};
    SDL_Window* window_{ nullptr };
    bool is_fullscreen_{ nullptr };
    double window_aspect_ratio_{ 1.0 };
    double scale_factor_{ 1.0 };
    int timer_x_0{ BORDER_THICKNESS };
    int timer_y_0{ BORDER_THICKNESS };
    SDL_Renderer* renderer_{ nullptr };
    Color border_color_{ 255, 255, 0 };
    Color bg_color_{};
    Color fg_color_{ 192,  31,  31 };
    Color hl_color_{ 255, 255, 191 };

    SDL_Rect character_positions[ 5 ];

    SDL_Rect window_size_{ 0, 0, TIMER_WIDTH + ( 2 * BORDER_THICKNESS ),TIMER_HEIGHT + ( 2 * BORDER_THICKNESS ) };
    SDL_Rect timer_area_{ BORDER_THICKNESS, BORDER_THICKNESS, TIMER_WIDTH, TIMER_HEIGHT };
    double timer_aspect_ratio_{ TIMER_WIDTH_d / TIMER_HEIGHT_d };
    double shuuryou_scale_{ 1.0 };
    
    std::array<SDL_Texture*, 10> digits_{
        nullptr, nullptr, nullptr, nullptr, nullptr, 
        nullptr, nullptr, nullptr, nullptr, nullptr };
    SDL_Texture* colon_{ nullptr };
    SDL_Texture* shuuryou_{ nullptr };
    int shuuryou_width_{ 1 };
    int shuuryou_height_{ 1 };

    struct KEYS
    {
        bool up{ false };
        bool down{ false };
        bool left{ false };
        bool right{ false };
        bool spacebar{ false };
        bool esc{ false };
        bool f11{ false };

        void reset( void );
    } key;
    SDL_Event event_handler_{};
    bool frame_first{ true };

    int selected_digit_{ MINUTES_ONES };
    Program_State state_{ Program_State::SETTING };
    Program_State previous_state_{ Program_State::SETTING };
    bool state_changed_{ false };

    void update_remaining_time( void );

    void update_title( void );

    void set_bg_draw_color( void );
    void set_fg_draw_color( void );
    void update_scale_factor( double window_ar );
    int number_height( void );
    int number_width( void );
    int colon_height( void );
    int colon_width( void );
    int scaled_timer_height( void );
    int scaled_timer_width( void );
    SDL_Rect shuuryou_rect( void );

    bool load_sprites( void );
    void update_window_size( void );

    void poll_events( void );

    void react_to_window_event( Uint8 e );
    void update_key_states( SDL_KeyboardEvent keyvent );

    void start_timing( void );
    bool start_frame( void );
    void end_frame( void );

    SDL_Texture* create_texture_from_Image_Array( Image_Array* arr );
    SDL_Surface* create_surface_from_Image_Array( Image_Array* arr );

    void change_state_to( Program_State new_state );

public:
    Program();
    ~Program();

    int run( void );

    void timing( void );
    void setting_timer( void );
    void beeping( void );
};

