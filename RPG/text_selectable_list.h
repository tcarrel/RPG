#pragma once

#include<vector>
using std::vector;

#include "text_line.h"
#include "box_contents.h"





/**
*   A text box contents type that displays options that the player can choose
*  from in a vertical list.
*/
class Selectable_List : public Box_Contents
{
public:
    Selectable_List( unsigned = 1 );

    void activate( void );
    void deactivate( void );

    void add_text( const char[], int );
    void add_text( const string&, int );
    void add_text( const Uint8_t_String&, int );

    void set_btn_rv( int, int );

    void update( void* = NULL, const unsigned& = 0 );
    int command( Control_enum_t );
    Box_Contents_enum_t type( void );
    ~Selectable_List( void );

private:

    void update_text( void );
    void down( void );
    void up( void );

    unsigned               spacing_;
    unsigned               selected_;
    bool                   active_;

    vector<Line_of_Text*>  selection_;
    vector<int>            return_values_;
    
    int                    cancel_btn_return_val_;
    int                    start_btn_return_val_;
};