#ifndef CLEANER_H
#define CLEANER_H

#include "Vec2D.h"
#include "Color.h"
#include "Safespace.h"
#include "Terminal.h"

class Cleaner {
    public:
    Cleaner(int x, int y);
    
    Vec2D get_position();
    
    bool get_is_building();

    void reset_is_building();

    bool get_refilling();

    void reset_refilling();

    color get_color();

    void control(char key, Safespace& safespace);

    void draw(Terminal& term);

    private:
    Vec2D _position;
    color _color;
    Vec2D _former_position;
    bool _is_building;
    bool _refilling;

};

#endif