#include "Safespace.h"    
    
    
Safespace::Safespace(Vec2D top_left, Vec2D bottom_right):
    _top_left(top_left),
    _bottom_right(bottom_right)
{}

void Safespace::draw(Terminal& term){
    
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

Vec2D Safespace::get_top_left(){
    return _top_left;
}

Vec2D Safespace::get_bottom_right(){
    return _bottom_right;
}

