#ifndef SPRAYER_H
#define SPRAYER_H

#include "Vec2D.h"
#include "Color.h"
#include "Terminal.h"
#include "Cleaner.h"

class Sprayer{
    public:

    Sprayer(int y);

    color get_color();

    void change_color(Cleaner& cleaner);

    Vec2D get_position();

    int get_hitpoints();

    void lose_hitpoints();

    void reset_hitpoints();

    int get_shots();

    void shoot();

    bool get_is_build();

    void build();

    void destroy();

    void draw(Terminal& term);

    private:
    Vec2D _position;
    color _color;
    int _hitpoints;
    int _shots;
    bool _is_build;
};

#endif
