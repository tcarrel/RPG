#pragma once

class Sprite;
class Uint8_t_String;




class Area_Map
{
public:
    Area_Map( int, int, int, const Uint8_t_String& );

    const Uint8_t_String& get_name( void );

    ~Area_Map( void );

    static const int MAX_VERTICAL;
    static const int MAX_HORIZONAL;
    static const int MAX_HEIGHT;

private:
    Sprite* tiles_;

    static unsigned unassigned_id_;
    unsigned id_;

    Uint8_t_String name_;// TODO: Modify ctor(s) to assign this.
    int    height_;
    int    horizontal_size_;
    int    vertical_size_;
    int*** bg_;
    int**  fg_;

    //Additional arrays will need to be added for more map features.
    //int*** usable_;
};