#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vec2D.h"
#include "Color.h"
#include "Terminal.h"

class Projectile {
    public:
    Projectile(int y, color color);

    Vec2D get_position();

    Vec2D get_prev_position();

    color get_color();
        
    bool is_destroyed();

    bool is_end_of_lane();

    void move();

    void draw(Terminal& term);

    void dedraw(Terminal& term);

    private:
    Vec2D _position;
    Vec2D _prev_position;
    color _color;
    bool _is_destroyed;
    bool _is_end_of_lane;
};

#endif
