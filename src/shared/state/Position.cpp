#include "Position.h"

namespace state
{
    Position::Position(){};

    Position::Position(int x, int y){
        setX(x);
        setY(y);
    };

    
    // Setters and Getters
    int Position::getX() const{
        return Position::x;
    };
    void Position::setX(int x){
        Position::x = x;
    };
    int Position::getY() const{
        return Position::y;
    };
    void Position::setY(int y){
        Position::y = y;
    };

    Position::~Position(){};

} // namespace state
