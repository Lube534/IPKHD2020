#include <chrono>
#include "Terminal.h"
#include "Game.h"

int main()
{
    Terminal term(60,26);
    Game game(term);
    
    using namespace std::chrono;
    using fmilli = duration<float, seconds::period>;

    auto t0 = high_resolution_clock::now();
    auto t1 = high_resolution_clock::now();
    


    while (!game.is_done()) {
       
     
        
        t0 = t1;
        t1 = high_resolution_clock::now();

        game.game_tick(fmilli(t1 - t0).count());
        game.update(fmilli(t1 - t0).count()); 
        game.spawn_all_lanes(fmilli(t1-t0).count());
        game.spawn_all_projectiles(fmilli(t1-t0).count());
        game.draw_actives();
    

        
    }

    term.close();
    return 0;
}

