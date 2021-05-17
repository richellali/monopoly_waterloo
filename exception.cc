#include "buildingexception.h"
#include "moneyexception.h"
#include "monopolyexception.h"

BuildingException::BuildingException(std::string name)
: WaterpolyException(name){}

MoneyException::MoneyException(std::string name, int change)
: WaterpolyException(name), change{change}{}


int MoneyException::getChange() {
    return change;
}

MonopolyException::MonopolyException(std::string name)
: WaterpolyException(name){}


