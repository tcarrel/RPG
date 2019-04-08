

#include "stdafx.h"






Game_Map::Game_Map( Event_Manager* em, Window* w, Console* c ) :
    Interface( em, c, w, INTERFACE_MAP )
{
	run();
}



void Game_Map::run( void )
{
	Console::current_interface( type() );

    for( ; !( exit_ || em_->quit() ); em_->process( this ) )
    {
		exit_ = true;
    }
}



inline Interface_enum_t Game_Map::type( void )
{
    return INTERFACE_MAP;
}



void Game_Map::add_state_machine_nodes(
    Pause* p,
    Combat* c,
    Menu* m,
    Item_Creation* ic )
{
    pause_screen_ = p;
    battle_ = c;
    menu_screen_ = m;
    item_creation_screen_ = ic;
}



void Game_Map::do_controls( unsigned u )
{
    if( ctrl_previous_[ u ] && !ctrl_current_[ u ] )
    {
        switch( u )
        {
        case CTRL_A:
            break;
        case CTRL_B:
            break;
        case CTRL_Y:
            break;
        case CTRL_X:
            break;
        case CTRL_L:
            break;
        case CTRL_R:
            break;
        case CTRL_UP:
            break;
        case CTRL_DOWN:
            break;
        case CTRL_LEFT:
            break;
        case CTRL_RIGHT:
            break;
        case CTRL_SELECT:
            break;
        case CTRL_START:
            break;
        default:
            break;
        }
    }
    ctrl_previous_[ u ] = ctrl_current_[ u ];
}
