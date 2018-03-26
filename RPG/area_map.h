#pragma once

class Sprite;
class Uint8_t_String;




class Area_Map
{
public:
    Area_Map( int, int, int );


    ~Area_Map( void );

public:
    Sprite* tiles_;

    static unsigned unassigned_id_;
    unsigned id_;

    Uint8_t_String name_;// TODO: Modify ctor(s) to assign this.
    int    map_layers_;
    int    map_width_;
    int    map_height_;
    int*** map_fg_;
    int**  map_bg_;

    //Additional arrays will need to be added for more map features.
    //int*** usable_;
};