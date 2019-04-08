#pragma once

class Play_Data;

class Interface;
class Console;
class Window;
class Event_Manager;


enum Interface_enum_t;




class New_Game_Creation : public Interface
{
public:
    New_Game_Creation( Event_Manager*, Window*, Console*, Start_Screen* );

    Interface_enum_t type( void );

    void run( void );
    Play_Data* get_game( void );
	Interface_enum_t get_next( void );

    ~New_Game_Creation( void );

    friend class Event_Manager;

private:

    void do_controls( unsigned );
    void character_name( int* );

    Play_Data*   new_game_;
    
    SDL_Texture* background_;
    SDL_Rect     background_pos_;

	Interface_enum_t next_;
};