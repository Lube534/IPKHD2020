#include "Lane.h"

Lane::Lane(int number, int start, int length):
_number(number),
_start(start),
_length(length),
_sprayer(start+2)            
{}


void Lane::draw(Terminal& term){
    for (int x = 0; x <= _length; ++x){
        term.set_cell(x+4, _start, '-', WHITE_BLACK);
        if(_number == 5){
            term.set_cell(x+4, _start+4, '-', WHITE_BLACK);
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
    if (_sprayer.get_is_built()){
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

int Lane::update(Terminal& term, Cleaner& cleaner, Safespace& safespace, int money){
    money = check_viruses(term, safespace, money);
    check_collisions(term, cleaner);
    check_projectiles(term);
    check_collisions(term, cleaner);
    if(build_sprayer(cleaner, money)){
        money -= 60;
    }
    
    if(refill_sprayer(cleaner, money)){
        money -= 10;
    }          
    if(_sprayer.get_hitpoints()<=0){
        _sprayer.dedraw(term);
        _sprayer.reset_hitpoints();
        _sprayer.reset_shots();
        _sprayer.destroy();
    } 
    return money;
}

void Lane::spawn_virus(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> cl(1, 3);
    
    if (cl(gen) == 1){
        Virus new_virus(_length+4, _start, BLUE_BLACK);
        _virus_in_lane.push_back(new_virus);
    }
    else if (cl(gen) == 2){
        Virus new_virus(_length+4, _start, GREEN_BLACK);
        _virus_in_lane.push_back(new_virus); 
    }
    else if(cl(gen) == 3){
        Virus new_virus(_length+4, _start, RED_BLACK);
        _virus_in_lane.push_back(new_virus);
    }

    else {
        Virus new_virus(_length+4, _start, YELLOW_BLACK);
        _virus_in_lane.push_back(new_virus);
    }

}

void Lane::spawn_projectiles(){
    if(_sprayer.get_is_built()&&_sprayer.get_shots() > 0){
        Projectile new_projectile(_start, _sprayer.get_color());
        _projectiles_in_lane.push_back(new_projectile);
        _sprayer.shoot();
    }
}

int Lane::check_viruses(Terminal& term, Safespace& safespace, int money){
    
    if(!_virus_in_lane.empty()){
        for (unsigned int i = 0; i < _virus_in_lane.size(); i++){
            if (_virus_in_lane[i].get_hitpoints() <= 0){
                // if (!_virus_in_lane[i].is_in_safespace()){
                money += 12;
                // }
                _virus_in_lane[i].dedraw(term);
                _virus_in_lane.erase(_virus_in_lane.begin()+i);
            }   
            
            if(_virus_in_lane[i].get_position().x == safespace.get_bottom_right().x-1
                && !_virus_in_lane[i].is_in_safespace()){
                _virus_in_lane[i].change_is_in_safespace();
                _virus_in_lane[i].reset_hitpoints();
            }

            if(_virus_in_lane[i].get_position().x == safespace.get_top_left().x + 1
                && _virus_in_lane[i].get_position().y == safespace.get_top_left().y + 1
                && _virus_in_lane[i].get_direction() != Directions::Down){

                // Substract the half HP of the virus at the top left corner
                // When it reaches this corner twice, it will auto die.
                _virus_in_lane[i].change_direction(Directions::Down);
                _virus_in_lane[i].substract_hitpoints();
                _virus_in_lane[i].substract_hitpoints();
                _virus_in_lane[i].substract_hitpoints();
            
            }

            if (_virus_in_lane[i].get_position().x == safespace.get_bottom_right().x - 1){
                _virus_in_lane[i].change_direction(Directions::Up);
            }
            
            if (_virus_in_lane[i].get_position().x == safespace.get_bottom_right().x - 1
            && _virus_in_lane[i].get_position().y == safespace.get_top_left().y + 1){
                _virus_in_lane[i].change_direction(Directions::Left);
            }

            if (_virus_in_lane[i].get_position().x == safespace.get_top_left().x + 1 
                && _virus_in_lane[i].get_position().y == safespace.get_bottom_right().y - 1
                && _virus_in_lane[i].is_in_safespace()){
                _virus_in_lane[i].change_direction(Directions::Right);
            }
        }   
    }
return money;
}

void Lane::check_projectiles(Terminal& term){
    if(!_projectiles_in_lane.empty()){
        for (unsigned int i = 0; i < _projectiles_in_lane.size(); i++){
            if(_projectiles_in_lane[i].get_position().x >= _length+4){
                _projectiles_in_lane[i].dedraw(term);
                _projectiles_in_lane.erase(_projectiles_in_lane.begin()+i);
            }
        }
    }
}

void Lane::check_collisions(Terminal& term, Cleaner& cleaner){
    
    if(!_virus_in_lane.empty()){
        for(unsigned int i = 0; i < _virus_in_lane.size(); i++){
            if(_virus_in_lane[i].get_position().x == cleaner.get_position().x
                && (_virus_in_lane[i].get_position().y == cleaner.get_position().y
                || _virus_in_lane[i].get_position().y == cleaner.get_position().y+1
                || _virus_in_lane[i].get_position().y == cleaner.get_position().y+2)){
                    cleaner.collided();
                    return;
            }
        }
    }
    if(!_virus_in_lane.empty() && _sprayer.get_is_built()){    
        for(unsigned int i = 0; i < _virus_in_lane.size(); i++){
            if((_virus_in_lane[i].get_position().x == _sprayer.get_position().x
            ||_virus_in_lane[i].get_position().x == _sprayer.get_position().x-1)
                && _virus_in_lane[i].get_position().y == _sprayer.get_position().y){
                    _sprayer.lose_hitpoints();
                    _virus_in_lane[i].dedraw(term);
                    _virus_in_lane.erase(_virus_in_lane.begin()+i);
            }
        }
    }  
        
    if(!_virus_in_lane.empty() && !_projectiles_in_lane.empty()){
        for(unsigned int i = 0; i < _virus_in_lane.size(); i++){
            for(unsigned int j = 0; j < _projectiles_in_lane.size(); j++){

                if (_virus_in_lane[i].get_position().x == _projectiles_in_lane[j].get_position().x
                    || _virus_in_lane[i].get_position().x == _projectiles_in_lane[j].get_prev_position().x){
                    if(_virus_in_lane[i].get_color() == _projectiles_in_lane[j].get_color()){
                        _virus_in_lane[i].substract_hitpoints();
                        _virus_in_lane[i].substract_hitpoints();
                        _projectiles_in_lane[j].dedraw(term);
                        _projectiles_in_lane.erase(_projectiles_in_lane.begin()+j);
                    }  

                    else
                    {
                        _virus_in_lane[i].substract_hitpoints();
                        _projectiles_in_lane[j].dedraw(term);
                        _projectiles_in_lane.erase(_projectiles_in_lane.begin()+j);
                    }    
                }
            }
        }
    }
}

bool Lane::build_sprayer(Cleaner& cleaner, int money){
    if (cleaner.get_position().y == _start+1 
    && cleaner.get_is_building() 
    && money >= 60 
    && !_sprayer.get_is_built()){
        _sprayer.change_color(cleaner);
        _sprayer.build();
        cleaner.reset_is_building();
       return true;
    }
    return false;
}

bool Lane::refill_sprayer(Cleaner& cleaner, int money){
    if (cleaner.get_position().y == _start+1 
        &&_sprayer.get_is_built()
        && cleaner.get_refilling()
        && money >= 10){
        _sprayer.change_color(cleaner);
        _sprayer.reset_shots();
        cleaner.reset_refilling();
        return true;
    }
    return false;
}

bool Lane::sprayer_is_built(){
    return _sprayer.get_is_built();
}

void Lane::reset(){
    _virus_in_lane.clear();
    _projectiles_in_lane.clear();
    _sprayer.destroy();
    _sprayer.reset_hitpoints();
    _sprayer.reset_shots();
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
