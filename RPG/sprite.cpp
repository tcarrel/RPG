

#include "stdafx.h"



/*static*/ unsigned Sprite::count_ = 0;
/*static*/ SDL_Renderer* Sprite::renderer_ = NULL;



Sprite::Sprite( void ) :
    Sprite( 0, 0, 0, 0 )
{}



/**
*   Sets all variables.
*/
Sprite::Sprite( int x, int y, int w, int h, Sprite_Sheet* sheet )
{
    set( x, y, w, h, sheet );
    if( sheet )
    {
        sprite_sheet_ = sheet->sheet_;
    }
    id_ = count_++;
}


/**
*   Horizontal (x) position on the sprite sheet.
*/
inline int& Sprite::x( void )
{
    return clip_.x;
}



/**
*   Vertical (y) position on the sprite sheet.
*/
inline int& Sprite::y( void )
{
    return clip_.y;
}



/**
*   The width of the sprite.
*/
inline int& Sprite::w( void )
{
    return clip_.w;
}



/**
*   The height of the sprite.
*/
inline int& Sprite::h( void )
{
    return clip_.h;
}



/**
*  The SDL_Rect containing the sprite's size and position on the sprite sheet.
*/
SDL_Rect* Sprite::clip( void )
{
    return &clip_;
}



/**
*  Performs the same function as the basic constructor.
*/
void Sprite::set( int x, int y, int w, int h, Sprite_Sheet* sheet )
{
    clip_ = { x, y, w, h };
    if( !sheet )
    {
        sprite_sheet_ = NULL;
        offset_x_ = offset_y_ = 0;
        return;
    }
    sprite_sheet_ = sheet->sheet_;
    offset_x_ = sheet->get_x_offset();
    offset_y_ = sheet->get_y_offset();
    if( !renderer_ )
    {
        renderer_ = sheet->renderer_;
    }
}



void Sprite::render( int x, int y )
{
    if( sprite_sheet_ )
    {
        SDL_Rect quad = {
			Scaler::scalei(x + offset_x_),
			Scaler::scalei(y + offset_y_),
			Scaler::scalei(clip_.w),
			Scaler::scalei(clip_.h) };
        SDL_RenderCopy( renderer_, sprite_sheet_, &clip_, &quad );
    }
}



void Sprite::set_renderer( SDL_Renderer* r )
{
    renderer_ = r;
}
