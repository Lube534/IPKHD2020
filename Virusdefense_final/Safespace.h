#ifndef SAFESPACE_H
#define SAFESPACE_H

#include "Vec2D.h" 
#include "Terminal.h"   
    
class Safespace {
    public:

    /**
    * Constructor.
    *     *
    * @param top_left The coordinates of the top left corner of the safespace.
    * @param bottom_right The coordinates of the bottom right corner of the safespace.
    */
    Safespace(Vec2D top_left, Vec2D bottom_right);
    
    /**
    * Draws the safespace on the terminal.
    *
    * @param term The terminal the safespace is drawn on.
    */
    void draw(Terminal& term);

    /**
    * Returns the x and y coordinates of the safespace's top left corner.
    *
    */
    Vec2D get_top_left();

    /**
    * Returns the x and y coordinates of the safespace's bottom right corner.
    *
    */
    Vec2D get_bottom_right();
    
    private:
    const Vec2D _top_left;
    const Vec2D _bottom_right;


};

#endif
