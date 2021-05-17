#include "item.h"

std::string Item::getName(){
    return name;
}


void ItemFactory::initFactory(std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings){
        this->players = players;
        this->buildings = buildings;
    }


Item::Item(std::string name, std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings):
    name{name}, players{players}, buildings{buildings}{}


   


