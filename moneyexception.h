#ifndef __MONEYEXCEPTION__
#define __MONEYEXCEPTION__
#include "waterpolyexception.h"
class MoneyException: public WaterpolyException{
    int change;
    
    public:
    bool isForcible=false;
    MoneyException(std::string name, int change);
    int getChange();
};

#endif
