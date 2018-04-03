

#include "stdafx.h"



/*static*/ unsigned Area_Map::unassigned_id_ = 0;
/*static*/ const int Area_Map::MAX_VERTICAL  = 512;
/*static*/ const int Area_Map::MAX_HORIZONAL = 512;
/*static*/ const int Area_Map::MAX_HEIGHT    = 4;



Area_Map::Area_Map(
    int layers,
    int width,
    int height,
    const Uint8_t_String& name ) :
    height_( layers ), horizontal_size_( width ), vertical_size_( height ), name_(name)
{
    id_ = unassigned_id_++;

    bg_ = new int**[ layers ];
    fg_ = new int*[ width ];

    for( int i = 0; i < layers; i++ )
    {
        bg_[ i ] = new int*[ width ];
        for( int j = 0; j < width; j++ )
        {
            bg_[ i ][ j ] = new int[ height ];
            fg_[ j ] = new int[ height ];
        }
    }
}



const Uint8_t_String & Area_Map::get_name( void )
{
    return name_;
}



Area_Map::~Area_Map( void )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < horizontal_size_; j++ )
        {
            delete[] bg_[ i ][ j ];
        }
        delete[] fg_[ i ];
        delete[] bg_[ i ];
    }
    delete[] fg_;
    fg_ = NULL;
    delete[] bg_;
    bg_ = NULL;
}
