#ifndef GAME_H
#define GAME_H

#include "Terminal.h"
#include <ncurses.h>
#include "Vec2D.h"
#include <chrono>
#include <vector>
#include <ctime>
#include <random>
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

    /**
    * Returns true if the game should be quit.
    *
    * @return The game's _is_done.
    */
    bool is_done();

    /**
    * Returns true if the cleaner is hit by a virus.
    *
    * @return The game's _is_over.
    */

    bool is_over();

    /**
    * Returns true if the score reaches 100.
    *
    * @return The game's _is_won.
    */
    bool is_won();
    
    /**
    * Returns true if game is still on the startpage.
    *
    * @return True is _startpage < 2.
    */
    bool is_on_startpage();

    /**
    * Increments _startpage by 1.
    *
    * @return True is _startpage < 2.
    */
    void add_startpage();
    
    /**
    * Checks whether the cleaner was hit by a virus.
    * Calls the control-function of _cleaner.
    * Manages restart and quit.
    * Calls the update-funtion of the lanes.
    * Increases money.
    * 
    * @param dt The time difference in wallclock time.
    */
    void update(float dt);

    /**
    * Moves the viruses and the projectiles.
    *
    * @param dt The time difference in wallclock time..
    */
    void game_tick(float dt);

    /**
    * Draws the borders of the map at the begining of the game.
    *
    */
    void draw_borders();
    
    /**
    * Calls the draw_borders-function.
    * Calls the cleaner's draw-function.
    * Cals the lanes' draw_functions.
    *
    */
    void draw_statics();

    /**
    * Draws the game over screen if the game is over.
    * Calls the safespace's draw-function.
    * Calls the cleaner's draw-function.
    * Calls the draw_time_and_money-function.
    * Calls the draw_sprayer, draw_projectiles and draw_viruses-functions on all lanes.
    *
    */
    void draw_actives();

    /**
    * Calls the spawn_virus-function on a random lane.
    * Is triggered by _spanwtime_virus.
    *
    * @param dt The time difference in wallclock time.
    */
    void spawn_all_lanes(float dt);

    /**
    * Calls the spawn_projectiles-function on all lanes.
    * Is triggered by _spanwtime_projectile.
    *
    * @param dt The time difference in wallclock time.
    */
    void spawn_all_projectiles(float dt);

    /**
    * Draws the game over text in the middle of the terminal.
    *
    */
    void draw_game_over();
    
    /**
    * Draws the game won text in the middle of the terminal.
    *
    */
    void draw_game_won();
    
    /**
    * Draws the startpage text in the middle of the terminal.
    *
    */
    void draw_startpage();
    
    /**
    * Draws the elapsed time, the money and destroyed viruses.
    *
    */
    void draw_time_and_money();

    /**
    * Sets _spawntime_projectiles, _ticktime, _spawntime_virus and elapsed time to 0.
    *
    */
    void reset_timers();

    private:

        Terminal& _term;
        bool _game_over;
        bool _is_done;
        bool _is_won;
        int _startpage;
        float _spawntime_virus;  //Comparison variable for spawning of viruses
        float _spawner_virus; //How fast viruses are spawned
        float _spawntime_projectile; //Comparison variable for spawning of projectiles
        float _spawner_projectiles; //How fast projectiles are spwaned
        float _ticktime_virus; // Comparison variable for moving of viruses
        float _movetime_virus; // How fast viruses move
        float _ticktime_projectile; // Comparison variable for moving of projectiles 
        float _movetime_projectile; //How fast projectiles move
        float _moneytick; //How often you get money
        float _elapsed_time; 
        int _score;
        int _prescore;
        int _money;
        Vec2D _map_top_left;
        Vec2D _map_bottom_right;
        std::vector<Lane> _lanes;
        Safespace _safespace;
        Cleaner _cleaner;
};

#endif

