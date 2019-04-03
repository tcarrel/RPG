#pragma once

#include<SDL.h>




SDL_Rect image_scaler( SDL_Surface*, int, int );
SDL_Rect image_centered( SDL_Surface*, int, int );
SDL_Rect image_fullscreen_uniform_scale__centered( SDL_Surface*, int, int );
int ftoi( float );
float itof( int );

Control_enum_t uint_to_cntlt( unsigned );

Cardinal_Directions_enum_t int_to_cardinal( int );

bool check_lua( lua_State*, int );