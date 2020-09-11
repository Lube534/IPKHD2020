#include "Cleaner.h"

Cleaner::Cleaner(int x, int y):
_position(x,y),
_color(BLUE_BLACK),
_former_position(x,y),
_is_building(false),
_refilling(false),
_collided(false)
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

void Cleaner::collided(){
    _collided = true;

}

bool Cleaner::get_collided(){
    return _collided;
}

int Cleaner::get_color(){
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

        case 'q':
            if (_color == BLUE_BLACK){
                _color = GREEN_BLACK;
            }
            else if (_color == GREEN_BLACK){
                _color = RED_BLACK;
            }
            else if (_color == RED_BLACK){
                _color = YELLOW_BLACK;
            }
            else {
                _color = BLUE_BLACK;
            }
            break;
        
        case 'd':
            _is_building = true;
            _refilling = false;
            break;

        case ' ':
            _refilling = true;
            _is_building = false;
            break;
            
        
        default:
            break;
    }

}

void Cleaner::draw(Terminal& term){
    term.set_cell(_former_position.x, _former_position.y, ' ', _color);
    term.set_cell(_former_position.x, _former_position.y+1, ' ', _color);
    term.set_cell(_former_position.x, _former_position.y+2, ' ', _color);
    
    term.set_cell(_position.x, _position.y, 'o', _color);
    term.set_cell(_position.x, _position.y+1,'D', _color);
    term.set_cell(_position.x, _position.y+2, 'L', _color);
}

void Cleaner::reset(){
    _position = {2,2};
    _former_position = {2,2};
    _color = BLUE_BLACK;
    _is_building = false;
    _refilling = false;
    _collided = false;
}