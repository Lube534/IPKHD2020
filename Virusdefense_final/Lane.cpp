#include "Lane.h"

Lane::Lane(int number, int start, int length):
_number(number),
_start(start),
_length(length),
_sprayer(start+2)            
{}


void Lane::draw(Terminal& term){
    for (int x = 0; x <= _length; ++x){
        term.set_cell(x+4, _start, '-');
        if(_number == 5){
            term.set_cell(x+4, _start+4, '-');
        }    
    }           
};

void Lane::move_viruses(){
    if (!_virus_in_lane.empty()){
        for(unsigned int i = 0; i < _virus_in_lane.size(); i++){
            _virus_in_lane[i].move();
        }
    }
};

void Lane::draw_viruses(Terminal& term){
    if (!_virus_in_lane.empty()){
            
        for (unsigned int i = 0; i < _virus_in_lane.size(); i++){
                _virus_in_lane[i].draw(term);
       }            
    }
}

void Lane::draw_sprayer(Terminal& term){
    if (_sprayer.get_is_build()){
        _sprayer.draw(term);
    }
}

void Lane::draw_projectiles(Terminal& term){
    if (!_projectiles_in_lane.empty()){

        for (unsigned int i = 0; i < _projectiles_in_lane.size(); i++){
            _projectiles_in_lane[i].draw(term);
        }
    }
}

void Lane::move_projectiles(){
    if (!_projectiles_in_lane.empty()){
        for(unsigned int i = 0; i < _projectiles_in_lane.size(); i ++){
            _projectiles_in_lane[i].move();
        }
    }
}

void Lane::update(Terminal& term, Cleaner& cleaner){
    check_viruses(term);
    check_projectiles(term);
    build_sprayer(cleaner);
    refill_sprayer(cleaner);           
}

void Lane::spawn_virus(){
    int rd = rand() % 3;
    if (rd == 0){
        Virus new_virus(_length+4, _start, color::Blue);
        _virus_in_lane.push_back(new_virus);
    }
    else if (rd == 1){
        Virus new_virus(_length+4, _start, color::Green);
        _virus_in_lane.push_back(new_virus); 
    }
    else {
        Virus new_virus(_length+4, _start, color::Red);
        _virus_in_lane.push_back(new_virus);
    }

}

void Lane::spawn_projectiles(){
    if(_sprayer.get_is_build()){
        Projectile new_projectile(_start, _sprayer.get_color());
        _projectiles_in_lane.push_back(new_projectile);
    }
}

void Lane::check_viruses(Terminal& term){
    if(!_virus_in_lane.empty()){
        for (unsigned int i = 0; i < _virus_in_lane.size(); i++){
            if (_virus_in_lane[i].get_position().x <= 4 
            || _virus_in_lane[i].get_hitpoints() <= 0){
                _virus_in_lane[i].dedraw(term);
                _virus_in_lane.erase(_virus_in_lane.begin()+i);
            }   
        }   
    }
}

void Lane::check_projectiles(Terminal& term){
    if(!_projectiles_in_lane.empty()){
        for (unsigned int i = 0; i < _projectiles_in_lane.size(); i++){
            if(_projectiles_in_lane[i].get_position().x >= 48){
                _projectiles_in_lane[i].dedraw(term);
                _projectiles_in_lane.erase(_projectiles_in_lane.begin()+i);
            }
        }
    }
}

void Lane::build_sprayer(Cleaner& cleaner){
    if (cleaner.get_position().y == _start+1 && cleaner.get_is_building()){
        _sprayer.change_color(cleaner);
        _sprayer.build();
        cleaner.reset_is_building();
    }
}

void Lane::refill_sprayer(Cleaner& cleaner){
    if (cleaner.get_position().y == _start+1 && cleaner.get_refilling()){
        _sprayer.change_color(cleaner);
        cleaner.reset_refilling();
    }
}

int Lane::get_number(){
    return _number;
}

int Lane::get_start(){
    return _start;
}

int Lane::get_length(){
    return _length;
}
