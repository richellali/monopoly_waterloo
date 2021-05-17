#ifndef __PROPERTY__
#define __PROPERTY__
#include "buildings.h"
#include "player.h"
#include "moneyexception.h"
#include "waterpolyexception.h"
#include "roll.h"
#include <string>
#include <vector>
class Player;
class Property: public Building {
    protected:
    int price;
    std::string type;
    bool isMortgage = false;
    bool canBuy = true;
    Player * owner;
    int tradeprice = 0;
    
    public:
    Property(std::string name,int position,int price);
    Property(std::string name,int position,int price,
        Player * owner);
    virtual ~Property();
    int getPurchaseCost();
    bool getMortgageStatus();
    Player * getOwner();
    void changeOwner(Player *  p); // change or add the owner of the building, also change the status of canBuy
    bool isOwned(); // check does the building has an owner
    void event(Player &p) override;
    void unmortgage();
    void setPurchaseCost(int n);
    std::string getType();
    void setToOriginal();
    void setMortgageStatus(bool b);

    //virtual std::string save();
    //virtual void load (std::string buildstr,std::shared_ptr<Player> owner);
    virtual void mortgage() = 0;
    virtual int getTuition(Player& p) = 0;
};

class AcademicBuilding: public Property {
    std::string monopoly;
    int improveCost;
    int improvedLevel;
    std::shared_ptr<std::vector<int>> tuition; 
    public:
    AcademicBuilding(std::string name, int position, int price, std::string monopolyBlock,
            int improveCost, std::shared_ptr<std::vector<int>> tuition);
    virtual ~AcademicBuilding();
    virtual int getTuition(Player& p) override;
    void improve();
    int getimproveValue();
    int getImprovedLevel();
    std::string getMonopoly();
    std::string save() override;
    void load (std::string buildstr, Player * owner) override;
    void mortgage() override;
    void sellImprovement();
    void sellAllImprovement();
    void getAsset();
    void destroyImprovements();

};

class Residence: public Property {
    std::vector<int> tuitionlist; //4 differnt kinds of price
    public:
    Residence(std::string name, int position);
    virtual ~Residence();
    virtual int getTuition(Player& p) override;
    std::string save() override;
    void load (std::string buildstr, Player * owner) override;
    void mortgage() override;
};

class Gym: public Property {
    
    std::vector<int> multiples; // two kinds of multiples
    public: 
    Gym(std::string name, int position);
    virtual ~Gym();
    virtual int getTuition(Player& p) override;
    std::string save() override;
    void load (std::string buildstr, Player * owner) override;
    void mortgage() override;
};

#endif

