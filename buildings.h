#ifndef _BUILDING_
#define _BUILDING_
#include <string>
#include "subject.h"
#include "info.h"

class Player;
class Building: public Subject{
    Info state;
    public:
    Building(std::string name, int position);
    ~Building();
    bool hasMine = false;
    Info getInfo() const;
    virtual void event(Player & player) = 0;
    virtual void load (std::string buildstr, Player * owner) = 0;
    virtual std::string save() = 0;
};

#endif

