#ifndef LANE_H
#define LANE_H

#include <vector>
#include "Virus.h"
#include "Sprayer.h"
#include "Terminal.h"
#include "Cleaner.h"
#include "Projectile.h"
#include <random>


class Lane {
        
    public:
    
    /**
    * Constructor
    *
    * @param number The number of the lane.
    * @param start The y coordinate where the lane starts.
    * @param length The x coordinate where the lane ends.
    */
    Lane(int number, int start, int length);

    /**
    * Draws the lanes' upper and lower borders.
    *
    * @param term The terminal to draw on.
    */
    void draw(Terminal& term);

    /**
    * Calls the move-function for every virus in lane.
    */
    void move_viruses();

    /**
    * Calls the draw-funtion for every virus in lane.
    *
    * @param term The terminal to draw on.
    */
    void draw_viruses(Terminal& term);

    /**
    * Calls the draw-function of the lanes' sprayer.
    *
    * @param term The terminal to draw on.
    */
    void draw_sprayer(Terminal& term);

    /**
    * Calls the draw-function for every projectile in lane.
    *
    * @param term The terminal to draw on.
    */
    void draw_projectiles(Terminal& term); 

    /**
    * Calls the move-function for every projectile in lane.
    *
    * @param term The terminal to draw on.
    */
    void move_projectiles();

    /**
    * Tracks viruses, collisions, projectiles and
    * money loss due to building and refilling.
    *
    * @param term The terminal to draw on.
    * @param cleaner The cleaner.
    * @param safespace The safespace where the cleaner can move in.
    * @param money The current money.
    * @return The updated money after building and refilling.
    */
    int update(Terminal& term, Cleaner& cleaner, Safespace& safespace, int money);
    
    /**
    * Spawns a virus with a random color.
    *
    */
    void spawn_virus();
    /**
    * Spawns a projectile if a sprayer is build
    * and has enough shots left.
    *
    */
    void spawn_projectiles();

    /**
    * Erases viruses when on 0 HP and rewards money.
    * Lets viruses move around the safespace in a circle.
    * 
    * @param term The terminal to draw on.
    * @param safespace The safespace where the cleaner can move in.
    * @param money The current money.
    * @return the updated money after rewarding virus kills.
    */
    int check_viruses(Terminal& term, Safespace& safespace, int money);

    /**
    * Deletes projectiles at the end of the map.
    *
    * @param term The terminal to draw on.

    */
    void check_projectiles(Terminal& term);

    /**
    * Checks whether there are any collissions between viruses and the cleaner.
    * Marks the cleaner as collided, when hit.
    * Checks whether there are any collissions betwen viruses and projectiles.
    * Erases projectiles when they hit viruses.
    * Subtracts hit viruses' hitpoints.
    *
    * @param cleaner The cleaner.
    * @param term The terminal to draw on.
    */
    void check_collisions(Terminal& term, Cleaner& cleaner);
    
    /**
    * Checks whether the cleaner is in lane and wants to build a sprayer.
    * Checks the total sum of money.
    * Builds the sprayer if it is not already built.
    *
    * @param cleaner The cleaner.
    * @param money The current money.
    * @return True if the sprayer was built.
    */
    bool build_sprayer(Cleaner& cleaner, int money);

    /**
    * Sets the shots of the sprayer back to the Maximum.
    *
    * @param cleaner The cleaner.
    * @param money The current money.
    * @return True if the sprayer was refilled.
    */
    bool refill_sprayer(Cleaner& cleaner, int money);


    /**
    * Returns True if there is a sprayer in the lane.
    *
    * @return Returns whether the lane has a sprayer built or not.
    */
    bool sprayer_is_built();
    
    /**
    * Calls clear-function for _virus_in_lane.
    * Calls clear function for _projectiles in lane.
    * Calls destroy function for _sprayer.
    *
    */
    void reset();
    /**
    * Returns the nubmer of the current lane.
    * @return _number of the current lane.
    */
    int get_number();
    
    /**
    * Returns the y coordinate, where the lane starts.
    *
    * @return _start of the current lane.
    */
    int get_start();
    
    /**
    * Returns the length of the current lane.
    *
    * @return _length of the current lane.
    */
    int get_length();

    private:
    int _number;
    int _start;
    int _length;
    std::vector<Virus> _virus_in_lane;
    std::vector<Projectile> _projectiles_in_lane;
    Sprayer _sprayer;
    
};

#endif
