#include <string>
#include <memory>
#include "buildings.h"

Building::Building(std::string name, int position) {
    state.name = name;
    state.position = position;
    state.isBankrupt = false;
}

Building::~Building(){}

Info Building::getInfo() const{
    return state;
}

