#pragma once

#include "stdafx.h"
class Console;
class Sprite;
class Text_Character;



/**
*  A wrapper for SDL_Texture for using and manipulating sprite sheet images.
*/
class Sprite_Sheet
{
public:

    Sprite_Sheet( void );
    Sprite_Sheet( const string&, transparent_color* color_key = NULL );
    ~Sprite_Sheet( void );

    bool load( const string&, transparent_color* color_key = NULL );
    void free( void );

    int get_width( void );
    int get_height( void );

    void render( int, int, SDL_Rect* clip = NULL );

    bool ready( void );

    static void set_renderer( SDL_Renderer* );
    SDL_Renderer* get_renderer( void );

    static void set_offsets( int, int );
    static int  get_x_offset( void );
    static int  get_y_offset( void );

    friend class Sprite;
    friend class Text_Character;

protected:

    SDL_Texture* sheet_;
    int width_;
    int height_;
	static float scale_factor_;

    bool ready_;

    static Console* console_;
    static unsigned reference_count_;
    static SDL_Renderer* renderer_;

    static int  offset_x_;
    static int  offset_y_;

private:

    static void dtor( void );
};