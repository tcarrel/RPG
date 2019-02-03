#pragma once

#include "stdafx.h"

class Scaler;

/**
*   A wrapper for the SDL Window.
*/
class Window
{

public:
    Window();

    bool good( void );
    void clear( void );
    void update( void );

    ~Window();

    SDL_Renderer* get_renderer( void );
    SDL_Surface* get_surface( void );
    SDL_Rect get_dimensions( void );
    int bpp( void );
    Uint32 format( void );

    int width( void );
    int height( void );

private:
    void splash( struct Splash_screen*, unsigned );
    void set_scale( float, float );

    bool is_good_;
    Uint32 flags_;

    int width_;
    int height_;
    int bpp_;

    SDL_DisplayMode mode_;
    SDL_Window* window_;
    SDL_Surface* surface_;

    Start_SDL subsys_init_;
    static Console* console_;

    struct
    {
        int x_;
        int y_;
    } pos;

    float scale_factor_;

    struct
    {
        int x_;
        int y_;
    } draw_offset;

    float aspect_;

    SDL_Renderer* renderer_;

    SDL_Rect borders_[ 2 ];
};
