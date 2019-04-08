

#include "stdafx.h"




Name_Character::Name_Character(
    Event_Manager* e,
    Window* w,
    Console* c,
    SDL_Texture* t,
    SDL_Rect& tclip,
    int* step,
    bool run_immediately ) :
    Interface( e, c, w, INTERFACE_CHARACTER_NAMING ),
    step_( step ),
    background_( t ),
    background_pos_( tclip )
{
    blink_count_ = 0;
    cursor_is_on_ = true;
    cursor_ = LTR_ok;
    box_ = {
        calculate_in_pixels__x_pos( 2 ) + Sprite_Sheet::get_x_offset(),
        calculate_in_pixels__y_pos( 2 ) + Sprite_Sheet::get_y_offset(),
        calculate_in_pixels__width( TEXT_COLUMNS - 4 ),
        calculate_in_pixels__height( TEXT_ROWS - 4 ) };

    reset_name();

    // Row  1
    selections_[ LTR_A ].text = "A";
    selections_[ LTR_A ].x = 16 + TEXT_CHARACTER_WIDTH * 5;
    selections_[ LTR_A ].y = (TEXT_CHARACTER_HEIGHT - 4) * 5;

    selections_[ LTR_B ].text = "B";
    selections_[ LTR_B ].x = 16 + TEXT_CHARACTER_WIDTH * 13;
    selections_[ LTR_B ].y = (TEXT_CHARACTER_HEIGHT - 4) * 5;

    selections_[ LTR_C ].text = "C";
    selections_[ LTR_C ].x = 16 + TEXT_CHARACTER_WIDTH * 21;
    selections_[ LTR_C ].y = (TEXT_CHARACTER_HEIGHT - 4) * 5;

    selections_[ LTR_D ].text = "D";
    selections_[ LTR_D ].x = 16 + TEXT_CHARACTER_WIDTH * 29;
    selections_[ LTR_D ].y = (TEXT_CHARACTER_HEIGHT - 4) * 5;

    selections_[ LTR_E ].text = "E";
    selections_[ LTR_E ].x = 16 + TEXT_CHARACTER_WIDTH * 37;
    selections_[ LTR_E ].y = (TEXT_CHARACTER_HEIGHT - 4) * 5;

    selections_[ LTR_F ].text = "F";
    selections_[ LTR_F ].x = 16 + TEXT_CHARACTER_WIDTH * 45;
    selections_[ LTR_F ].y = (TEXT_CHARACTER_HEIGHT - 4) * 5;

    selections_[ LTR_G ].text = "G";
    selections_[ LTR_G ].x = 16 + TEXT_CHARACTER_WIDTH * 53;
    selections_[ LTR_G ].y = (TEXT_CHARACTER_HEIGHT - 4) * 5;


    // Row  2
    selections_[ LTR_H ].text = "H";
    selections_[ LTR_H ].x = 16 + TEXT_CHARACTER_WIDTH * 5;
    selections_[ LTR_H ].y = (TEXT_CHARACTER_HEIGHT - 4) * 8;

    selections_[ LTR_I ].text = "I";
    selections_[ LTR_I ].x = 16 + TEXT_CHARACTER_WIDTH * 13;
    selections_[ LTR_I ].y = (TEXT_CHARACTER_HEIGHT - 4) * 8;

    selections_[ LTR_J ].text = "J";
    selections_[ LTR_J ].x = 16 + TEXT_CHARACTER_WIDTH * 21;
    selections_[ LTR_J ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 8;

    selections_[ LTR_K ].text = "K";
    selections_[ LTR_K ].x = 16 + TEXT_CHARACTER_WIDTH * 29;
    selections_[ LTR_K ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 8;

    selections_[ LTR_L ].text = "L";
    selections_[ LTR_L ].x = 16 + TEXT_CHARACTER_WIDTH * 37;
    selections_[ LTR_L ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 8;

    selections_[ LTR_M ].text = "M";
    selections_[ LTR_M ].x = 16 + TEXT_CHARACTER_WIDTH * 45;
    selections_[ LTR_M ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 8;

    selections_[ LTR_N ].text = "N";
    selections_[ LTR_N ].x = 16 + TEXT_CHARACTER_WIDTH * 53;
    selections_[ LTR_N ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 8;


    // Row  3
    selections_[ LTR_O ].text = "O";
    selections_[ LTR_O ].x = 16 + TEXT_CHARACTER_WIDTH * 5;
    selections_[ LTR_O ].y = (TEXT_CHARACTER_HEIGHT - 4) * 11;

    selections_[ LTR_P ].text = "P";
    selections_[ LTR_P ].x = 16 + TEXT_CHARACTER_WIDTH * 13;
    selections_[ LTR_P ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 11;
    
    selections_[ LTR_Q ].text = "Q";
    selections_[ LTR_Q ].x = 16 + TEXT_CHARACTER_WIDTH * 21;
    selections_[ LTR_Q ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 11;

    selections_[ LTR_R ].text = "R";
    selections_[ LTR_R ].x = 16 + TEXT_CHARACTER_WIDTH * 29;
    selections_[ LTR_R ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 11;

    selections_[ LTR_S ].text = "S";
    selections_[ LTR_S ].x = 16 + TEXT_CHARACTER_WIDTH * 37;
    selections_[ LTR_S ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 11;

    selections_[ LTR_T ].text = "T";
    selections_[ LTR_T ].x = 16 + TEXT_CHARACTER_WIDTH * 45;
    selections_[ LTR_T ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 11;

    selections_[ LTR_U ].text = "U";
    selections_[ LTR_U ].x = 16 + TEXT_CHARACTER_WIDTH * 53;
    selections_[ LTR_U ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 11;


    // Row  4
    selections_[ LTR_V ].text = "V";
    selections_[ LTR_V ].x = 16 + TEXT_CHARACTER_WIDTH * 5;
    selections_[ LTR_V ].y = (TEXT_CHARACTER_HEIGHT - 4) * 14;

    selections_[ LTR_W ].text = "W";
    selections_[ LTR_W ].x = 16 + TEXT_CHARACTER_WIDTH * 13;
    selections_[ LTR_W ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 14;

    selections_[ LTR_X ].text = "X";
    selections_[ LTR_X ].x = 16 + TEXT_CHARACTER_WIDTH * 21;
    selections_[ LTR_X ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 14;

    selections_[ LTR_Y ].text = "Y";
    selections_[ LTR_Y ].x = 16 + TEXT_CHARACTER_WIDTH * 29;
    selections_[ LTR_Y ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 14;

    selections_[ LTR_Z ].text = "Z";
    selections_[ LTR_Z ].x = 16 + TEXT_CHARACTER_WIDTH * 37;
    selections_[ LTR_Z ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 14;

    selections_[ LTR__ ].text = "_";
    selections_[ LTR__ ].x = 16 + TEXT_CHARACTER_WIDTH * 45;
    selections_[ LTR__ ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 14;

    selections_[ LTR_hyphen ].text = "-";
    selections_[ LTR_hyphen ].x = 16 + TEXT_CHARACTER_WIDTH * 53;
    selections_[ LTR_hyphen ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 14;


    // Row  5
    selections_[ LTR_a ].text = "a";
    selections_[ LTR_a ].x = 16 + TEXT_CHARACTER_WIDTH * 5;
    selections_[ LTR_a ].y = (TEXT_CHARACTER_HEIGHT - 4) * 17;

    selections_[ LTR_b ].text = "b";
    selections_[ LTR_b ].x = 16 + TEXT_CHARACTER_WIDTH * 13;
    selections_[ LTR_b ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 17;

    selections_[ LTR_c ].text = "c";
    selections_[ LTR_c ].x = 16 + TEXT_CHARACTER_WIDTH * 21;
    selections_[ LTR_c ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 17;

    selections_[ LTR_d ].text = "d";
    selections_[ LTR_d ].x = 16 + TEXT_CHARACTER_WIDTH * 29;
    selections_[ LTR_d ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 17;

    selections_[ LTR_e ].text = "e";
    selections_[ LTR_e ].x = 16 + TEXT_CHARACTER_WIDTH * 37;
    selections_[ LTR_e ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 17;

    selections_[ LTR_f ].text = "f";
    selections_[ LTR_f ].x = 16 + TEXT_CHARACTER_WIDTH * 45;
    selections_[ LTR_f ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 17;

    selections_[ LTR_g ].text = "g";
    selections_[ LTR_g ].x = 16 + TEXT_CHARACTER_WIDTH * 53;
    selections_[ LTR_g ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 17;


    // Row  6
    selections_[ LTR_h ].text = "h";
    selections_[ LTR_h ].x = 16 + TEXT_CHARACTER_WIDTH * 5;
    selections_[ LTR_h ].y = (TEXT_CHARACTER_HEIGHT - 4) * 20;

    selections_[ LTR_i ].text = "i";
    selections_[ LTR_i ].x = 16 + TEXT_CHARACTER_WIDTH * 13;
    selections_[ LTR_i ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 20;

    selections_[ LTR_j ].text = "j";
    selections_[ LTR_j ].x = 16 + TEXT_CHARACTER_WIDTH * 21;
    selections_[ LTR_j ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 20;

    selections_[ LTR_k ].text = "k";
    selections_[ LTR_k ].x = 16 + TEXT_CHARACTER_WIDTH * 29;
    selections_[ LTR_k ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 20;

    selections_[ LTR_l ].text = "l";
    selections_[ LTR_l ].x = 16 + TEXT_CHARACTER_WIDTH * 37;
    selections_[ LTR_l ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 20;

    selections_[ LTR_m ].text = "m";
    selections_[ LTR_m ].x = 16 + TEXT_CHARACTER_WIDTH * 45;
    selections_[ LTR_m ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 20;

    selections_[ LTR_n ].text = "n";
    selections_[ LTR_n ].x = 16 + TEXT_CHARACTER_WIDTH * 53;
    selections_[ LTR_n ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 20;


    // Row  7
    selections_[ LTR_o ].text = "o";
    selections_[ LTR_o ].x = 16 + TEXT_CHARACTER_WIDTH * 5;
    selections_[ LTR_o ].y = (TEXT_CHARACTER_HEIGHT - 4) * 23;

    selections_[ LTR_p ].text = "p";
    selections_[ LTR_p ].x = 16 + TEXT_CHARACTER_WIDTH * 13;
    selections_[ LTR_p ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 23;

    selections_[ LTR_q ].text = "q";
    selections_[ LTR_q ].x = 16 + TEXT_CHARACTER_WIDTH * 21;
    selections_[ LTR_q ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 23;

    selections_[ LTR_r ].text = "r";
    selections_[ LTR_r ].x = 16 + TEXT_CHARACTER_WIDTH * 29;
    selections_[ LTR_r ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 23;

    selections_[ LTR_s ].text = "s";
    selections_[ LTR_s ].x = 16 + TEXT_CHARACTER_WIDTH * 37;
    selections_[ LTR_s ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 23;

    selections_[ LTR_t ].text = "t";
    selections_[ LTR_t ].x = 16 + TEXT_CHARACTER_WIDTH * 45;
    selections_[ LTR_t ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 23;

    selections_[ LTR_u ].text = "u";
    selections_[ LTR_u ].x = 16 + TEXT_CHARACTER_WIDTH * 53;
    selections_[ LTR_u ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 23;


    // Row  8
    selections_[ LTR_v ].text = "v";
    selections_[ LTR_v ].x = 16 + TEXT_CHARACTER_WIDTH * 5;
    selections_[ LTR_v ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 26;

    selections_[ LTR_w ].text = "w";
    selections_[ LTR_w ].x = 16 + TEXT_CHARACTER_WIDTH * 13;
    selections_[ LTR_w ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 26;

    selections_[ LTR_x ].text = "x";
    selections_[ LTR_x ].x = 16 + TEXT_CHARACTER_WIDTH * 21;
    selections_[ LTR_x ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 26;

    selections_[ LTR_y ].text = "y";
    selections_[ LTR_y ].x = 16 + TEXT_CHARACTER_WIDTH * 29;
    selections_[ LTR_y ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 26;

    selections_[ LTR_z ].text = "z";
    selections_[ LTR_z ].x = 16 + TEXT_CHARACTER_WIDTH * 37;
    selections_[ LTR_z ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 26;

    selections_[ LTR_apostrophe ].text = "\'";
    selections_[ LTR_apostrophe ].x = 16 + TEXT_CHARACTER_WIDTH * 45;
    selections_[ LTR_apostrophe ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 26;

    selections_[ LTR_del ].text = "4";
    selections_[ LTR_del ].text[ 0 ] = CHAR_ARROW_LEFT;
    selections_[ LTR_del ].x = 16 + TEXT_CHARACTER_WIDTH * 53;
    selections_[ LTR_del ].y = ( TEXT_CHARACTER_HEIGHT - 4 ) * 26;


    // Row  9
    selections_[ LTR_space ].text = "SPACE";
    selections_[ LTR_space ].x = 880;
    selections_[ LTR_space ].y = ( ( TEXT_CHARACTER_HEIGHT - 4 ) * 29 ) - 8;
    

    // Row 10
    selections_[ LTR_clear ].text = "CLEAR";
    selections_[ LTR_clear ].x = 352;
    selections_[ LTR_clear ].y = 14 + ( TEXT_CHARACTER_HEIGHT - 4 ) * 32;

    selections_[ LTR_reset ].text = "RESET";
    selections_[ LTR_reset ].x = 704;
    selections_[ LTR_reset ].y = 14 + ( TEXT_CHARACTER_HEIGHT - 4 ) * 32;

    selections_[ LTR_exit ].text = "EXIT";
    selections_[ LTR_exit ].x = 1072;
    selections_[ LTR_exit ].y = 14 + ( TEXT_CHARACTER_HEIGHT - 4 ) * 32;

    selections_[ LTR_ok ].text = "CONFIRM";
    selections_[ LTR_ok ].x = 1376;
    selections_[ LTR_ok ].y = 14 + ( TEXT_CHARACTER_HEIGHT - 4 ) * 32;

    if( run_immediately )
    {
        run();
    }
}


void Name_Character::blink_cursor( void )
{
    blink_count_ = ( blink_count_ + 1 ) % FRAMES_PER_SECOND;

    if( !blink_count_ )
    {
        cursor_is_on_ = !cursor_is_on_;
    }
}



Interface_enum_t Name_Character::type( void )
{
	return INTERFACE_CHARACTER_NAMING;
}



void Name_Character::run( void )
{
	Console::current_interface( type() );

    for( ; !( exit_ || em_->quit() ); em_->process( this ) )
    {
        window_->clear();
        SDL_RenderCopy( renderer_, background_, NULL, &background_pos_ );
        render_fill();
        render_border();
        render_name();
        render_options();
        window_->update();
    }
}



char* Name_Character::get_name( void )
{
    return name_;
}



void Name_Character::copy_name( char* name, int& max_length )
{
        for( int i = 0; i < name_length_; i++ )
        {
            name[ i ] = name_[ i ];
        }
        for( int i = name_length_; i <= max_length; i++ )
        {
            name[ i ] = 0;
        }
        max_length = name_length_;
}



void Name_Character::cursor_left( void )
{
    if( cursor_ == 0 )
    {
        cursor_ = LTR_ok;
        return;
    }
    --cursor_;
}



void Name_Character::cursor_right( void )
{
    if( cursor_ == LTR_ok )
    {
        cursor_ = LTR_A;
        return;
    }
    ++cursor_;
}



void Name_Character::do_controls( unsigned u )
{
    if( ctrl_previous_[ u ] && !ctrl_current_[ u ] )
    {
        switch( u )
        {
        case CTRL_A:
            select();
            return;
        case CTRL_B:
            if( current_letter_ == 0 && name_[ 0 ] == 0 )
            {
                cancel();
                return;
            }
            del( true );
            return;
        case CTRL_LEFT:
            cursor_left();
            return;
        case CTRL_RIGHT:
            cursor_right();
            return;
        case CTRL_DOWN:
            cursor_down();
            return;
        case CTRL_UP:
            cursor_up();
            return;
        case CTRL_L:
            del( true );
            return;
        case CTRL_R:
            name_[ current_letter_ ] = ' ';
            letter_right();
            return;
        case CTRL_START:
            if( cursor_ == LTR_ok )
            {
                select();
                return;
            }
            cursor_ = LTR_ok;
            return;
        default:
            ;
        }
    }
}



void Name_Character::cursor_down( void )
{
    switch( cursor_ )
    {
    default:
        cursor_ += 7;
        return;
    case LTR_v: //fallthrough.
    case LTR_w:
        cursor_ = LTR_clear;
        return;
    case LTR_x:
        cursor_ = LTR_reset;
        return;
    case LTR_y:
        cursor_ = LTR_space;
        return;
    case LTR_z:
        cursor_ = LTR_exit;
        return;
    case LTR_apostrophe: //fallthrough.
    case LTR_del:
        cursor_ = LTR_ok;
        return;
    case LTR_space:
        cursor_ = LTR_reset;
        return;
    case LTR_clear:
        cursor_ = LTR_A;
        return;
    case LTR_reset:
        cursor_ = LTR_C;
        return;
    case LTR_exit:
        cursor_ = LTR_E;
        return;
    case LTR_u:
        cursor_ = LTR_del;
        return;
    case LTR_ok:
        cursor_ = LTR_G;
    }
}



void Name_Character::cursor_up( void )
{
    switch( cursor_ )
    {
    default:
        cursor_ -= 7;
        return;
    case LTR_A: // fallthrough.
    case LTR_B:
        cursor_ = LTR_clear;
        return;
    case LTR_C: // fallthrough
    case LTR_D:
        cursor_ = LTR_reset;
        return;
    case LTR_E:
        cursor_ = LTR_exit;
        return;
    case LTR_F: // fallthrough.
    case LTR_G:
        cursor_ = LTR_ok;
        return;
    case LTR_space:
        cursor_ = LTR_y;
        return;
    case LTR_clear:
        cursor_ = LTR_w;
        return;
    case LTR_reset:
        cursor_ = LTR_x;
        return;
    case LTR_exit:
        cursor_ = LTR_z;
        return;
    case LTR_del:
        cursor_ = LTR_u;
        return;
    case LTR_ok:
        cursor_ = LTR_apostrophe;
    }
}



void Name_Character::letter_right( void )
{
    if( current_letter_ == ( MAX_CHARACTER_NAME_LENGTH - 2 ) )
    {
        ++current_letter_;
        cursor_ = LTR_ok;
        return;
    }
    ++current_letter_;
    ++name_length_;
}



void Name_Character::letter_left( bool loop )
{
    if( loop && current_letter_ == 0 )
    {
        cursor_ = LTR_exit;
        --current_letter_;
        return;
    }
    --current_letter_;
    --name_length_;
}



void Name_Character::select( void )
{
    switch( cursor_ )
    {
    case LTR_exit:
		//TODO: Fix this.  Does not return to Start Menu as it should.
        cancel();
        return;
    case LTR_clear:
        for( int i = 0; i < MAX_CHARACTER_NAME_LENGTH - 1; i++ )
        {
            name_[ i ] = 0;
        }
        current_letter_ = 0;
        return;
    case LTR_del:
        del( false );
        return;
    case LTR_reset:
        reset_name();
        return;
    case LTR_ok:
        *step_ = 2;
        exit_ = true;
    case LTR_space:
        name_[ current_letter_ ] = ' ';
        letter_right();
        return;
    default:
        name_[ current_letter_ ] = selections_[ cursor_ ].text[ 0 ];
        letter_right();
    }
}



void Name_Character::del( bool back )
{

    if( current_letter_ == 0 )
    {
        if( back )
        {
            cursor_ = LTR_exit;
        }
        return;
    }

    if( current_letter_ == ( MAX_CHARACTER_NAME_LENGTH - 2 ) )
    {
        if( name_[ ( MAX_CHARACTER_NAME_LENGTH - 2 ) ] != 0 )
        {
            name_[ ( MAX_CHARACTER_NAME_LENGTH - 2 ) ] = 0;
        }
        else
        {
            name_[ --current_letter_ ] = 0;
        }
        return;
    }

    name_[ --current_letter_ ] = 0;
}



void Name_Character::cancel( void )
{
    *step_ = 5;
    exit_ = true;
}



void Name_Character::reset_name( void )
{
    name_length_ = current_letter_ = 9;
    name_[ 0 ] = 'H';
    name_[ 1 ] = name_[ 5 ] = 'e';
    name_[ 2 ] = 'n';
    name_[ 3 ] = 'r';
    name_[ 4 ] = 'i';
    name_[ 6 ] = name_[ 7 ] = 't';
    name_[ 8 ] = 'a';
    name_[ 9 ] = 0;
}



void Name_Character::render_fill( void )
{
    SDL_SetRenderDrawColor( renderer_, 0x0, 0x20, 0x3F, 0xCC );
	SDL_Rect sb = { Scaler::scalei(box_.x),  Scaler::scalei(box_.y),  Scaler::scalei(box_.w),  Scaler::scalei(box_.h) };
    SDL_RenderFillRect( renderer_, &sb );
}



void Name_Character::render_border( void )
{
    int hl = TEXT_HIGHLIGHT_TYPE_NORMAL;
    text_->letter( hl, CHAR_BOX_TOP_LEFT ).render(
        calculate_in_pixels__x_pos( 1 ),
        calculate_in_pixels__y_pos( 1 ) );
    text_->letter( hl, CHAR_BOX_TOP_RIGHT ).render(
        calculate_in_pixels__x_pos( 2 ) + box_.w,
        calculate_in_pixels__y_pos( 1 ) );
    text_->letter( hl, CHAR_BOX_BOTTOM_LEFT ).render(
        calculate_in_pixels__x_pos( 1 ),
        calculate_in_pixels__y_pos( 2 ) + box_.h );
    text_->letter( hl, CHAR_BOX_BOTTOM_RIGHT ).render(
        calculate_in_pixels__x_pos( 2 ) + box_.w,
        calculate_in_pixels__y_pos( 2 ) + box_.h );
    text_->letter( hl, CHAR_BOX_T_LEFT ).render(
        calculate_in_pixels__x_pos( 2 ) - TEXT_CHARACTER_WIDTH,
        calculate_in_pixels__y_pos( 4 ) - TEXT_CHARACTER_HEIGHT );
    text_->letter( hl, CHAR_BOX_T_RIGHT ).render(
        calculate_in_pixels__x_pos( 2 ) + box_.w,
        calculate_in_pixels__y_pos( 4 ) - TEXT_CHARACTER_HEIGHT );
    text_->letter( hl, CHAR_BOX_T_LEFT ).render(
        calculate_in_pixels__x_pos( 2 ) - TEXT_CHARACTER_WIDTH,
        calculate_in_pixels__y_pos( TEXT_ROWS - 6 ) );
    text_->letter( hl, CHAR_BOX_T_RIGHT ).render(
        calculate_in_pixels__x_pos( 2 ) + box_.w,
        calculate_in_pixels__y_pos( TEXT_ROWS - 6 ) );
    
    for( int i = 0; i < TEXT_COLUMNS - 4; i++ )
    {
        int x = calculate_in_pixels__x_pos( 2 ) +
            ( i * TEXT_CHARACTER_WIDTH );

        text_->letter( hl, CHAR_BOX_TOP ).render(
            x,
            calculate_in_pixels__y_pos( 2 ) -
            TEXT_CHARACTER_HEIGHT );
        text_->letter( hl, CHAR_BOX_CENTERED_HORIZONTAL ).render(
            x,
            calculate_in_pixels__y_pos( 2 ) +
            calculate_in_pixels__height( 1 ) );
        text_->letter( hl, CHAR_BOX_CENTERED_HORIZONTAL ).render(
            x,
            calculate_in_pixels__y_pos( 2 ) +
            calculate_in_pixels__height( TEXT_ROWS - 8 ) );
        text_->letter( hl, CHAR_BOX_BOTTOM ).render(
            x,
            calculate_in_pixels__y_pos( 2 ) +
            calculate_in_pixels__height( TEXT_ROWS - 4 ) );
    }
    for( int i = 0; i < TEXT_ROWS - 4; i++ )
    {
        if( i != 1 && i != TEXT_ROWS - 8 )
        {
            text_->letter( hl, CHAR_BOX_LEFT ).render(
                calculate_in_pixels__x_pos( 2 ) -
                TEXT_CHARACTER_WIDTH,
                calculate_in_pixels__y_pos( 2 ) +
                ( i * TEXT_ROW_HEIGHT ) );
            text_->letter( hl, CHAR_BOX_RIGHT ).render(
                calculate_in_pixels__x_pos( 2 ) + box_.w,
                calculate_in_pixels__y_pos( 2 ) +
                ( i * TEXT_ROW_HEIGHT ) );
        }
    }
}



void Name_Character::render_name( void )
{
    for( int i = 0; i < MAX_CHARACTER_NAME_LENGTH - 1; i++ )
    {
        if( i != current_letter_ )
        {
            text_->letter( TEXT_HIGHLIGHT_TYPE_NORMAL, CHAR_50_PERCENT ).render( 
                    calculate_in_pixels__width( TEXT_COLUMNS / 2 ) -
                    ( ( 17 * TEXT_CHARACTER_WIDTH ) / 2 ) +
                    ( 2 * i * TEXT_CHARACTER_WIDTH ),
                    calculate_in_pixels__height( 3 ) -
                    ( ( TEXT_CHARACTER_HEIGHT - 8 ) / 2 ) );
        }

        if( current_letter_ == ( MAX_CHARACTER_NAME_LENGTH - 2 ) )
        {
            text_->letter( TEXT_HIGHLIGHT_TYPE_NORMAL, name_[ i ] ).render(
                calculate_in_pixels__width( TEXT_COLUMNS / 2 ) -
                ( ( 17 * TEXT_CHARACTER_WIDTH ) / 2 ) +
                ( 2 * i * TEXT_CHARACTER_WIDTH ),
                calculate_in_pixels__height( 3 ) -
                ( ( TEXT_CHARACTER_HEIGHT - 8 ) / 2 ) );
        }

        if(  i < (int)current_letter_ )
        {
            text_->letter( TEXT_HIGHLIGHT_TYPE_NORMAL, name_[ i ] ).render(
                calculate_in_pixels__width( TEXT_COLUMNS / 2 ) -
                ( ( 17 * TEXT_CHARACTER_WIDTH ) / 2 ) +
                ( 2 * i * TEXT_CHARACTER_WIDTH ),
                calculate_in_pixels__height( 3 ) -
                ( ( TEXT_CHARACTER_HEIGHT - 8 ) / 2 ) );
        }

        if( i == current_letter_ && cursor_is_on_ )
        {
            text_->letter( TEXT_HIGHLIGHT_TYPE_BRIGHT, CHAR_25_PERCENT ).render(
                calculate_in_pixels__width( TEXT_COLUMNS / 2 ) -
                ( ( 17 * TEXT_CHARACTER_WIDTH ) / 2 ) +
                ( 2 * i * TEXT_CHARACTER_WIDTH ),
                calculate_in_pixels__height( 3 ) -
                ( ( TEXT_CHARACTER_HEIGHT - 8 ) / 2 ) );
        }
    }
}



void Name_Character::render_options( void )
{
    for( unsigned u = 0; u < ALL_LETTERS; u++ )
    {
        for( unsigned v = 0; v < selections_[ u ].text.size(); v++ )
        {
            text_->letter(
                u == cursor_ ?
                TEXT_HIGHLIGHT_TYPE_BRIGHT :
                TEXT_HIGHLIGHT_TYPE_NORMAL,
                selections_[ u ].text[ v ] ).render(
                    selections_[ u ].x + ( v * TEXT_CHARACTER_WIDTH ),
                    selections_[ u ].y );
        }
    }
}



inline int Name_Character::calculate_in_pixels__x_pos( int x )
{
    return ( x * TEXT_CHARACTER_WIDTH ) + TEXT_X_OFFSET;
}



inline int Name_Character::calculate_in_pixels__y_pos( int y )
{
    return ( y * TEXT_CHARACTER_HEIGHT ) + TEXT_Y_OFFSET;
}



inline int Name_Character::calculate_in_pixels__width( int w )
{
    return w * TEXT_CHARACTER_WIDTH;
}



inline int Name_Character::calculate_in_pixels__height( int h )
{
    return h * TEXT_CHARACTER_HEIGHT;
}
