#ifndef __SLC__
#define __SLC__
#include "nonproperty.h"
#include <memory>

class StrategySLC;

class SLC: public NonProperty {
    
    std::unique_ptr<StrategySLC> strategy;
    public:
    SLC(std::string, int);
    //SLC(int position, std::string name="SLC");
    virtual void event(Player & p);
};

class StrategySLC {
    //Info buildingInfo;
    public:
    //StrategySLC(Info);
    virtual void dosth(Player & p)=0;
    //Info getInfo();

};

class Back3: public StrategySLC {
    public:
    //Back3(Info);
    virtual void dosth(Player & p);
};

class Back2: public StrategySLC {
    public:

    virtual void dosth(Player & p);
};

class Back1: public StrategySLC {
    public:
    virtual void dosth(Player & p);
};

class Forward1: public StrategySLC {
    public:
    virtual void dosth(Player & p);
};

class Forward2: public StrategySLC {
    public:
    virtual void dosth(Player & p);
};

class Forward3: public StrategySLC {
    public:
    virtual void dosth(Player & p);
};

class GoDC: public StrategySLC {
    public:
    virtual void dosth(Player & p);
};

class OSAP: public StrategySLC {
    public:
    virtual void dosth(Player & p);
};

#endif
