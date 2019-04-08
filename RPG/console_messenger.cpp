

#include "stdafx.h"



/*static*/ bool Console::verbose_   = false;
/*static*/ bool Console::first_     = true;
/*static*/ unsigned Console::message_num_ = 1;
#ifdef _DEBUG
/*static*/ bool Console::val_previous_ = false;
#endif


Console::Console( void )
{
    if( first_ )
    {
        printf( ".\n" );
        first_ = false;
    }
}


/**
*   Can, optionally, activate a verbose output more for sending messages to the
*  console.
*/
Console::Console( bool v ) : Console()
{
    verbose_ = v;
    no_error( "Console", "Verbose:\tno", "Verbose:\tyes" );
}



/**
*   Sends an error message to the console.
*/
/*static*/ void Console::error( string source, string shrt_msg, string long_msg )
{
#ifdef _DEBUG
    if( val_previous_ )
    {
        hline();
        val_previous_ = false;
    }
#endif
//    fprintf( stderr, "\033[1;33m" );
    fprintf( stderr, "\n%s\n", string( 80, 'X' ).c_str() );
    fprintf(
        stderr,
        "(%u)\n"
        "X\tMessage:\n"
        "X\t\tSource\t%s\n"
        "X\t\tError\tyes\n"
        "X\t\t\t%s\n",
        message_num_++,
        source.c_str(),
        (verbose_ ? long_msg : shrt_msg).c_str()
    );
    fprintf( stderr, "%s\n", string( 80, 'X' ).c_str() );
    hline();

    //fprintf( stderr, "\033[0m" );
}



/*static*/ void Console::no_error( string source, string shrt_msg, string long_msg )
{
#ifdef _DEBUG
    if( val_previous_ )
    {
        hline();
        val_previous_ = false;
    }
#endif

    printf(
        "(%u)\n"
        "\tMessage:\n"
        "\t\tSource\t%s\n"
        "\t\tError\tno\n"
        "\t\t\t%s\n",
        message_num_++,
        source.c_str(),
        ( verbose_ ? long_msg : shrt_msg ).c_str()
    );
    hline();
}



/*static*/ void Console::vb_only_no_err( string source, string msg )
{
    if( !verbose_ )
    {
        return;
    }

#ifdef _DEBUG
    if( val_previous_ )
    {
        hline();
        val_previous_ = false;
    }
#endif

    printf(
        "(%u)\n"
        "\tMessage:\n"
        "\t\tSource\t%s\n"
        "\t\tError\tno\n"
        "\t\t\t%s\n",
        message_num_++,
        source.c_str(),
        msg.c_str()
    );
    hline();
}



//*static*/ void Console::vb_variable_value( string type, string& o, string& v, char* c )
#ifdef _DEBUG
void Console::vb_variable_value( string object, string var, bool value)
{
    if( !verbose_ )
    {
        return;
    }

	if( !val_previous_ )
	{
		printf( "(%u)\n\tVariable Values:\n", message_num_++ );
		val_previous_ = true;
	}

    vb_variable_value( "bool", object, var, value ? "true" : "false" );
}



/*static*/ void Console::vb_variable_value( string object, string var, unsigned value)
{
    if( !verbose_ )
    {
        return;
    }

	if( !val_previous_ )
	{
		printf( "(%u)\n\tVariable Values:\n", message_num_++ );
		val_previous_ = true;
	}

    char str[ 33 ];
    snprintf( str, 33, "%u // 0x%x", value, value );
    vb_variable_value( "unsigned", object, var, str );
}



/*static*/ void Console::vb_variable_value( string object, string var, int value )
{
    if( !verbose_ )
    {
        return;
    }

	if( !val_previous_ )
	{
		printf( "(%u)\n\tVariable Values:\n", message_num_++ );
		val_previous_ = true;
	}

    char str[ 33 ];
    snprintf( str, 33, "%i // 0x%x", value, value );
    vb_variable_value( "int", object, var, str );
}




/*static*/ void Console::vb_variable_value( string object, string var, void* addr )
{
    if( !verbose_ )
    {
        return;
    }

    if( !val_previous_ )
    {
        printf( "(%u)\n\tVariable Values:\n", message_num_++ );
        val_previous_ = true;
    }

    printf(
        "\t      \tpointer %s::%s = 0x%p\n",
        object.c_str(), var.c_str(), addr );
}



/*static*/ void Console::vb_variable_value( string object, string var, float val )
{
    if( !verbose_ )
    {
        return;
    }

	if( !val_previous_ )
	{
		printf( "(%u)\n\tVariable Values:\n", message_num_++ );
		val_previous_ = true;
	}

    char str[ 33 ];
    snprintf( str, 33, "%f // 0x%x", val, *(int*)&val );
    vb_variable_value( "int", object, var, str );
}


/*static*/ void Console::vb_variable_value(
    string object,
    string var,
    Uint8_t_String& str )
{
    if( !verbose_ )
    {
        return;
    }

	if( !val_previous_ )
	{
		printf( "(%u)\n\tVariable Values:\n", message_num_++ );
		val_previous_ = true;
	}

    printf( "\t      \tUint8_t_String %s::%s = %s\n",
            object.c_str(),
            var.c_str(),
            str.c_str() );
}



/*static*/ void Console::vb_variable_value(
	string object,
	string var,
	string& str )
{
	if( !verbose )
	{
		return;
	}

	if( !val_previous_ )
	{
		printf( "(%u)\n\tVariable Values:\n", message_num_++ );
		val_previous_ = true;
	}

	printf( "\t      \tstd::string %s::%s = %s\n",
		object.c_str(),
		var.c_str(),
		str.c_str() );
}



void Console::vb_variable_value( string obj, string name, Line_of_Text& line )
{
    if( !verbose_ )
    {
        return;
    }

    if( !val_previous_ )
    {
        printf( "(%u)\n\tVariable Values:\n", message_num_++ );
        val_previous_ = true;
    }

    printf( "\t      \tLine_of_Text %s::%s {\n", obj.c_str(), name.c_str() );
    printf( "\t      \t\taddr        = 0x%p\n", &line );
    printf( "\t      \t\ttext        = %s\n", line.text.c_str() );
    printf( "\t      \t\ttext.size() = %i\n", line.text.size() );
    printf( "\t      \t\tx           = %i\n", line.x );
    printf( "\t      \t\ty           = %i\n", line.y );
    printf( "\t      \t\thl          = " );

    switch( line.hl )
    {
    case TEXT_HIGHLIGHT_TYPE_BRIGHT:
        printf( "TEXT_HIGHLIGHT_TYPE_BRIGHT }\n" );
        break;
    case TEXT_HIGHLIGHT_TYPE_GRAYED:
        printf( "TEXT_HIGHLIGHT_TYPE_GRAYED }\n" );
        break;
    case TEXT_HIGHLIGHT_TYPE_NORMAL:
        printf( "TEXT_HIGHLIGHT_TYPE_NORMAL }\n" );
    default:
        break;
    }
}



/*static*/ void Console::vb_variable_value( string object, string name, SDL_Rect& rect)
{
    if( !verbose_ )
    {
        return;
    }

    if( !val_previous_ )
    {
        printf( "(%u)\n\tVariable Values:\n", message_num_++ );
        val_previous_ = true;
    }

    printf( "\t      \tSDL_Rect %s::%s {\n", object.c_str(), name.c_str() );
    printf( "\t      \t\tx = %i\n", rect.x );
    printf( "\t      \t\ty = %i\n", rect.y );
    printf( "\t      \t\tw = %i\n", rect.w );
    printf( "\t      \t\th = %i }\n", rect.h );
}



/*static*/ void Console::vb_variable_value( string type, string& o, string& v, char* c )
{
    if( !val_previous_ )
    {
        printf( "(%u)\n\tVariable Values:\n", message_num_++ );
        val_previous_ = true;
    }
    printf(
        "\t      \t%s %s::%s = %s\n",
        type.c_str(), o.c_str(), v.c_str(), c );
}



/*static*/ void Console::current_interface( int ix )
{
	if( !verbose_ )
	{
		return;
	}

#ifdef _DEBUG
	if( val_previous_ )
	{
		hline();
		val_previous_ = false;
	}
#endif
	printf(
		"(%u)\n"
		"\tMessage: CURRENT INTERFACE\n",
		message_num_++
	);

	printf("\t      \t");
	switch( ix )
	{
		case INTERFACE_START_MENU:
			printf("Start Menu");
			break;
		case INTERFACE_MAP:
			printf("Map");
			break;
		case INTERFACE_PAUSE:
			printf("Pause");
			break;
		case INTERFACE_COMBAT:
			printf("Combat");
		case INTERFACE_MENU:
			printf("Menu Screen");
			break;
		case INTERFACE_ITEM:
			printf("Shopping");
			break;
		case INTERFACE_GAME_OVER:
			printf("Game Over Screen");
			break;
		case INTERFACE_LOAD_MENU:
			printf("Load Game");
			break;
		case INTERFACE_SAVE_MENU:
			printf("Save Game");
			break;
		case INTERFACE_SETTINGS:
			printf("Game Setttings");
			break;
		case INTERFACE_NEW_GAME_SETUP:
			printf("New Game");
			break;
		case INTERFACE_CONFIRM_QUIT:
			printf("Quit?");
			break;
		case INTERFACE_CHARACTER_NAMING:
			printf("Name Character");
			break;
		default:
			printf("Unknown Interface");
	}
	printf( "\n\n" );
	hline();
}
#else

/*static*/ void Console::vb_variable_value( string, string, bool ) {}
/*static*/ void Console::vb_variable_value( string, string, unsigned ) {}
/*static*/ void Console::vb_variable_value( string, string, int ) {}
/*static*/ void Console::vb_variable_value( string, string, float ) {}
/*static*/ void Console::vb_variable_value( string, string, Uint8_t_String& ) {}
/*static*/ void Console::vb_variable_value( string, string, SDL_Rect& ) {}
/*static*/ void Console::vb_variable_value( string, string, void* ) {}
/*static*/ void Console::vb_variable_value( string, string&, string&, char* ) {}
/*static*/ void Console::vb_variable_value( string, string, string& ) {}
#endif



/**
*   Displays video mode info.
*/
/*static*/ void Console::video_info( const SDL_DisplayMode& mode )
{
    if( !verbose_ )
    {
        return;
    }

#ifdef _DEBUG
    if( val_previous_ )
    {
        hline();
        val_previous_ = false;
    }
#endif

    char msg[ 1024 ];
    snprintf( msg, 1024,
              "+===================+===========================+\n"
              "\t\t\t| Resolution        | %dx%d\t\t\t|\n"
              "\t\t\t| BPP               | %d\t\t\t|\n"
              "\t\t\t| Format            | %d\t\t\t|\n"
              "\t\t\t| Pixel Format Name | %s\t|\n"
              "\t\t\t+===================+===========================+\n\n",
              mode.w, mode.h, SDL_BITSPERPIXEL( mode.format ), mode.format,
              SDL_GetPixelFormatName( mode.format ) );

    no_error( "SDL2", msg, msg );
}



const bool& Console::verbose( void )
{
    return verbose_;
}



/*static*/ void Console::hline( void )
{
    for( unsigned i = 0; i < 80; i++ )
    {
        printf( "=" );
    }
    printf( "\n" );
}

