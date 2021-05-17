#ifndef __NONPROPERTY__
#define __NONPROPERTY__
#include "buildings.h"
#include "player.h"
#include "roll.h"
#include "moneyexception.h"
#include <string>
class Player;
class NonProperty: public Building {
    //void dcRow();
    void dcPay50(Player& p);
    void dcUseCup(Player& p);
    void dcthreefail(Player& p);
    void dctimsline(Player& p);
    public:
    NonProperty(std::string name, int position);
    virtual ~NonProperty();
    void event(Player &p) override;
    void load (std::string buildstr, Player * owner) override;
    std::string save() override;
};


#endif
