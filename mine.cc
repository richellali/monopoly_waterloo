#include "mine.h"
#include "buildings.h"
#include "waterpolyexception.h"
class Building;
Mine::Mine(std::string name, std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings):Item(name, players, buildings){}

void Mine::event(Player&p){
    std::cerr << "Please input the name of the building to set the Mine" << std::endl;
    std::string name;
    std::cin >> name;
    for (auto &o : *buildings){
        if (o.second->getInfo().name == name){
            o.second->hasMine = true;
            std::cout << name << " now has a mine, be careful!" << std::endl;
            return;
        }
    }
    throw WaterpolyException("Mine");
}

std::shared_ptr<Item> MineFactory::produceItem(std::string name){
    return std::make_shared<Mine>(name, players, buildings);
}

