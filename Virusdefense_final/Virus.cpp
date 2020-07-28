#include "Virus.h"

Virus::Virus(int x, int y, int color):
_position(x, y + 2),
_prev_position(x, y + 2),
_color(color),
_direction(Directions::Left),
_hitpoints(6),
_is_destroyed(false),
_is_in_safespace(false),
_round_done(false)
{}

Vec2D Virus::get_position(){
    return _position;
}

Vec2D Virus::get_prev_position(){
    return _prev_position;
}

int Virus::get_color(){
    return _color;
}

int Virus::get_hitpoints(){
    return _hitpoints;
}

void Virus::reset_hitpoints(){
    _hitpoints = 6;
}

void Virus::substract_hitpoints(){
    _hitpoints -= 1;
}

bool Virus::get_flag(){
    return _round_done;
}

void Virus::set_flag(){
    _round_done = true;
}

Directions Virus::get_direction(){
    return _direction;
}

void Virus::change_direction(Directions direction){
    _direction = direction;
}

bool Virus::is_destroyed(){
    return _is_destroyed;
}

bool Virus::is_in_safespace(){
    return _is_in_safespace;
}

void Virus::change_is_in_safespace(){
    _is_in_safespace = true;
}

void Virus::move(){
     _prev_position = _position;
    if(!_is_in_safespace){
    _position.x = _position.x - 1;
    }
    else{
        switch(_direction){
            case Directions::Down:
                _position.y += 1;
                break;

            
            case Directions::Up:
                _position.y -= 1;
                break;

            case Directions::Left:
                _position.x -= 1;
                break;
                
            case Directions::Right:
                _position.x += 1;
                break;
        }
    }
}

void Virus::draw_hull(Terminal& term){
    term.set_cell(_prev_position.x-1, _prev_position.y, ' ', _color);
    term.set_cell(_prev_position.x+1, _prev_position.y, ' ', _color);
    term.set_cell(_position.x-1, _position.y, '{', _color);
    term.set_cell(_position.x+1, _position.y, '}', _color);
    
}

void Virus::draw(Terminal& term){
    term.set_cell(_prev_position.x, _prev_position.y, ' ', _color);
    
    switch(_is_in_safespace){
        case true:
            term.set_cell(_position.x, _position.y, '@', _color);
            break;    
                    
        case false:
            draw_hull(term);
            term.set_cell(_position.x, _position.y, '@', _color);
            break;
    }
}

void Virus::dedraw(Terminal& term){
    
    term.set_cell(_prev_position.x, _prev_position.y, ' ', _color);  
    term.set_cell(_position.x, _position.y, ' ', _color);  
    term.set_cell(_position.x-1, _position.y, ' ', _color);  
    term.set_cell(_prev_position.x+1, _prev_position.y, ' ', _color);  
}
            