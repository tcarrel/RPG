#pragma once

class Console;
class Window;
class Event_Manager;
class Combat;
class Game_Map;
class Menu;
class Start_Screen;
class Pause;
class Item_Creation;
class Play_Data;

class Interface;

struct SDL_Renderer;
struct lua_State;


/**
*   Organizes, manages, and initializes the game's interfaces and various
*  other components.
*/
class Game
{
public:
    Game( Console*, Window*, Event_Manager* ); //Ctor.

    void main_loop( void ); //The game loop.

    ~Game( void ); //Dtor.

private:
    void newgame( void );

    Start_SDL      sdl_init_;

	lua_State*     Lua_;

    Console&       console_;
    Window&        window_;
    Event_Manager& events_;

    Start_Screen   start_menu_;
    Combat         combat_;
    Game_Map       on_map_;
    Menu           menu_;
    Item_Creation  creation_;
    Game_Over      over_;
    Pause          pause_;
    Load_Menu save_load_;
    
    Interface*     interface_[ ALL_INTERFACES ];

    Play_Data*     play_data_;

    SDL_Renderer*  renderer_;
    Text*          text_system_;

    Interface_enum_t current_interface_;
};