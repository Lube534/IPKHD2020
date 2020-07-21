#ifndef LANE_H
#define LANE_H

#include <vector>
#include "Virus.h"
#include "Sprayer.h"
#include "Terminal.h"
#include "Cleaner.h"
#include "Projectile.h"


class Lane {
        
    public:
    Lane(int number, int start, int length);


    void draw(Terminal& term);
    
    void move_viruses();

    void draw_viruses(Terminal& term);

    void draw_sprayer(Terminal& term);

    void draw_projectiles(Terminal& term); 

    void move_projectiles();

    void update(Terminal& term, Cleaner& cleaner);

    void spawn_virus();

    void spawn_projectiles();

    void check_viruses(Terminal& term);

    void check_projectiles(Terminal& term);

    void build_sprayer(Cleaner& cleaner);

    void refill_sprayer(Cleaner& cleaner);

    int get_number();
    
    int get_start();

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
