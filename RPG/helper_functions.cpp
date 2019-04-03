

#include "stdafx.h"

enum Control_enum_t;



SDL_Rect image_scaler( SDL_Surface* image, int screen_x, int screen_y )
{
    SDL_Rect scale = { 0, 0, 0, 0 };

    float
        x = itof( screen_x ),
        y = itof( screen_y ),
        screen_ar = x / y,
        image_ar = itof( image->w ) / itof( image->h );

    if( screen_ar >= image_ar )
    {
        scale.h = screen_y;
        scale.w = ftoi( itof( scale.h )*image_ar );
        return scale;
    }

    scale.w = screen_x;
    scale.h = ftoi( itof( scale.w ) / image_ar );

    return scale;
}



SDL_Rect image_centered( SDL_Surface* image, int screenx, int screeny )
{
    SDL_Rect position = { 0, 0, 0, 0 };

    float
        screen_ar = itof( screenx ) / itof( screeny ),
        image_ar = itof( image->w ) / itof( image->h );

    if( screen_ar > image_ar )
    {        
        position.x = ( screenx - ftoi( itof( screeny ) * image_ar ) ) / 2;
        return position;
    }

    position.y = ( screeny - ftoi( itof( screenx ) / image_ar ) ) / 2;
    return position;
}



SDL_Rect image_fullscreen_uniform_scale__centered(
    SDL_Surface* image,
    int screen_width,
    int screen_height )
{
    SDL_Rect
        scale = image_scaler( image, screen_width, screen_height ),
        pos = image_centered( image, screen_width, screen_height );

    return{ pos.x, pos.y, scale.w, scale.h };
}



inline int ftoi( float f )
{
    return (int)f;
}



inline float itof( int i )
{
    return (float)i;
}



Control_enum_t uint_to_cntlt( unsigned u )
{

    switch( u )
    {
    case CTRL_X:
        return CTRL_X;
    case CTRL_A:
        return CTRL_A;
    case CTRL_B:
        return CTRL_B;
    case CTRL_Y:
        return CTRL_Y;
    case CTRL_L:
        return CTRL_L;
    case CTRL_R:
        return CTRL_R;
    case CTRL_UP:
        return CTRL_UP;
    case CTRL_DOWN:
        return CTRL_DOWN;
    case CTRL_LEFT:
        return CTRL_LEFT;
    case CTRL_RIGHT:
        return CTRL_RIGHT;
    case CTRL_START:
        return CTRL_START;
    case CTRL_SELECT:
        return CTRL_SELECT;
    case CTRL_ALT:
        return CTRL_ALT;
    case CTRL_F4:
        return CTRL_F4;

    default:
        return CTRL_NULL;
    }
}



Cardinal_Directions_enum_t int_to_cardinal( int dir )
{
    switch( dir )
    {
    default:
        return INVALID_DIRECTION;

    case UP:
        return UP;
    case UP_RIGHT:
        return UP_RIGHT;
    case RIGHT:
        return RIGHT;
    case DOWN_RIGHT:
        return DOWN_RIGHT;

    case DOWN:
        return DOWN;
    case DOWN_LEFT:
        return DOWN_LEFT;
    case LEFT:
        return LEFT;
    case UP_LEFT:
        return UP_LEFT;
    }
}



bool check_lua(lua_State* L, int r)
{
	if (r == LUA_OK)
	{
		return true;
	}

	string errmsg = lua_tostring(L, -1);
	std::cerr << errmsg << "\n" << std::endl;
	return false;
}
