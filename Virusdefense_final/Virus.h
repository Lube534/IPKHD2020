#ifndef VIRUS_H
#define VIRUS_H

#include "Vec2D.h"
#include "Terminal.h"
#include "Directions.h"

class Virus {
    public:
    /**
    * Constructor.
    *
    * @param x The x coordinate of the virus' position.
    * @param y The y coordinate of the virus' position.
    * @param color The color of the virus.
    */
    Virus(int x, int y, int color);

    /**
    * Returns the virus' position.
    *
    * @return The virus' _position.
    */
    Vec2D get_position();

    /**
    * Returns the virus' previous position.
    *
    * @return The virus' _prev_position.
    */
    Vec2D get_prev_position();

    /**
    * Returns the virus' color.
    *
    * @return The cirus' _color.
    */
    int get_color();
    
    /**
    * Returns the virus' hitpoints.
    *
    * @return The virus' _hitpoints.
    */
    int get_hitpoints();

    /**
    * Sets the virus' hitpoints to the maximum.
    *
    */
    void reset_hitpoints();

    /**
    * Reduces the virus' hitpoints by 1.
    *
    */
    void substract_hitpoints();

    /**
    * Returns whether the virus has already completed 1 round in the safespace.
    *
    * @return The virus' _round_done.
    */
    bool get_flag();

    /**
    * Sets the virus' _round_done to true.
    *
    */
    void set_flag();

    /**
    * Returns the current direction of the virus.
    *
    * @return The virus' _direction.
    */
    Directions get_direction();
    
    /**
    * Sets the current direction of the virus.
    * 
    *
    * @param direction The direction the virus' _direction will be set on.
    */
    void change_direction(Directions direction);
    
        /**
    * Returns true if the virus is destroyed.
    *
    * @return The virus' _is_destroyed.
    */
    bool is_destroyed();
    
    /**
    * Returns true if the virus is in the safespace.
    *
    * @return The virus' _is_in_safespace.
    */
    bool is_in_safespace();

    /**
    * Sets the virus' _is_in_safespace to true.
    *
    */
    void change_is_in_safespace(); 

    /**
    * Changes the position of the virus depending on the current direction.
    *
    */
    void move();

    /**
    * Draws the virus' hull while it is outside the safespace.
    *
    * @param term The terminal the hull is drawn on.
    */
    void draw_hull(Terminal& term);

    /**
    * Draws the virus depending on its _color.
    *
    * @param term The terminal the virus is drawn on.
    */
    void draw(Terminal& term);

    /**
    * Draws a space on the virus' previous position.
    *
    * @param term The terminal the virus is erased from.
    */
    void dedraw(Terminal& term);

    private:
    Vec2D _position;
    Vec2D _prev_position;
    int _color;
    Directions _direction;
    int _hitpoints;
    bool _is_destroyed;
    bool _is_in_safespace;
    bool _round_done; 
};

#endif
