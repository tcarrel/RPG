#pragma once

class Play_Data;

class Interface;
class Console;
class Window;
class Event_Manager;
class Sprite;


enum Interface_enum_t;



class Name_Character : public Interface
{
public:
    Name_Character(
        Event_Manager*,
        Window*,
        Console*,
        SDL_Texture*,
        SDL_Rect&,
        int*,
        bool = false );

	Interface_enum_t type( void );

    void run( void );
    char* get_name( void );
    void copy_name( char*, int& );

    friend class Event_Manager;

private:
    enum Letters_t
    {
        LTR_A, LTR_B, LTR_C, LTR_D, LTR_E, LTR_F, LTR_G,
        LTR_H, LTR_I, LTR_J, LTR_K, LTR_L, LTR_M, LTR_N,
        LTR_O, LTR_P, LTR_Q, LTR_R, LTR_S, LTR_T, LTR_U,
        LTR_V, LTR_W, LTR_X, LTR_Y, LTR_Z, LTR__, LTR_hyphen,
        LTR_a, LTR_b, LTR_c, LTR_d, LTR_e, LTR_f, LTR_g,
        LTR_h, LTR_i, LTR_j, LTR_k, LTR_l, LTR_m, LTR_n,
        LTR_o, LTR_p, LTR_q, LTR_r, LTR_s, LTR_t, LTR_u,
        LTR_v, LTR_w, LTR_x, LTR_y, LTR_z, LTR_apostrophe, LTR_del,
        LTR_space,
        LTR_clear, LTR_reset, LTR_exit, LTR_ok,
        ALL_LETTERS
    };

    void do_controls( unsigned );

    int calculate_in_pixels__x_pos( int );
    int calculate_in_pixels__y_pos( int );
    int calculate_in_pixels__width( int );
    int calculate_in_pixels__height( int );

    void render_fill( void );
    void render_border( void );
    void render_name( void );
    void render_options( void );

    void cursor_left( void );
    void cursor_right( void );
    void cursor_down( void );
    void cursor_up( void );

    void blink_cursor( void );

    void letter_right( void );
    void letter_left( bool );

    void select( void );

    void del( bool );

    void cancel( void );
    void reset_name( void );

    char name_[ MAX_CHARACTER_NAME_LENGTH - 1 ];
    unsigned current_letter_;

    SDL_Rect box_;

    int*            step_;
    int             name_length_;
    Sprite**        letters_;
    SDL_Texture*    background_;
    SDL_Rect        background_pos_;
    Line_of_Text    selections_[ ALL_LETTERS ];
    int             cursor_;

    bool            cursor_is_on_;
    char            blink_count_;
};
