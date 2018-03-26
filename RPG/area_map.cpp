

#include "stdafx.h"



/*static*/ unsigned Area_Map::unassigned_id_ = 0;



Area_Map::Area_Map( int layers, int width, int height ) :
    map_layers_( layers ), map_width_( width ), map_height_( height )
{
    id_ = unassigned_id_++;

    map_fg_ = new int**[ layers ];
    map_bg_ = new int*[ width ];

    for( int i = 0; i < layers; i++ )
    {
        map_fg_[ i ] = new int*[ width ];
        for( int j = 0; j < width; j++ )
        {
            map_fg_[ i ][ j ] = new int[ height ];
            map_bg_[ j ] = new int[ height ];
        }
    }
}



Area_Map::~Area_Map( void )
{
    for( int i = 0; i < map_layers_; i++ )
    {
        for( int j = 0; j < map_width_; j++ )
        {
            delete[] map_fg_[ i ][ j ];
        }
        delete[] map_fg_[ i ];
        delete[] map_bg_[ i ];
    }
    delete[] map_fg_;
    map_fg_ = NULL;
    delete[] map_bg_;
    map_bg_ = NULL;
}
