


#include<SDL.h>



struct Image_Array
{
    size_t w{ 0 };
    size_t h{ 0 };
    size_t p{ 0 };
    Uint32 rmask{ 0x00'00'00'FF };
    Uint8* red{ nullptr };
    Uint32 gmask{ 0x00'00'FF'00 };
    Uint8* green{ nullptr };
    Uint32 bmask{ 0x00'FF'00'00 };
    Uint8* blue{ nullptr };
    Uint32 amask{ 0xFF'00'00'00 };
    Uint8* alpha{ nullptr };

    ~Image_Array( void );
};

Image_Array* get_ALPHA_0( void );
Image_Array* get_ALPHA_1( void );
Image_Array* get_ALPHA_2( void );
Image_Array* get_ALPHA_3( void );
Image_Array* get_ALPHA_4( void );
Image_Array* get_ALPHA_5( void );
Image_Array* get_ALPHA_6( void );
Image_Array* get_ALPHA_7( void );
Image_Array* get_ALPHA_8( void );
Image_Array* get_ALPHA_9( void );
Image_Array* get_ALPHA_COLON( void );