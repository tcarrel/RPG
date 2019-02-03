

#include "stdafx.h"


/*static*/ uint8_t Text_Box::fill_color_[ 4 ] = { 0x0, 0x20, 0x3f, 0xcc };
/*static*/ SDL_Renderer* Text_Box::renderer_ = NULL;
/*static*/ bool Text_Box::initialized_ = false;



/**
*   Sets up the basic settings for a text box based the contents passed in.
*/
Text_Box::Text_Box( Box_Contents* bcp, const SDL_Rect& dims ) :
    dimensions_( dims ),
    content_( bcp )
{
    if( !Text_Box::initialized_ )
    {
        initialized_ = true;
        renderer_ = text_[ 0 ].get_renderer();
    }
    type_ = content_->type();
}



/**
*   Sets the fill color for all text boxes.
*/
void Text_Box::set_fill( uint8_t r, uint8_t g, uint8_t b, uint8_t a )
{
    fill_color_[ 0 ] = r;
    fill_color_[ 1 ] = g;
    fill_color_[ 2 ] = b;
    fill_color_[ 3 ] = a;
}



void Text_Box::set_size( const int& w, const int& h )
{
    set_dimensions( dimensions_.x, dimensions_.y, w, h );
}



void Text_Box::set_pos( const int& x, const int& y )
{
    set_dimensions( x, y, dimensions_.w, dimensions_.h );
}



void Text_Box::set_width( const int& w )
{
    set_dimensions( dimensions_.x, dimensions_.y, w, dimensions_.h );
}



void Text_Box::set_height( const int& h )
{
    set_dimensions( dimensions_.x, dimensions_.y, dimensions_.w, h );
}



void Text_Box::set_x_coord( const int& x )
{
    set_dimensions( x, dimensions_.y, dimensions_.w, dimensions_.h );
}



void Text_Box::set_y_coord( const int& y )
{
    set_dimensions( dimensions_.x, y, dimensions_.w, dimensions_.h );
}



void Text_Box::set_dimensions(
    const int& x,
    const int& y,
    const int& w,
    const int& h )
{
    dimensions_ = { x, y, w, h };
}



/**
*   Adds additional lines of text to the text box.  This will probably have to
*  be changed later to allow for images to be displayed withing textboxes.
*/
void Text_Box::add_text( const char cca[], int i )
{
    content_->add_text( Uint8_t_String( cca ), i );
}



/**
*   Adds additional lines of text to the text box.  This will probably have to
*  be changed later to allow for images to be displayed withing textboxes.
*/
void Text_Box::add_text( const string& csr, int i )
{
    content_->add_text( Uint8_t_String( csr ), i );
}



/**
*   Adds additional lines of text to the text box.  This will probably have to
*  be changed later to allow for images to be displayed withing textboxes.
*/
void Text_Box::add_text( const Uint8_t_String& cu8sr, int i )
{
    content_->add_text( cu8sr, i );
}



/**
*   Returns a pointer to the contents of the text box.
*/
Box_Contents* Text_Box::contents( void )
{
    return content_;
}



/**
*   Passes commands on to the text box's contents.
*/
int Text_Box::command( Control_enum_t c )
{
    return content_->command( c );
}



inline int Text_Box::calculate_in_pixels__x_pos( int x )
{
    return  ( x * TEXT_CHARACTER_WIDTH ) + TEXT_X_OFFSET;
}



inline int Text_Box::calculate_in_pixels__y_pos( int y )
{
    return  ( y * TEXT_CHARACTER_HEIGHT ) + TEXT_Y_OFFSET;
}



inline int Text_Box::calculate_in_pixels__width( int w )
{
    return  w * TEXT_CHARACTER_WIDTH;
}



inline int Text_Box::calculate_in_pixels__height( int h )
{
    return  h * TEXT_CHARACTER_HEIGHT;
}



/**
*   Render's the text box fill.
*/
void Text_Box::render_fill( void )
{

    SDL_Rect fill =
    { Scaler::scalei(calculate_in_pixels__x_pos( dimensions_.x ) + text_[ 0 ].get_x_offset()),
		Scaler::scalei(calculate_in_pixels__y_pos( dimensions_.y ) + text_[ 0 ].get_y_offset()),
		Scaler::scalei(calculate_in_pixels__width( dimensions_.w )),
		Scaler::scalei(calculate_in_pixels__height( dimensions_.h )) };


    SDL_SetRenderDrawColor(
        renderer_,
        fill_color_[ 0 ],
        fill_color_[ 1 ],
        fill_color_[ 2 ],
        fill_color_[ 3 ] );
    SDL_RenderFillRect( renderer_, &fill );
}



/**
*   Begins the rendering process.
*/
void Text_Box::render( void )
{
    render_border();
    render_fill();

    for( int i = 0; i < dimensions_.h; i++ )
    {
        line_rendering_ = i;
        render( content_->get_text()->get_line( i ) );
    }
}



/**
*   Render's the box's text.
*/
void Text_Box::render( Line_of_Text* txt)
{
    for(
        unsigned ltr = 0;
        (ltr < (unsigned) dimensions_.w ) && ( ltr < txt->text.size() );
        ltr++ )
    {
        render_char( txt->text[ ltr ], ltr, txt->hl );
    }
}



/**
*   Renders each individual character.
*/
void Text_Box::render_char( unsigned l, unsigned u, unsigned hl )
{
    letter_[ hl ][ l ].render(
        calculate_in_pixels__x_pos( dimensions_.x ) +
        ( u * TEXT_CHARACTER_WIDTH ),
        calculate_in_pixels__y_pos( dimensions_.y ) +
        ( line_rendering_ * TEXT_ROW_HEIGHT ) );
}



/**
*   Renders the text box border.
*/
void Text_Box::render_border( void )
{
    //Corners
    // Top left
    letter_[ TEXT_HIGHLIGHT_TYPE_NORMAL ][ CHAR_BOX_TOP_LEFT ].render(
        calculate_in_pixels__x_pos( dimensions_.x ) - TEXT_CHARACTER_WIDTH,
        calculate_in_pixels__y_pos( dimensions_.y ) - TEXT_CHARACTER_HEIGHT );

    // Top right
    letter_[ TEXT_HIGHLIGHT_TYPE_NORMAL ][ CHAR_BOX_TOP_RIGHT ].render(
        calculate_in_pixels__x_pos( dimensions_.x ) +
        calculate_in_pixels__width( dimensions_.w ),
        calculate_in_pixels__y_pos( dimensions_.y ) - TEXT_CHARACTER_HEIGHT );

    // Bottom left
    letter_[ TEXT_HIGHLIGHT_TYPE_NORMAL ][ CHAR_BOX_BOTTOM_LEFT ].render(
        calculate_in_pixels__x_pos( dimensions_.x ) - TEXT_CHARACTER_WIDTH,
        calculate_in_pixels__y_pos( dimensions_.y ) +
        calculate_in_pixels__height( dimensions_.h ) );

    // Bottom right
    letter_[ TEXT_HIGHLIGHT_TYPE_NORMAL ][ CHAR_BOX_BOTTOM_RIGHT ].render(
        calculate_in_pixels__x_pos( dimensions_.x ) +
        calculate_in_pixels__width( dimensions_.w ),
        calculate_in_pixels__y_pos( dimensions_.y ) +
        calculate_in_pixels__height( dimensions_.h ) );

    // Top and bottom.
    for( int i = 0; i < dimensions_.w; i++ )
    {
		letter_[TEXT_HIGHLIGHT_TYPE_NORMAL][CHAR_BOX_TOP].render(
			calculate_in_pixels__x_pos(dimensions_.x) +
			(i * TEXT_CHARACTER_WIDTH),
			calculate_in_pixels__y_pos(dimensions_.y) -
			TEXT_CHARACTER_HEIGHT);

        letter_[ TEXT_HIGHLIGHT_TYPE_NORMAL ][ CHAR_BOX_BOTTOM ].render(
            calculate_in_pixels__x_pos( dimensions_.x ) +
			( i * TEXT_CHARACTER_WIDTH ),
            calculate_in_pixels__y_pos( dimensions_.y ) +
            calculate_in_pixels__height( dimensions_.h ) );
    }
    // Sides
    for( int i = 0; i < dimensions_.h; i++ )
    {
        letter_[ TEXT_HIGHLIGHT_TYPE_NORMAL ][ CHAR_BOX_LEFT ].render(
            calculate_in_pixels__x_pos( dimensions_.x ) -
			TEXT_CHARACTER_WIDTH,
            calculate_in_pixels__y_pos( dimensions_.y ) +
			( i * TEXT_ROW_HEIGHT ) );

        letter_[ TEXT_HIGHLIGHT_TYPE_NORMAL ][ CHAR_BOX_RIGHT ].render(
            calculate_in_pixels__x_pos( dimensions_.x ) +
            calculate_in_pixels__width( dimensions_.w ),
            calculate_in_pixels__y_pos( dimensions_.y ) +
			( i * TEXT_ROW_HEIGHT ) );
    }
}