#include "Terminal.h"
#include <ncurses.h>
#include "Vec2D.h"
#include <chrono>
#include <vector>
#include <ctime>
#include <random>



class Game {
    
    public:
    
    Game(Terminal& term) :
        _elapsed_time(0.f),
        _ticktime(0.f),
        _spawntime(0.f),
        _game_over(false),
        _is_done(false),
        _term(term),
        _cleaner(Cleaner(2,2)),
        _safespace(Safespace(Vec2D(0,0), Vec2D(3, 22))),
        _lane1(Lane(1, 1, 45)),
        _lane2(Lane(2, 5, 45)),
        _lane3(Lane(3, 9, 45)),
        _lane4(Lane(4, 13, 45)),
        _lane5(Lane(5, 17, 45)),
        _map_top_left(0,0),
        _map_bottom_right(50,22)
    {    
        draw_statics();  
    }

    class Safespace {
        public:
        Safespace(Vec2D top_left, Vec2D bottom_right):
        _top_left(top_left),
        _bottom_right(bottom_right)
        {}
        
        void draw(Terminal& term){
            
            for(int y = _top_left.y; y <= _bottom_right.y; ++y)
            {
                term.set_cell(_top_left.x, y, '#');
                term.set_cell(_bottom_right.x, y, '|');
            }
            
            for(int x = _top_left.x; x <= _bottom_right.x; ++x)
            {
                term.set_cell(x, _top_left.y, '#');
                term.set_cell(x, _bottom_right.y, '#');
            }
        
        }

        Vec2D get_top_left(){
            return _top_left;
        }

        Vec2D get_bottom_right(){
            return _bottom_right;
        }
        
        private:
        const Vec2D _top_left;
        const Vec2D _bottom_right;


    };

    void update(float dt){
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
                        _lane1.update(_term);                   
                        _lane2.update(_term);                   
                        _lane3.update(_term);                   
                        _lane4.update(_term);                   
                        _lane5.update(_term);                   
                    }

        _elapsed_time += dt;
        if (_elapsed_time >= 0.1f) 
        {
            
        }
       _elapsed_time = 0.f;
    }

   void game_tick(float dt){
       _ticktime += dt;

       if (_ticktime >= 1.0f){
           
            _lane1.move_viruses();
            _lane2.move_viruses();
            _lane3.move_viruses();
            _lane4.move_viruses();
            _lane5.move_viruses();
            _ticktime = 0.f;
       }


   }
   
    void draw_borders(){
        
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

    void spawn_all_lanes(float dt){

        _spawntime += dt;
        if(_spawntime >= 5.0f){
            
            
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> lane(1, 4);
            
            
            
            if (lane(gen) == 0){
                _lane1.spawn_virus();
            }
            else if (lane(gen) == 1){
                _lane2.spawn_virus();
            }
            else if (lane(gen) == 2){
                _lane3.spawn_virus();
            }
            else if (lane(gen) == 3){
                _lane4.spawn_virus();
            }
            else {
                _lane5.spawn_virus();
            };
            _spawntime = 0.f;


        }
        

    }

    void draw_statics(){
        draw_borders();
        _cleaner.draw(_term);
        _lane1.draw(_term);
        _lane2.draw(_term);
        _lane3.draw(_term);
        _lane4.draw(_term);
        _lane5.draw(_term);

    }

    void draw_mobiles()
    { 
        _safespace.draw(_term);
        _cleaner.draw(_term);
        _lane1.draw_sprayer(_term);
        _lane1.draw_viruses(_term);

        _lane2.draw_sprayer(_term);
        _lane2.draw_viruses(_term);

        _lane3.draw_sprayer(_term);
        _lane3.draw_viruses(_term);
        
        _lane4.draw_sprayer(_term);
        _lane4.draw_viruses(_term);
        
        _lane5.draw_sprayer(_term);
        _lane5.draw_viruses(_term);
    }

    bool is_done()
    {
        return _is_done;
    }
    
    enum class color{
        Blue,
        Green,
        Red
    };

    class Cleaner {
        public:
        Cleaner(int x, int y):
        _color(color::Blue),
        _position(x,y),
        _former_position(x,y)
        {}

        Vec2D get_position(){
            return _position;
        }

        void control(char key, Game::Safespace& safespace){

            switch(key){

                case 'i':
                    if(_position.y > safespace.get_top_left().y+1){
                        _former_position = _position;
                        _position.y--;
                    }
                break;

                case 'k':
                    if(_position.y < safespace.get_bottom_right().y-3){
                        _former_position = _position;
                        _position.y++;
                    }
                    break;

                case 'j':
                    if(_position.x > safespace.get_top_left().x+1){
                        _former_position = _position;
                        _position.x--;
                    }
                    break;

                case 'l':
                    if(_position.x < safespace.get_bottom_right().x-1){
                        _former_position = _position;
                        _position.x++;
                    }
                    break;

                case 'a':
                    if(_color == color::Blue){
                        _color = color::Green;
                    }
                    else if (_color == color::Green){
                        _color = color::Red;
                    }
                    else{
                        _color = color::Blue;
                    }
                default:
                    break;
            }

        }

        void draw(Terminal& term){
            term.set_cell(_former_position.x, _former_position.y, ' ');
            term.set_cell(_former_position.x, _former_position.y+1, ' ');
            term.set_cell(_former_position.x, _former_position.y+2, ' ');
            
            switch(_color){
                case color::Blue:
                    term.set_cell(_position.x, _position.y, 'B');
                    term.set_cell(_position.x, _position.y+1,'H');
                    term.set_cell(_position.x, _position.y+2, 'L');
                    break;

                case color::Green:
                    term.set_cell(_position.x, _position.y, 'G');
                    term.set_cell(_position.x, _position.y+1, 'H');
                    term.set_cell(_position.x, _position.y+2, 'L');
                    break;

                case color::Red:
                    term.set_cell(_position.x, _position.y, 'R');
                    term.set_cell(_position.x, _position.y+1, 'H');
                    term.set_cell(_position.x, _position.y+2, 'L');
                    break;     
            }
            
        }

        private:
        Vec2D _former_position;
        Vec2D _position;
        color _color;

    };
    
    class Lane {
        public:
        Lane(int number, int start, int length):
        _number(number),
        _start(start),
        _length(length),
        _sprayer(start+2)            
        {}

        class Virus {
            public:
            Virus(int x, int y, color color):
            _color(color),
            _position(x, y + 2),
            _prev_position(x, y + 2),
            _is_destroyed(false),
            _is_end_of_lane(false),
            _hitpoints(6)
            {}

            Vec2D get_position(){
                return _position;
            }
            Vec2D get_prev_position(){
                return _prev_position;
            }
            color get_color(){
                return _color;
            }

            int get_hitpoints(){
                return _hitpoints;
            }

            bool is_destroyed(){
                return _is_destroyed;
            }

            bool is_end_of_lane(){
                return _is_end_of_lane;
            }

            void move(){
                _prev_position = _position;
                _position.x = _position.x - 1;
            }

            void draw(Terminal& term){
                term.set_cell(_prev_position.x, _prev_position.y, ' ');
                term.set_cell(_prev_position.x-1, _prev_position.y, ' ');
                term.set_cell(_prev_position.x+1, _prev_position.y, ' ');
                
                switch(_color){
                    case color::Blue:
                        term.set_cell(_position.x, _position.y, 'B');
                        term.set_cell(_position.x-1, _position.y, '{');
                        term.set_cell(_position.x+1, _position.y, '}');
                        break;    
                                
                    case color::Green:
                        term.set_cell(_position.x, _position.y, 'G');
                        term.set_cell(_position.x-1, _position.y, '{');
                        term.set_cell(_position.x+1, _position.y, '}');

                        break;

                    case color::Red:
                        term.set_cell(_position.x, _position.y, 'R');
                        term.set_cell(_position.x-1, _position.y, '{');
                        term.set_cell(_position.x+1, _position.y, '}');

                        break;
                }
            }

            void dedraw(Terminal& term){
                
                term.set_cell(_position.x, _position.y, ' ');  
                term.set_cell(_position.x-1, _position.y, ' ');  
                term.set_cell(_position.x+1, _position.y, ' ');  
            }
                        

                    
            

            

            
            private:
            Vec2D _position;
            Vec2D _prev_position;
            color _color;
            int _hitpoints;
            bool _is_destroyed;
            bool _is_end_of_lane;

            };

        class Sprayer{
            public:

            Sprayer(int y):
                _color(color::Blue),
                _position(5,y),
                _is_build(true),
                _hitpoints(5),
                _shots(6)
                {}

            color get_color(){
                return _color;
            }

            void change_color(){
                if(_color == color::Blue){
                    _color = color::Green;
                }
                else if(_color == color::Green){
                    _color = color::Red;
                }
                else{
                    _color = color:: Blue;
                }
            }

            Vec2D get_position(){
                return _position;
            }

            int get_hitpoints(){
                return _hitpoints;
            }

            void lose_hitpoints(){
                _hitpoints -= 1;
            }

            void reset_hitpoints(){
                _hitpoints = 6;
            }

            int get_shots(){
                return _shots;
            }

            void shoot(){
                _shots -= 1;
            }

            bool get_is_build(){
                return _is_build;
            }

            void build(){
                _is_build = true;
            }

            void destroy(){
                _is_build = false;
            }

            void draw(Terminal& term){
                if(_is_build){
                    term.set_cell(_position.x, _position.y-1,'>');
                    term.set_cell(_position.x, _position.y, '\'');
                    term.set_cell(_position.x, _position.y+1, ')');
                            
                    term.set_cell(_position.x-1, _position.y, '|');
                    term.set_cell(_position.x-1, _position.y+1, '(');
                   
                    switch(_color){
                        case color::Blue:
                            term.set_cell(_position.x-1, _position.y-1,'B');
                            break;

                        case color::Green:
                            term.set_cell(_position.x-1, _position.y-1,'R');
                            break;

                        case color::Red:
                            term.set_cell(_position.x-1, _position.y-1,'G');
                            break;     
                    }
                }
            }

            private:
            color _color;
            Vec2D _position;
            int _hitpoints;
            int _shots;
            bool _is_build;
        };

        void draw(Terminal& term){
            for (int x = 0; x <= _length; ++x){
                term.set_cell(x+4, _start, '-');
                if(_number == 5){
                    term.set_cell(x+4, _start+4, '-');
                }    
            }           
        };
        
        void move_viruses(){
            if (!_virus_in_lane.empty()){
                for(int i = 0; i < _virus_in_lane.size(); i++){
                    _virus_in_lane[i].move();
                }
            }
        };

        void draw_viruses(Terminal& term){
            if (!_virus_in_lane.empty()){
                    
                    for (int i = 0; i < _virus_in_lane.size(); i++){
                        _virus_in_lane[i].draw(term);
                    }
                        
        
                }
        }
        
        void draw_sprayer(Terminal& term){
            if (_sprayer.get_is_build()){
                _sprayer.draw(term);
            }
        }

        void update(Terminal& term){
            
            // draw_viruses(term);
            check_viruses(term);           
            
        }

        void spawn_virus(){
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

        void check_viruses(Terminal& term){
            if(!_virus_in_lane.empty()){
                for (int i = 0; i < _virus_in_lane.size(); i++){
                    if (_virus_in_lane[i].get_position().x <= 30 
                    || _virus_in_lane[i].get_hitpoints() <= 0){
                        _virus_in_lane[i].dedraw(term);
                        _virus_in_lane.erase(_virus_in_lane.begin()+i);
                    }   
                }   
            }
        }

        int get_number(){
            return _number;
        }
        
        int get_start(){
            return _start;
        }

        int get_length(){
            return _length;
        }

        private:
        int _number;
        int _start;
        int _length;
        std::vector<Virus> _virus_in_lane;
        Sprayer _sprayer;
        
    };
   
    private:

        float _spawntime;
        float _ticktime;
        float _elapsed_time; 
        bool _game_over;
        bool _is_done;
        Terminal& _term;
        Cleaner _cleaner;
        Safespace _safespace;
        Lane _lane1;
        Lane _lane2;
        Lane _lane3;
        Lane _lane4;
        Lane _lane5;
        Vec2D _map_top_left;
        Vec2D _map_bottom_right;
};


//////////////////////////////////////////////////////



int main()
{
    Terminal term(80,50);
    Game game(term);
    
    using namespace std::chrono;
    using fmilli = duration<float, seconds::period>;

    auto t0 = high_resolution_clock::now();
    auto t1 = high_resolution_clock::now();
    


    while (!game.is_done()) {
        t0 = t1;
        t1 = high_resolution_clock::now();

        game.update(fmilli(t1 - t0).count());
        game.game_tick(fmilli(t1 - t0).count());
        game.spawn_all_lanes(fmilli(t1-t0).count());
        game.draw_mobiles();


        
    }

    term.close();
    return 0;
}

