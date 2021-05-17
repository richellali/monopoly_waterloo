#include "grid.h"
#include "nonproperty.h"
#include "property.h"
#include "subject.h"
#include <fstream>
#include "slc.h"
#include "needleshall.h"

std::shared_ptr<Player> Grid::findPlayer(std::string name){
    for (auto &o : players){
        if (o->getInfo().name == name){
            return o;
        }
    }
    return nullptr;
}


void Grid::displayBoard(){
    std::cout << *textDisplay << std::endl;
}

void Grid::displayAllAssets(){
    for (auto o : players){
        o->displayAsset();
    }
}


std::shared_ptr<Player> Grid::nextTurn(){
    int size = players.size();
    if (size == 1){
        isend = true;
    }
    index++;
    
    if (index == size) index = 0;
    return players.at(index);
}

void Grid::initBuildings(){
    for (int i = 0; i < 40; i++){
       if (i == 0) buildings[i] = std::make_shared<NonProperty>("COLLECT OSAP", i);
       //first init all academic buildings
       else if (i == 1) {
           static const int arr[]= {2,10,30,90,160,250};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("AL", i, 40, "Arts1", 50,v);
       }
       else if (i == 3) {
           static const int arr[]= {4,20,60,180,320,450};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("ML", i, 60, "Arts1", 50, v);
       }
       else if (i == 6) {
           static const int arr[]= {6,30,90,270,400,550};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("ECH", i, 100, "Arts2", 50, v);
       }
       else if (i == 8) {
           static const int arr[]= {6,30,90,270,400,550};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("PAS", i, 100, "Arts2", 50, v);
       }
       else if (i == 9) {
           static const int arr[]= {8,40,100,300,450,600};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("HH", i, 120, "Arts2",50, v);
       }
       else if (i == 11) {
           static const int arr[]= {10, 50, 150, 450, 625, 750};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("RCH", i, 140, "Eng", 100, v);
       }
       else if (i == 13) {
           static const int arr[]= {10, 50, 150, 450, 625, 750};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("DWE", i, 140, "Eng", 100, v);
       }
       else if (i == 14) {
           static const int arr[]= {12, 60, 180, 500, 700, 900};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("CPH", i, 160, "Eng", 100, v);
       }
       else if (i == 16) {
           static const int arr[]= {14, 70, 200, 550, 750, 950};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("LHI", i, 180, "Health", 100, v);
       }
       else if (i == 18) {
           static const int arr[]= {14, 70, 200, 550, 750, 950};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("BMH", i, 180, "Health", 100, v);
       }
       else if (i == 19) {
           static const int arr[]= {16, 80, 220, 600, 800, 1000};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("OPT", i, 200, "Health", 100, v);
       }
       else if (i == 21) {
           static const int arr[]= {18, 90, 250, 700, 875, 1050};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("EV1", i, 220, "ENV", 150, v);
       }
       else if (i == 23) {
           static const int arr[]= {18, 90, 250, 700, 875, 1050};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("EV2", i, 220, "ENV", 150, v);
       }
       else if (i == 24) {
           static const int arr[]= {20, 100, 300, 750, 925, 1100};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("EV3", i, 240, "ENV", 150, v);
       }
       else if (i == 26) {
           static const int arr[]= {22, 110, 330, 800, 975, 1150};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("PHYS", i, 260, "Sci1", 150, v);
       }
       else if (i == 27) {
           static const int arr[]= {22, 110, 330, 800, 975, 1150};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("B1", i, 260, "Sci1", 150, v);
       }
       else if (i == 29) {
           static const int arr[]= {24, 120, 360, 850, 1025, 1200};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("B2", i, 280, "Sci1", 150, v);
       }
       else if (i == 31) {
           static const int arr[]= {26, 130, 390, 900, 1100, 1275};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("EIT", i, 300, "Sci2", 200, v);
       }
       else if (i == 32) {
           static const int arr[]= {26, 130, 390, 900, 1100, 1275};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("ESC", i, 300, "Sci2", 200, v);
       }
       else if (i == 34) {
           static const int arr[]= {28, 150, 450, 1000, 1200, 1400};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("C2", i, 320, "Sci2", 200, v);
       }
       else if (i == 37) {
           static const int arr[]= {35, 175, 500, 1100, 1300, 1500};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("MC", i, 350, "Math", 200, v);
       }
       else if (i == 39) {
           static const int arr[]= {50, 200, 600, 1400, 1700, 2000};
           auto v = std::make_shared<std::vector<int>>(arr,arr+sizeof(arr)/sizeof(arr[0]));
           buildings[i] = std::make_shared<AcademicBuilding>("DC", i, 400, "Math", 200, v);
       }
       
       //then init all Non-properties
       else if (i == 2 || i == 17 || i == 33) buildings[i] = std::make_shared<SLC>("SLC", i);
       else if (i == 4) buildings[i] = std::make_shared<NonProperty>("TUITION", i);
       else if (i == 7 || i == 22 || i == 36) buildings[i] = std::make_shared<NeedlesHall>("NEEDLES HALL", i, &players, &buildings);
       else if (i == 10) buildings[i] = std::make_shared<NonProperty>("DC Tims Line", i);
       else if (i == 20) buildings[i] = std::make_shared<NonProperty>("GOOSE NESTING", i);
       else if (i == 30) buildings[i] = std::make_shared<NonProperty>("GO TO TIMS", i);
       else if (i == 38) buildings[i] = std::make_shared<NonProperty>("COOP FEE", i);

       //init all residences and gyms
       else if (i == 5) buildings[i] = std::make_shared<Residence>("MKV", i);
       else if (i == 15) buildings[i] = std::make_shared<Residence>("UWP", i);
       else if (i == 25) buildings[i] = std::make_shared<Residence>("V1", i);
       else if (i == 35) buildings[i] = std::make_shared<Residence>("REV", i);
       else if (i == 12) buildings[i] = std::make_shared<Gym>("PAC", i);
       else if (i == 28) buildings[i] = std::make_shared<Gym>("CIF", i);
       
    }
}

void Grid::addPlayer(std::string s,int order){
    players.emplace_back(std::make_shared<Player>(s,order,&buildings));
}

std::vector<std::shared_ptr<Player>> Grid::currentPlayers(){
    return players;
}

void Grid::initBoard(){
    std::vector<std::string> p;
    for (auto o : players){
        p.emplace_back(o->getInfo().name);
    }
    textDisplay = std::make_shared<Board>(p, &buildings);
    for (auto &o : players){
        o->attach(textDisplay);
    }
    for (auto &o : players){
        o->notifyObservers();
    }
}

std::map<int, std::shared_ptr<Building>>* Grid::getBuildings(){
    return &buildings;
}

void Grid::notify(Subject& whoNotified){
    if (whoNotified.getInfo().isBankrupt){
        index --;
        auctionPeriod(whoNotified);
        for (auto i = players.begin(); i != players.end(); i++){
            if ((*i)->getInfo().name == whoNotified.getInfo().name){
                players.erase(i);
                return;
            }
        }
    } else if (whoNotified.getInfo().needAuction) {
        auctionNeeded(whoNotified);
        Player &p = dynamic_cast<Player &> (whoNotified);
        p.changeAuctionStatus();
    }
}

void Grid::auctionPeriod(Subject& whoBankrupt){
    if (whoBankrupt.getInfo().liabilityToBank != true) {
        return;
    }
    std::cout << "---------------------Auction begin!!!---------------------" << std::endl;
    auto currentPlayers = players;
    currentPlayers.erase(currentPlayers.begin()+whoBankrupt.getInfo().order); // currentPlayers is the vector of players without the bankrupted one
    auto properties = players.at(whoBankrupt.getInfo().order)->getProperty(); //get the properties of that player
    for (auto &p : properties){         //auction on each of his properties
        auto activePlayers = currentPlayers;    //every player should attend all the auctions
        std::cout << p.first << ": " << std::endl;
        int auctionIndex = 0;
        int currentPrice = 0;
        //int size = activePlayers.size();

        p.second->setMortgageStatus(false);
        while (activePlayers.size() != 1){      //if the size of activePlayer is 1, then the only player is the winner
            while (true){
                if (auctionIndex == activePlayers.size()){      //if the player is the last player, then switch to the first player
                            auctionIndex = 0;
                        }
                std::string readin;
                std::cout << "Hey Player " << activePlayers.at(auctionIndex)->getInfo().name << ", are you willing to purchase this for a price more than " << currentPrice << "?" << std::endl;
                std::cout << "Answer q to quit the auction or a price larger than " << currentPrice << " to continue the auction. " << std::endl;
                std::cin >> readin;
                if (readin == "q"){
                    activePlayers.erase(activePlayers.begin() + auctionIndex);  //if the player quit, then the index and currentPrice does not change
                    //std::cout << activePlayers.size() <<std::endl;
                    break;
                }   else {
                    std::istringstream iss{readin};                 
                    int readPrice = 0;
                    if (iss >> readPrice && readPrice > currentPrice){      // if the player gives a higher price, then give the turn to next player and change the price
                        currentPrice = readPrice;
                        auctionIndex++;
                        if (auctionIndex == activePlayers.size()){      //if the player is the last player, then switch to the first player
                            auctionIndex = 0;
                        }
                        break;
                    }
                    std::cout << "invalid input, please try again!" << std::endl;   //else, the input is invalid
                }
            }
        }
        //set the price and let the player buy the property
        p.second->setPurchaseCost(currentPrice); 
        p.second->changeOwner(nullptr);   
        activePlayers.front()->buy(p.second);
        activePlayers.front()->setMoney(-p.second->getPurchaseCost());
        std::cout << "Congratulations to Player " << activePlayers.front()->getInfo().name << "! " << p.second->getInfo().name << " is yours!" << std::endl;
        std::cout << std::endl << std::endl;

    }
    std::cout << "----------------------Auction ended!!!----------------------" << std::endl;
}

void Grid::auctionNeeded(Subject& p){ 

    std::cout << "---------------------Auction begin!!!---------------------" << std::endl;
    auto currentPlayers = players;
    currentPlayers.erase(currentPlayers.begin()+p.getInfo().order); // currentPlayers is the vector of players without the bankrupted one
    auto property = buildings[p.getInfo().position]; //get the property for auction

    auto activePlayers = currentPlayers;    //every player should attend all the auctions
    std::cout << property->getInfo().name << ": " << std::endl;
    int auctionIndex = 0;
    int currentPrice = 0;
    while (activePlayers.size() != 1){      //if the size of activePlayer is 1, then the only player is the winner
        while (true){
            if (auctionIndex == activePlayers.size()){      //if the player is the last player, then switch to the first player
                auctionIndex = 0;
            }
            std::string readin;
            std::cout << "Hey Player " << activePlayers.at(auctionIndex)->getInfo().name << ", are you willing to purchase this for a price more than " << currentPrice << "?" << std::endl;
            std::cout << "Answer q to quit the auction or a price larger than " << currentPrice << " to continue the auction. " << std::endl;
            std::cin >> readin;
            if (readin == "q"){
                activePlayers.erase(activePlayers.begin() + auctionIndex);  //if the player quit, then the index and currentPrice does not change
                break;
            }   else {
                std::istringstream iss{readin};                 
                int readPrice = 0;
                if (iss >> readPrice && readPrice > currentPrice){      // if the player gives a higher price, then give the turn to next player and change the price
                    currentPrice = readPrice;
                    auctionIndex++;
                    if (auctionIndex == activePlayers.size()){      //if the player is the last player, then switch to the first player
                        auctionIndex = 0;
                    }
                    break;
                }
                std::cout << "invalid input, please try again!" << std::endl;   //else, the input is invalid
            }
        }
    }
        //set the price and let the player buy the property
        Property &pro = dynamic_cast<Property &> (*property);
        pro.setPurchaseCost(currentPrice); 
        pro.changeOwner(nullptr);   
        activePlayers.front()->buy(&pro);
        activePlayers.front()->setMoney(-pro.getPurchaseCost());
        std::cout << "Congratulations to Player " << activePlayers.front()->getInfo().name << "! " << pro.getInfo().name << " is yours!" << std::endl;
        std::cout << std::endl << std::endl;

    
    std::cout << "----------------------Auction ended!!!----------------------" << std::endl;    
}

void Grid::save(std::string filename){
    std::ofstream of{filename};
    of << index-1 << std::endl;
    of << players.size() << std::endl;
    int i = 1;
    for (auto &o : players){
        //std::cerr << "i am saveing palyers" << std::endl;
        of << "Player" << i << " " << o->save() << std::endl; 
        i++;
    }
    for (int p = 0; p < 28; p++){
        std::string savestr = buildings[propertyindex[p]]->save();
        if (!savestr.empty()){
            //std::cerr << "i am saveing buildings" << std::endl;
            of << buildings[propertyindex[p]]->save() << std::endl;
        }
    }
    std::cout << "All information successfully saved in \"" << filename << "\"." << std::endl;
}

void Grid::load(std::ifstream &is){
    std::string readin;
    int pindex = 0;
    int bindex = 0;
    is >> index;
    //std::cerr << "i am reading the index" << std::endl;
    //std::getline(is, readin);
    while(std::getline(is, readin)){
        std::string firstStr;
        std::istringstream iss{readin};
        iss >> firstStr;
        if (firstStr.length() == 7 &&firstStr.at(0) == 'P'){
            //std::cerr << "i am reading Players" << std::endl;
            int TimsCups;
            int money;
            int pos;
            int canRoll;
            int boolnum = 0;
            int DCtimes = 0;
            
            iss >> firstStr >>TimsCups >> money >> pos >> canRoll >> boolnum >> DCtimes;
            players.emplace_back(std::make_shared<Player>(firstStr, pindex, TimsCups, money, pos, boolnum, DCtimes, &buildings));
            players[pindex]->canRoll = canRoll;
            pindex++;
        }   else {
            if (firstStr.length() > 1){
                std::string secondStr;              //playername
                iss >> secondStr;
                //std::cerr << "i am reading properties" << std::endl;
                auto pptr = &(*findPlayer(secondStr));
                buildings[propertyindex[bindex]]->load(readin, pptr);
                bindex++;
            }
        }
    }
    std::cout << "All information successfully loaded." << std::endl;
}








