#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vec2D.h"
#include "Terminal.h"

class Projectile {
    public:
    
    /**
    * Contructor.
    *
    * @param y The correspondnig lane's y coordinate.
    * @param color The corresponding sprayer's color.
    */
    Projectile(int y, int color);

    /**
    * Returns the projectile's position.
    *
    * @return The projectile's _position.
    */
    Vec2D get_position();

    /**
    * Returns the projectile's previous position.
    *
    * @return The projectile's _prev_position.
    */
    Vec2D get_prev_position();
    
    /**
    * Returns the projectile's color.
    *
    * @return The projectile's _color.
    */
    int get_color();
    
    /**
    * Returns whether the projectile is destroyed.
    *
    * @return The projectile's _is_destroyed.
    */    
    bool is_destroyed();

    /**
    * Returns whether the projectile is at the end of a lane.
    *
    * @return The projectile's _is_end_of_lane.
    */
    bool is_end_of_lane();

    /**
    * Update the previous position with the current position.
    * Increases the x coordinate of the current position by 1.
    *
    */
    void move();

    /**
    * Draws the projectile on the terminal.
    * Color depends on _color.
    *
    * @param term The terminal the projectile is drawn on.
    */
    void draw(Terminal& term);

    /**
    * Overrides the projectiles previous position with a space.
    *
    * @param term The Terminal the projectile is deleted from.
    */
    void dedraw(Terminal& term);

    private:
    Vec2D _position;
    Vec2D _prev_position;
    int _color;
    bool _is_destroyed;
    bool _is_end_of_lane;
};

#endif
