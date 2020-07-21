#include "Cleaner.h"

Cleaner::Cleaner(int x, int y):
_position(x,y),
_color(color::Blue),
_former_position(x,y),
_is_building(false),
_refilling(false)
{}

Vec2D Cleaner::get_position(){
    return _position;
}

bool Cleaner::get_is_building(){
    return _is_building;
}

void Cleaner::reset_is_building(){
    _is_building = false;
}

bool Cleaner::get_refilling(){
    return _refilling;
}

void Cleaner::reset_refilling(){
    _refilling = false;
}

color Cleaner::get_color(){
    return _color;
}

void Cleaner::control(char key, Safespace& safespace){

    switch(key){

        case 'i':
            if(_position.y > safespace.get_top_left().y+1){
                _former_position = _position;
                _position.y--;
            }
            _is_building = false;
            _refilling = false;
        break;

        case 'k':
            if(_position.y < safespace.get_bottom_right().y-3){
                _former_position = _position;
                _position.y++;
            }
            _is_building = false;
            _refilling = false;
            break;

        case 'j':
            if(_position.x > safespace.get_top_left().x+1){
                _former_position = _position;
                _position.x--;
            }
            _is_building = false;
            _refilling = false;
            break;

        case 'l':
            if(_position.x < safespace.get_bottom_right().x-1){
                _former_position = _position;
                _position.x++;
            }
            _is_building = false;
            _refilling = false;
            break;

        case 'a':
            if (_color == color::Blue){
                _color = color::Green;
            }
            else if (_color == color::Green){
                _color = color::Red;
            }
            else{
                _color = color::Blue;
            }
            break;
        
        case 's':
            _is_building = true;
            _refilling = false;
            break;

        case 'c':
            _refilling = true;
            _is_building = false;
            break;
            
        
        default:
            break;
    }

}

void Cleaner::draw(Terminal& term){
    term.set_cell(_former_position.x, _former_position.y, ' ');
    term.set_cell(_former_position.x, _former_position.y+1, ' ');
    term.set_cell(_former_position.x, _former_position.y+2, ' ');
    
    switch(_color){
        case color::Blue:
            term.set_cell(_position.x, _position.y, 'B');
            term.set_cell(_position.x, _position.y+1,'H');
            term.set_cell(_position.x, _position.y+2, 'L');
            break;

        case color::Green:
            term.set_cell(_position.x, _position.y, 'G');
            term.set_cell(_position.x, _position.y+1, 'H');
            term.set_cell(_position.x, _position.y+2, 'L');
            break;

        case color::Red:
            term.set_cell(_position.x, _position.y, 'R');
            term.set_cell(_position.x, _position.y+1, 'H');
            term.set_cell(_position.x, _position.y+2, 'L');
            break;     
    }
    
}
