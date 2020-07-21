#include "Game.h"

Game::Game(Terminal& term) :
    _term(term),
    _game_over(false),
    _is_done(false),
    _spawntime_virus(0.f),
    _spawntime_projectile(0.f),
    _ticktime(0.f),
    _elapsed_time(0.f),
    _map_top_left(0,0),
    _map_bottom_right(50,22),
    _lane1(Lane(1, 1, 45)),
    _lane2(Lane(2, 5, 45)),
    _lane3(Lane(3, 9, 45)),
    _lane4(Lane(4, 13, 45)),
    _lane5(Lane(5, 17, 45)),
    _safespace(Safespace(Vec2D(0,0), Vec2D(3, 22))),
    _cleaner(Cleaner(2,2))
{    
    draw_statics();  
}

void Game::update(float dt){

    char pressed = _term.get_key();
    _cleaner.control(pressed, _safespace);
    switch (pressed)
    {
        case 'r':
            _game_over = false;
        
        case 'q':
            _is_done = true;
            break;
    
    default:
        break;
    }
    if (!_game_over) {
                    _lane1.update(_term, _cleaner);                   
                    _lane2.update(_term, _cleaner);                   
                    _lane3.update(_term, _cleaner);                   
                    _lane4.update(_term, _cleaner);                   
                    _lane5.update(_term, _cleaner);                   
                }

    _elapsed_time += dt;
    if (_elapsed_time >= 0.1f) 
    {}
    _elapsed_time = 0.f;
}

void Game::game_tick(float dt){
       _ticktime += dt;

       if (_ticktime >= 1.0f){
           
            _lane1.move_viruses();
            _lane1.move_projectiles();
            _lane2.move_viruses();
            _lane2.move_projectiles();
            _lane3.move_viruses();
            _lane3.move_projectiles();
            _lane4.move_viruses();
            _lane4.move_projectiles();
            _lane5.move_viruses();
            _lane5.move_projectiles();
            _ticktime = 0.f;
       }


   }
   
 void Game::draw_borders(){
        
        for(int y = _map_top_left.y; y <= _map_bottom_right.y; ++y)
            {
                _term.set_cell(_map_top_left.x, y, '#');
                _term.set_cell(_map_bottom_right.x, y, '#');
            }
            
            for(int x = _map_top_left.x; x <= _map_bottom_right.x; ++x)
            {
                _term.set_cell(x, _map_top_left.y, '#');
                _term.set_cell(x, _map_bottom_right.y, '#');
            }
            
    }

void Game::spawn_all_lanes(float dt){
    
    _spawntime_virus += dt;
    if(_spawntime_virus >= 5.0f){
        
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> lane(1, 5);
                            
        if (lane(gen) == 1){
            _lane1.spawn_virus();
        }
        else if (lane(gen) == 2){
            _lane2.spawn_virus();
        }
        else if (lane(gen) == 3){
            _lane3.spawn_virus();
        }
        else if (lane(gen) == 4){
            _lane4.spawn_virus();
        }
        else {
            _lane5.spawn_virus();
        };


        _spawntime_virus = 0.f;


    }
        
}

void Game::spawn_all_projectiles(float dt){

    _spawntime_projectile += dt;
    if(_spawntime_projectile >= 3.0f){
                            
         _lane1.spawn_projectiles();
         _lane2.spawn_projectiles();
         _lane3.spawn_projectiles();
         _lane4.spawn_projectiles();
         _lane5.spawn_projectiles();

        _spawntime_projectile = 0.f;
    }

}

void Game::draw_statics(){
        draw_borders();
        _cleaner.draw(_term);
        _lane1.draw(_term);
        _lane2.draw(_term);
        _lane3.draw(_term);
        _lane4.draw(_term);
        _lane5.draw(_term);

    }

void Game::draw_actives()
    { 
        _safespace.draw(_term);
        _cleaner.draw(_term);
        _lane1.draw_sprayer(_term);
        _lane1.draw_projectiles(_term);
        _lane1.draw_viruses(_term);

        _lane2.draw_sprayer(_term);
        _lane2.draw_projectiles(_term);
        _lane2.draw_viruses(_term);

        _lane3.draw_sprayer(_term);
        _lane3.draw_projectiles(_term);
        _lane3.draw_viruses(_term);
        
        _lane4.draw_sprayer(_term);
        _lane4.draw_projectiles(_term);
        _lane4.draw_viruses(_term);
        
        _lane5.draw_sprayer(_term);
        _lane5.draw_projectiles(_term);
        _lane5.draw_viruses(_term);
    }

bool Game::is_done()
    {
        return _is_done;
    }
    

