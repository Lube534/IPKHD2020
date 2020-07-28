#ifndef SPRAYER_H
#define SPRAYER_H

#include "Vec2D.h"
#include "Terminal.h"
#include "Cleaner.h"

class Sprayer{
    public:
    
    /**
    * Constructor
    *
    * @param y The y coordinate of the lane the sprayer belongs to.
    */
    Sprayer(int y);
    

    /**
    * Returns the color of the sprayer.
    *
    * @return sprayer's _color.
    */
    int get_color();

    /**
    * Changes the color of the sprayer to the color of the cleaner.
    *
    * @param cleaner The cleaner.
    */
    void change_color(Cleaner& cleaner);

    /**
    * Returns the position of the sprayer.
    *
    * @return sprayer's _position.
    */
    Vec2D get_position();

    /**
    * Returns the hitpoints of the sprayer.
    *
    * @return sprayer's _hitpoints.
    */
    int get_hitpoints();

    /**
    * Reduces the sprayer's hitpoints by 1.
    *
    */
    void lose_hitpoints();

    /**
    *Sets the sprayer's hitpoints to the maximum.
    *
    */
    void reset_hitpoints();
    
    /**
    * Returns the remaining shots of the sprayer.
    *
    * @return sprayer's _shots.
    */
    int get_shots();
    /**
    *Sets the sprayer's shots to the maximum.
    *
    */
    void reset_shots();

    /**
    *Reduces the sprayer's shots by 1.
    *
    */
    void shoot();

    /**
    *Returns whether the sprayer is built.
    *
    * @return Sprayer's _is_built.
    */
    bool get_is_built();
   
    /**
    *Sets the sprayer's _is_built to true.
    *
    */
    void build();

    /**
    *Sets the sprayer's _is_built to false.
    *
    */
    void destroy();

    /**
    *Draws the Sprayer on the terminal.
    The Color depends on _color and _shots.
    *
    * @param term The Terminal the sprayer is drawn on.
    */
    void draw(Terminal& term);

    /**
    *Draws space on the terminal where the sprayer's position is.
    *
    * @param term The Terminal the sprayer is erased from.
    */
    void dedraw(Terminal& term);
    private:
    Vec2D _position;
    int _color_fg;
    int _color_bg;
    int _hitpoints;
    int _shots;
    bool _is_built;
};

#endif
