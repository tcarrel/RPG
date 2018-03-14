
#include "stdafx.h"



/**
*   Ctor.
*/
Event_Manager::Event_Manager( Console* c ) :
    console_( c ),
    ev_mgr_init_( SDL_INIT_EVENTS ),
    quit_( false ),
    current_ixs_( INTERFACE_START_MENU ),
    gamepad_( NULL )
{
    for( unsigned i = 0; i < ALL_INTERFACES; i++ )
    {
        ixs_[ i ] = NULL;
    }

    if( !ev_mgr_init_.good() )
    {
        quit_ = true;
        ev_mgr_init_.show_errors();
    }

    if( !ev_mgr_init_.init( SDL_INIT_GAMECONTROLLER ) )
    {
        quit_ = true;
        ev_mgr_init_.show_errors();
    }

    for( unsigned i = 0; i < ALL_CTRL; i++ )
    {
        *( ctrl_ + i ) = false;
    }

    //Setup gamepad, if connected.
    int controller_qty = SDL_NumJoysticks();
    console_->vb_variable_value( "Event_Manager", "controller_qty", controller_qty );

    if( controller_qty < 0 )
    {
        console_->error( "SDL2 (Gamepad)", "Gamepad enumeration error.", SDL_GetError() );
    }

    if( controller_qty > 0 )
    {
        load_mappings();
    }

    for( int i = 0; i < controller_qty; i++ )
    {
        if( !SDL_IsGameController( i ) )
        {
            gamepad_ = SDL_JoystickOpen( i );
            console_->no_error(
                "Event_Manager",
                "Joystick attached.",
                "Joystick attached: " + string( SDL_JoystickName( gamepad_ ) ) );
            break;
        }
        else
        {
            gamepad_ = SDL_GameControllerGetJoystick( SDL_GameControllerOpen( i ) );
            console_->vb_variable_value( "Event_Manager", "gamepad_", gamepad_ );            
            console_->no_error(
                "Event_Manager",
                "Controller attached.",
                "Controller Attached: " + string( SDL_JoystickName( gamepad_ ) ) );
            break;
        }
    }

    if( gamepad_ )
    {
        SDL_JoystickGUID guid = SDL_JoystickGetGUID( gamepad_ );
        char pszGUID[ 34 ];
        SDL_JoystickGetGUIDString( guid, pszGUID, 34 );
        console_->vb_only_no_err( "SDL2/Joystick", "GUID: " + string( pszGUID ) );
    }


    for( int i = 0; i < ALL_JOYS; i++ )
    {
        joy_to_ctrl[ i ] = CTRL_NULL;
    }
    for( int i = 0; i < ALL_KEYS; i++ )
    {
        key_to_ctrl[ i ] = CTRL_NULL;
    }

    joy_to_ctrl[ JOY_A_BUTTON ] = CTRL_A;
    joy_to_ctrl[ JOY_B_BUTTON ] = CTRL_B;
    joy_to_ctrl[ JOY_X_BUTTON ] = CTRL_X;
    joy_to_ctrl[ JOY_Y_BUTTON ] = CTRL_Y;
    joy_to_ctrl[ JOY_UP ]       = CTRL_UP;
    joy_to_ctrl[ JOY_DOWN ]     = CTRL_DOWN;
    joy_to_ctrl[ JOY_LEFT ]     = CTRL_LEFT;
    joy_to_ctrl[ JOY_RIGHT ]    = CTRL_RIGHT;
    joy_to_ctrl[ JOY_START ]    = CTRL_START;
    joy_to_ctrl[ JOY_SELECT ]   = CTRL_SELECT;
    joy_to_ctrl[ JOY_L_BUTTON ] = CTRL_L;
    joy_to_ctrl[ JOY_R_BUTTON ] = CTRL_R;

    SDL_RWops* file = SDL_RWFromFile(
        KEYBOARD_MAPPING_SETTINGS_FILE_PATH,
        "rb" );
    if( !file )
    {
        // File does not exist, set default keyboard mapping and write to file.
        key_to_ctrl[ SDL_SCANCODE_UP ]    = CTRL_UP;
        key_to_ctrl[ SDL_SCANCODE_DOWN ]  = CTRL_DOWN;
        key_to_ctrl[ SDL_SCANCODE_LEFT ]  = CTRL_LEFT;
        key_to_ctrl[ SDL_SCANCODE_RIGHT ] = CTRL_RIGHT;

        key_to_ctrl[ SDL_SCANCODE_V ] = CTRL_A;
        key_to_ctrl[ SDL_SCANCODE_C ] = CTRL_B;
        key_to_ctrl[ SDL_SCANCODE_D ] = CTRL_X;
        key_to_ctrl[ SDL_SCANCODE_X ] = CTRL_Y;
        key_to_ctrl[ SDL_SCANCODE_A ] = CTRL_L;
        key_to_ctrl[ SDL_SCANCODE_S ] = CTRL_R;

        key_to_ctrl[ SDL_SCANCODE_RETURN ]  = CTRL_START;
        key_to_ctrl[ SDL_SCANCODE_RETURN2 ] = CTRL_START;

        key_to_ctrl[ SDL_SCANCODE_KP_SPACE ] = CTRL_SELECT;
        key_to_ctrl[ SDL_SCANCODE_SPACE ]    = CTRL_SELECT;

        key_to_ctrl[ SDL_SCANCODE_ESCAPE ] = CTRL_START;

        key_to_ctrl[ SDL_SCANCODE_RALT ]  = CTRL_ALT;
        key_to_ctrl[ SDL_SCANCODE_LALT ]  = CTRL_ALT;
        key_to_ctrl[ SDL_SCANCODE_F4 ]    = CTRL_F4;
        key_to_ctrl[ SDL_SCANCODE_PAUSE ] = CTRL_START;

        console_->vb_only_no_err(
            "SDL/RW",
            "No saved keyboard mapping exists, " 
            "using default and\n\t\t\tsaving to file." );
        file = SDL_RWFromFile( "keyboard.mapping.bin", "wb" );
        SDL_RWwrite( file, key_to_ctrl, sizeof( int ), ALL_KEYS );
    }
    else
    {
        console_->vb_only_no_err( "SDL/RW", "Loading keyboard mapping from file." );
        SDL_RWread( file, key_to_ctrl, sizeof( int ), ALL_KEYS );
    }
    SDL_RWclose( file );
    file = NULL;

}



/**
*   Polls the event manager.
*/
void Event_Manager::operator()( void )
{
    process();
}



/**
*   Polls the event manager.
*/
inline void Event_Manager::process( void )
{
    while( SDL_PollEvent( &e_ ) )
    {
        switch( e_.type )
        {
        case SDL_QUIT:
            quit_ = 1;
            break;
        case SDL_KEYDOWN:
            if( e_.key.keysym.scancode == SDL_SCANCODE_F4 )
            {
                if( ctrl_[ CTRL_ALT ] )
                {
                    quit_ = true;
                }
            }
            key_down( e_.key.keysym.scancode );
            break;
        case SDL_KEYUP:
            key_up( e_.key.keysym.scancode );
            break;
        case SDL_JOYBUTTONDOWN:
            joy_down( e_.jbutton.button );
            printf( "Button down: %i\n", e_.jbutton.button );
            break;
        case SDL_JOYBUTTONUP:
            joy_up( e_.jbutton.button );
            printf( "Button up  : %i\n", e_.jbutton.button );
            break;
        case SDL_JOYAXISMOTION:
            joy_axis( e_.jaxis.axis, e_.jaxis.value );
            break;
        default:
            ;
        }
    }
}



/**
*  Quit the game.
*/
const bool& Event_Manager::quit( void )
{
    return quit_;
}



/**
*   Connects the various game interfaces.
*/
bool Event_Manager::register_interface( Interface* ix, unsigned ixe )
{
    if( !ix )
    {
        return false;
    }

    switch( ixe )
    {
    case INTERFACE_START_MENU:
        ixs_[ INTERFACE_START_MENU ] = (Main_Menu*)ix;
        ixs_[ INTERFACE_START_MENU ]->register_ctrl( ctrl_ );
        console_->vb_only_no_err(
            "Event_Manager",
            "Start menu interface, registered." );
        console_->vb_variable_value(
            "Event_Manager",
            "ixs_[ INTERFACE_START_MENU ]",
            ixs_[ INTERFACE_START_MENU ] );
        break;
    case INTERFACE_MAP:
        ixs_[ INTERFACE_MAP ] = (Game_Map*)ix;
        ixs_[ INTERFACE_MAP ]->register_ctrl( ctrl_ );
        console_->vb_only_no_err(
            "Event_Manager",
            "On-Map interface, registered." );
        console_->vb_variable_value(
            "Event_Manager",
            "ixs_[ INTERFACE_MAP ]",
            ixs_[ INTERFACE_MAP ] );
        break;
    case INTERFACE_MENU:
        ixs_[ INTERFACE_MENU ] = (Menu*)ix;
        ixs_[ INTERFACE_MENU ]->register_ctrl( ctrl_ );
        console_->vb_only_no_err(
            "Event_Manager",
            "In-game menu interface, registered." );
        console_->vb_variable_value(
            "Event_Manager",
            "ixs_[ INTERFACE_MENU ]",
            ixs_[ INTERFACE_MENU ] );
        break;
    case INTERFACE_COMBAT:
        ixs_[ INTERFACE_COMBAT ] = (Combat*)ix;
        ixs_[ INTERFACE_COMBAT ]->register_ctrl( ctrl_ );
        console_->vb_only_no_err(
            "Event_Manager",
            "Combat interface, registered." );
        console_->vb_variable_value(
            "Event_Manager",
            "ixs_[ INTERFACE_COMBAT ]",
            ixs_[ INTERFACE_COMBAT ] );
        break;
    case INTERFACE_PAUSE:
        ixs_[ INTERFACE_PAUSE ] = (Pause*)ix;
        ixs_[ INTERFACE_PAUSE ]->register_ctrl( ctrl_ );
        console_->vb_only_no_err(
            "Event_Manager",
            "Pause screen interface, registered." );
        console_->vb_variable_value(
            "Event_Manager",
            "ixs_[ INTERFACE_PAUSE ]",
            ixs_[ INTERFACE_PAUSE ] );
        break;
    case INTERFACE_SAVE_LOAD_MENU:
        ixs_[ INTERFACE_SAVE_LOAD_MENU ] = (Save_Load_Menu*)ix;
        ixs_[ INTERFACE_SAVE_LOAD_MENU ]->register_ctrl( ctrl_ );
        console_->vb_only_no_err(
            "Event_Manager",
            "Save/Load interface, registered." );
        console_->vb_variable_value(
            "Event_Manager",
            "ixs_[ INTERFACE_SAVE_LOAD_MENU ]",
            ixs_[ INTERFACE_SAVE_LOAD_MENU ] );
        break;
    case INTERFACE_ITEM:
        ixs_[ INTERFACE_ITEM ] = (Item_Creation*)ix;
        ixs_[ INTERFACE_ITEM ]->register_ctrl( ctrl_ );
        console_->vb_only_no_err(
            "Event_Manager",
            "Item creation interface, registered." );
        console_->vb_variable_value(
            "Event_Manager",
            "ixs_[ INTERFACE_ITEM ]",
            ixs_[ INTERFACE_ITEM ] );
        break;
    case INTERFACE_GAME_OVER:
        ixs_[ INTERFACE_GAME_OVER ] = (Game_Over*)ix;
        ixs_[ INTERFACE_GAME_OVER ]->register_ctrl( ctrl_ );
        console_->vb_only_no_err(
            "Event_Manager",
            "\"Game Over\" screen interface, registered." );
        console_->vb_variable_value(
            "Event_Manager",
            "ixs_[ INTERFACE_GAME_OVER ]",
            ixs_[ INTERFACE_GAME_OVER ] );
        break;
    default:
        return false;
    }

    all_registered();
    return true;
}



/**
*   Dtor.
*/
Event_Manager::~Event_Manager( void )
{
    if( console_ )
    {
        //  In the case of this class, the console i/f must be passed in and 
        // we should leave it to the location that passed it in to delete it.
        console_ = NULL;
    }

    if( gamepad_ )
    {
        SDL_JoystickClose( gamepad_ );
        gamepad_ = NULL;
    }
}



/**
*   Loads controller mappings.
*/
void Event_Manager::load_mappings( void )
{
    int qty = SDL_GameControllerAddMappingsFromRW(
        SDL_RWFromFile(
            GAME_CONTROLLER_MAPPING_DATABASE_FILE_PATH,
            "rb" ),
        1 );

    if( qty < 0 )
    {
        console_->error(
            "SDL2/GameController",
            "Could not load mappings.", SDL_GetError() );
    }
    else
    {
        char text[ 64 ];
        snprintf( text, 64, "Loaded %i mappings.", qty );
        console_->vb_only_no_err( "SDL2/GameControiler", text );
    }
}



/**
*   Keyboard button down events.
*/
void Event_Manager::key_down( SDL_Scancode i )
{
    ctrl_[ key_to_ctrl[ i ] ] = true;
}



/**
*   Keyboard button up events.
*/
void Event_Manager::key_up( SDL_Scancode i )
{
    ctrl_[ key_to_ctrl[ i ] ] = false;
} 



/**
*   Joystick and gamepad button down events.
*/
void Event_Manager::joy_down( int i )
{
    ctrl_[ joy_to_ctrl[ i ] ] = true;
}



/**
*   Joystick and gamepad button up events.
*/
void Event_Manager::joy_up( int i )
{
    ctrl_[ joy_to_ctrl[ i ] ] = false;
}



/**
*   Joystick and gamepad axis movement events.
*/
void Event_Manager::joy_axis( Uint8 axis, Sint16 v )
{
    signed char value;
    if( JOY_DEAD_ZONE < v  )
    {
        value = 1;
    }
    else if( -JOY_DEAD_ZONE <= v && v < JOY_DEAD_ZONE )
    {
        value = 0;
    }
    else
    {
        value = -1;
    }


    switch( axis )
    {
    default:
        break;
    case 0:  // LEFT and RIGHT
        switch( value )
        {
        default:
            break;
        case 1: //Right
            printf( "Axis 0, right   (%i)\n", v );
            joy_down( JOY_RIGHT );
            break;
        case 0: //Neutral
            joy_up( JOY_LEFT );
            joy_up( JOY_RIGHT );
            break;
        case -1: //Left
            printf( "Axis 0, left    (%i)\n", v );
            joy_down( JOY_LEFT );
        }
        break;
    case 1:   // UP and DOWN
        switch( value )
        {
        default:
            break;
        case 1: //Down
            printf( "Axis 1, down    (%i)\n", v );
            joy_down( JOY_DOWN );
            break;
        case 0: //Neutral
            joy_up( JOY_UP );
            joy_up( JOY_DOWN );
            break;
        case -1: //Up
            printf( "Axis 1, up      (%i)\n", v );
            joy_down( JOY_UP );
        }
    }

}



/**
*   Tests if all game interfaces have been registered.
*/
void Event_Manager::all_registered( void )
{
    bool all = true;
    for( unsigned i = 0; i < ALL_INTERFACES; i++ )
    { 
        all = ( ixs_[ i ] != NULL ) && all;
    }

    if( all )
    {
        console_->vb_only_no_err( "Event_Manager", "All interfaces registered." );
    }
}
