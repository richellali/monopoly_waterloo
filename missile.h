#ifndef _MISSILE_
#define _MISSILE_
#include "item.h"

class Missile : public Item {
    public:
    Missile(std::string name, std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings);
    void event(Player&) override;
};

class MissileFactory : public ItemFactory{
    public:
    std::shared_ptr<Item> produceItem(std::string name);
};




#endif

