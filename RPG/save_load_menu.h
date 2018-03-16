#pragma once


class Play_Data;
class Interface;
class Window;
class Event_Manager;

enum Interface_t;



/**
*   The save and load screens.  This may need to be split into seperate
*  interfaces for saving and loading.
*/
class Save_Load_Menu : public Interface
{
public:
    Save_Load_Menu( Event_Manager*, Window*, Console* ); //Ctor.

    void run( void ); //Save menu loop.

    Interface_t type( void ); //Returns the type.

    friend class Event_Manager;

private:

    void do_controls( unsigned ); //Responds to user input.

    Interface_t next_;
};