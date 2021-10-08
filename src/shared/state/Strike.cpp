#include "Strike.h"


namespace state{
    char Strike::getType() {return Strike::type; };
    int Attack::getDamage(){return damage;};
    int Attack::getRange(){return range;};
    void Attack::setType(char type){state::Attack::type=type;};
    void Attack::setDamage(int damage){};
    void Attack::setRange(int range){};

    




}

//Strike S = Strike()
//PowerfullStrike pS = PowerfullStrike()

//std::vector<Attack> L = Vector<Attack>();
//L.pb(S)
//L.pb(pS)

//map<string, Attack>