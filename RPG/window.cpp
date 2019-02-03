

#include "stdafx.h"

/*static*/ Console* Window::console_ = NULL;



SDL_Rect* get_splash_screen_image_size( SDL_Surface*, SDL_Surface* );


/**
*   Initializes the windowing system, creates the fullscreen game window, and
*  displays the start-up splash screens.
*/
Window::Window( void ) :
    subsys_init_( SDL_INIT_VIDEO ),
    is_good_(true),
    flags_( /*SDL_WINDOW_FULLSCREEN |*/ SDL_WINDOW_ALLOW_HIGHDPI )
{
    if( !console_ )
    {
        console_ = new Console;
    }

    if( !subsys_init_.good() )
    {
        subsys_init_.show_errors();
    }

    if( 0 != SDL_GetDesktopDisplayMode( 0, &mode_ ) )
    {
        console_->error( "SDL2", "Could not query display.", SDL_GetError() );
    }

    bpp_ = SDL_BITSPERPIXEL( mode_.format );
    console_->video_info( mode_ );

    pos.x_ = pos.y_ = -1;
    width_ = mode_.w;
    height_ = mode_.h;
    aspect_ = ( ( (float)width_ ) / ( (float)height_ ) ); // Might not need this.

    window_ = SDL_CreateWindow(
        GAME_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        mode_.w,
        mode_.h,
        flags_ );
    if( !window_ )
    {
        console_->error( "SDL2", "Could not create window.",
                         "Could not create window: " + string(SDL_GetError()) );
    }
    SDL_SetWindowIcon( window_, SDL_LoadBMP( "Graphics/Icon.bmp" ) );
    SDL_Delay( 100 );

    surface_ = SDL_GetWindowSurface( window_ );
    SDL_FillRect( surface_, NULL, SDL_MapRGB( surface_->format, 0x0, 0x0, 0x0 ) );

    Splash_screen splashes[ 3 ] =
    { { "Graphics/splash1_test.png" ,5},
      { "Graphics/splash2_test.png" ,5},
      { "Graphics/tech_splash.png"  ,5} };
    splash(splashes, 3);
    
    // Create the renderer.
    renderer_ = SDL_CreateRenderer(
        window_,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( !renderer_ )
    {
        console_->error(
            "SDL2",
            "Could not create renderer.",
            "Could not create renderer: " + string( SDL_GetError() ) );
    }
    else
    {
        SDL_SetRenderDrawBlendMode( renderer_, SDL_BLENDMODE_BLEND );
        SDL_SetRenderDrawColor( renderer_, 1, 1, 1, 0 );
    }

    set_scale( (float)mode_.w, (float)mode_.h );
    Sprite_Sheet::set_renderer( renderer_ );
    Sprite_Sheet::set_offsets( draw_offset.x_, draw_offset.y_ );
}



inline bool Window::good( void )
{
    return is_good_;
}



/**
*  Clears the screen.
*/
void Window::clear( void )
{
    SDL_SetRenderDrawColor( renderer_, 0, 33, 0, 0xff );
    SDL_RenderClear( renderer_ );
}



/**
*  Updates the frame buffer.
*/
void Window::update( void )
{
    static bool first = true;
    if( first )
    {
        first = false;
        console_->vb_variable_value(
            "Window", "draw_offset.x_", draw_offset.x_ );
        console_->vb_variable_value(
            "Window", "draw_offset.y_", draw_offset.y_ );

    }

    if( DRAW_BORDERS )
    {
        SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 0xff );
        SDL_RenderFillRects( renderer_, borders_, 2 );
    }

    SDL_RenderPresent( renderer_ );
}




Window::~Window( void )
{
    //SDL_Delay( 2000 );
    SDL_DestroyRenderer( renderer_ );
    SDL_DestroyWindow( window_ );
    surface_ = NULL;
}



SDL_Renderer* Window::get_renderer( void )
{
    return renderer_;
}



inline SDL_Surface* Window::get_surface( void )
{
    return SDL_GetWindowSurface( window_ );
}



SDL_Rect Window::get_dimensions( void )
{
    return{ pos.x_, pos.y_, width_, height_ };
}



int Window::bpp( void )
{
    return bpp_;
}



Uint32 Window::format( void )
{
    return mode_.format;
}



int Window::width( void )
{
    return width_;
}



int Window::height( void )
{
    return height_;
}



/**
*  Shows the splash screens.
*/
void Window::splash( Splash_screen* files, unsigned qty )
{
    SDL_Surface* image = NULL;
    SDL_Rect* size = NULL;
    
    for( unsigned i = 0; i < qty; i++ )
    {
        if( i > 0 )
        {
            SDL_Delay( 500 );
        }
        image = IMG_Load( files[i].path.c_str() );
        size = get_splash_screen_image_size( image, surface_ );
        SDL_BlitScaled( image, NULL, surface_, size );
        SDL_UpdateWindowSurface( window_ );
        SDL_Delay( files[i].time );
        SDL_FillRect( surface_, NULL, SDL_MapRGB( surface_->format, 0x0, 0x0, 0x0 ) );
        delete size;
        size = NULL;
        SDL_FreeSurface( image );
    }



    image = NULL;
}



/**
*   Determines the appropriate size of a splash screen imager.
*/
SDL_Rect* get_splash_screen_image_size( SDL_Surface* image, SDL_Surface* window )
{
    if( !image || !window )
    {
        return NULL;
    }

    float target_ar = ( ( (float)window->w) / ( (float)window->h) );
    float image_ar = ( ( (float)image->w ) / ( (float)image->h ) );
    SDL_Rect* out = new SDL_Rect;

    if( target_ar > image_ar )
    {
        out->h = window->h;
        out->w = ftoi( itof( out->h ) * image_ar );

        out->y = 0;
        out->x = ( window->w - out->w ) / 2;

        return out;
    }

    out->w = window->w;
    out->h = ftoi( itof( out->w ) / image_ar );

    out->x = 0;
    out->y = ( window->h - out->h ) / 2;

    return out;
}



void Window::set_scale( float w, float h )
{
    if( w == SCREEN_X_PIXELS && h == SCREEN_Y_PIXELS )
    {
        scale_factor_ = 1;
        draw_offset.x_ = draw_offset.y_ = 0;
        for( unsigned i = 0; i < 2; i++ )
        {
            borders_[ i ].h = 0;
            borders_[ i ].w = 0;
            borders_[ i ].x = 0;
            borders_[ i ].y = 0;
        }

		Scaler::init(scale_factor_);

        return;
    }

    float target_ar = w / h;
    float image_ar = ( (float)SCREEN_X_PIXELS ) / ( (float)SCREEN_Y_PIXELS );
    scale_factor_ = 1;

    if( target_ar > image_ar )
    {
        scale_factor_ = h / SCREEN_Y_PIXELS;

        int pixels_w = (int)(SCREEN_X_PIXELS * scale_factor_);
        int pixels_h = mode_.h;

        draw_offset.y_ = 0;
        draw_offset.x_ = ( mode_.w - pixels_w ) / 2;

        borders_[ 0 ].x = 0;
        borders_[ 0 ].y = 0;
        borders_[ 0 ].w = draw_offset.x_;
        borders_[ 0 ].h = mode_.h;

        borders_[ 1 ].x = mode_.w - draw_offset.x_;
        borders_[ 1 ].y = 0;
        borders_[ 1 ].w = borders_[ 0 ].w;
        borders_[ 1 ].h = borders_[ 0 ].h;

        console_->vb_variable_value( "Window", "scale_factor_", scale_factor_ );
        console_->vb_variable_value( "Window", "pixels_w", pixels_w );
        console_->vb_variable_value( "Window", "pixels_h", pixels_h );
        console_->vb_variable_value( "Window", "mode_.w", mode_.w );
        console_->vb_variable_value( "Window", "draw_offset.x", draw_offset.x_ );
        console_->vb_variable_value( "Window", "draw_offset.y", draw_offset.y_ );
        console_->vb_variable_value( "Window", "borders_[0]", borders_[ 0 ] );
        console_->vb_variable_value( "Window", "borders_[1]", borders_[ 1 ] );

		Scaler::init(scale_factor_);

        return;
    }

    scale_factor_ = w / 1024;

    int pixels_w = mode_.w;
    int pixels_h = (int)( SCREEN_Y_PIXELS * scale_factor_ );

    draw_offset.y_ = ( mode_.h - pixels_w ) / 2;
    draw_offset.x_ = 0;

    borders_[ 0 ].x = 0;
    borders_[ 0 ].y = 0;
    borders_[ 0 ].w = pixels_w;
    borders_[ 0 ].h = draw_offset.y_;

    borders_[ 1 ].x = 0;
    borders_[ 1 ].y = mode_.h - draw_offset.y_;
    borders_[ 1 ].w = borders_[ 0 ].w;
    borders_[ 1 ].h = borders_[ 0 ].h;

    console_->vb_variable_value( "Window", "scale_factor_", scale_factor_ );
    console_->vb_variable_value( "Window", "pixels_w", pixels_w );
    console_->vb_variable_value( "Window", "pixels_h", pixels_h );
    console_->vb_variable_value( "Window", "mode_.w", mode_.w );
    console_->vb_variable_value( "Window", "draw_offset.x", draw_offset.x_ );
    console_->vb_variable_value( "Window", "draw_offset.y", draw_offset.y_ );
    console_->vb_variable_value( "Window", "borders_[0]", borders_[ 0 ] );
    console_->vb_variable_value( "Window", "borders_[1]", borders_[ 1 ] );

	Scaler::init(scale_factor_);

    return;
}
