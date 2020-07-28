#ifndef CLEANER_H
#define CLEANER_H

#include "Vec2D.h"
#include "Safespace.h"
#include "Terminal.h"
#include "Virus.h"

class Cleaner {
    public:
    
    /**
    * Constructor.
    *
    * @param x The x coorinate of the position.
    * @param y The y coorinate of the position.
    */
    Cleaner(int x, int y);
    
    /**
    * Returns the position of the cleaner.
    *
    * @return cleaner's _position.
    */
    Vec2D get_position();
    
    /**
    * Returns wheter the cleaner is building.
    *
    * @return cleaner's _is_building.
    */
    bool get_is_building();

    /**
    * Sets _is_building to false.
    *
    */
    void reset_is_building();

    /**
    * Returns wheter the cleaner is refilling.
    *
    * @return cleaner's _refilling.
    */
    bool get_refilling();

    /**
    *Sets _refilling to false.
    *
    */
    void reset_refilling();

    /**
    * Sets _collided to true.
    *
    */
    void collided();

    /**
    * Returns wheter the cleaner is collided with a virus.
    *
    * @return cleaner's _collided.
    */
    bool get_collided();

    /**
    * Returns the color of the cleaner.
    *
    * @return cleaner's _color.
    */
    int get_color();

    /**
    * Lets the user change the position of the cleaner.
    * Lets the user change the color of the cleaner.
    * Lets the user build with the cleaner.
    * Lets the user refill with the cleaner.
    *
    * @param key The key pressed by the user.
    * @param safespace The safespace where the cleaner can move in.
    */
    void control(char key, Safespace& safespace);

    /**
    * Draws the cleaner on the terminal.
    *
    * @param term The terminal the cleaner is drawn on.
    */
    void draw(Terminal& term);

    /**
    * Sets _position and _former_position to {2,2,}.
    * Sets _color to blue.
    * Sets _is_building, _refilling and _collided to false.
    *
    */
    void reset();

    private:
    Vec2D _position;
    int _color;
    Vec2D _former_position;
    bool _is_building;
    bool _refilling;
    bool _collided;

};

#endif