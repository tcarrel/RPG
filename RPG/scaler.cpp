

#include "stdafx.h"


/*static*/ float Scaler::factor_ = 1.0;



/**
*   Set the scaling factor.
*/
/*static*/ void Scaler::init( float f )
{
    factor_ = f;
}



/**
*   Returns the scale factor as an integer.
*/
/*static*/ int Scaler::scalei( const int& v )
{
    return (int)ceil( (float)v * factor_ );
}



/**
*   Returns the scale factor as a float.
*/
/*static*/ float Scaler::scalef( const float& v )
{
    return v * factor_;
}