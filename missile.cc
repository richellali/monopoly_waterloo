#include "missile.h"
#include <iostream>
#include "property.h"

Missile::Missile(std::string name, std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings):Item(name, players, buildings){}

void Missile::event(Player&p){
    std::cerr << "please input the name of target Player and his property" << std::endl;
    std::cerr << "i am destorying the property!" << std::endl;
    std::string name1;
    std::string name2;
    std::cin >> name1 >> name2;
    for (auto &o : *players){
        if (o->getInfo().name == name1){
            auto properties = o->getProperty();
            if (properties.count(name2)){
                if (properties[name2]->getType() == "academic"){
                    auto ac = dynamic_cast<AcademicBuilding&>(*properties[name2]);
                    if (ac.getImprovedLevel()>0) {
                        std::cerr << "improved academic buildings can not be destroyed!" << std::endl;
                        throw WaterpolyException("level");
                    }
                }
                properties[name2]->changeOwner(nullptr);
                o->eliminateProperty(properties[name2]);
                return;
            }   else {
                std::cerr << "The player does not own such property" << std::endl;
                throw WaterpolyException("level");
            }
        }
    }
    std::cerr << "Cannot find target Player!" << std::endl;
    throw WaterpolyException("level");
}

std::shared_ptr<Item> MissileFactory::produceItem(std::string name){
    return std::make_shared<Missile>(name, players, buildings);
}

