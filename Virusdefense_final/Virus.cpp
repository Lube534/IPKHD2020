#include "Virus.h"


Virus::Virus(int x, int y, color color):
_position(x, y + 2),
_prev_position(x, y + 2),
_color(color),
_hitpoints(6),
_is_destroyed(false),
_is_end_of_lane(false)
{}

Vec2D Virus::get_position(){
    return _position;
}

Vec2D Virus::get_prev_position(){
    return _prev_position;
}

color Virus::get_color(){
    return _color;
}

int Virus::get_hitpoints(){
    return _hitpoints;
}

bool Virus::is_destroyed(){
    return _is_destroyed;
}

bool Virus::is_end_of_lane(){
    return _is_end_of_lane;
}

void Virus::move(){
    _prev_position = _position;
    _position.x = _position.x - 1;
}

void Virus::draw(Terminal& term){
    term.set_cell(_prev_position.x, _prev_position.y, ' ');
    term.set_cell(_prev_position.x-1, _prev_position.y, ' ');
    term.set_cell(_prev_position.x+1, _prev_position.y, ' ');
    
    switch(_color){
        case color::Blue:
            term.set_cell(_position.x, _position.y, 'B');
            term.set_cell(_position.x-1, _position.y, '{');
            term.set_cell(_position.x+1, _position.y, '}');
            break;    
                    
        case color::Green:
            term.set_cell(_position.x, _position.y, 'G');
            term.set_cell(_position.x-1, _position.y, '{');
            term.set_cell(_position.x+1, _position.y, '}');

            break;

        case color::Red:
            term.set_cell(_position.x, _position.y, 'R');
            term.set_cell(_position.x-1, _position.y, '{');
            term.set_cell(_position.x+1, _position.y, '}');

            break;
    }
}

void Virus::dedraw(Terminal& term){
    
    term.set_cell(_position.x, _position.y, ' ');  
    term.set_cell(_position.x-1, _position.y, ' ');  
    term.set_cell(_position.x+1, _position.y, ' ');  
}
            