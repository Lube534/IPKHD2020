#ifndef SAFESPACE_H
#define SAFESPACE_H

#include "Vec2D.h" 
#include "Terminal.h"   
    
    class Safespace {
        public:
        Safespace(Vec2D top_left, Vec2D bottom_right);
        
        void draw(Terminal& term);

        Vec2D get_top_left();

        Vec2D get_bottom_right();
        
        private:
        const Vec2D _top_left;
        const Vec2D _bottom_right;


    };

#endif
