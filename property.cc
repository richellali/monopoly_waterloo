#include "property.h"
class MoneyException;
class WaterpolyException;

Property::Property(std::string name,int position,int price): 
Building(name,position),price(price) {}

Property::Property(std::string name,int position,int price, 
    Player * owner): 
Building(name,position),price(price),owner(owner) {}

Property::~Property(){}


int Property::getPurchaseCost() {
    return price;
}

bool Property::getMortgageStatus() {
    return isMortgage;
}

Player * Property::getOwner() {
    return owner;
}

// change or add the owner of the building, also change the status of canBuy
void Property::changeOwner(Player * p) {
    owner = p;
    if (!owner) canBuy = true;
    else canBuy = false;
}

bool Property::isOwned() {
    return !canBuy;
}

void Property::event(Player &p) {
    if (hasMine){
        p.nextCanRoll = false;
        hasMine=false;
        std::cout << "Boom! it hurts! Next turn you can not move!" << std::endl;
    }
    if (canBuy) {
        std::cerr << "This property: " << getInfo().name << " does not have an owner yet."<< std::endl;
        std::cerr << "Do you want to buy it for $" << getPurchaseCost() << "? Enter \"yes\" or \"no\"." << std::endl;
        std::string ans;
        while (true) {
            std::cin >> ans;
            if (ans == "yes") {
                try {
                    p.setMoney(-getPurchaseCost());
                    p.buy(this);
                    std::cerr << "This property is now yours. Congratulation!" << std::endl;
                }
                catch (MoneyException &we) {
                    std::cerr << "Money is not enough to buy this property! ";
                    throw;
                }
                break;
            } else if (ans == "no") {
                throw WaterpolyException("auctionNeeded");
                break;
            } else {
                std::cerr << "Invaild input. Please enter \"yes\" or \"no\"." << std::endl;
            }
        }
    } else {
        getTuition(p);
    }
}

void Property::unmortgage() {
    int mortgagemoney = getPurchaseCost()*0.6;
    try {
    getOwner()->setMoney(-mortgagemoney);
    isMortgage = false;
    }
    catch (MoneyException &we) {
            std::cerr << "Money is not enough to unmortgage this property!";
        }
}

void Property::setPurchaseCost(int n) {
    price = n;
}

void Property::setMortgageStatus(bool b) {
    isMortgage = b;
}

void Property::setToOriginal() {
    canBuy = true;
    owner = nullptr;
}

std::string Property::getType() {
    return type;
}

AcademicBuilding::AcademicBuilding(std::string name, int position, int price, std::string monopolyBlock,
            int improveCost, std::shared_ptr<std::vector<int>> tuition):
Property(name, position, price), monopoly(monopolyBlock), improveCost(improveCost),tuition(tuition) {
    type = "academic";
}


void AcademicBuilding::destroyImprovements(){
    improvedLevel = 0;
}


AcademicBuilding::~AcademicBuilding() {}

int AcademicBuilding::getTuition(Player& p) {
    //MoneyException we;
    int cost;
    if (p.isOwnProperty(*this))
    return 0;
    if (getMortgageStatus() == false) {
        //std::cerr << "DEBUGGING:i am at getTuition and gonna access the tuition vector" << tuition->size() << std::endl;
        cost = tuition->at(improvedLevel);
        //std::cerr << "DEBUGGING:i am at getTuition and get the cost" << std::endl;
        if (owner->hasMonopoly(monopoly) == true && improvedLevel == 0) 
        cost *= 2;
        try {
            //std::cerr << "DEBUGGING:i am setting the money of player" << std::endl;
            p.setMoney(-cost);
            //std::cerr << "DEBUGGING:i am setting the money of owner" << std::endl;
            owner->setMoney(cost);
            std::cout << "You have paid tuition: $" << cost << " to Player " << owner->getInfo().name<< std::endl;

        }
        catch (MoneyException &we) {
            std::cerr << "Money is not enough to pay tuition! " ;
            we.isForcible=true;
            p.liabilityTo= owner;
            p.isliabilityTo = true;
            throw;
        }
        return cost;
    } else {
        return 0;
    }
}

void AcademicBuilding::improve() {
    if (improvedLevel == 5) {
        std::cerr << "Maximum improvement bought already. You cannot improve anymore." << std::endl;
        return;
    }
    try {
    getOwner()->setMoney(-improveCost);
    improvedLevel += 1;
    std::cerr << "You successfully bought an improvement." << std::endl;
    } catch (MoneyException &we) {
            std::cerr << "Money is not enough to pay improvement fee!" << std::endl;
            //throw;
    }
}

int AcademicBuilding::getimproveValue() {
    return improveCost;
}

int AcademicBuilding::getImprovedLevel() {
    return improvedLevel;
}

std::string AcademicBuilding::getMonopoly() {
    return monopoly;
}

void AcademicBuilding::mortgage() {
    //std::cout << "here1";
    if (improvedLevel > 0) { 
        std::cout << "You have to sell all your improvement on this building first. (" ;
        std::cout << improvedLevel << " improvement(s) in total)" << std::endl;
        std::cout << "Do you still want to mortgage this building?" << std::endl;
        std::cout << "Please enter \"yes\" or \"no\"." << std::endl;
        std::string ans;
        while (true) {
            std::cin >> ans;
            if (ans == "yes") {
                sellAllImprovement();
                std::cout << "You successfully sold all improvement. ";
                break;
            } else if (ans == "no") {
                return;
            } else {
                std::cerr << "Invaild input. Please enter \"yes\" or \"no\"." << std::endl;
            }
        }
    }
    int mortgagemoney = getPurchaseCost()/2;
    getOwner()->setMoney(mortgagemoney);
    isMortgage = true;
    std::cout << "You have mortgage " << getInfo().name << "."<< std::endl;
}

void AcademicBuilding::sellImprovement() {
    std::cerr << "You have bought " << improvedLevel << " improvement(s)" << std::endl;
    std::cerr << "How many improvement(s) do you want to sell? Enter a number." << std::endl;
    char ans;
    while (true) {
        if (std::cin >> ans) {
            if (!(ans == '0' || ans == '1' || ans == '2' || ans == '3' || ans == '4' || ans == '5')) {
                std::cerr << "Invalid input. Please enter a number again." << std::endl;
            } else {
                int ansnum = ans - '0';
                if (ansnum <= improvedLevel) {
                    getOwner()->setMoney(ansnum*improveCost/2);
                    improvedLevel -= ansnum;
                    std::cout << "You have sold " << ansnum << " improvement(s)." << std::endl;
                    break;
                } else {
                    std::cerr << "Invalid number. You do not have enough improvement(s) to sell." <<std::endl;
                    std::cerr << "Please enter a number again." << std::endl;
                }
            }
        } else {
            std::cerr << "Invalid input. Please enter a number." << std::endl;
        }
    }
}

void AcademicBuilding::sellAllImprovement() {
    getOwner()->setMoney(improvedLevel*improveCost);
    improvedLevel = 0;
}

std::string AcademicBuilding::save() {
    std::string s;
    std::string il = std::to_string(improvedLevel);
    if (getMortgageStatus() == true) {
        s =  getInfo().name + " " + getOwner()->getInfo().name + " " + "-1";
    } else if (isOwned()) {
        s =  getInfo().name + " " + getOwner()->getInfo().name + " " + il;
    } else {
        s =  getInfo().name + " Bank " + il;
    }
    return s;
}

void AcademicBuilding::load (std::string buildstr, Player* ownerload) {
    //std::cout << getType() << std::endl;
    this->type = "academic";
    std::string buildingname;
    std::string ownername;
    std::string il;
    int n = 0;
    int len = buildstr.length();
    while ( n < len && (buildstr[n] != ' ')) {
        n+=1;
    }
    buildingname += buildstr.substr(0,n);
    int m = n+1;
    while ( m < len && (buildstr[m] != ' ')) {
        m+=1;
    }
    ownername += buildstr.substr(n+1, m-n);
    //std::cout << ownername <<std::endl;
    int k = m+1;
    while ( k < len) {
        k+=1;
    }
    il += buildstr.substr(m+1, k-m);
    if (il == "-1") {
        isMortgage = true;
    } else {
        int imp = stoi(il); 
        improvedLevel = imp;
    }
    if (ownerload == nullptr) {
        canBuy = true;
    } else {
        this->owner = ownerload;
        ownerload->addProperty(this);
        canBuy = false;
    }
        
} 

void AcademicBuilding::getAsset() {
    std::cout << getInfo().name << ": ";
    if (this->improvedLevel == 5) {
        std::cout << "4 bathrooms and one cafeteria";
        return;
    } else if (this->improvedLevel == 0) {
        std::cout << "no improvement";
    } else {
    std::cout << improvedLevel << " bathroom(s)";
    }
}

Residence::Residence(std::string name, int position): Property(name, position,200) {
    tuitionlist.emplace_back(25);
    tuitionlist.emplace_back(50);
    tuitionlist.emplace_back(100);
    tuitionlist.emplace_back(200);
    type = "residence";
}


Residence::~Residence() {}

int Residence::getTuition(Player& p) {
    if (p.isOwnProperty(*this))
    return 0;
    //std::cout << p.getResidenceNum() <<std::endl;
    if (getMortgageStatus() == false) {
        //std::cout << owner->getResidenceNum() << std::endl;
        int cost = tuitionlist.at(owner->getResidenceNum()-1);
        try {
            p.setMoney(-cost);
            getOwner()->setMoney(cost);
            std::cout << "You have paid tuition: $" << cost << " to Player " << owner->getInfo().name<< std::endl;
        }
        catch (MoneyException &we) {
            std::cerr << "Money is not enough to pay tuition! ";
            we.isForcible=true;
            p.liabilityTo= owner;
            p.isliabilityTo = true;
            throw;
        }
        return cost;
    } else {
        return 0;
    }
}

std::string Residence::save() {
    std::string s;
    if (getMortgageStatus() == true) {
        s =  getInfo().name + " " + getOwner()->getInfo().name + " -1";
    } else if (isOwned()) {
        s =  getInfo().name + " " + getOwner()->getInfo().name + " 0";
    } else {
        s =  getInfo().name + " Bank 0";
    }
    return s;
}

void Residence::load (std::string buildstr, Player * ownerload) {
    type = "residence";
    std::string buildingname;
    std::string ownername;
    std::string il;
    int n = 0;
    int len = buildstr.length();
    while ( n < len && (buildstr[n] != ' ')) {
        n+=1;
    }
    buildingname += buildstr.substr(0,n);
    int m = n+1;
    while ( m < len && (buildstr[m] != ' ')) {
        m+=1;
    }
    ownername += buildstr.substr(n+1, m-n);
    int k = m+1;
    while ( k < len) {
        k+=1;
    }
    il += buildstr.substr(m+1, k-m);
    if (il == "-1") {
        isMortgage = true;
    }
    if (ownerload == nullptr) {
        canBuy = true;
    } else {
        this->owner = ownerload;
        ownerload->addProperty(this);
        canBuy = false;
    }
}

void Residence::mortgage() {
    int mortgagemoney = getPurchaseCost()/2;
    getOwner()->setMoney(mortgagemoney);
    isMortgage = true;
}


Gym::Gym(std::string name, int position): Property(name, position, 150) {
    multiples.emplace_back(4);
    multiples.emplace_back(10);
    type = "gym";
}

Gym::~Gym() {}

int Gym::getTuition(Player& p) {
    if (p.isOwnProperty(*this) || (getMortgageStatus() == true))
    return 0;
    int mul = multiples.at(owner->getGymNum()-1);
    int roll1 = rollnum1();
    int roll2 = rollnum2();
    int final = roll1 + roll2;
    int cost = final*mul;
    try {
        p.setMoney(-cost);
        getOwner()->setMoney(cost);
        std::cout << "You have paid tuition: $" << cost << " to Player " << owner->getInfo().name<< std::endl;
    }
    catch (MoneyException &we) {
        std::cerr << "Money is not enough to pay tuition! ";
        we.isForcible=true;
        p.liabilityTo= owner;
        p.isliabilityTo = true;
        throw;
    }
    return cost;
}

std::string Gym::save() {
    std::string s;
    if (getMortgageStatus() == true) {
        s =  getInfo().name + " " + getOwner()->getInfo().name + " -1";
    } else if (isOwned()) {
        s =  getInfo().name + " " + getOwner()->getInfo().name + " 0";
    } else {
        s =  getInfo().name + " Bank 0";
    }
    return s;
}

void Gym::load (std::string buildstr, Player * ownerload) {
    type = "gym";
    std::string buildingname;
    std::string ownername;
    std::string il;
    int n = 0;
    int len = buildstr.length();
    while ( n < len && (buildstr[n] != ' ')) {
        n+=1;
    }
    buildingname += buildstr.substr(0,n);
    int m = n+1;
    while ( m < len && (buildstr[m] != ' ')) {
        m+=1;
    }
    ownername += buildstr.substr(n+1, m-n);
    //std::cout << ownername <<std::endl;
    int k = m+1;
    while ( k < len) {
        k+=1;
    }
    il += buildstr.substr(m+1, k-m);
    if (il == "-1") {
        isMortgage = true;
    }
    if (ownerload == nullptr) {
        canBuy = true;
    } else {
        this->owner = ownerload;
        ownerload->addProperty(this);
        canBuy = false;
    }
} 

void Gym::mortgage() {
    int mortgagemoney = getPurchaseCost()/2;
    getOwner()->setMoney(mortgagemoney);
    isMortgage = true;
}
