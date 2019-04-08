#pragma once




/**
*    Resposible for store all gameplay data and some functions for allow this
*   data to be adjusted as necessary.
*/
class Play_Data
{
public:
    Play_Data( void );

    unsigned* money_addr( void );
    void      money_add( unsigned );
    unsigned  money_add( unsigned, unsigned );
//    bool money_subtract( void );

    unsigned* seed_addr( void );

    void set_main_char_name( Name_Character& );
	void set_current_map( char*& );
	void set_char_position( int, int );

    void debug_print( void );

private:

    //Party info.
    unsigned random_seed_;
    unsigned money_;

    //Character info.
    //TODO: Make objects for these, but this will have to do for now.
    char  character_name_[ MAX_CHARACTER_NAME_LENGTH + 1];
    int   character_name_length_;
    int   character_name_storage_size_; //probably unnecessary.

	char  current_map_filename_[MAP_FILENAME_MAX_LENGTH + 1];
	int   character_pos_[2];
};