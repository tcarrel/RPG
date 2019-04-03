// RPG.cpp : Defines the entry point for the console application.
//


#include<iostream>
#include "stdafx.h"

//#include "lua_.h"

using namespace std;

#undef main
/**
*   Entry point.
*/
int main( int argc, char* argv[] )
{

    bool verbose = false;
    if( argc > 1 )
    {
        for( int arg = 1; arg < argc; arg++ )
        {
            if( !strncmp( argv[ arg ], "-verbose", 8 ) )
            {
                verbose = true;
            }
        }
    }

	Console console( verbose );
    Window window;
    Event_Manager em( verbose ? &console : NULL );
    Game game( &console, &window, &em );

    game.main_loop();

    return 0;
}

