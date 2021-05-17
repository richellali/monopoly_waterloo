#ifndef _REMOTEROLLER_
#define _REMOTEROLLER_
#include "item.h"

class RemoteRoller : public Item {
    public:
    RemoteRoller(std::string name, std::vector<std::shared_ptr<Player>> *players,
    std::map<int, std::shared_ptr<Building>> *buildings);
    void event(Player&) override;
};

class RemoteRollerFactory : public ItemFactory{
    public:
    std::shared_ptr<Item> produceItem(std::string name);
};




#endif
