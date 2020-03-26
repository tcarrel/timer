#pragma once



constexpr bool GOOD{ true };
constexpr bool BAD{ !GOOD };

constexpr auto PROGRAM_NAME = "Timer";

constexpr int BORDER_THICKNESS = 4;
constexpr int CHARACTER_HEIGHT = 300;
constexpr int NUMBER_WIDTH = 210;
constexpr int COLON_WIDTH = 100;
constexpr int TIMER_HEIGHT = CHARACTER_HEIGHT;
constexpr int TIMER_WIDTH = NUMBER_WIDTH + NUMBER_WIDTH + COLON_WIDTH + NUMBER_WIDTH + NUMBER_WIDTH;
constexpr double TIMER_ASPECT_RATIO = static_cast<double>( TIMER_WIDTH ) / static_cast<double>( TIMER_HEIGHT );
constexpr double TIMER_HEIGHT_d = static_cast<double>( TIMER_HEIGHT );
constexpr double TIMER_WIDTH_d = static_cast<double>( TIMER_WIDTH );

constexpr auto TIME_WIDTH = COLON_WIDTH + ( 4 * NUMBER_WIDTH );
