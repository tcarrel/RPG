

#include "stdafx.h"



Item_Creation::Item_Creation( Console* c ) :
    Interface( c, INTERFACE_ITEM )
{}



Interface_enum Item_Creation::run( void )
{

    return type_;
}



void Item_Creation::do_controls( void )
{}