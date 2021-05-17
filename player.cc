#include "player.h"
#include "info.h"
#include "grid.h"
#include "moneyexception.h"
#include "buildingexception.h"
#include "monopolyexception.h"
#include "property.h"

//std::shared_ptr<Building> getMovedPosition(int);

Player::Player(std::string name, int order,std::map<int, std::shared_ptr<Building>>* bp) 
: state{0, name, order}, buildings{bp}{}

Player::Player(std::string name, int order, int Timcups, int money, int position,
    bool isInline, int DCtimes, std::map<int, std::shared_ptr<Building>>* bp)
    :state{position, name, order},
    money{money},
    DCCups{Timcups},
    isInline{isInline},
    DCtimes{DCtimes},
    buildings{bp} {}

void Player::addProperties(std::map<const std::string, Property*> properties) {
    this->properties = properties;
}

Player::~Player(){}

int Player::getMoney() noexcept {
    return money;
}

int Player::getDCCups() {
    return DCCups;
}

std::map<int, std::shared_ptr<Building>>* Player::getBuildings(){
    return buildings;
}

void Player::setBuildings(std::map<int, std::shared_ptr<Building>>* bp){
    buildings = bp;
}

void Player::setDCCups(int change) {
    DCCups += change;
}

void Player::setMoney(int change) {
    if (change < 0 && -change > money) {
        throw MoneyException(state.name, change); // declare bankrupt
    } else {
        money += change;
    }
}

void Player::declareBankrupt() {
    if (isliabilityTo == true) {
        std::string ownername = liabilityTo->getInfo().name;
        std::string brname = getInfo().name;
        std::cout << "Hi Player " << ownername <<", since Player "<< brname;
        std::cout << " owes you money and this player decide to drop out (bankrupt), all his/her assets are yours." << std::endl;
        liabilityTo->setMoney(this->money);
        std::cout << "You get cash: $"<< this->money << std::endl;
        std::cout << "You get property: ";
        for (auto &o : properties){
            o.second->changeOwner(liabilityTo);
            liabilityTo->addProperty(o.second);
            std::cout << o.second->getInfo().name << " ";
        }
        std::cout << std::endl;
        for (auto &o : properties){
            if (o.second->getMortgageStatus() == true) {
                std::string name = o.second->getInfo().name;
                int money = o.second->getPurchaseCost()/10;
                std::cout << "Since " << name <<  " is mortgaged, you need to pay 10% of its original price." << std::endl;
                try {
                    o.second->getOwner()->setMoney(-money);
                    std::cout << "$" << money << " is paid."<< std::endl;
                    std::cout << "You can choose to A. unmortgage the property now for only 50% of its original price."<< std::endl;
                    std::cout << "Or you can choose to B. unmortgage the property later for 60% of its original price."<< std::endl;
                    std::cout << "Please enter A or B."<< std::endl;
                    char ans;
                    int money1 = o.second->getPurchaseCost()/2;
                    
                    while (true) {
                    std::cin >> ans;
                    if (ans == 'A') {
                        try {
                        liabilityTo->setMoney(-money1);
                        std::cout << "$" << money1<<" is paid to unmortgage " << name << std::endl;
                        o.second->setMortgageStatus(false);
                        break;
                        }
                        catch (MoneyException &we) {
                        std::cout << "Money is not enough to unmortgage now! Please wait for later."<< std::endl;
                        break;
                        }
                    } else if (ans == 'B') {
                            break;
                    } else {
                        std::cout << "Invalid input. Please enter \"A\" or \"B\"." << std::endl;
                    }
                    }

                } catch (MoneyException &me) {
                    o.second->getOwner()->liabilityToBank = true;
                    std::cout << "You do not have $" << money << "to pay." << std::endl;
                }
            }
        }
        std::cout << std::endl;
    } else {
    for (auto &o : properties){
        o.second->changeOwner(nullptr);
    }
    }
    state.isBankrupt = true;
    notifyObservers();
}
bool Player::isBankrupted() {
    return state.isBankrupt;
}

void Player::move(int position) {
    if (state.position + position > 39) {
        state.position = state.position + position - 39 -1;
        money += 200;
        std::cerr << "Collect OSAP! Receive 200 Dollars!" << std::endl;
    } else if (state.position + position < 0) {
        state.position = 39 + (state.position + position + 1);
        /*
        if (state.position == 0 ) {
            money += 200;
            std::cout << "Collect OSAP! Receive 200 Dollars!" << std::endl;
        }
        */
    } else {
        state.position += position;
    }
    notifyObservers();
    try {
    (*buildings)[state.position]->event(*this);
    } catch (WaterpolyException &we) {
        if (we.getExceptionName() == "auctionNeeded") {
            this->state.needAuction = true;
            notifyObservers();
        } else {
            throw;
        }
    }
}

int Player::totalWorth() {
    int total = getMoney();
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        if (it->second->getType() == "academic") {
            AcademicBuilding & ac = dynamic_cast<AcademicBuilding &>(*it->second);
            total += ac.getPurchaseCost();
            total += ac.getImprovedLevel()*ac.getimproveValue();
        } else if (it->second->getType() == "gym") {
            Gym & g = dynamic_cast<Gym &>(*it->second);
            total += g.getPurchaseCost();
        } else {
            Residence & r = dynamic_cast<Residence &>(*it->second);
            total += r.getPurchaseCost();
        }
    }
    return total;
}

// for these two functions below we may need to call dosth in the building class
// later discussion required
void Player::goTim() {
    std::cout << "OHHHH NO, you have to go to DC Tims Line." << std::endl;
    state.position = 10;
    isInline = true;
    DCtimes++;
    notifyObservers();
    (*buildings)[10]->event(*this);
}

void Player::leaveLine() {
    isInline = false;
    DCtimes = 0;
}
bool Player::inLine(){
    return isInline;
}
int Player::timesInDC(){
    return DCtimes;
}
void Player::addTimTurn() {
    DCtimes++;
}

void Player::stayInTim(){
    (*buildings)[10]->event(*this);
}

void Player::collectOSAP(){
    state.position = 0;
    money += 200;
    std::cerr << "Collect OSAP! Receive 200 Dollars!" << std::endl;
    notifyObservers();
}

Info Player::getInfo() const{
    return state;
}

std::map<const std::string, Property*> Player::getProperty() {
    return properties;
}
bool Player::hasMonopoly(std::string monopolyBlock) {
    int count=0 ;
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        if (it->second->getType() == "academic") {
            AcademicBuilding & ac = dynamic_cast<AcademicBuilding &>(*it->second);
            std::string str = ac.getMonopoly();
            if (str == monopolyBlock){
                count +=1 ;
            }
        }
    }
    if (monopolyBlock == "Arts1") {
        if (count == 2)
        return true;
    } else if (monopolyBlock == "Arts2") {
        if (count == 3)
        return true;
    } else if (monopolyBlock == "Eng") {
        if (count == 3)
        return true;
    } else if (monopolyBlock == "Health") {
        if (count == 3)
        return true;
    } else if (monopolyBlock == "Env") {
        if (count == 3)
        return true;
    } else if (monopolyBlock == "Sci1") {
        if (count == 3)
        return true;
    } else if (monopolyBlock == "Sci2") {
        if (count == 3)
        return true;
    } else {
        if (count == 2)
        return true;
    }
    return false;
}


void Player::buy(Property* building) {
    // don't have enough money
    if (building->getPurchaseCost() > money) {
        throw MoneyException(building->getInfo().name, 
        -building->getPurchaseCost());
        return;
    }
    if (building->isOwned()) { // can check if the building has an owner
        throw BuildingException(building->getInfo().name);
        return;
    }
    // can own the building
    Info buildingInfo = building->getInfo();

    properties[buildingInfo.name] = building;
    building->changeOwner(this);

}

void Player::improve(Property & building) { ///change
    if (building.getType() != "academic") {
        throw BuildingException(building.getInfo().name);
    }
    AcademicBuilding & ac = dynamic_cast<AcademicBuilding &>(building);
    if (ac.getMortgageStatus()) {
        throw BuildingException(building.getInfo().name);
    }
    if (ac.getimproveValue() > money) {
        throw MoneyException(state.name, -ac.getimproveValue());
    }
    if (!hasMonopoly(ac.getMonopoly())) {
        throw MonopolyException(building.getInfo().name);
    }
    ac.improve();
    
}
void Player::sellImprovements(Property & building) {
    if (building.getType() == "academic") {
        AcademicBuilding &ac = dynamic_cast<AcademicBuilding &>(building);
        ac.sellImprovement();
    } else {
        throw BuildingException(building.getInfo().name);
    }
}

void Player::mortgage(Property & building) {
    building.mortgage();
}

void Player::unmortgage(Property & building) {
    building.unmortgage();
    std::cout << "You have unmortgage " << building.getInfo().name << std::endl;
}

void Player::mortgageList() {
    std::cerr << "These are the buildings that you can mortgage!" << std::endl;
    for (auto it = properties.begin(); it != properties.end(); it++) {
        if (!it->second->getMortgageStatus()) {
            std::cerr << it->first << " ";
        }
    }
    std::cerr << '\n';
    std::cerr << "Please enter the name you want to mortgage, if you do not "
    << "want to mortgage any building, enter none instead." << std::endl;
}

void Player::unmortgageList() {
    std::cerr << "These are the buildings that you can unmortgage!" << std::endl;
    for (auto it = properties.begin(); it != properties.end(); it++) {
        if (it->second->getMortgageStatus()) {
            std::cerr << it->first << " ";
        }
    }
    std::cerr << '\n';
    std::cerr << "Please enter the name you want to unmortgage, if you do not "
    << "want to mortgage any building, enter \"none\" instead." << std::endl;
}


Property & Player::getBuilding(std::string buildingName) {
    for (auto it = properties.begin(); it != properties.end(); it++) {
        if (it->first == buildingName) {
            return *it->second;
        }
    }
    std::cerr << "The building does not exist." << std::endl;
    throw BuildingException(buildingName);
}

bool Player::isOwnProperty(Property & building) {
    std::string buildingName = building.getInfo().name;
    for (auto it = properties.begin(); it != properties.end(); it++) {
        if (it->first == buildingName) {
            return true;
        }
    }
    return false;
}
// trade section~
void Player::trade(Player & other, int myMoney, Property & otherB) {
    if (myMoney > money) {
        throw MoneyException(state.name, -myMoney);
    }
    auto otherProperties = other.getProperty();
    if (!otherProperties.count(otherB.getInfo().name)){
        throw BuildingException(other.getInfo().name);
    }
    if (otherB.getType() == "academic"){ 
        AcademicBuilding & ac = dynamic_cast<AcademicBuilding &>(otherB);
        if (ac.getImprovedLevel() > 0)
        throw BuildingException(other.getInfo().name);
        for (auto it = otherProperties.begin(); it != otherProperties.end(); ++it) {
                    if (it->second->getType() == "academic") {
                        AcademicBuilding & ac1 = dynamic_cast<AcademicBuilding &>(*it->second);
                        std::string str = ac1.getMonopoly();
                        if (str == ac.getMonopoly()){
                            if (ac1.getImprovedLevel() > 0) {
                                std::cerr << "You can only offer to trade a property if all properties in the monopoly do not have improvements." << std::endl;
                                throw BuildingException(other.getInfo().name);
                            }
                        }
                    }
                }
    }
    std::cout << "Hi Player " << other.getInfo().name << "! Player " << state.name << " is willing to use " << myMoney <<" to trade your " << otherB.getInfo().name << std::endl;
    std::cout << "reply (yes) to complete the trade and (no) to refuse" << std::endl;
    std::string readin;
    while(true){
        std::cin >> readin;
        if (readin == "yes") break;
        if (readin == "no") throw BuildingException(other.getInfo().name);
        std::cerr << "invalid response, please reply it again." << std::endl;
    }
    other.tradeTo(otherB, *this);
    addProperty(&otherB);
    other.eliminateProperty(&otherB);
    money -= myMoney;
    other.setMoney(myMoney);
}

void Player::trade(Player & other, Property & myB, int otherMoney) {
    std::string buildingName = myB.getInfo().name;
    for (auto it = properties.begin(); it != properties.end(); it++) {
        if (it->first == buildingName) {
            // check if the building is available for trade
            try {
                AcademicBuilding & ac = dynamic_cast<AcademicBuilding &>(myB);
                if (ac.getImprovedLevel() > 0) {
                    throw BuildingException(buildingName);
                }
                for (auto it = properties.begin(); it != properties.end(); ++it) {
                    if (it->second->getType() == "academic") {
                        AcademicBuilding & ac1 = dynamic_cast<AcademicBuilding &>(*it->second);
                        std::string str = ac1.getMonopoly();
                        if (str == ac.getMonopoly()){
                            if (ac1.getImprovedLevel() > 0) {
                                std::cerr << "You can only offer to trade a property if all properties in the monopoly do not have improvements." << std::endl;
                                throw BuildingException(buildingName);
                            }
                        }
                    }
                }  
            } catch (std::bad_cast & ac){}
            // check if other player has enough money
            try {
                std::cerr << "Hi Player " << other.getInfo().name << "! Player " << state.name << " is willing to trade " << myB.getInfo().name << " to your $" << otherMoney << std::endl;
                std::cerr << "reply (yes) to complete the trade and (no) to refuse." << std::endl;
                std::string readin;
                while(true){
                    std::cin >> readin;
                    if (readin == "yes") break;
                    if (readin == "no") throw BuildingException(other.getInfo().name);
                    std::cerr << "invalid response, please reply it again." << std::endl;
                }
                other.tradeTo(otherMoney);
                eliminateProperty(&myB);
            } catch (MoneyException) {
                throw MoneyException(state.name, -otherMoney);
            }
            myB.changeOwner(&other);
            other.addProperty(&myB);
            money += otherMoney;
            return;
        }
    }
    throw BuildingException(buildingName);

}
void Player::trade(Player & other,  Property & otherB, Property & myB) {
    std::string buildingName = myB.getInfo().name;
    for (auto it = properties.begin(); it != properties.end(); it++) {
        if (it->first == buildingName) {
            // check if the building is available for trade
            try {
                AcademicBuilding & ac = dynamic_cast<AcademicBuilding &>(myB);
                if (ac.getImprovedLevel() > 0) {
                    throw BuildingException(buildingName);
                }
            } catch (std::bad_cast & ac){}
            // check if other player has enough money
            std::cerr << "Hi Player " << other.getInfo().name << "! Player " << state.name << " is willing to trade " << myB.getInfo().name << " to your " << otherB.getInfo().name << std::endl;
            std::cerr << "reply (yes) to complete the trade and (no) to refuse" << std::endl;
            std::string readin;
            while(true){
                std::cin >> readin;
                if (readin == "yes") break;
                if (readin == "no") return; //throw BuildingException(other.getInfo().name);
                std::cerr << "invalid response, please reply it again" << std::endl;
            }
            other.tradeTo(otherB, *this);
            eliminateProperty(&myB);
            addProperty(&otherB);
            other.eliminateProperty(&otherB);
            other.addProperty(&myB);
            myB.changeOwner(&other);
            return;
        }
    }
    throw BuildingException(buildingName);

}


void Player::addProperty(Property * property){
    properties[property->getInfo().name] = property;
}
void Player::eliminateProperty(Property *property){
    properties.erase(property->getInfo().name);
}


void Player::tradeTo(int otherMoney) {
    if (otherMoney > money) {
        throw MoneyException(state.name, -otherMoney);
    } else {
        money -= otherMoney;
    }
}
void Player::tradeTo(Property & building, Player & other) {
    std::string buildingName = building.getInfo().name;
    for (auto it = properties.begin(); it != properties.end(); it++) {
        if (it->first == buildingName) {
            // check if the building is available for trade
            try {
                AcademicBuilding & ac = dynamic_cast<AcademicBuilding &>(building);
                if (ac.getImprovedLevel() > 0) {
                    throw BuildingException(buildingName);
                }
            } catch (std::bad_cast & ac){}
            
            building.changeOwner(&other);
            return;
        }
    }
    throw BuildingException(buildingName);   
}

int Player::getGymNum() {
    int count = 0;
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        if (it->second->getType() == "gym") {
            count++;
        }
    }
    return count;
}

int Player::getResidenceNum(){
    int count = 0;
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        //std::cout << it->second->getInfo().name <<std::endl;
        //std::cout << it->second->getType() <<std::endl;
        if (it->second->getType() == "residence") {
            count++;
        }
    }
    return count;
}
void Player::displayAsset() {
    std::cout << "Player Name: " << state.name << std::endl;
    std::cout << "Money: " << money << std::endl;
    std::cout << "TimCups: " << DCCups << std::endl;
    std::cout << "Buildings: " << std::endl;
    for (auto it = properties.begin(); it != properties.end(); ++it) {
            if (!it->second->getMortgageStatus()){
            if (it->second->getType() == "academic") {
                AcademicBuilding & ac = dynamic_cast<AcademicBuilding &>(*it->second);
                ac.getAsset();
            } else {
                std::cout << it->second->getInfo().name;
            }
            std::cout << "\n";
        }
    }
    std::cout << std::endl;
}

std::string Player::save() {
    
    std::string str = state.name + " " + std::to_string(DCCups) + " " 
    + std::to_string(money)
    + " " + std::to_string(state.position);
    if (canRoll) {
        str = str + " 1";
    } else {
        str = str + " 0";
    }
    if (state.position == 10 && isInline ) {
        str = str + " " + "1" + " " + std::to_string(DCtimes);
    } else if (state.position == 10) {
        str += " 0";
    }
    return str;
}

void Player::oweBank() {
    liabilityToBank = true;
    state.liabilityToBank = true;
}

void Player::addItem(std::shared_ptr<Item> it){
    items.emplace_back(it);
}
void Player::useItem(int index){
    int size = items.size();
    if (index < 0) {
        std::cerr << "Invalid input." << std::endl;
        return;
    }
    if (index < size){
        try{
        items.at(index)->event(*this);
        items.erase(items.begin()+index);
        } catch(WaterpolyException){
            std::cerr << "Invalid use." << std::endl;
        }
    }
}

void Player::changeAuctionStatus() {
    state.needAuction=false;
}

void Player::displayItemList(){
    std::cout << "Item List" << std::endl;
    int index = 0;
    for (auto p : items){
        
        std::cout << index << " " << p->getName() << std::endl;
        index++;
    }
}

