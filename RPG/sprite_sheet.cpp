

#include "stdafx.h"



/*static*/ Console* Sprite_Sheet::console_ = NULL;
/*static*/ SDL_Renderer* Sprite_Sheet::renderer_ = NULL;
/*static*/ int Sprite_Sheet::offset_x_ = 0;
/*static*/ int Sprite_Sheet::offset_y_ = 0;



/**
*   Initializes all internals.
*/
Sprite_Sheet::Sprite_Sheet( void ) :
    sheet_( NULL ),
    width_( 0 ),
    height_( 0 ),
    ready_(false)
{
    if( !console_ )
    {
        console_ = new Console;
        atexit( dtor );
    }
}



/**
*   Ctor that also loads the bitmap image to be used as a sprite sheet.
*/
Sprite_Sheet::Sprite_Sheet( const string& path, transparent_color* ck ) :
    Sprite_Sheet()
{
    ready_ = load( path, ck );
}



/**
*   Instance dtor.
*/
Sprite_Sheet::~Sprite_Sheet( void )
{
    this->free();
}



/**
*   Loads the bitmap image to be used as a sprite sheet.
*/
bool Sprite_Sheet::load( const string& path, transparent_color* color_key )
{
    this->free();

    SDL_Texture* new_texture = NULL;

   // SDL_Surface* loaded = SDL_LoadBMP( path.c_str() );
    SDL_Surface* loaded = IMG_Load( path.c_str() );
    if( !loaded )
    {
        string long_msg(
            "Unable to load sprite sheet <" +
            path +
            ">: " +
            SDL_GetError() );

        console_->error( "SDL2", "Unable to load sprite sheet.", long_msg );
        return false;
    }

    if( color_key )
    {
        SDL_SetColorKey(
            loaded,
            SDL_TRUE,
            SDL_MapRGB(
                loaded->format,
                color_key->r,
                color_key->g,
                color_key->b ) );
    }

    new_texture = SDL_CreateTextureFromSurface( renderer_, loaded );
    Console::vb_variable_value( "Sprite_Sheet", "renderer_", renderer_ );
    if( !new_texture )
    {
        string shrt(
            "Unable to create texture from <" + path + ">."
        );
        string longm(
            "Unable to create texture from <" + path + ">: " + SDL_GetError()
        );
        console_->error( "SDL2", shrt, longm );
        return false;
    }

    width_  = loaded->w;
    height_ = loaded->h;

    SDL_FreeSurface( loaded );
    loaded = NULL;

    sheet_ = new_texture;
    new_texture = NULL;

    console_->vb_only_no_err( "Sprite_Sheet", "Sheet " + path + ", loaded." );
    console_->vb_variable_value( "Sprite_Sheet", "SDL_Texture*", sheet_ );

    return true;
}



/**
*   Frees the current texture, called either from the dtor or when loading a
*  new texture.
*/
void Sprite_Sheet::free( void )
{
    if( sheet_ )
    {
        SDL_DestroyTexture( sheet_ );
        sheet_ = NULL;
        width_ = height_ = 0;
    }
}



/**
*   Returns the height, in pixels, of the currently stored sprite sheet.
*/
int Sprite_Sheet::get_height( void )
{
    return height_;
}



/**
*   Returns the width, in pixels, of the currently stored sprite sheet.
*/
int Sprite_Sheet::get_width( void )
{
    return width_;
}



/**
*   Stores the renderer for it's own uses.
*/
void Sprite_Sheet::set_renderer( SDL_Renderer* r )
{
    Console::vb_variable_value( "Sprite_Sheet", "set_renderer()", r );
    renderer_ = r;
}



/**
*   Returns the current renderer.
*/
SDL_Renderer * Sprite_Sheet::get_renderer( void )
{
    return renderer_;
}



/**
*   Renders the entire image or just a sprite from it, if clip is provided.
*/
void Sprite_Sheet::render( int x, int y, SDL_Rect* clip )
{
    SDL_Rect quad = { x + offset_x_, y + offset_y_, width_, height_ };

    if( clip )
    {
        quad.h = clip->h;
        quad.w = clip->w;
    }

    SDL_RenderCopy( renderer_, sheet_, clip, &quad );
}



/**
*   If the sprite sheet is ready for use.
*/
bool Sprite_Sheet::ready( void )
{
    return ready_;
}



/**
*   Offsets.  For simplifying rendering to screens that are not 16:9 aspect
*  ratio.
*/
/*static*/ void Sprite_Sheet::set_offsets( int w, int h )
{
    offset_x_ = w;
    offset_y_ = h;
}



/**
*   Returns the horizontal offset.
*/
int Sprite_Sheet::get_x_offset( void )
{
    return offset_x_;
}



/**
*   Returns the vertical offset.
*/
int Sprite_Sheet::get_y_offset( void )
{
    return offset_y_;
}



/**
*   Final dtor to be called once atexit().
*/
void Sprite_Sheet::dtor( void )
{
    delete console_;
    console_ = NULL;
}
