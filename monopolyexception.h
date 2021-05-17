#ifndef __MONOPOLYEXCEPTION__
#define __MONOPOLYEXCEPTION__
#include "waterpolyexception.h"
class MonopolyException: public WaterpolyException{
    public:
    MonopolyException(std::string name);
};
#endif
