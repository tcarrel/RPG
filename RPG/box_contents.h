#pragma once

#include<SDL.h>
#include "text_passage.h"
#include "text_line.h"

class Text;
class Passage;
class Scaler;



/**
*   For storing the content of any text box.
*/
class Box_Contents
{
public:
    Box_Contents( void );
    Box_Contents( const char[] );
    Box_Contents( const string& );
    Box_Contents( const Uint8_t_String& );
    Box_Contents( const Passage& );

    ~Box_Contents( void );

    void set_fixed_width( void );
    void unset_fixed_width( void );

    Uint8_t_String& operator[]( const unsigned& );
    Uint8_t_String& operator[]( const int& );

    virtual void add_text( const char[], int );
    virtual void add_text( const string&, int );
    virtual void add_text( const Uint8_t_String&, int );

    void set_position( int, int );
    void set_width( int );

    virtual void activate( void );
    virtual void deactivate( void );

    SDL_Rect& size( void );
    Passage* get_text( void );
    unsigned lines( void );

    virtual void update( void* = NULL, const unsigned& = 0) = 0;

    //void render( int, int );
    virtual int command( Control_enum_t ) = 0;

    static void init( Text* );

    virtual Box_Contents_enum_t type( void );

protected:

    SDL_Rect size_; // Stores values in terms of text row and column numbers.
    Passage text_;

    static Text* text_system_;

    bool fixed_width_;

    void update_width( void );


};
