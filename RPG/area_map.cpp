

#include "stdafx.h"



/*static*/ unsigned Area_Map::unassigned_id_ = 0;
/*static*/ const int Area_Map::MAX_VERTICAL  = 512;
/*static*/ const int Area_Map::MAX_HORIZONAL = 512;
/*static*/ const int Area_Map::MAX_HEIGHT    = 4;



Area_Map::Area_Map(std::string& filename)
{
	std::ifstream map(filename.c_str());
	Random R;

	int name_length;
	map >> name_length;

	std::string tile_sheet;
	map >> tile_sheet;
	sheet_ = new Sprite_Sheet;
	sheet_->load(tile_sheet.c_str());
	int index = 0;
	for (int x = 0; x < (TILE_WIDTH * 16); x = x + 16)
	{
		for (int y = 0; y < (TILE_HEIGHT * 16); y = y + 16)
		{
			tiles_[index].set( x, y, TILE_WIDTH, TILE_HEIGHT, sheet_ );
			++index;
		}
	}

	char* name = new char[name_length + 1];
	name[name_length] = 0;
	map.get( name, name_length );
	map >> horizontal_size_ >> vertical_size_ >> height_;

	bg_ = new int**[height_];
	for (int layer = 0; layer < height_; layer++)
	{
		bg_[layer] = new int*[horizontal_size_];
		for (int x = 0; x < horizontal_size_; x++)
		{
			bg_[layer][x] = new int[vertical_size_];
			for (int y = 0; y < vertical_size_; y++)
			{
				char tile = 0;
				map.get(tile);

				if (tile = ' ')
				{
					tile = R.get(0, 1);
				}
				else
				{
					tile = tile - '0' - 1;
				}

				bg_[layer][x][y] = tile;
			}
		}
	}
}



/*
int Area_Map::setup(
    int layers,
    int width,
    int height,
    const Uint8_t_String& name )
    //height_( layers ), horizontal_size_( width ), vertical_size_( height ), name_(name)
{
	height_ = layers;
	horizontal_size_ = width;
	vertical_size_ = height_;
	name_ = name;

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
*/



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
