#include <stdlib.h> 
#include <math.h>
#include "Position.h"

namespace state
{
    Position::Position(){};

    Position::Position(int x, int y) :
    x(x),
    y(y)
    {};


    Position::~Position(){};

    Position Position::operator+ (Position p){
        return Position(x + p.x, y + p.y);
    }
    bool Position::operator== (Position p){
        return (x == p.x && y == p.y);
    }
    bool Position::operator!= (Position p){
        return (x != p.x && y != p.y);
    }
    Position Position::operator* (int x){
        return Position(this->x*x, this->y*y);
    }
    Position Position::operator/ (int x){
        return Position(floor(this->x/x), floor(this->y/y));
    }
    int Position::grid_distance (Position p){
        return (abs(x-p.x) + abs(y-p.y));
    }

} // namespace state
