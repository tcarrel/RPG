

#include "stdafx.h"




New_Game_Creation::New_Game_Creation(
    Event_Manager* e,
    Window* w,
    Console* c,
    Start_Screen* s ) :
    Interface( e, c, w, INTERFACE_NEW_GAME_SETUP ),
    new_game_( new Play_Data ),
	next_(INTERFACE_START_MENU)
{
    s->bg_image( background_, background_pos_ );
}



Interface_enum_t New_Game_Creation::type( void )
{
    return INTERFACE_NEW_GAME_SETUP;
}



Interface_enum_t New_Game_Creation::get_next( void )
{
	return next_;
}



void New_Game_Creation::run( void )
{
	Console::current_interface( type() );

    exit_ = false;

    int step = 1;
	char* curr_map = "map01.lvl";

    for( ; !( exit_ || em_->quit() ); em_->process( this ) )
    {
        switch( step )
        {
        case 1:
			next_ = INTERFACE_START_MENU;
            character_name( &step );
			Console::current_interface( type() );
			
			printf("XXXXXXXXXXXXXXXXXXXXX  %i  XXXXXXXXXXXXXXXXX\n", step );

            break;
		case 2:
			Console::current_interface( type() );

			step = 3;
			break;
		case 3:
			new_game_->set_char_position( 5, 5 );
			step = 4;
			break;
		case 4:
			exit_ = true;
			next_ = INTERFACE_MAP;
			break;
        case 5:
			printf( "999999999999999999999999999999999999999999\n");
			next_ = INTERFACE_START_MENU;
            exit_ = true;
            //TODO: maybe.
            break;
        default:
            exit_ = true;
        }
    }
}



Play_Data* New_Game_Creation::get_game( void )
{
    return new_game_;
}



New_Game_Creation::~New_Game_Creation( void )
{
    new_game_ = NULL;
    background_ = NULL;
}



void New_Game_Creation::do_controls( unsigned u )
{

    switch( u )
    {
    case CTRL_B:
        exit_ = true;
        break;
    default:
        break;
    }

}



void New_Game_Creation::character_name( int* step )
{
    new_game_->set_main_char_name( Name_Character(
        em_,
        window_,
        console_,
        background_,
        background_pos_,
        step,
        true ) );
}
