
#include "stdafx.h"




/*static*/ Screen_Texture Pause::screen_image_;



Pause::Pause( Event_Manager* em, Window* w, Console* c ) :
    Interface( em, c, w, INTERFACE_PAUSE )
{
    screen_ = w->get_dimensions();
    renderer_ = w->get_renderer();
    exit_ = false;
    pause_.text = "PAUSED";

    pause_.x = ( SCREEN_X_PIXELS / 2 ) - ( 3 * TEXT_CHARACTER_WIDTH );
    pause_.y = ( SCREEN_Y_PIXELS / 2 ) - ( ( 1 * TEXT_CHARACTER_HEIGHT ) / 2 );
    pause_.hl = TEXT_HIGHLIGHT_TYPE_BRIGHT;
}



/*
void Pause::init( Text* t )
{
}
*/



/**
*   Runs the pause screen 'loop.'
*/
void Pause::run( void )
{
	Console::current_interface( type() );

    screen_image_.update();
    exit_ = false;

    for( ; !( exit_ || em_->quit() ); em_->process( this ) )
    {
        window_->clear();

        screen_image_.render();
        SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 204 );
        SDL_RenderFillRect( renderer_, &screen_ );

        text_->render( &pause_ );
        window_->update();
    }
}



inline Interface_enum_t Pause::type( void )
{
    return INTERFACE_PAUSE;
}



/**
*   Responds to player inpuet.  (Just unpausing.)
*/
void Pause::do_controls( unsigned u )
{

    if(
        u == CTRL_START &&
        ctrl_previous_[ CTRL_START ] &&
        !ctrl_current_[ CTRL_START ] )
    {
        exit_ = true;
    }
}
