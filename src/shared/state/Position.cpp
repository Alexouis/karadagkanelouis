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

} // namespace state
