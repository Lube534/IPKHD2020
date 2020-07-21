#ifndef GAME_H
#define GAME_H

#include "Terminal.h"
#include <ncurses.h>
#include "Vec2D.h"
#include <chrono>
#include <vector>
#include <ctime>
#include <random>
#include "Color.h"
#include "Lane.h"
#include "Safespace.h"
#include "Sprayer.h"
#include "Cleaner.h"

class Game{
    public:
    /**
	* Initializes a new game
	*
	* @param term The terminal to draw our game on
	*/
    Game(Terminal&);

    bool is_done();
    
    void update(float dt);

    void game_tick(float ft);

    void draw_borders();
    
    void draw_statics();

    void draw_actives();

    void spawn_all_lanes(float dt);

    void spawn_all_projectiles(float dt);


    private:

        Terminal& _term;
        bool _game_over;
        bool _is_done;
        float _spawntime_virus;
        float _spawntime_projectile;
        float _ticktime;
        float _elapsed_time; 
        Vec2D _map_top_left;
        Vec2D _map_bottom_right;
        Lane _lane1;
        Lane _lane2;
        Lane _lane3;
        Lane _lane4;
        Lane _lane5;
        Safespace _safespace;
        Cleaner _cleaner;
};

#endif

