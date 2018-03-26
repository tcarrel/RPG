

#include "stdafx.h"



/*static*/ Screen_Texture Confirm_Quit::screen_image_;



Confirm_Quit::Confirm_Quit(
    Event_Manager* em, Window* w, Console* c, SDL_Renderer* r ) :
    Interface( em, c, w, INTERFACE_CONFIRM_QUIT )
{
    renderer_ = r;

    Selectable_List* yes_no = new Selectable_List( 2 );
    yes_no->add_text(
        "  Are you sure you want to quit?",
        MENU_UNSELECTABLE_ITEM );
    yes_no->add_text(
        "All unsaved progress will be lost.",
        MENU_UNSELECTABLE_ITEM );
    yes_no->add_text(
        "   No",
        MENU_RETURN_VALUE__NO );
    yes_no->add_text(
        "   Yes",
        MENU_RETURN_VALUE__YES );
    yes_no->set_btn_rv( MENU_RETURN_VALUE__YES, MENU_RETURN_VALUE__NO );
    yes_no->activate();

    SDL_Rect coords = { ( TEXT_COLUMNS - 34 ) / 2,( TEXT_ROWS - 9 ) / 2, 34, 9 };

    box_ = new Text_Box( yes_no, coords );

    yes_no = NULL;
}



void Confirm_Quit::run( void )
{
    screen_image_.update();
    exit_ = false;

    for( ; !( exit_ || em_->quit() ); em_->process( this ) )
    {
        window_->clear();
        screen_image_.render();
        box_->render();
        window_->update();
    }
}


Interface_enum_t Confirm_Quit::type( void )
{
    return INTERFACE_CONFIRM_QUIT;
}



Confirm_Quit::~Confirm_Quit( void )
{
    delete box_;
    box_ = NULL;
}



void Confirm_Quit::do_controls( unsigned key )
{
    if( ctrl_previous_[ key ] && !ctrl_current_[ key ] )
    {
        switch( box_->command( uint_to_cntlt( key ) ) )
        {
        case MENU_RETURN_VALUE__NO:
            exit_ = true;
            return;
        case MENU_RETURN_VALUE__YES:
            em_->quit_game();
            return;
        default:
            ;
        }
    }
}
