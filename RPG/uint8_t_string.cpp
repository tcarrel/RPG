

#include "stdafx.h"



/**
*   Generic ctor.
*/
Uint8_t_String::Uint8_t_String( void ) :
    string_( new uint8_t[17] ),
    length_( 0 ),
    capacity_( 17 )
{
    string_[ capacity_ - 1 ] = 0;
}



/**
*   Copy ctor.
*/
Uint8_t_String::Uint8_t_String( const Uint8_t_String& u )
{
    *this = u;
}



/**
*   Ctor to convert from a c-string.
*/
Uint8_t_String::Uint8_t_String( const char c[] )
{
    unsigned u;
    capacity_ = length_ = cstrlen( c );
    ++capacity_;

    while( ( capacity_ % 16 ) != 1 )
    {
        ++capacity_;
    }
    string_ = new uint8_t[ capacity_ ];
    for( u = 0; c[u] != 0; u++ )
    {
        string_[ u ] = (uint8_t) c[ u ];
    }
    string_[ length_ ] = 0;
}



/**
*   Ctor to convert from a c++-style string.
*/
Uint8_t_String::Uint8_t_String( const string& str ) 
{
    capacity_ = length_ = str.size();
    ++capacity_;

    while( ( capacity_ % 16 ) != 1 )
    {
        ++capacity_;
    }

    string_ = new uint8_t[ capacity_ ];
    for( unsigned u = 0; u < length_; u++ )
    {
        string_[ u ] = (uint8_t)str[ u ];
    }
    string_[ length_ ] = 0;
}



/**
*   Copies from a unsigned char string with a known length.
*/
Uint8_t_String::Uint8_t_String( const unsigned& qty, const uint8_t& chr )
{
    length_ = capacity_ = qty;
    while( ( capacity_ % 16 ) != 1 )
    {
        ++capacity_;
    }
    string_ = new uint8_t[ capacity_ ];

    for( unsigned u = 0; u < length_; u++ )
    {
        string_[ u ] = chr;
    }
    string_[ length_ ] = 0;
}



/**
*   Copy assignment operator.
*/
Uint8_t_String& Uint8_t_String::operator=( const Uint8_t_String& right_side )
{
    delete[] this->string_;
    this->length_ = right_side.length_;
    this->capacity_ = right_side.capacity_;
    this->string_ = new uint8_t[ capacity_ ];

    for( unsigned u = 0; u < capacity_; u++ )
    { 
        this->string_[ u ] = right_side.string_[ u ];
    }
     
    return *this;
}



/**
*   Assignment operator from c++-string.
*/
Uint8_t_String& Uint8_t_String::operator=( const string& rhs )
{
    if( string_ )
    {
        delete[] string_;
    }

    capacity_ = length_ = rhs.size();
    while( ( capacity_ % 16 ) != 1 )
    {
        ++capacity_;
    }

    string_ = new uint8_t[ capacity_ ];
    for( unsigned u = 0; u < length_; u++ )
    {
        string_[ u ] = (uint8_t)rhs[ u ];
    }
    string_[ length_ ] = 0;

    return *this;
}



/**
*   Assignment operator copies from c-string.
*/
Uint8_t_String& Uint8_t_String::operator=( const char right_side[] )
{
    delete[] this->string_;

    this->string_ = new uint8_t[ 17 ];
    this->capacity_ = 16;
    this->length_ = 0;

    unsigned u;
    for( u = 0; right_side[ u ] != 0; u++ )
    {
        grow( u );
        string_[ u ] = right_side[ u ];
        ++length_;
    }
    string_[ u ] = 0;

    return *this;
}



/**
*   Array-like element access.
*/
uint8_t& Uint8_t_String::operator[]( const unsigned& subscript )
{
    return string_[ subscript ];
}



/**
*   Array-like element access.
*/
uint8_t& Uint8_t_String::operator[]( const int& subscript )
{
    return string_[ subscript ];
}



/**
*   Returns the internal unsigned char array.
*/
uint8_t* Uint8_t_String::c_str( void )
{
    return string_;
}



/**
*   Returns the length of the string.
*/
unsigned Uint8_t_String::size( void )
{
    return length_;
}



/**
*   Internal use only.  Increases the string's capacity.
*/
void Uint8_t_String::grow( unsigned u )
{
    if( u < capacity_ )
    {
        return;
    }
    
    unsigned new_capacity = capacity_ + 16;

    // TODO: Make this not horrible.  It is only used during loading and
    //initializaion, so it's not a major priority.
    while( ( new_capacity % 16 ) != 1 )
    {
        ++new_capacity;
    }

    uint8_t* new_str = new uint8_t[ new_capacity ];

    for( unsigned u = 0; u < capacity_; u++ )
    {
        new_str[ u ] = string_[ u ];
    }
    new_str[ capacity_ + 1 ] = 0;

    delete[] string_;
    string_ = new_str;
    new_str = NULL;

    capacity_ = new_capacity;
    string_[ capacity_ ] = 0;
}



/**
*   Dtor.
*/
Uint8_t_String::~Uint8_t_String( void )
{
    if( string_ )
    {
        delete[] string_;
        string_ = NULL;
    }
}
