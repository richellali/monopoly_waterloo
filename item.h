#ifndef _ITEM_
#define _ITEM_
#include <memory>
#include "player.h"
class Player;
class Building;
class Item{
    protected:
    std::string name;
    std::vector<std::shared_ptr<Player>> *players;
    std::map<int, std::shared_ptr<Building>> *buildings;
    public:
    virtual void event(Player&) = 0;
    std::string getName();
    Item(std::string name, std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings);
};

class ItemFactory{
    protected:
    std::vector<std::shared_ptr<Player>> *players;
    std::map<int, std::shared_ptr<Building>> *buildings;
    public:
    void initFactory(std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings);
    virtual std::shared_ptr<Item> produceItem(std::string s) = 0;
};

#endif

