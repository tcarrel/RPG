

#include "stdafx.h"



/*static*/ Text* Interface::text_ = NULL;
/*static*/ SDL_Renderer* Interface::renderer_ = NULL;
/*static*/ bool Interface::goto_start_menu_ = true;
/*static*/ bool* Interface::ctrl_current_ = NULL;
/*static*/ bool* Interface::ctrl_previous_ = NULL;



/*static*/ void Interface::register_ctrl( bool* cc, bool* cp )
{
    /*
    if( ctrl_current_ && Console::verbose() )
    {
        Console::error(
            "Interface",
            "",
            "Multiple registrations of control flags attempted." );
        return;
    }*/

    ctrl_current_ = cc;
    ctrl_previous_ = cp;
}



Interface_enum_t Interface::type( void )
{
    return _INTERFACE_BASE;
}



Interface::Interface( Event_Manager* em, Console * c, Window * w, Interface_enum_t t ) :
    console_( c ),
    //ctrl_current_( NULL ),
    came_from_( t ),
    em_( em ),
    window_( w ),
    exit_( false )
{}



/*static*/ void Interface::set_renderer( SDL_Renderer* r )
{
    renderer_ = r;
}



void Interface::set_text( Text* t )
{
    text_ = t;
}



/**
*   For storing the previous interface for so it can be returned to when
*  necessary.
*/
void Interface::set_source( Interface_enum_t source )
{
    came_from_ = source;
}



Interface::~Interface( void )
{}
