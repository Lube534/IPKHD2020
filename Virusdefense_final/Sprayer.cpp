#include "Sprayer.h"

Sprayer::Sprayer(int y):
    _position(5,y),
    _color_fg(BLUE_BLACK),
    _color_bg(BLACK_BLUE),
    _hitpoints(3),
    _shots(3),
    _is_built(false)
    {}

int Sprayer::get_color(){
    if(_is_built){
        return _color_fg;
    }
}

void Sprayer::change_color(Cleaner& cleaner){
    _color_fg = cleaner.get_color();
    if (cleaner.get_color() == BLUE_BLACK){
        _color_bg = BLACK_BLUE;
    }
    
    if (cleaner.get_color() == GREEN_BLACK){
        _color_bg = BLACK_GREEN;
    }

    if (cleaner.get_color() == RED_BLACK){
        _color_bg = BLACK_RED;
    }
    
    if (cleaner.get_color() == YELLOW_BLACK){
        _color_bg = BLACK_YELLOW;
    }
    
}

Vec2D Sprayer::get_position(){
    if(_is_built){
        return _position;
    }
}

int Sprayer::get_hitpoints(){
    if(_is_built){
        return _hitpoints;
    }
}

void Sprayer::lose_hitpoints(){
    if(_is_built){
        _hitpoints -= 1;
    }
}

void Sprayer::reset_hitpoints(){
    {
        _hitpoints = 3;
    }
}

int Sprayer::get_shots(){
    if(_is_built){
        return _shots;
    }
}

void Sprayer::reset_shots(){
    _shots = 3;
}

void Sprayer::shoot(){
    if(_is_built){
        _shots -= 1;
    }
}

bool Sprayer::get_is_built(){

    return _is_built;

}

void Sprayer::build(){
    _is_built = true;
}

void Sprayer::destroy(){
    _is_built = false;
}

void Sprayer::draw(Terminal& term){


    if(_is_built){

        if (_shots > 2){
            term.set_cell(_position.x, _position.y-1,'_', _color_bg);
            term.set_cell(_position.x, _position.y, '<', _color_bg);
            term.set_cell(_position.x, _position.y+1, ')', _color_bg);
                    
            term.set_cell(_position.x-1, _position.y-1, '_', _color_bg);
            term.set_cell(_position.x-1, _position.y, 'T', _color_bg);
            term.set_cell(_position.x-1, _position.y+1, '(', _color_bg);
        }

        else if (_shots > 1){
            term.set_cell(_position.x, _position.y-1,'_', _color_fg);
            term.set_cell(_position.x, _position.y, '<', _color_bg);
            term.set_cell(_position.x, _position.y+1, ')', _color_bg);
                    
            term.set_cell(_position.x-1, _position.y-1, '_', _color_fg);
            term.set_cell(_position.x-1, _position.y, 'T', _color_bg);
            term.set_cell(_position.x-1, _position.y+1, '(', _color_bg);
        }
        
        else if (_shots > 0){
            term.set_cell(_position.x, _position.y-1,'_', _color_fg);
            term.set_cell(_position.x, _position.y, '<', _color_fg);
            term.set_cell(_position.x, _position.y+1, ')', _color_bg);
                    
            term.set_cell(_position.x-1, _position.y-1, '_', _color_fg);
            term.set_cell(_position.x-1, _position.y, 'T', _color_fg);
            term.set_cell(_position.x-1, _position.y+1, '(', _color_bg);
        }

        else{
            term.set_cell(_position.x, _position.y-1,'_', _color_fg);
            term.set_cell(_position.x, _position.y, '<', _color_fg);
            term.set_cell(_position.x, _position.y+1, ')', _color_fg);
                    
            term.set_cell(_position.x-1, _position.y-1, '_', _color_fg);
            term.set_cell(_position.x-1, _position.y, 'T', _color_fg);
            term.set_cell(_position.x-1, _position.y+1, '(', _color_fg);
        }
        
    }
}

void Sprayer::dedraw(Terminal& term){


    term.set_cell(_position.x, _position.y-1,' ', _color_fg);
    term.set_cell(_position.x, _position.y, ' ', _color_fg);
    term.set_cell(_position.x, _position.y+1, ' ', _color_fg);
            
    term.set_cell(_position.x-1, _position.y-1, ' ', _color_fg);
    term.set_cell(_position.x-1, _position.y, ' ', _color_fg);
    term.set_cell(_position.x-1, _position.y+1, ' ', _color_fg);
}