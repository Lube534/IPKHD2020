#include "Projectile.h"


Projectile::Projectile(int y, int color):
_position(6, y + 2),
_prev_position(6, y + 2),
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

int Projectile::get_color(){
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
   term.set_cell(_prev_position.x, _prev_position.y, ' ', _color);
   term.set_cell(_position.x, _position.y, '*', _color);

}

void Projectile::dedraw(Terminal& term){
    
    term.set_cell(_position.x, _position.y, ' ', _color);  
    term.set_cell(_prev_position.x, _prev_position.y, ' ', _color);  
}
          