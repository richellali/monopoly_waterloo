#ifndef _PLAYER_
#define _PLAYER_
#include <iostream>
#include <map>
#include <string>
#include <memory>
/*
#include "observer.h"
*/
#include "subject.h"
#include "info.h"
#include "item.h"
class Property;
class Building;
class AcademicBuilding;
class Item;
class Player: public Subject{
    Info state;
    int money=1500;
    int DCCups=0;
    bool isInline=false;
    int DCtimes=0;
    std::map<const std::string, Property*> properties;
    std::map<int, std::shared_ptr<Building>>* buildings;
    std::vector<std::shared_ptr<Item>> items;
    public:
    bool canRoll = true;
    bool nextCanRoll = true;
    int rollDouble = 0;
    // ctor dtor
    Player(std::string name, int order, std::map<int, std::shared_ptr<Building>>* bp);
    Player(std::string name, int order, int Timcups, int money, int position,
     bool isInline, int DCtimes, std::map<int, std::shared_ptr<Building>>* bp);

    void addProperties(std::map<const std::string, Property*> properties);
    void addProperty(Property * property);
    void eliminateProperty(Property *property);
    virtual ~Player();
    void sellImprovements(Property & building);
    // accessor mutator
    std::map<int, std::shared_ptr<Building>>* getBuildings();
    int getMoney() noexcept;
    int getDCCups();
    bool hasMonopoly(std::string monopolyBlock);
    void setDCCups(int change);
    void setMoney(int change); // exception: declare bankrupt
        // move the player + -> move forward, - -> move backward
    void move(int position);
    void collectOSAP();
    void setBuildings(std::map<int, std::shared_ptr<Building>>* bp);
    Property & getBuilding(std::string buildingName);
    Info getInfo() const;
    std::map<const std::string, Property*> getProperty();
    void declareBankrupt();
    bool isBankrupted();
    
    int totalWorth();
    void changeAuctionStatus();

    // Tim blocks
    void goTim();
    void leaveLine();
    bool inLine();
    int timesInDC(); // record how many turns the player is in Tim
    void addTimTurn();
    void stayInTim();


    // interaction with building
    void buy(Property* building); // might change to shared ptr later
    void improve(Property & building); // improve a specific building
    bool isOwnProperty(Property & building);
    void mortgage(Property & building);
    void unmortgage(Property & building);
    void mortgageList();
    void unmortgageList();

    // trade
        // other players call this function to trade with the current player
    void tradeTo(int otherMoney);
    void tradeTo(Property & building, Player & other);
        // current player calls this function to trade with other player.
    void trade(Player & other, int myMoney, Property & otherB);
    void trade(Player & other, Property & myB, int otherMoney);
    void trade(Player & other, Property & myB, Property & otherB);

    //void setliabilityTo(Player & other);
    bool isliabilityTo = false;
    void oweBank();
    Player* liabilityTo;
    bool liabilityToBank = false; //True if player owns money to bank 
    
    // return building number the player owns
    int getGymNum();
    int getResidenceNum();

    /*
    void notify();
    void notify(Subject & whoNotified);
    */

   // display assets the player owns
    void displayAsset();
    
    // save and load
    std::string save();

    //items
    void addItem(std::shared_ptr<Item> it);
    void useItem(int index);
    void displayItemList();

};

#endif
