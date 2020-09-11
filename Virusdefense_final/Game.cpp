#include "Game.h"

Game::Game(Terminal& term) :
    _term(term),
    _game_over(false),
    _is_done(false),
    _is_won(false),
    _startpage(0),
    _spawntime_virus(0.f),
    _spawner_virus(5.0),
    _spawntime_projectile(0.f),
    _spawner_projectiles(3.0),
    _ticktime_virus(0.f),
    _movetime_virus(0.7),
    _ticktime_projectile(0.f),
    _movetime_projectile(0.7),
    _moneytick(0.f),
    _elapsed_time(0.f),
    _score(0),
    _prescore(0),
    _money(70),
    _map_top_left(0,0),
    _map_bottom_right(50,22),
    _safespace(Safespace(Vec2D(0,0), Vec2D(3, 22))),
    _cleaner(Cleaner(2,2))
{ _lanes = {{1,1,45}, {2,5,45}, {3,9,45},{4,13,45},{5,17,45}};
 draw_statics();  
}

bool Game::is_done(){
    return _is_done;
}

bool Game::is_over(){
    return _game_over;
}

bool Game::is_won(){
    return _is_won;
}

bool Game::is_on_startpage(){
    if(_startpage < 2){
        return true;
    }
    return false;
}

void Game::add_startpage(){
    _startpage += 1;
}

void Game::update(float dt){

    char pressed = _term.get_key();
    if(_cleaner.get_collided()){
        _game_over = true;
    }
    if(_score >= 99999){
        _is_won = true;
    }
    _cleaner.control(pressed, _safespace);
    switch (pressed)
    {
        case 'r':
            _game_over = false;
            _is_won = false;
            reset_timers();
            _money = 70;
            _score = 0;
            _term.clear();
            for (unsigned int i =0; i < _lanes.size(); i++){
                _lanes[i].reset();
            }

            _cleaner.reset();
            draw_statics();
            break;

        
        case 't':
            _is_done = true;
            break;


        break;
    }
    if (!_game_over||!_is_won) {
        for (unsigned int i = 0; i < _lanes.size(); i++){
                int tmp = 0;
                tmp += _lanes[i].update(_term, _cleaner, _safespace, _money)-_money;
                _money += tmp;
                if (tmp >=0){
                    _score += tmp/12;}

        }       
       

        _moneytick += dt;
        _elapsed_time += dt;
        if (_moneytick >= 3.f) {
            _money += 3;
            _moneytick = 0.f;}
    }
}

void Game::game_tick(float dt){
       
       _ticktime_virus += dt;
       _ticktime_projectile += dt;
       if (_score - _prescore >= 100){
           _movetime_virus *= 0.7;
           _movetime_projectile *= 0.7;
           _prescore = _score;

       }

       if (_ticktime_virus >= _movetime_virus){
           
           for (unsigned int i = 0; i < _lanes.size(); i++){
                _lanes[i].move_viruses();
            }

            _ticktime_virus = 0.f;
       }

       if (_ticktime_projectile >= _movetime_projectile){
           
           for (unsigned int i = 0; i < _lanes.size(); i++){
                _lanes[i].move_projectiles();
            }

            _ticktime_projectile = 0.f;
       }


   }
   
 void Game::draw_borders(){
        
        for(int y = _map_top_left.y; y <= _map_bottom_right.y; ++y)
            {
                _term.set_cell(_map_top_left.x, y, '#', WHITE_BLACK);
                _term.set_cell(_map_bottom_right.x, y, '#', WHITE_BLACK);
            }
            
            for(int x = _map_top_left.x; x <= _map_bottom_right.x; ++x)
            {
                _term.set_cell(x, _map_top_left.y, '#', WHITE_BLACK);
                _term.set_cell(x, _map_bottom_right.y, '#', WHITE_BLACK);
            }
            
    }

void Game::draw_statics(){

    draw_borders();
    _cleaner.draw(_term);
    for (unsigned int i = 0; i < _lanes.size(); i++){
                _lanes[i].draw(_term);
            }


}

void Game::draw_actives() { 
    if(_game_over){
        for(unsigned int i; i < _lanes.size(); i++){
            _lanes[i].reset();
        }
        draw_game_over();
        return;
    }
    if(_is_won){
        for(unsigned int i; i < _lanes.size(); i++){
            _lanes[i].reset();
        }
        draw_game_won();
        return;
    }
    
    _safespace.draw(_term);
    _cleaner.draw(_term);
    draw_time_and_money();
    for (unsigned int i = 0; i < _lanes.size(); i++){
        _lanes[i].draw_sprayer(_term);
        _lanes[i].draw_projectiles(_term);
        _lanes[i].draw_viruses(_term);
    }
}

void Game::spawn_all_lanes(float dt){
    
    bool full_lanes = true;
    for (unsigned int i = 0; i < _lanes.size(); i++){
        if(!_lanes[i].sprayer_is_built()){
            full_lanes = false;
        }
    }

    if(full_lanes){
        _spawner_virus = 2.5;
    }
    else{
        _spawner_virus = 5;
    }
    _spawntime_virus += dt;
    if(_spawntime_virus >= _spawner_virus){
        
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> lane(0, 4);

        _lanes[lane(gen)].spawn_virus();                   
        _spawntime_virus = 0.f;
    }
}
   
void Game::spawn_all_projectiles(float dt){

    if (_score - _prescore >= 100){
        _spawner_projectiles *= 0.9;
        _prescore = _score;
    }
    _spawntime_projectile += dt;
    if(_spawntime_projectile >= _spawner_projectiles){
        for (unsigned int i = 0; i < _lanes.size(); i++){
                _lanes[i].spawn_projectiles();
            }
                            

        _spawntime_projectile = 0.f;
    }

}

void Game::draw_game_over(){
    std::string game_over_text = "Game Over!";
    std::string score_text = "Your score is " + std::to_string(_score) + "!";
    std::string reset_text = "Press 'r' to restart.";

    int half_width = _term.width() / 2;
    int half_height = _term.height() / 2;

    _term.clear();
    _term.draw_text(half_width - game_over_text.size()/2, half_height, game_over_text);
    _term.draw_text(half_width - score_text.size()/2, half_height + 1, score_text);
    _term.draw_text(half_width - reset_text.size()/2, half_height + 2, reset_text);

    _term.sleep(4);
}

void Game::draw_game_won(){
    std::string game_won_text = "Congratulation! You Won the game!";
    std::string score_text = "Your score is " + std::to_string(_score) + "!";
    std::string reset_text = "Press 'r' to restart.";

    int half_width = _term.width() / 2;
    int half_height = _term.height() / 2;

    _term.clear();
    _term.draw_text(half_width - score_text.size()/2, half_height, game_won_text);
    _term.draw_text(half_width - score_text.size()/2, half_height + 1, score_text);
    _term.draw_text(half_width - reset_text.size()/2, half_height + 2, reset_text);

    _term.sleep(4);
}

void Game::draw_startpage(){
    
    std::string line1;
    std::string line2;
    std::string line3;
    std::string line4;
    std::string line5;
    std::string line6;
    std::string line7;
    std::string line8;
    std::string line9;
    std::string line10;
    if (_startpage == 0){
        line1 = "Welcome to VIRUS DEFENSE";
        line2 = "In this lane tower defense your goal is to kill 100 viruses.";
        line3 = "The viruses will spawn on the left and move towards you.";
        line4 = "You are a cleaner and build desinfection sprayers.";
        line5 = "Use matching colors for maximum effectivity.";
        line6 = "Money is short, but refilling still costs money.";
        line7 = "3 Viruses break one sprayer so you have to build it again.";
        line8 = "Viruses kill on touch but die in the safespace.";
        line9 = "Destroying viruses gets you money and so does time elapsing.";
        line10 = "Press y to continue";
    }
    else{
        line1 = "Game controls:";
        line3 = "Move up: i, Move down: k, Move right: l, Move left: j";
        line4 = "Build a Sprayer: d; costs 60 Viros";
        line5 = "Refill a sprayer with your color: Space; costs 10 Viros";
        line6 = "Change your color: q";
        line7 = "Restart: r";
        line8 = "Terminate the game: t";
        line9 = "So lets go and kick some spike proteins!";
        line10 = "Press y to start!";

    }

    int half_width = _term.width() / 2;
    int half_height = _term.height() / 2;

    _term.clear();
    _term.draw_text(half_width - line1.size()/2, half_height-4, line1);
    _term.draw_text(half_width - line2.size()/2, half_height-3, line2);
    _term.draw_text(half_width - line3.size()/2, half_height-2, line3);
    _term.draw_text(half_width - line4.size()/2, half_height-1, line4);
    _term.draw_text(half_width - line5.size()/2, half_height, line5);
    _term.draw_text(half_width - line6.size()/2, half_height+1, line6);
    _term.draw_text(half_width - line7.size()/2, half_height+2, line7);
    _term.draw_text(half_width - line8.size()/2, half_height+3, line8);
    _term.draw_text(half_width - line9.size()/2, half_height+4, line9);
    _term.draw_text(half_width - line10.size()/2, half_height+5, line10);

    _term.sleep(4);
}

void Game::draw_time_and_money(){
    std::string time = "Time elapsed: " + std::to_string((int)_elapsed_time) + " seconds";
    std::string money = "Money: " + std::to_string(_money) + " Viros";
    std::string viruses = "Viruses destroyed: " + std::to_string(_score);
    std::string clear_string = "                                          ";

    int left = 1;
    int bottom = _map_bottom_right.y + 1;

    _term.draw_text(left, bottom, clear_string);
    _term.draw_text(left, bottom, money);
    _term.draw_text(left, bottom + 1, viruses);
    _term.draw_text(left, bottom + 2, time);
}

void Game::reset_timers(){
    _spawntime_projectile = 0;
    _spawntime_virus = 0;
    _ticktime_virus = 0;
    _ticktime_projectile = 0;
    _elapsed_time = 0;
    _movetime_projectile = 0.7;
    _movetime_virus = 0.7;
    _spawner_projectiles = 3.0;
    _spawner_virus = 5.0;
    
}