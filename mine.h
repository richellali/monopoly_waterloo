#ifndef _MINE_
#define _MINE_
#include "item.h"

class Mine : public Item {
    public:
    Mine(std::string name, std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings);
    void event(Player&) override;
};

class MineFactory : public ItemFactory{
    public:
    std::shared_ptr<Item> produceItem(std::string name);
};




#endif

