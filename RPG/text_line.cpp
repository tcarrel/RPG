

#include "stdafx.h"



/**
*   Ctor.
*/
Line_of_Text::Line_of_Text( void )
{
    this->x = this->y = 0;
    this->text = "";
    hl = TEXT_HIGHLIGHT_TYPE_NORMAL;
}



/**
*   Ctor for converting from a Uint8_t_String.
*/
Line_of_Text::Line_of_Text( const Uint8_t_String& str )
{
    this->x = this->y = 0;
    this->text = str;
    hl = TEXT_HIGHLIGHT_TYPE_NORMAL;
}



/**
*   Ctor for converting from a c-string.
*/
Line_of_Text::Line_of_Text( const char cstr[] )
{
    *this = cstr;
}



Line_of_Text::Line_of_Text(
    const int& xpos,
    const int& ypos,
    const Text_Highlighting_enum_t& hi,
    const Uint8_t_String& ui8s ) :
    text( ui8s )
{
    x = Scaler::scalei(xpos);
    y = Scaler::scalei(ypos);
    hl = hi;
}



Line_of_Text::Line_of_Text(
    const int& xpos,
    const int& ypos,
    const Text_Highlighting_enum_t& hi,
    const char cc[] ) :
    text(cc)
{
	x = xpos;//Scaler::scalei(xpos);
	y = ypos;//Scaler::scalei(ypos);
    hl = hi;
}



/**
*   Copy ctor.
*/
Line_of_Text::Line_of_Text( const Line_of_Text& copy_from )
{
    *this = copy_from;
}



/**
*   Assignment operator from Uint8_t_String.
*/
Line_of_Text& Line_of_Text::operator=( const Uint8_t_String& str )
{
    this->text = str;
    return *this;
}



/**
*   Assignment operator from c-string.
*/
Line_of_Text& Line_of_Text::operator=( const char cstr[] )
{
    this->text = cstr;
    return *this;
}



/**
*   Assignment operator from another Line_of_Text.
*/
Line_of_Text& Line_of_Text::operator=( const Line_of_Text& rhs )
{
    this->hl = rhs.hl;
    this->x = rhs.x;
    this->y = rhs.y;
    this->text = rhs.text;
    return *this;
}