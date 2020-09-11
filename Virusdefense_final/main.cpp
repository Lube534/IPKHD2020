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


        if(game.is_on_startpage()){
            game.draw_startpage();
            char prePressed = term.get_key();
            switch (prePressed)
            {
            case 'y':
                game.add_startpage();
                break;

            case 't':
                term.close();
                return 0;
            
            default:
                break;
            }

            term.clear(); 
            }
        
        else if (!game.is_over() || !game.is_won()){
            t0 = high_resolution_clock::now();
            term.sleep(1);
            t1 = high_resolution_clock::now();
            game.game_tick(fmilli(t1 - t0).count());
            game.update(fmilli(t1 - t0).count()); 
            game.spawn_all_lanes(fmilli(t1-t0).count());
            game.spawn_all_projectiles(fmilli(t1-t0).count());
            game.draw_statics();
            game.draw_actives();

        }
    
        

    }


    term.close();
    return 0;
}

