

#include "stdafx.h"




/**
*   Ctor.
*/
Selectable_List::Selectable_List( unsigned spacing ) :
    Box_Contents()
{
    text_.add( new Line_of_Text( "" ) );
    selected_ = 0;
    spacing_ = ( spacing < 1 ) ? 1 : spacing;
    active_ = true;
}



/**
*   Activates the text box.  (For use with text boxes that can be commanded by
*  the player.
*/
void Selectable_List::activate( void )
{
    active_ = true;
    update_text();
}



/**
*   Deactivates the text box.  (For use with text boxes that can be commanded by
*  the player.
*/
void Selectable_List::deactivate( void )
{
    active_ = false;
    update_text();
}



void Selectable_List::add_text( const char text[], int return_value )
{
    add_text( Uint8_t_String( text ), return_value );
}



void Selectable_List::add_text( const string& text, int return_value )
{
    add_text( Uint8_t_String( text ), return_value );
}



/**
*   Adds options or headings to the selection box.  No ordering is performed,
*  so they must be added in the order in which they are to appear.
*/
void Selectable_List::add_text( const Uint8_t_String& u8str, int return_val )
{

    Line_of_Text* lot = new Line_of_Text( u8str );

    text_.add( lot );
    if( return_val != MENU_UNSELECTABLE_ITEM )
    {
        selection_.push_back( lot );
        return_values_.push_back( return_val );
    }

    for( unsigned u = 0; u < spacing_ - 1; u++ )
    {
        text_.add( new Line_of_Text( "" ) );
    }
    update_text();
}



void Selectable_List::set_btn_rv( int start, int cancel )
{
    start_btn_return_val_ = start;
    cancel_btn_return_val_ = cancel;
}



void Selectable_List::update( void*, const unsigned& )
{
    update_text();
}



/**
*   Ignores or reacts to user input.
*/
int Selectable_List::command( Control_enum_t control )
{
    switch( control )
    {
    case CTRL_A:
        return return_values_[ selected_ ];
    case CTRL_DOWN:
        down();
        update_text();
        break;
    case CTRL_UP:
        up();
        update_text();
        break;
    case CTRL_B:
        return cancel_btn_return_val_;
    case CTRL_START:
        return start_btn_return_val_;
    default:
        ;
    }
    return void__MENU_RETURN_VALUE__;
}



/**
*   Returns the enum value representing this text box type.
*/
Box_Contents_enum_t Selectable_List::type( void )
{
    return BOX_TEXT_SELECTABLE_LIST;
}



Selectable_List::~Selectable_List( void )
{
    for( unsigned u = 0; u < selection_.size(); u++ )
    {
        //delete selection_[ u ];
        selection_[ u ] = NULL;
    }
    selection_.clear();
}



/**
*   Changes which text is highlighted.
*/
void Selectable_List::update_text( void )
{
    for( int i = 0; i < (int)selection_.size(); i++ )
    {
        selection_[ i ]->hl =
            ( active_ && ( i == selected_ ) ) ?
            TEXT_HIGHLIGHT_TYPE_BRIGHT :
            TEXT_HIGHLIGHT_TYPE_NORMAL;
    }
}



void Selectable_List::down( void )
{
    ++selected_;
    if( selected_ >= selection_.size() )
    {
        selected_ = 0;
    }
}



void Selectable_List::up( void )
{
    if( selected_ == 0 )
    {
        selected_ = selection_.size() - 1;
        return;
    }
    --selected_;
}
