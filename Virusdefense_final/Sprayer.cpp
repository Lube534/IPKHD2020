#include "Sprayer.h"

Sprayer::Sprayer(int y):
    _position(5,y),
    _color(color::Blue),
    _hitpoints(5),
    _shots(6),
    _is_build(false)
    {}

color Sprayer::get_color(){
    if(_is_build){
        return _color;
    }
}

void Sprayer::change_color(Cleaner& cleaner){
    _color = cleaner.get_color();
    _hitpoints = 6;
}

Vec2D Sprayer::get_position(){
    if(_is_build){
        return _position;
    }
}

int Sprayer::get_hitpoints(){
    if(_is_build){
        return _hitpoints;
    }
}

void Sprayer::lose_hitpoints(){
    if(_is_build){
        _hitpoints -= 1;
    }
}

void Sprayer::reset_hitpoints(){
    if(_is_build){
        _hitpoints = 6;
    }
}

int Sprayer::get_shots(){
    if(_is_build){
        return _shots;
    }
}

void Sprayer::shoot(){
    if(_is_build){
        _shots -= 1;
    }
}

bool Sprayer::get_is_build(){
    if(_is_build){
        return _is_build;
    }
}

void Sprayer::build(){
    _is_build = true;
}

void Sprayer::destroy(){
    _is_build = false;
}

void Sprayer::draw(Terminal& term){
    if(_is_build){
        term.set_cell(_position.x, _position.y-1,'>');
        term.set_cell(_position.x, _position.y, '\'');
        term.set_cell(_position.x, _position.y+1, ')');
                
        term.set_cell(_position.x-1, _position.y, '|');
        term.set_cell(_position.x-1, _position.y+1, '(');
        
        switch(_color){
            case color::Blue:
                term.set_cell(_position.x-1, _position.y-1,'B');
                break;

            case color::Green:
                term.set_cell(_position.x-1, _position.y-1,'G');
                break;

            case color::Red:
                term.set_cell(_position.x-1, _position.y-1,'R');
                break;     
        }
    }
}
