

#include "stdafx.h"



/*static*/ Text* Box_Contents::text_system_ = NULL;



/**
*   Initializes all variable to 'safe' values.
*/
Box_Contents::Box_Contents( void ) :
    size_{ 0, 0, 0, 0 }
{
    if( !text_system_ )
    {
        text_system_ = new Text;
    }
    size_.h = text_.size();
    fixed_width_ = false;
}



/**
*   Initializes and stores a single string.
*/
Box_Contents::Box_Contents( const string& str ) :
    Box_Contents( Uint8_t_String( str ) )
{}



/**
*   Initializes and stores a single string.
*/
Box_Contents::Box_Contents( const char cstr[] ) :
    Box_Contents( Uint8_t_String( cstr ) )
{}



/**
*   Initializes and stores a single string.
*/
Box_Contents::Box_Contents( const Uint8_t_String& str ) :
    Box_Contents()
{
    text_.add( new Line_of_Text( str ) );
    size_.h = text_.size();

    update_width();
}



/**
*   Initializes and stores a copy of an entire Passage.
*/
Box_Contents::Box_Contents( const Passage& cp ) :
    text_( cp )
{
    size_.h = text_.size();

    update_width();
}



/**
*   Adds one line of text.
*/
void Box_Contents::add_text( const char ccstr[], int i )
{
    add_text( Uint8_t_String( ccstr ), i );
}



/**
*   Adds one line of text.
*/
void Box_Contents::add_text( const string& str, int i )
{
    add_text( Uint8_t_String( str ), i );
}



/**
*   Adds one line of text.
*/
void Box_Contents::add_text( const Uint8_t_String& u8str, int )
{
    text_.add( new Line_of_Text( u8str ) );
    
    size_.h = text_.size();
    update_width();
}



/**
*   Sets the position of the text box.
*/
void Box_Contents::set_position( int x, int y )
{
	size_.x = x;//Scaler::scalei(x);
	size_.y = y;//Scaler::scalei(y);
}



/**
*   Sets the width of the text box.
*/
void Box_Contents::set_width( int w )
{
	size_.w = w;//Scaler::scalei(w);
}



/**
*   Activates the text box.  (For use with text boxes that can be commanded by
*  the player.
*/
void Box_Contents::activate( void )
{}



/**
*   Deactivates the text box.  (For use with text boxes that can be commanded by
*  the player.
*/
void Box_Contents::deactivate( void )
{}



/**
*   Returns the text box's text.
*/
Passage* Box_Contents::get_text( void )
{
    return &text_;
}



/**
*   Dtor.
*/
Box_Contents::~Box_Contents( void )
{
    text_system_ = NULL;
}



/**
*   Prevents the text box from resizing itself when new text is added.
*/
void Box_Contents::set_fixed_width( void )
{
    fixed_width_ = true;
}



/**
*   Allows the text box to resize itself when new text is added.
*/
void Box_Contents::unset_fixed_width( void )
{
    fixed_width_ = false;
}



/**
*   Array-style access to the contained text.  It is left to the user to avoid
*  seg faults.
*/
Uint8_t_String& Box_Contents::operator[]( const unsigned& u )
{
    return text_[ u ]->text;
}



/**
*   Array-style access to the contained text.  It is left to the user to avoid
*  seg faults.
*/
Uint8_t_String& Box_Contents::operator[]( const int& i )
{
    return text_[ i ]->text;
}



/**
*   Returns an SDL_Rect containing the size and position of the text box.
*/
SDL_Rect& Box_Contents::size( void )
{
    return size_;
}



/**
*   Return how many line of text are in the current text box.
*/
unsigned Box_Contents::lines( void )
{
    return (unsigned)size_.h;
}



/**
*   If fixed_width_ is not set, this updates the width of the text box to fit
*  the longest line of text that has currently been provided.
*/
void Box_Contents::update_width( void )
{
    if( fixed_width_ )
    {
        return;
    }

    for( unsigned i = 0; i < text_.size(); i++ )
    {
        if( size_.w < (int)text_[ i ]->text.size() )
        {
            size_.w = (int)text_[ i ]->text.size();
        }
    }
}



/**
*   Initializes the text-box-system.
*/
void Box_Contents::init( Text* t )
{
    text_system_ = t;
}



/**
*   Returns the enum value representing this text box type.
*/
Box_Contents_enum_t Box_Contents::type( void )
{
    return BOX_BOX_CONTENTS_BASE_TYPE;
}
