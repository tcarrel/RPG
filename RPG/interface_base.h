#pragma once

class Console;
class Window;
class Event_Manager;

enum Interface_t;



class Interface
{
public:

    Interface( Event_Manager*, Console*, Window*, Interface_t );

    static void set_renderer( SDL_Renderer* ); //Sets the renderer.

    virtual void run( void ) = 0; //For supplying the necessary loop

    virtual void set_source( Interface_t );
    void register_ctrl( bool*, bool* ); //Connects the input registers.
    virtual Interface_t type( void ); //Returns the type.

    ~Interface( void ); //Dtor.

    friend class Event_Manager;
protected:

    virtual void do_controls( unsigned ) = 0;

    static SDL_Renderer* renderer_;

    Console* console_;
    bool* ctrl_current_;
    bool* ctrl_previous_;
    Interface_t came_from_;

    Event_Manager* em_;
    Window* window_;

    bool exit_;
    static bool goto_start_menu_;


private:

    Interface() {}
};