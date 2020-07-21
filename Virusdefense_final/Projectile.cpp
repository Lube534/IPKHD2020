#include "Projectile.h"


Projectile::Projectile(int y, color color):
_position(5, y + 2),
_prev_position(4, y + 2),
_color(color),
_is_destroyed(false),
_is_end_of_lane(false)
{}

Vec2D Projectile::get_position(){
    return _position;
}
Vec2D Projectile::get_prev_position(){
    return _prev_position;
}
color Projectile::get_color(){
    return _color;
}

bool Projectile::is_destroyed(){
    return _is_destroyed;
}

bool Projectile::is_end_of_lane(){
    return _is_end_of_lane;
}

void Projectile::move(){
    _prev_position = _position;
    _position.x += 1;
}

void Projectile::draw(Terminal& term){
   term.set_cell(_prev_position.x, _prev_position.y, ' ');

    switch(_color){
        case color::Blue:
            term.set_cell(_position.x, _position.y, 'b');
            break;    
                    
        case color::Green:
            term.set_cell(_position.x, _position.y, 'g');
            break;

        case color::Red:
            term.set_cell(_position.x, _position.y, 'r');
            break;
    }
}

void Projectile::dedraw(Terminal& term){
    
    term.set_cell(_position.x, _position.y, ' ');  
}
          