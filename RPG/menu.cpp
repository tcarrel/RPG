
#include "stdafx.h"





Menu::Menu( Event_Manager* em, Window* w, Console* c ) :
    Interface( em, c, w, INTERFACE_MENU )
{}



void Menu::init( Play_Data* pd )
{
    SDL_Rect dims = { TEXT_COLUMNS - 11, TEXT_ROWS - 3, 11, 1 };

    game_data_ = pd;
    base_menu_.funds_box =
        new Text_Box( new Money_Display( game_data_->money_addr() ), dims );

    dims = { 0, 0, 11, 17 };
    base_menu_.main_selections = new Text_Box(
        new Selectable_List( 2 ), dims );
    base_menu_.main_selections->add_text(
        " Inventory",
        MENU_RETURN_VALUE__OPEN_ITEM_INVENTORY );
    base_menu_.main_selections->add_text(
        " Magic",
        MENU_RETURN_VALUE__OPEN_MAGIC_MENU );
    base_menu_.main_selections->add_text(
        " Equipment ",
        MENU_RETURN_VALUE__OPEN_EQUIP_MENU );
    base_menu_.main_selections->add_text(
        " Status",
        MENU_RETURN_VALUE__OPEN_STATUS );
    base_menu_.main_selections->add_text(
        " Settings",
        MENU_RETURN_VALUE__OPEN_SETTINGS_MENU );
    base_menu_.main_selections->add_text(
        " Load Game",
        MENU_RETURN_VALUE__OPEN_LOAD_GAME_MENU );
    base_menu_.main_selections->add_text(
        " Return",
        MENU_RETURN_VALUE__EXIT_MENU );
    base_menu_.main_selections->add_text(
        " Quit Game",
        MENU_RETURN_VALUE__QUIT_GAME_REQUEST );

    active_window_stack_.push( base_menu_.main_selections );
    active_window_stack_.top()->contents()->activate();
}



void Menu::run( void )
{
	Console::current_interface( type() );

    reset();

    Interface* temp = NULL;

    for( ; !( exit_ || em_->quit() ); em_->process( this ) )
    {
        switch( goto_interface_ )
        {
        case INTERFACE_PAUSE:
            pause_screen_->run();
            goto_interface_ = type();
            break;
        case INTERFACE_CONFIRM_QUIT:
            base_menu_.main_selections->contents()->deactivate();
            __update();
            __render();
            temp = new Confirm_Quit( em_, window_, console_, renderer_ );
            ((Confirm_Quit*)temp)->run();
            delete temp;
            temp = NULL;
            goto_interface_ = type();
            base_menu_.main_selections->contents()->activate();
            break;
        default:
            ;
        }

        __update();
        __render();
    }
    window_->clear();
}



/**
*   Returns the type.
*/
inline Interface_enum_t Menu::type( void )
{
    return INTERFACE_MENU;
}



void Menu::add_state_machine_nodes( Pause* p, Item_Creation* ic , Load_Menu* slm )
{
    pause_screen_ = p;
    item_creation_screen_ = ic;
    save_load_screen_ = slm;
}



/**
*   Responds to player inputs.
*/
void Menu::do_controls( unsigned u )
{
    if( ctrl_previous_[ u ] && !ctrl_current_[ u ] )
    {
        switch( u )
        {
        case CTRL_B:
            exit_ = true;
            return;
        case CTRL_A:
            react( active_window_stack_.top()->command( CTRL_A ) );
            return;
        case CTRL_UP:
            active_window_stack_.top()->command( CTRL_UP );
            goto_interface_ = type();
            exit_ = false;
            return;
        case CTRL_DOWN:
            active_window_stack_.top()->command( CTRL_DOWN );
            goto_interface_ = type();
            exit_ = false;
            return;
        case CTRL_PAUSE:
        case CTRL_START:
            goto_interface_ = INTERFACE_PAUSE;
            exit_ = false;
            return;
        default:
            goto_interface_ = type();
            return;
        }
    }
}



void Menu::react( int menu_selection )
{
//    auto iter = open_windows_.begin();
    switch( menu_selection )
    {
    case MENU_RETURN_VALUE__QUIT_GAME_REQUEST:
        goto_interface_ = INTERFACE_CONFIRM_QUIT;
        break;
    case MENU_RETURN_VALUE__QUIT_GAME:
        em_->quit_game();
        return;
    case MENU_RETURN_VALUE__EXIT_MENU:
        exit_ = true;
        return;
    case MENU_RETURN_VALUE__EXIT_CURRENT_WINDOW:
/*
        while( *iter != active_window_stack_.top() )
        {
            ++iter;
        }
        *iter = NULL;
        open_windows_.erase( iter );
*/
        delete active_window_stack_.top();
        active_window_stack_.top() = NULL;
        active_window_stack_.pop();
        active_window_stack_.top()->contents()->activate();
        break;
    default:
        return;
    }
    ctrl_previous_[ CTRL_A ] = ctrl_current_[ CTRL_A ];
    ctrl_current_[ CTRL_A ] = false;
}



void Menu::reset( void )
{
//    open_windows_.clear();
    while( !active_window_stack_.empty() )
    {
        active_window_stack_.top() = NULL;
        active_window_stack_.pop();
    }
    active_window_stack_.push( base_menu_.main_selections );                    
    exit_ = false;
}



/**
*   Updates the internal status before rendering.
*/
void Menu::__update( void )
{
    base_menu_.funds_box->contents()->update();
    base_menu_.main_selections->contents()->update();
}



/**
*   Actually performs rendering.
*/
void Menu::__render( void )
{
    window_->clear();

    //render base menu
    base_menu_.funds_box->render();
    base_menu_.main_selections->render();

    //render additional windows.
    /*
    for( unsigned u = 0; u < open_windows_.size(); u++ )
    {
        open_windows_[ u ]->render();
    }
    */

    window_->update();
}
