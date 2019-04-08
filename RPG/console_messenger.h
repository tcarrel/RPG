#pragma once

#include<SDL.h>
#include<string>

class Uint8_t_String;
struct Line_of_Text;

using std::string;



/**
*   For outputing messages to the console.
*/
class Console
{
public:
    Console( void ); //Ctor
    Console( bool ); //Ctor, sets verbose_.
    static void error( string, string, string ); //Error message.
    static void no_error( string, string, string ); //Non-error message.

    static void vb_only_no_err( string, string );

    /**
    *   These functions all do nothing in the release version but can provide
    *  useful information for debugging.
    */
    static void vb_variable_value( string, string, bool );
    static void vb_variable_value( string, string, unsigned );
    static void vb_variable_value( string, string, int );
    static void vb_variable_value( string, string, float );
    static void vb_variable_value( string, string, Uint8_t_String& );
    static void vb_variable_value( string, string, Line_of_Text& );
    static void vb_variable_value( string, string, void* );
    static void vb_variable_value( string, string, SDL_Rect& );
	static void vb_variable_value( string, string, string& );
	static void current_interface( int );
    
    static void video_info( const SDL_DisplayMode& );

    static const bool& verbose( void );

private:
    
    static void vb_variable_value( string, string&, string&, char* );
    static void hline( void );

    static bool verbose_;
    static bool first_;
#ifdef _DEBUG
    static bool val_previous_;
#endif

    static unsigned message_num_;
};