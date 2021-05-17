#ifndef __NEEDLESHALL__
#define __NEEDLESHALL__
#include "nonproperty.h"
#include <memory>
#include "missile.h"
#include "remoteRoller.h"
#include "mine.h"
class StrategyND;

class NeedlesHall: public NonProperty {
    std::unique_ptr<StrategyND> strategy;
    MissileFactory mf;
    RemoteRollerFactory rf;
    MineFactory mif;
    void shoppingPeriod(Player &p);
    public:
    NeedlesHall(std::string, int,std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings);
    virtual void event(Player & p);
};

class StrategyND {
    public:
    virtual void dosth(Player & Player)=0;
};

class L200: public StrategyND {
    public:
    virtual void dosth(Player & player);
};

class L100: public StrategyND {
    public:
    virtual void dosth(Player & player);
};

class L50: public StrategyND {
    public:
    virtual void dosth(Player & player);
};

class W25: public StrategyND {
    public:
    virtual void dosth(Player & player);
};

class W50: public StrategyND {
    public:
    virtual void dosth(Player & player);
};

class W100: public StrategyND {
    public:
    virtual void dosth(Player & player);
};

class W200: public StrategyND {
    public:
    virtual void dosth(Player & player);
};
#endif
