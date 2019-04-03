

#include "stdafx.h"
#include<cassert>


/**
*    With the exception of a few systems that need to be initialized first,
*   this ctor is responsible for initializing all of the other systems in the
*   game and making the necessary connections between them (getting and
*   setting) various pointers.
*
*    It is also responsible for providing all the interfaces with everything
*   necessary for the state machine that runs behind the scenes in the game to
*   function correctly.
*/
Game::Game( Console* c, Window* w, Event_Manager* e ) :
    sdl_init_( SDL_INIT_TIMER ),
    console_( *c ),
    window_( *w ),
    events_( *e ),
    start_menu_( e, w, c ),
    combat_( e, w, c ),
    on_map_( e, w, c ),
    menu_( e, w, c ),
    creation_( e, w, c ),
    pause_( e, w, c ),
    over_( e, w, c ),
    save_load_( e, w, c )
{
	Lua_ = luaL_newstate();  //Init Lua.
	luaL_openlibs( Lua_ );

    renderer_ = window_.get_renderer();
    text_system_ = new Text;

    Interface::set_renderer( renderer_ );
    Sprite_Sheet::set_renderer( renderer_ );
    Screen_Texture::init( &window_ );

    interface_[ INTERFACE_PAUSE ] = &pause_;
    events_.register_interface( &pause_, INTERFACE_PAUSE );
    interface_[ INTERFACE_START_MENU ] = &start_menu_;
    events_.register_interface( &start_menu_, INTERFACE_START_MENU );           
    interface_[ INTERFACE_MAP ] = &on_map_;
    events_.register_interface( &on_map_, INTERFACE_MAP );
    interface_[ INTERFACE_COMBAT ] = &combat_;
    events_.register_interface( &combat_, INTERFACE_COMBAT );
    interface_[ INTERFACE_MENU ] = &menu_;
    events_.register_interface( &menu_, INTERFACE_MENU );
    interface_[ INTERFACE_ITEM ] = &creation_;
    events_.register_interface( &creation_, INTERFACE_ITEM );
    interface_[ INTERFACE_GAME_OVER ] = &over_;
    events_.register_interface( &over_, INTERFACE_GAME_OVER );
    interface_[ INTERFACE_LOAD_MENU ] = &save_load_;
    events_.register_interface( &save_load_,  INTERFACE_LOAD_MENU );

    //pause_.add_state_machine_nodes(); //Unnecessary
    start_menu_.add_state_machine_nodes( &save_load_ );
    on_map_.add_state_machine_nodes( &pause_, &combat_, &menu_, &creation_ );
    combat_.add_state_machine_nodes( &pause_, &on_map_, &over_ );
    menu_.add_state_machine_nodes( &pause_, &creation_, &save_load_ );
    creation_.add_state_machine_nodes( &pause_ );
    //over_.add_state_machine_nodes(); //Unnecessary
    //save_load_.add_state_machine_nodes(); //Unnecessary

    play_data_ = NULL;

    Interface::set_text( text_system_ );

    Box_Contents::init( text_system_ );

}



void Game::main_loop( void )
{
    window_.update();
    window_.clear();

    while( !events_.quit() )
    {
        start_menu_.run();
        switch( start_menu_.picked() )
        {
        case INTERFACE_NEW_GAME_SETUP:
            Console::vb_only_no_err(
                "Start_Screen",
                "Work-In-Progress." );
            newgame();
            //play_data_ = newgame.ge
            break;
        case INTERFACE_LOAD_MENU:
            Console::vb_only_no_err(
                "Start_Screen",
                "Continue not implemented." );
            break;
        case INTERFACE_SETTINGS:
            Console::vb_only_no_err( "Start_Screen", "Settings not implemented." );
            break;
        default:
            ;
        }
        if( play_data_ )
        {
            play_data_->debug_print();
            //Begin game.
        }
    }
}



void Game::newgame( void )
{
    New_Game_Creation ngc( &events_, &window_, &console_, &start_menu_ );
    ngc.run();
    play_data_ = ngc.get_game();
}



Game::~Game( void )
{
	/*
	//std::string cmd = "a = 6 * 3 + math.sin(5)";

	if ( check_lua( Lua_, luaL_dofile( Lua_, "Lua_Script.lua" ) ) )
	{
		lua_getglobal(Lua_, "a");
		if (lua_isnumber(Lua_, -1))
		{
			float acpp = (float)lua_tonumber(Lua_, -1);
			std::cout << "Lua says, \"6 * 3 + sin(5) is " << acpp << ".\"\n" << std::endl;
		}
	}
	*/


	// Shut Lua down.
	lua_close(Lua_);
	Lua_ = NULL;
}
